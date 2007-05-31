//
//
// $Id: WindBarb.cpp,v 1.14 2005/06/12 02:12:13 martinc Exp $
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

// WindBarb.cpp: implementation of the WindBarb class.
//
//////////////////////////////////////////////////////////////////////

#include "WindBarb.h"
#include "SkewTMetFormulas.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace skewt;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

WindBarb::WindBarb(Rect& rect, double x, double y, double wspd, double wdir):
m_rect(rect), 
m_x(x), m_y(y), 
m_wspd(wspd), m_wdir(wdir)
  {
  m_aspectRatio = rect.aspectRatio();	
  }

//////////////////////////////////////////////////////////////////////
WindBarb::~WindBarb()
  {
  
  }

//////////////////////////////////////////////////////////////////////
void WindBarb::draw()
  {
  
  
  double barbLen = 0.4;
  double symScale = 0.25 * barbLen;
  
  double d;
  Rect::point p1(m_x, m_y);
  Rect::point p2(m_x, m_y);
  
  d = 450 - m_wdir;
  if (d < 0)
    d = d + 360;
  if (d >= 360) 
    d = d - 360;
		
  
  xyang(p1, d, barbLen, p2);
  m_rect.drawLine(Rect::line(p1,p2), SKEWT_BLUE, Rect::SolidLine, 0);
  p1 = p2;
  
  m_rect.symbol(Rect::point(m_x, m_y), SKEWT_BLUE, Rect::SmallDot);
  
  //	convert from m/s to knots.
  double w = m_wspd*1.94;
  
  double triLength = symScale / sin(60 * 3.14159 / 180);
  
  double delta;
  
  // plot the 50 symbols, which will be equilateral triangles
  
  bool did50 = 0;
  
  delta = 50;
  
  while (w > delta) {
    xyang( p1, d - 120, triLength, p2);
    m_rect.drawLine(Rect::line(p1,p2), SKEWT_BLUE, Rect::SolidLine, 0);
    p1 = p2;
    xyang( p1, d + 120, triLength, p2 );
    m_rect.drawLine(Rect::line(p1,p2), SKEWT_BLUE, Rect::SolidLine, 0);
    p1 = p2;
    
    w = w - delta;
    did50 = 1;
    }
  
  if (did50) {
    xyang( p1, d + 180, symScale / 3, p2);   // move in along the barb
    m_rect.drawLine(Rect::line(p1,p2), SKEWT_BLUE, Rect::SolidLine, 0);
    p1 = p2;
    }
  
  // plot the 10 symbols, which will be full length flags
  
  delta = 10;
  
  while (w > delta) {
    
    xyang( p1, d - 90, symScale, p2);
    m_rect.drawLine(Rect::line(p1,p2), SKEWT_BLUE, Rect::SolidLine, 0);
    p1 = p2;
    
    xyang( p1, d + 90, symScale, p2);
    m_rect.drawLine(Rect::line(p1,p2), SKEWT_BLUE, Rect::SolidLine, 0);
    p1 = p2;
    
    xyang( p1, d + 180, symScale / 2, p2);
    p1 = p2;
    
    w = w - delta;
    }
  
  // plot the 5 symbols, which will be half length flags
  
  delta = 5;
  
  while (w > delta) {
    
    xyang( p1, d - 90, symScale / 2, p2);
    m_rect.drawLine(Rect::line(p1,p2), SKEWT_BLUE, Rect::SolidLine, 0);
    p1 = p2;
    
    xyang( p1, d + 90, symScale / 2, p2);
    m_rect.drawLine(Rect::line(p1,p2), SKEWT_BLUE, Rect::SolidLine, 0);
    p1 = p2;
    
    xyang( p1, d + 180, symScale / 2, p2);
    p1 = p2;
    
    w = w - delta;
    }
  }


//////////////////////////////////////////////////////////////////////
void WindBarb::xyang(Rect::point p, double angle, double length, Rect::point& newP)
  {
  double d = angle * 3.14159 / 180.0;
  
  double deltaX = length * cos(d);
  double deltaY = length * sin(d)/m_aspectRatio;
  newP.x = p.x + deltaX;
  newP.y = p.y + deltaY;
  
  }
