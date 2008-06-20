/************************************************************************\
	Copyright 2008 University Corporation for Atmospheric Research.
	All rights reserved.
	Use of this code is subject to UCAR's standard Terms of Use,
	which can be found at http://www.ucar.edu/legal/terms_of_use.shtml .
	By using this source code, you agree to abide by those Terms of Use.
\*************************************************************************/

// WindBarbs.cpp: implementation of the WindBarbs class.
//
//////////////////////////////////////////////////////////////////////

#include "WindBarbs.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace skewt;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

WindBarbs::windData::windData(double pres, double wspd, double wdir):
m_pres(pres),
m_wspd(wspd),
m_wdir(wdir)
  {
  }


//////////////////////////////////////////////////////////////////////
WindBarbs::windData::~windData()
  {
  }

//////////////////////////////////////////////////////////////////////
bool WindBarbs::windData::operator< (const windData& rhs) const {
  
  return rhs.m_pres < m_pres;
  
  }

//////////////////////////////////////////////////////////////////////
WindBarbs::WindBarbs(SkewTAdapter& adapter,
                     double xmin, double xmax, double ymin, double ymax,
                     double pmin, double pmax, 
                     vector<double>& pres, 
                     vector<double>& wspd, 
                     vector<double>& wdir,
                     int nBarbs):
PresRect(adapter, xmin, xmax, ymin, ymax, pmin, pmax),
m_nBarbs(nBarbs)
  {
  for (size_t i = 0; i < pres.size(); i++) {
    if (pres[i] <= pmax && pres[i] >= pmin)  {
      m_data.push_back(windData(pres[i], wspd[i], wdir[i]));
      }
    }
  
  sort(m_data.begin(), m_data.end());
  
  if (m_nBarbs <1)
    return;
  
  if (m_pmax - m_pmin < 1.0)
    return;                
  
  _logPmin = log10(m_pmin);
  _logPmax = log10(m_pmax);
  _logInc = (_logPmax - _logPmin) / m_nBarbs;
  
  }

//////////////////////////////////////////////////////////////////////
WindBarbs::~WindBarbs()
  {
  }

//////////////////////////////////////////////////////////////////////
void WindBarbs::draw()
  {
  if (m_nBarbs <1)
    return;
  
  if (m_data.size() < 1)
    return;
  
  if (m_pmax - m_pmin < 1.0)
    return;                
  
  for (size_t i = 0; i < m_data.size(); i++) {
    
    double pres = m_data[i].m_pres;
    drawBarb(m_data[i].m_wspd, m_data[i].m_wdir, pres);
    
    }
  
  }

//////////////////////////////////////////////////////////////////////
void WindBarbs::drawBarb(double wspd, double wdir, double pres) {
  
  if (pres < m_pmin)
    return;
  
  int index = presSegmentIndex(pres);
  
  if (m_plottedBarbIndices.find(index) != m_plottedBarbIndices.end())
    return;
  
  m_plottedBarbIndices.insert(index);
  
  double ybarb = y(pres);
  WindBarb barb(*this, 0.5, ybarb, wspd, wdir);
  barb.draw();
  
  }

//////////////////////////////////////////////////////////////////////
int 
WindBarbs::presSegmentIndex(double pres) 
  {
  
  if (pres < 0.1)
    return 0;
  
  if (m_nBarbs <1)
    return 0;
  
  if (m_pmax - m_pmin < 1.0)
    return 0;           
  
  double log10pres = log10(pres);
  
  int index = (int) ((_logPmax - log10pres)/_logInc);
  
  return index;
  
  }
