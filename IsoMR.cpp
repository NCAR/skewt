//
//
// $Id: IsoMR.cpp,v 1.14 2005/06/12 02:12:12 martinc Exp $
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

// IsoMR.cpp: implementation of the IsoMR class.
//
//////////////////////////////////////////////////////////////////////

#include "IsoMR.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace skewt;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IsoMR::IsoMR(SkewTAdapter& adapter,
             double xmin, double xmax, double ymin, double ymax, 
             double tmin, double tmax, double pmin, double pmax,
             double tSlope):
IsoPleth(adapter, xmin, xmax, ymin, ymax, tmin, tmax, pmin, pmax, tSlope)
  {
  
  }

//////////////////////////////////////////////////////////////////////
IsoMR::~IsoMR()
  {
  
  }

//////////////////////////////////////////////////////////////////////
void IsoMR::draw()
  {
  
  static double values[] = {0.1, 0.2, 0.4,  
    1.0, 2.0, 3.0,5.0,
    8.0, 12.0, 16.0, 20.0, 
    30.0, 40.0, 50.0, 60.0};
  
  
  unsigned int color = SKEWT_GREY;
  
  int n = sizeof(values)/sizeof(double);
  double pmin = m_pmin;
  if (pmin < 200.0)
    pmin = 200.0;
  if (m_pmax < 200.0)
    return;
  
  double logDeltaP = (log10(m_pmax) - log10(pmin))/5.0;
  
  for (int i = 0; i < n; i++) {
    resetLastP2();
    point labelPoint;
    bool haveLabelPoint = false;
    
    double p1 = pmin;
    double t1 = m_mf.t_mr( p1, values[i]) - 273.16;
    while (p1 <= m_pmax) {
      double p2 = pow(10.0, log10(p1) + logDeltaP);
      double t2 = m_mf.t_mr(p2, values[i]) - 273.16;
      drawLine(t1, p1, t2, p2, color, SkewTRect::DashedLine);
      haveLabelPoint = lastP2(labelPoint);
      p1 = p2;
      t1 = t2;
      }
    if (haveLabelPoint) {
      std::string s = "";
      char buf[100];
      if (values[i] >= 1.0)
        sprintf(buf, "|r%.0f", values[i]);
      else
        sprintf(buf, "|r%.1f", values[i]);
      Rect::Text(buf, labelPoint, color);
      }
    }
  
  }


