//
//
// $Id: SkewTtrace.cpp,v 1.13 2005/06/12 02:12:13 martinc Exp $
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

// Trace.cpp: implementation of the Trace class.
//
//////////////////////////////////////////////////////////////////////

#include "SkewTtrace.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace skewt;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SkewTtrace::SkewTtrace(SkewTAdapter& adapter,
                       double xmin, double xmax, double ymin, double ymax, 
                       double tmin, double tmax, double pmin, double pmax,
                       double tSlope,
                       vector<double> pres, vector<double> t,
                       unsigned int color, TraceSymbol symbol):
SkewTRect(adapter, xmin, xmax, ymin, ymax, tmin, tmax, pmin, pmax, tSlope),
m_pres(pres), m_t(t),
m_color(color), m_symbol(symbol)
  {
  
  }

//////////////////////////////////////////////////////////////////////
SkewTtrace::~SkewTtrace()
  {
  
  }

//////////////////////////////////////////////////////////////////////
void SkewTtrace::draw(bool tdry)
  {
  
  if (tdry) {
    for(size_t i = 0; i < m_pres.size(); i++) {
      addTdry(m_t[i],m_pres[i]);
      }
    } else {
    for(size_t i = 0; i < m_pres.size(); i++) {
      addDp(m_t[i],m_pres[i]);
      }
      }
    
  }

//////////////////////////////////////////////////////////////////////
void SkewTtrace::drawTdry(double pres, double tdry) 
  {
  addTdry(tdry, pres);
  }

//////////////////////////////////////////////////////////////////////
void SkewTtrace::drawDp(double pres, double dp) 
  {
  addDp(dp, pres);
  }
