//
//
// $Id: IsoTherms.cpp,v 1.13 2005/06/12 02:12:13 martinc Exp $
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
