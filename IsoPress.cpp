/************************************************************************\
	Copyright 2008 University Corporation for Atmospheric Research.
	All rights reserved.
	Use of this code is subject to UCAR's standard Terms of Use,
	which can be found at http://www.ucar.edu/legal/terms_of_use.shtml .
	By using this source code, you agree to abide by those Terms of Use.
\*************************************************************************/

// IsoPress.cpp: implementation of the IsoPress class.
//
//////////////////////////////////////////////////////////////////////

#include "IsoPress.h"
#include <string>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace skewt;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IsoPress::IsoPress(SkewTAdapter& adapter,
                   double xmin, double xmax, double ymin, double ymax, 
                   double tmin, double tmax, double pmin, double pmax,
                   double tSlope):
IsoPleth(adapter, xmin, xmax, ymin, ymax, tmin, tmax, pmin, pmax, tSlope)
  {
  
  }

//////////////////////////////////////////////////////////////////////
IsoPress::~IsoPress()
  {
  
  }

//////////////////////////////////////////////////////////////////////
void IsoPress::draw()
  {
  unsigned int color = SKEWT_RED;
  
  double tmin = t(0.0, 1.0);
  double p = floor(m_pmin/100.0)*100.0;
  
  while (p <= m_pmax)
    {
    drawLine(tmin, p, m_tmax, p, color);
    char label[100];
    sprintf(label, "|r%4.0f", p);
    Text(label, -0.03, p, -0.01, color);
    p += 100.0;
    }
  }
