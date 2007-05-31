//
//
// $Id: WindBarb.h,v 1.10 2005/06/12 02:12:13 martinc Exp $
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

// WindBarb.h: interface for the WindBarb class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINDBARB_H__61B3B281_E5DF_11D2_B034_00C04FA30B92__INCLUDED_)
#define AFX_WINDBARB_H__61B3B281_E5DF_11D2_B034_00C04FA30B92__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SkewTdefs.h"
#include "Rect.h"

namespace skewt {
	/**
	* WindBarb draws a standard meteorlogical wind barb, representing the speed and direction of the 
	* wind. The barb points towards the direction the wind is coming from. Flags on the barb cummulatively add
	* to the wind speed: 1/2 line is 5, a whole line is 10, and a triangle is 50. No assumption is made about the units of the
	* wind speed.
	*/
	class WindBarb  
	{
	public:
		/**
		* @param rect The Rect that the barb will be drawn into.
		* @param x The x location within the Rect.
		* @param y The y location within the Rect.
		* @param wspd The wind speed.
		* @param wdir The cartession vector wind direction, in degrees.
		*/
		WindBarb(Rect& rect, double x, double y, double wspd, double wdir);
		virtual ~WindBarb();
		/**
		* draw the barb.
		*/
		void draw();

	protected:
		/**
		* Calculate the position of an endpoint at a given legth and direction from a starting
		* point. The aspect ratio of the Rect is taken into consideration, so that the 
		* direction is validly portrayed.
		* @param p The initial point.
		* @param angle The line angle, in cartessian coordinate system.
		* @param length The length of the line, in Rect units.
		* @param  newP The calculated endpoint is returned here.
		*/
		void xyang(Rect::point p, double angle, double length, Rect::point& newP);
		Rect& m_rect;    ///< The Rect that the barb will be drawn into.
		double m_x;      ///< The x location within the Rect.
		double m_y;      ///< The y location within the Rect.
		double m_wspd;   ///< The wind speed.
		double m_wdir;   ///< The cartession vector wind direction, in degrees.
		double m_aspectRatio; ///< The aspect ratio of the Rect.
	};
}
#endif // !defined(AFX_WINDBARB_H__61B3B281_E5DF_11D2_B034_00C04FA30B92__INCLUDED_)
