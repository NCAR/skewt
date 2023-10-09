/************************************************************************\
	Copyright 2008 University Corporation for Atmospheric Research.
	All rights reserved.
	Use of this code is subject to UCAR's standard Terms of Use,
	which can be found at http://www.ucar.edu/legal/terms_of_use.shtml .
	By using this source code, you agree to abide by those Terms of Use.
\*************************************************************************/

// SkewTRect.h: interface for the SkewTRect class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKEWTRECT_H__5813CCBF_D1A4_11D2_B5B6_ED3B095D6882__INCLUDED_)
#define AFX_SKEWTRECT_H__5813CCBF_D1A4_11D2_B5B6_ED3B095D6882__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SkewTdefs.h"
#include "SkewTAdapter.h"
#include "PresRect.h"

#include <cmath>
#include <string>

namespace skewt {

	class outcode;
	/**
	* SkewTRect implements a Rect, with pressure as the vertical axis, and skewed temperature
	* as the horizontal axis. It is the main building block of the thermodynamic section of a
	* SkewT plot.
	*
	* The slope and span of the temperature scale, and the span of the pressure range, 
	* have a large impact the appearance of the thermodynamic region of the plot. For instance,
	* to produce a plot that is similar to the USAF DOD-WPC 9-16-1 standard skew-t chart,
	* the following values can be used:
	* <ul>
	* <li> tmin: -33.3 deg C
	* <li> tmax:  50.0 deg C
	* <li> pmin:  100 mb
	* <li> pmax: 1050 mb
	* <li> tSlope: 1.125
	* </ul>
	*/
	class SkewTRect: public PresRect  
	{
	public:
		void addDp(double x, double y);
		void addTdry(double x, double y);
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
		SkewTRect(SkewTAdapter& adapter,
			double xmin, double xmax, double ymin, double ymax, 
			double tmin, double tmax,
			double pmin, double pmax, 
			double tSlope);
		virtual ~SkewTRect(); ///< Destructor
		/**
		* Calculate the x coordinate, as a function of temperature and the y coordinate.
		* @param t Temperature
		* @param y Y value
		* @returns X value
		*/
		double x(double t, double y);
		/**
		* Calculate temperature, from the x and y coordinate.
		* @param x X coordinate
		* @param y Y coordinate
		* @returns The temperature.
		*/
		double t(double x, double y);

	private:

		double m_tSpan; ///< SkewTRect::m_tmax - SkewTRect::m_tmin

		double m_slope; ///< The slope of the isotherms (set to 1.0);

	protected:
		/**
		* Draw text at the specified temperature and pressure coordinates.
		* @param s Text string.
		* @param t Temperature coordinate.
		* @param p Pressure coordinate.
		* @param xoffset Offset the symbol by this amount in x. The units of x are a fraction of 1.0; i.e. a fraction of the Rect.
		* @param yoffset Offset the symbol by this amount in y. The units of y are a fraction of 1.0; i.e. a fraction of the Rect.
		* @param color Color code.
		*/
		void Text(const std::string& s, const double t, const double p, const double xoffset, const double yoffset, unsigned int color);
		/**
		* Draw text at the specified x and pressure coordinates.
		* @param s Text string.
		* @param x X coordinate.
		* @param p Pressure coordinate.
		* @param yoffset Offset the symbol by this amount in y. The units of y are a fraction of 1.0; i.e. a fraction of the Rect.
		* @param color Color code.
		*/
		void Text(const std::string& s, const double x, const double p, const double yoffset, unsigned int color);
		/**
		* Draw a line between two points, specified in temperature and pressure coordinates.
		* @param t1 Temperature of the first point.
		* @param p1 Pressure of the first point.
		* @param t2 Temperature of the second point.
		* @param p2 Pressure of the second point.
		* @param color Color code.
		*/
		void drawLine(double t1, double p1, double t2, double p2, unsigned int color = SKEWT_BLACK);
		void symbol(double t, double pres, unsigned int color);


		double m_tmin; ///< Minimum temperature.
		double m_tmax; ///< Maximum temperature.

	};
}
#endif // !defined(AFX_SKEWTRECT_H__5813CCBF_D1A4_11D2_B5B6_ED3B095D6882__INCLUDED_)
