//
//
// $Id: IsoPress.cpp,v 1.13 2005/06/12 02:12:13 martinc Exp $
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
