/************************************************************************\
	Copyright 2008 University Corporation for Atmospheric Research.
	All rights reserved.
	Use of this code is subject to UCAR's standard Terms of Use,
	which can be found at http://www.ucar.edu/legal/terms_of_use.shtml .
	By using this source code, you agree to abide by those Terms of Use.
\*************************************************************************/

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
