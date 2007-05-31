//
//
// $Id: SkewTtrace.h,v 1.12 2005/06/12 02:12:13 martinc Exp $
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

// Trace.h: interface for the Trace class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRACE_H__E16D3E00_DD2F_11D2_B034_00C04FA30B92__INCLUDED_)
#define AFX_TRACE_H__E16D3E00_DD2F_11D2_B034_00C04FA30B92__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SkewTdefs.h"
#include "SkewTRect.h"
#include "SkewTAdapter.h"

#include <vector>
using namespace std;

namespace skewt {
	/**	
	* SkewTtrace manages a collection of data points, and plots them on a SkewTRect.  It
	* also has members for plotting individual points.
	*/
	class SkewTtrace : public SkewTRect  
	{
	public:
		/**
		* The type of symbol to be plotted.
		* @todo This is not recognized in some of the adapters.
		*/  
		enum TraceSymbol {TraceDot, TraceTriangle, TraceCross};
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
		* @param pres Vector of pressure values.
		* @param t Vector of temperatures, either dry or dewpoint.
		* @param color Color code for trace.
		* @param symbol Symbol type.
		*/
		SkewTtrace(SkewTAdapter& adapter,
			double xmin, double xmax, double ymin, double ymax, 
			double tmin, double tmax, double pmin, double pmax,
			double tSlope,
			vector<double> pres, vector<double> t,
			unsigned int color, TraceSymbol symbol);
		virtual ~SkewTtrace();
		/**
		* Draw a complete trace.
		* @param tdry Set this true, to draw temperature, false to draw dewpoint
		*/
		void draw(bool tdry);
		/** 
		* Draw a single tdry point
		* @param pres Pressure
		* @param tdry Temperature.
		*/
		void drawTdry(double pres, double tdry);
		/** 
		* Draw a single dewpoint point
		* @param pres Pressure
		* @param dp Dewpoint temperature.
		*/
		void drawDp(double pres, double dp);

	protected:
		vector<double> m_pres; ///< Vector of pressures.
		vector<double> m_t;    ///< Vector of temperatures.
		unsigned int m_color;  ///< Color code.
		TraceSymbol m_symbol;  ///< Symbol type.
	};
}
#endif // !defined(AFX_TRACE_H__E16D3E00_DD2F_11D2_B034_00C04FA30B92__INCLUDED_)
