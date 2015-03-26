/************************************************************************\
	Copyright 2008 University Corporation for Atmospheric Research.
	All rights reserved.
	Use of this code is subject to UCAR's standard Terms of Use,
	which can be found at http://www.ucar.edu/legal/terms_of_use.shtml .
	By using this source code, you agree to abide by those Terms of Use.
\*************************************************************************/

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
		double m_pRatio; ///< log10(m_pmin/m_pmax)

	};
}
#endif // !defined(AFX_PRESRECT_H__61B3B282_E5DF_11D2_B034_00C04FA30B92__INCLUDED_)
