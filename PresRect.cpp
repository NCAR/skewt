/************************************************************************\
	Copyright 2008 University Corporation for Atmospheric Research.
	All rights reserved.
	Use of this code is subject to UCAR's standard Terms of Use,
	which can be found at http://www.ucar.edu/legal/terms_of_use.shtml .
	By using this source code, you agree to abide by those Terms of Use.
\*************************************************************************/

// PresRect.cpp: implementation of the PresRect class.
//
//////////////////////////////////////////////////////////////////////

#include "PresRect.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace skewt;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PresRect::PresRect(SkewTAdapter& adapter,
                   double xmin, double xmax, double ymin, double ymax,
                   double pmin, double pmax):
Rect(adapter, xmin, xmax, ymin, ymax),
m_pmin(pmin), m_pmax(pmax)  
  {
  m_pRatio = log10(m_pmin/m_pmax);
  }

//////////////////////////////////////////////////////////////////////
PresRect::~PresRect()
  {
  
  }

//////////////////////////////////////////////////////////////////////
double PresRect::p(double y)
  {
  return m_pmax*pow(10.0, y*m_pRatio);
  }

//////////////////////////////////////////////////////////////////////
double PresRect::y(double p)
  {
  return log10(p/m_pmax)/m_pRatio;
  }
