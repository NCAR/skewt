/************************************************************************\
	Copyright 2008 University Corporation for Atmospheric Research.
	All rights reserved.
	Use of this code is subject to UCAR's standard Terms of Use,
	which can be found at http://www.ucar.edu/legal/terms_of_use.shtml .
	By using this source code, you agree to abide by those Terms of Use.
\*************************************************************************/

// SkewTRect.cpp: implementation of the SkewTRect class.
//
//////////////////////////////////////////////////////////////////////

#include "SkewTRect.h"
#include  <cmath>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace skewt;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SkewTRect::SkewTRect(SkewTAdapter& adapter,
                     double xmin, double xmax, double ymin, double ymax,
                     double tmin, double tmax,
                     double pmin, double pmax, 
                     double tSlope):
PresRect(adapter, xmin, xmax, ymin, ymax, pmin, pmax),
m_slope(tSlope), m_tmin(tmin), m_tmax(tmax)
  {
  m_tSpan    = m_tmax - m_tmin;
  
  }

//////////////////////////////////////////////////////////////////////
SkewTRect::~SkewTRect()
  {
  
  }

//////////////////////////////////////////////////////////////////////
double SkewTRect::x(double t, double y)
  {
  double xx = (t - m_tmin) / (m_tSpan) + y / m_slope;
  return xx;
  }


//////////////////////////////////////////////////////////////////////
void SkewTRect::drawLine(double t1, double p1, double t2, double p2, unsigned int color, LineType lineType)
  {
  
  double y1 = y(p1);
  double x1 = x(t1, y1);
  double y2 = y(p2);
  double x2 = x(t2, y2);
  
  line l = line(point(x1,y1), point(x2,y2));
  
  Rect::LineType skLineType;
  switch (lineType) {
    case DashedLine:
      skLineType = Rect::DashedLine;
      break;
    case SolidLine:
    default:
      skLineType = Rect::SolidLine;
      break;
    }
  
  Rect::drawLine(l, color, skLineType);
  
  return;
  
  }

//////////////////////////////////////////////////////////////////////
double SkewTRect::t(double x, double y)
  {
  return (x - y/m_slope)*(m_tSpan) + m_tmin;
  }


//////////////////////////////////////////////////////////////////////
void SkewTRect::Text(const std::string &s, const double t, const double p, 
                     const double xoffset, const double yoffset, unsigned int color)
  {
  point p1;
  p1.x = x(t,y(p)) + xoffset;
  p1.y = y(p) + yoffset;
  
  Rect::Text(s, p1, color);
  
  }

//////////////////////////////////////////////////////////////////////
void SkewTRect::Text(const std::string &s, const double xx, const double p,
                     const double yoffset, unsigned int color)
  {
  
  double yy = y(p) + yoffset;
  point p1(xx,yy);
  
  Rect::Text(s, p1, color);
  
  }

//////////////////////////////////////////////////////////////////////
void SkewTRect::symbol(double t, double pres, unsigned int color) {
  point pp;
  pp.y = y(pres);
  pp.x = x(t, pp.y);
  
  Rect::symbol(pp, color);
  }

//////////////////////////////////////////////////////////////////////
void SkewTRect::addTdry(double t, double p)
  {
  double yy = y(p);
  double xx = x(t, yy);
  Rect::addTdry(xx, yy);
  }

//////////////////////////////////////////////////////////////////////
void SkewTRect::addDp(double t, double p)
  {
  double yy = y(p);
  double xx = x(t, yy);
  Rect::addDp(xx, yy);
  
  }
