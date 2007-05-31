//
//
// $Id: PresRect.h,v 1.10 2005/06/12 02:12:13 martinc Exp $
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

// PresRect.h: interface for the PresRect class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRESRECT_H__61B3B282_E5DF_11D2_B034_00C04FA30B92__INCLUDED_)
#define AFX_PRESRECT_H__61B3B282_E5DF_11D2_B034_00C04FA30B92__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SkewTdefs.h"
#include "Rect.h"

namespace skewt {
	/**
	* PresRect implements a Rect, with pressure as the veritcal axis.
	*
	*/
	class PresRect : public Rect  
	{
	public:
		/**
		* @param adapter The adapter that renders this Rect on the graphics component.
		* @param xmin Left extent of the Rect on the graphics page.
		* @param xmax Right extent of the Rect on the graphics page.
		* @param ymin Bottom extent of the Rect on the graphics page.
		* @param ymax Top extent of the Rect on the graphics page.
		* @param pmin Minimum value of pressure.
		* @param pmax Maximum value of pressure.
		*/
		PresRect(SkewTAdapter& adapter,
			double xmin, double xmax, double ymin, double ymax, 
			double pmin, double pmax);

		virtual ~PresRect(); ///< Destructor

		/**
		* Given y, calculate pressure.
		* @param y Y value
		* @returns Pressure
		*/
		double p(double y);
		/**
		* Calculate the y value from the pressure.
		* @param pres Pressure
		* @returns Y value
		*/
		double y(double pres);

		double m_pmin; ///< Minimum pressure
		double m_pmax; ///< Maximum pressure

	protected:
		double m_pRatio; ///< log10(PresRect::m_pmin/PresRect::m_pmax)

	};
}
#endif // !defined(AFX_PRESRECT_H__61B3B282_E5DF_11D2_B034_00C04FA30B92__INCLUDED_)
