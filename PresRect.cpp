//
//
// $Id: PresRect.cpp,v 1.10 2005/06/12 02:12:13 martinc Exp $
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
