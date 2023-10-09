/************************************************************************\
	Copyright 2008 University Corporation for Atmospheric Research.
	All rights reserved.
	Use of this code is subject to UCAR's standard Terms of Use,
	which can be found at http://www.ucar.edu/legal/terms_of_use.shtml .
	By using this source code, you agree to abide by those Terms of Use.
\*************************************************************************/

// IsoMR.cpp: implementation of the IsoMR class.
//
//////////////////////////////////////////////////////////////////////

#include "IsoMR.h"

#include <cstdio>  // sprintf

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
    double t1 = m_mf.t_mr( p1, values[i]) - 273.15;
    while (p1 <= m_pmax) {
      double p2 = pow(10.0, log10(p1) + logDeltaP);
      double t2 = m_mf.t_mr(p2, values[i]) - 273.15;
      drawLine(t1, p1, t2, p2, color);
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


