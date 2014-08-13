/********************************************************************
Vireio Perception: Open-Source Stereoscopic 3D Driver
Copyright (C) 2012 Andres Hernandez

File <HMDisplayInfo.h> and
Structure <HMDisplayInfo> :
Copyright (C) 2013 Chris Drain

Vireio Perception Version History:
v1.0.0 2012 by Andres Hernandez
v1.0.X 2013 by John Hicks, Neil Schneider
v1.1.x 2013 by Primary Coding Author: Chris Drain
Team Support: John Hicks, Phil Larkson, Neil Schneider
v2.0.x 2013 by Denis Reischl, Neil Schneider, Joshua Brown

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
********************************************************************/

#ifndef HMDISPLAYINFO_RIFTUP_H_INCLUDED
#define HMDISPLAYINFO_RIFTUP_H_INCLUDED

#include "d3d9.h"
#include "d3dx9.h"
#include <utility>
#include <sstream>

#include "HMDisplayInfo.h"

/**
* Predefined head mounted display info.
* Default constructing with Rift DK1 values.
***/
struct HMDisplayInfo_RiftUp :
	public HMDisplayInfo
{
public:

#pragma warning( push )
#pragma warning( disable : 4351 ) //disable "new behaviour warning for default initialised array" for this constructor
	/**
	* All rift values from OVR_Win32_HMDDevice.cpp in LibOVR
	* Default constructing with Rift DK1 values.
	***/

	HMDisplayInfo_RiftUp() :
		HMDisplayInfo()
	{
		ovr_Initialize();
		distortionCoefficients[0] = 1.0f;
		distortionCoefficients[1] = 0.15f;
		distortionCoefficients[2] = 0.09f;
		distortionCoefficients[3] = 0.0f;
		
		ovrHmd hmd=ovrHmd_Create(0);
		IPD=ovrHmd_GetFloat(hmd,OVR_KEY_IPD,0);
		resx=hmd->Resolution.w;
		resy=hmd->Resolution.h;
		ovrHmd_Destroy(hmd);

		std::stringstream sstm;
		sstm << "scaleToFillHorizontal: " << GetScaleToFillHorizontal() << std::endl;
		OutputDebugString(sstm.str().c_str());
	}

	virtual std::string GetHMDName() {return "RiftUp!";}

	/**
	* Screen resolution, in pixels.
	* <horizontal, vertical>
	***/
	virtual std::pair<UINT, UINT>  GetResolution()
	{
		return std::make_pair(resx,resy);
		//return std::make_pair<UINT, UINT>(resx, resy);
	}

	/**
	* Physical characteristics are in meters.
	* <horizontal, vertical> 
	***/
	virtual std::pair<float, float> GetPhysicalScreenSize()
	{
		return std::make_pair<float, float>(0.1296f, 0.0729f);
	}

	/**
	* Currently constant eye to screen distance (according to rift dev kit 1)
	***/
	virtual float GetEyeToScreenDistance()
	{
		return 0.041f;
	}

	/**
	* Physical lens seperation (currently constant rift dev kit 1 value=default ipd 0.064f).
	***/
	virtual float GetPhysicalLensSeparation()
	{
		return IPD;
		return 0.064f;
	}


	/**
	* The distance in a 0 to 1 range that the center of each lens is from the center of each half of
	* the screen on Y axis
	***/
	virtual float GetLensYCenterOffset()
	{
		return 0.5f;
	}

	/**
	* The distance in a -1 to 1 range that offsets the center of each lens is from the center of each half of
	* the screen on X axis
	***/
	virtual float GetLensIPDCenterOffset()
	{
		return 0.0f;
	}

	/**
	* The minimum distortion scale allowed, varies between headsets (-1.0 is fine for DK1, whereas -0.5 is better for RiftUp)
	***/
	virtual float GetMinDistortionScale()
	{
		return -0.5;
	}

	/**
	* From Rift docs on distortion : uvResult = uvInput * (K0 + K1 * uvLength^2 + K2 * uvLength^4).
	***/
	virtual float* GetDistortionCoefficients()
	{
		return distortionCoefficients;
	}
};
#endif