/************************************************************************\
	Copyright 2008 University Corporation for Atmospheric Research.
	All rights reserved.
	Use of this code is subject to UCAR's standard Terms of Use,
	which can be found at http://www.ucar.edu/legal/terms_of_use.shtml .
	By using this source code, you agree to abide by those Terms of Use.
\*************************************************************************/

// PAdiabats.h: interface for the PAdiabats class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PADIABATS_H__60EC9C21_DBD2_11D2_B5B6_DAEF9F2EFBE6__INCLUDED_)
#define AFX_PADIABATS_H__60EC9C21_DBD2_11D2_B5B6_DAEF9F2EFBE6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SkewTdefs.h"
#include "IsoPleth.h"
#include "SkewTMetFormulas.h"

namespace skewt {
	/**
	* Creates isopleths of equivalent potential temperature.
	*/
	class PAdiabats : public IsoPleth
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
		PAdiabats(SkewTAdapter& adapter,
			double xmin, double xmax, double ymin, double ymax, 
			double tmin, double tmax, double pmin, double pmax,
			double tSlope);
		virtual ~PAdiabats();
		/**
		* Draw the lines.
		*/
		void draw();

	protected:
		SkewTMetFormulas m_mf;
	};
}
#endif // !defined(AFX_PADIABATS_H__60EC9C21_DBD2_11D2_B5B6_DAEF9F2EFBE6__INCLUDED_)
