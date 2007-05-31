//
//
// $Id: PAdiabats.cpp,v 1.13 2005/06/12 02:12:13 martinc Exp $
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

// PAdiabats.cpp: implementation of the PAdiabats class.
//
//////////////////////////////////////////////////////////////////////

#include "PAdiabats.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace skewt;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PAdiabats::PAdiabats(SkewTAdapter& adapter,
                     double xmin, double xmax, double ymin, double ymax, 
                     double tmin, double tmax, double pmin, double pmax,
                     double tSlope):
IsoPleth(adapter, xmin, xmax, ymin, ymax, tmin, tmax, pmin, pmax, tSlope)
  {
  
  }

//////////////////////////////////////////////////////////////////////
PAdiabats::~PAdiabats()
  {
  
  }

//////////////////////////////////////////////////////////////////////
void PAdiabats::draw()
  {
  
  unsigned int color = SKEWT_GREEN;
  
  double pmin = m_pmin;
  if (pmin < 200.0)
    pmin = 200.0;
  if (m_pmax < 200.0)
    return;
  
  double logDeltaP = (log10(m_pmax) - log10(pmin)) / 15.0;
  double  t = -40.0;
  double t2;
  double p2;
  
  while (t < 40.0) {
    resetLastP2();
    double ept = m_mf.theta_e(273.16+t, 273.16+t, 1000.0);
    double p1 = m_pmax;
    double t1 = m_mf.t_sat(ept, p1);
    while (p1 > pmin) {
      p2 = pow(10.0, log10(p1) - logDeltaP);
      if (p2 < pmin)
        p2 = pmin;
      t2 = m_mf.t_sat(ept, p2);
      drawLine(t1-273.16, p1, t2 - 273.16, p2, color);
      t1 = t2;
      p1 = p2;
      }
    
    point lastPoint;
    if (lastP2(lastPoint)) {
      char s[100];
      sprintf(s, "|c%3.0f", t);
      Rect::Text(s, lastPoint, color);
      }
    t += 5.0;
    }
  }
