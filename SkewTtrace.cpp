/************************************************************************\
	Copyright 2008 University Corporation for Atmospheric Research.
	All rights reserved.
	Use of this code is subject to UCAR's standard Terms of Use,
	which can be found at http://www.ucar.edu/legal/terms_of_use.shtml .
	By using this source code, you agree to abide by those Terms of Use.
\*************************************************************************/

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
