//
//
// $Id: Adiabats.h,v 1.11 2005/06/12 02:12:12 martinc Exp $
//
//////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2003
// University Corporation for Atmospheric Research, UCAR
//
// Permission to use, copy, modify, distribute and sell this software and
// its documentation for any purpose is hereby granted without fee,
// provided that the above copyright notice appear in all copies and that
// both that copyright notice and this permission notice appear in
// supporting documentation.  UCAR makes no representations about the
// suitability of this software for any purpose.  It is provided "as is"
// without express or implied warranty.
// 
// Note from the author:
//
// Where possible, you are encouraged to follow the GNU General Public
// License, or at least the spirit of the license, for the distribution and
// licensing of this software and any derived works.  See
// http://www.gnu.org/copyleft/gpl.html.
//

// Adiabats.h: interface for the Adiabats class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ADIABATS_H__01F03960_DAFC_11D2_B034_00C04FA30B92__INCLUDED_)
#define AFX_ADIABATS_H__01F03960_DAFC_11D2_B034_00C04FA30B92__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SkewTdefs.h"
#include "IsoPleth.h"

/**
* Creates isopleths of potential temperature.
*/

namespace skewt {
	class Adiabats : public IsoPleth  
	{
	public:
		/**
		* xmin, xmax, ymin and ymax will run between 0 and 1 in the 
		* available graphing area.
		* @param adapter The adapter that renders this Rect on the graphics component.
		* @param xmin Left extent of the Rect on the graphics page.
		* @param xmax Right extent of the Rect on the graphics page.
		* @param ymin Bottom extent of the Rect on the graphics page.
		* @param ymax Top extent of the Rect on the graphics page.
		* @param tmin Minimum value of temperature.
		* @param tmax Maximum value of temperature.
		* @param pmin Minimum value of pressure.
		* @param pmax Maximum value of pressure.
		* @param tSlope Slope of the pressure isopleths, deltaY/deltaX (These are in sceen units).
		*/
		Adiabats(SkewTAdapter& adapter,
			double xmin, double xmax, double ymin, double ymax, 
			double tmin, double tmax, double pmin, double pmax,
			double tSlope);
		virtual ~Adiabats();
		/**
		* Draw the lines.
		*/
		void draw();

	protected:
		/*
		* Compute temperature from pressure and potential temperature.
		* @param pres Pressure (mb).
		* @param theta Potential temperature (deg K).
		* @return Temperature (deg. C).
		*/
		double tFromTheta(double pres, double theta);
	};
}

#endif // !defined(AFX_ADIABATS_H__01F03960_DAFC_11D2_B034_00C04FA30B92__INCLUDED_)
