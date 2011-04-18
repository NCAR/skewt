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
#include <cstdio>

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
  double pLine, pStep;
  double pDelta = m_pmax - m_pmin;
  if (pDelta > 400.0)
    pStep = 100.0;
  else if (pDelta > 150.0)
    pStep = 50.0;
  else if (pDelta > 50.0)
    pStep = 20.0;
  else if (pDelta > 10.0)
    pStep = 10.0;
  else
    pStep = 1.0;
  
  pLine = floor(m_pmin/pStep)*pStep;
  while (pLine <= m_pmax) {
    drawLine(tmin, pLine, m_tmax, pLine, color);
    char label[100];
    sprintf(label, "|r%4.0f", pLine);
    Text(label, -0.03, pLine, -0.01, color);
    pLine += pStep;
  }
}
