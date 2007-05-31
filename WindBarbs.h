//
//
// $Id: WindBarbs.h,v 1.14 2005/06/12 02:12:13 martinc Exp $
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

// WindBarbs.h: interface for the WindBarbs class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINDBARBS_H__61B3B280_E5DF_11D2_B034_00C04FA30B92__INCLUDED_)
#define AFX_WINDBARBS_H__61B3B280_E5DF_11D2_B034_00C04FA30B92__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SkewTdefs.h"
#include "PresRect.h"
#include "WindBarb.h"
#include <algorithm>
#include <set>
using namespace std;

namespace skewt {

	/**
	* WindBarbs draws a collection of WindBarb into a PresRect. The total number of barbs to be drawn, over the pressure
	* range, is specified. 
	* 
	* In order to handle real-time updates of the wind barbs, the pressure range is subdivided into logrithmic segments, and only one
	* wind per segment is allowed to be plotted. The log(pressure) segments are assigned indices, starting at zero. A std::set
	* contains the collection of indices that have already been plotted. When a candidate wind is requested to
	* drawn, its index is calculated and the set is checked to make sure that it has not already been drawn. when a barb is drawn
	* for a particular segment, its index is entered into the set.
	*
	*/
	class WindBarbs : public PresRect  
	{
	public:
		/**
		* render the wind barbs
		*/
		void draw();
		/**
		* @param adapter The adapter that renders this Rect on the graphics component.
		* @param xmin Left extent of the Rect on the graphics page.
		* @param xmax Right extent of the Rect on the graphics page.
		* @param ymin Bottom extent of the Rect on the graphics page.
		* @param ymax Top extent of the Rect on the graphics page.
		* @param pmin Minimum value of pressure.
		* @param pmax Maximum value of pressure.
		* @param pres The pressure values.
		* @param wspd The wind speed values.
		* @param wdir The wind direction values (in meteorlogical coordinates).
		* @param nBarbs The number of barbs to draw on the graph.
		*/
		WindBarbs(SkewTAdapter& adapter,
			double xmin, 
			double xmax, 
			double ymin, 
			double ymax, 
			double pmin, 
			double pmax, 
			vector<double>& pres, 
			vector<double>& wspd, 
			vector<double>& wdir,
			int nBarbs);

		virtual ~WindBarbs();

		/**
		* Draw a single barb, but only if there hasn't been a barb already drawn for the
		* corresponding pressure segment.
		* @param wspd  Wind speed
		* @param wdir  Wind direction
		* @param pres  Pressure (mb)
		*/
		void drawBarb(double wspd, double wdir, double pres);
	protected:

		/**
		* return the index of the pressure segment in which this pressure falls.
		* This is used to restrict the drawing of a single barb in one level.
		* The number of levels is specified in the constructor.
		* @param pres Pressure in mb.
		* @returns The index of the level.
		*/
		int presSegmentIndex(double pres);

		/**
		* A collection class for wind data. It also provides a comparrison operator (<), which
		* allows the wind to be sorted by pressure height.
		*/
		class windData {
		public:
			/**
			@param pres Pressure level for the wind.
			@param spd Wind speed.
			@param dir Wind direction (in meteorlogical coordinates).
			*/
			windData(double pres, double spd, double dir);
			virtual ~windData();

			double m_pres; ///< Pressure level for the wind.
			double m_wspd; ///< Wind speed.
			double m_wdir; ///< Wind direction (in meteorlogical coordinates).

			/**
			* Compare the pressure level of two winds.
			* @returns True if LHS pressure is less than RHS pressure.
			*/
			bool operator<(const windData& RHS) const;
		};

		int m_nBarbs;                   ///< The number of barbs to draw on the plot
		std::vector<windData> m_data;   ///< The wind data.
		std::set<int> m_plottedBarbIndices; ///< When a wind barb has been plotted, its index is added to this set.
		double _logPmin;                ///< Log of the minimum pressure
		double _logPmax;                ///< Log of the maximum pressure
		double _logInc;                 ///< The increment of the log pressure, for pressure segments.

	};
}
#endif // !defined(AFX_WINDBARBS_H__61B3B280_E5DF_11D2_B034_00C04FA30B92__INCLUDED_)
