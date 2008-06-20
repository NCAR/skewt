/************************************************************************\
	Copyright 2008 University Corporation for Atmospheric Research.
	All rights reserved.
	Use of this code is subject to UCAR's standard Terms of Use,
	which can be found at http://www.ucar.edu/legal/terms_of_use.shtml .
	By using this source code, you agree to abide by those Terms of Use.
\*************************************************************************/

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
