/************************************************************************\
	Copyright 2008 University Corporation for Atmospheric Research.
	All rights reserved.
	Use of this code is subject to UCAR's standard Terms of Use,
	which can be found at http://www.ucar.edu/legal/terms_of_use.shtml .
	By using this source code, you agree to abide by those Terms of Use.
\*************************************************************************/

// IsoTherms.cpp: implementation of the IsoTherms class.
//
//////////////////////////////////////////////////////////////////////

#include "IsoTherms.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace skewt;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IsoTherms::IsoTherms(SkewTAdapter& adapter,
                     double xmin, double xmax, double ymin, double ymax, 
                     double tmin, double tmax, double pmin, double pmax,
                     double tSlope):
IsoPleth(adapter, xmin, xmax, ymin, ymax, tmin, tmax, pmin, pmax, tSlope)
  {
  
  }

//////////////////////////////////////////////////////////////////////
IsoTherms::~IsoTherms()
  {
  
  }

//////////////////////////////////////////////////////////////////////
void IsoTherms::draw()
  {
  
  unsigned int color = SKEWT_BLUE;
  
  double tmin = t(0.0, 1.0);
  double tord = (floor(tmin/10.0))*10.0;
  while (tord < m_tmax) 
    {
    resetFirstP1();
    resetLastP2();
    
    drawLine(tord, m_pmin, tord, m_pmax, color);
    
    point p1, p2;
    
    if (firstP1(p1) && lastP2(p2)) {
      char s[100];
      sprintf(s, "|r%.0f", tord);
      double yText = (p1.y+p2.y)/2.0;
      Text(s, tord, p(yText), 0.0, 0.0, color);
      }
    
    tord += 10.0;
    }
  }
