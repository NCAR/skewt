/************************************************************************\
	Copyright 2008 University Corporation for Atmospheric Research.
	All rights reserved.
	Use of this code is subject to UCAR's standard Terms of Use,
	which can be found at http://www.ucar.edu/legal/terms_of_use.shtml .
	By using this source code, you agree to abide by those Terms of Use.
\*************************************************************************/

// SkewT.cpp: implementation of the SkewT class.
//
//////////////////////////////////////////////////////////////////////

#include "SkewT.h"
#include "IsoTherms.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
//#define new DEBUG_NEW
#endif

using namespace skewt;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SkewT::SkewT(SkewTAdapter& adapter,
             int n,
             double* pTdry, double* pRH, double* pWspd, double* pWdir, double* pPres,
             int nWindBarbs,
             std::string title,
             std::string subTitle, 
             std::string credit):
m_subTitleString(subTitle),
m_titleString(title),
m_creditString(credit),
m_isoMR(NULL),
m_isoTherms(NULL),
m_adiabats(NULL),
m_isoPress(NULL),
m_padiabats(NULL),
m_windBarbs(NULL),
m_tdryTrace(NULL),
m_dewptTrace(NULL),
m_adapter(adapter),
m_tSlope(1.125),
m_nWindBarbs(nWindBarbs)
  {
  m_thermoPageXmin = 0.07;
  m_thermoPageXmax = 0.9;
  
  m_windsPageXmin = m_thermoPageXmax;
  m_windsPageXmax = 1.0;
  
  m_pageYmin = 0.07;
  m_pageYmax = 0.90;
  
  m_tdry.erase(m_tdry.begin(),      m_tdry.end());
  m_presTdry.erase(m_presTdry.begin(),  m_presTdry.end());
  m_dewpt.erase(m_dewpt.begin(),     m_dewpt.end());
  m_presDewpt.erase(m_presDewpt.begin(), m_presDewpt.end());
  m_wspd.erase(m_wspd.begin(),      m_wspd.end());
  m_wdir.erase(m_wdir.begin(),      m_wdir.end());
  m_presWinds.erase(m_presWinds.begin(), m_presWinds.end());
  
  for (int i = 0; i < n; i++) {
    if (pPres[i] != -999.0) {
      double pres = pPres[i];
      
      // tdry and dew point
      if (pTdry[i] != -999.0) {
        m_tdry.push_back(pTdry[i]);
        m_presTdry.push_back(pres);
        if (pRH[i] != -999.0) {
          double dp = dewPt(pTdry[i], pRH[i]);
          m_dewpt.push_back(dp);
          m_presDewpt.push_back(pres);
          }
        }
      
      // wspd and wdir
      if (pWspd[i] != -999.0 && pWdir[i] != -999.0) {
        m_wspd.push_back(pWspd[i]);
        m_wdir.push_back(pWdir[i]);
        m_presWinds.push_back(pres);
        }
      
      }
    }
  
  initialLimits();
  
  brandNewPlot();
  }

/////////////////////////////////////////////////////////////////////////////
SkewT::~SkewT()
  {
  destroyRects();
  }

/////////////////////////////////////////////////////////////////////////////
void SkewT::drawTdry(double pres, double tdry)
  {
  if (pres == -999.0 || tdry == -999.0)
    return;

  m_tdry.push_back(tdry);
  m_presTdry.push_back(pres);

  m_tdryTrace->drawTdry(pres, tdry);
  }

/////////////////////////////////////////////////////////////////////////////
void 
SkewT::drawDp(double pres, double tdry, double RH)
  {
  if (pres == -999.0 || tdry == -999.0 || RH == -999.0)
    return;

  double dp = dewPt(tdry, RH);
  m_dewpt.push_back(dp);
  m_presDewpt.push_back(pres);

  m_dewptTrace->drawDp(pres, dp);
  }

/////////////////////////////////////////////////////////////////////////////
void 
SkewT::drawWind(double pres, double wspd, double wdir) {

  if (pres == -999.0 || wspd == -999.0 || wspd == -999.0)
    return;

  m_wspd.push_back(wspd);
  m_wdir.push_back(wdir);
  m_presWinds.push_back(pres);

  m_windBarbs->drawBarb(wspd, wdir, pres);
  }

/////////////////////////////////////////////////////////////////////////////
void SkewT::draw()
  {
  m_windBarbs->draw();
  m_isoTherms->draw();
  m_adiabats->draw();
  m_isoPress->draw();
  m_padiabats->draw();
  m_isoMR->draw();
  m_tdryTrace->draw(1);
  m_dewptTrace->draw(0);
  
  m_adapter.title(m_titleString);
  m_adapter.subTitle(m_subTitleString);
  
  std::string credit = "|l";
  credit += m_creditString;
  
  m_adapter.Text(credit.c_str(), 0.01, 0.01, 0);
  
  m_adapter.draw_finished();
  }

/////////////////////////////////////////////////////////////////////////////
void SkewT::maximize()
  {
  m_adapter.maximize();
  }

/////////////////////////////////////////////////////////////////////////////
void SkewT::unzoom()
  {
  
  m_adapter.unzoom();
  
  initialLimits();	
  brandNewPlot();
  
  }

/////////////////////////////////////////////////////////////////////////////
void SkewT::zoomin()
  {
  // change the t and pressure limits to
  // match the zoomed area. This must be done
  // before the unzoom, so that we can get the
  // zoomed extents
  
  rescaleLimits();
  m_adapter.unzoom();
  m_adapter.init();
  brandNewPlot();
  
  }

/////////////////////////////////////////////////////////////////////////////
void SkewT::initialLimits()
  {
  m_tmin = -40.0;
  m_tmax = 40.0;
  m_pmin = 100.0;
  m_pmax = 1050.0;

  }

/////////////////////////////////////////////////////////////////////////////
void SkewT::destroyRects()
  {
  delete m_isoTherms;
  delete m_adiabats;
  delete m_isoPress;
  delete m_padiabats;
  delete m_isoMR;
  delete m_tdryTrace;
  delete m_dewptTrace;
  delete m_windBarbs;
  
  m_isoTherms  = NULL;
  m_adiabats   = NULL;
  m_isoPress   = NULL;
  m_padiabats  = NULL;
  m_isoMR      = NULL;
  m_tdryTrace  = NULL;
  m_dewptTrace = NULL;
  m_windBarbs  = NULL;
  
  }

/////////////////////////////////////////////////////////////////////////////
void SkewT::createRects()
  {
  
  destroyRects();
  
  m_isoTherms = new IsoTherms(m_adapter,
    m_thermoPageXmin, m_thermoPageXmax, m_pageYmin, m_pageYmax,
    m_tmin, m_tmax, m_pmin, m_pmax, m_tSlope);
  
  m_adiabats  = new  Adiabats(m_adapter,
    m_thermoPageXmin, m_thermoPageXmax, m_pageYmin, m_pageYmax,
    m_tmin, m_tmax, m_pmin, m_pmax, m_tSlope);
  
  m_isoPress  = new  IsoPress(m_adapter,
    m_thermoPageXmin, m_thermoPageXmax, m_pageYmin, m_pageYmax,
    m_tmin, m_tmax, m_pmin, m_pmax, m_tSlope);
  
  m_padiabats = new PAdiabats(m_adapter,
    m_thermoPageXmin, m_thermoPageXmax, m_pageYmin, m_pageYmax,
    m_tmin, m_tmax, m_pmin, m_pmax, m_tSlope);
  
  m_isoMR     = new     IsoMR(m_adapter,
    m_thermoPageXmin, m_thermoPageXmax, m_pageYmin, m_pageYmax,
    m_tmin, m_tmax, m_pmin, m_pmax, m_tSlope);
  
  m_tdryTrace = new     SkewTtrace(m_adapter,
    m_thermoPageXmin, m_thermoPageXmax, m_pageYmin, m_pageYmax,
    m_tmin, m_tmax, m_pmin, m_pmax, m_tSlope,
    m_presTdry, m_tdry, SKEWT_RED, SkewTtrace::TraceDot);
  
  m_dewptTrace = new    SkewTtrace(m_adapter,
    m_thermoPageXmin, m_thermoPageXmax, m_pageYmin, m_pageYmax,
    m_tmin, m_tmax, m_pmin, m_pmax, m_tSlope,
    m_presDewpt, m_dewpt, SKEWT_BLUE, SkewTtrace::TraceDot);
  
  m_windBarbs = new WindBarbs(m_adapter,
    m_windsPageXmin, m_windsPageXmax, m_pageYmin, m_pageYmax,
    m_pmin, m_pmax,
    m_presWinds, m_wspd, m_wdir, m_nWindBarbs);
  
  }

/////////////////////////////////////////////////////////////////////////////
void SkewT::rescaleLimits()
  {
  double xmin, xmax, ymin, ymax;
  m_adapter.extents(xmin, xmax, ymin, ymax);
  
  // make sure that the box is within
  // our region, and trim off the margins
  xmin = amax(xmin, m_thermoPageXmin);
  xmax = amin(xmax, m_thermoPageXmax);
  ymin = amax(ymin, m_pageYmin);
  ymax = amin(ymax, m_pageYmax);
  
  xmin = (xmin-m_thermoPageXmin)/(m_thermoPageXmax-m_thermoPageXmin);
  xmax = (xmax-m_thermoPageXmin)/(m_thermoPageXmax-m_thermoPageXmin);
  ymin = (ymin-m_pageYmin)/(m_pageYmax-m_pageYmin);
  ymax = (ymax-m_pageYmin)/(m_pageYmax-m_pageYmin);
  
  
  // borrow m_isoPress to do our coordinate transformation
  
  m_pmin = m_isoPress->p(ymax);
  m_pmax = m_isoPress->p(ymin);
  
  m_tmin = m_isoPress->t(xmin, m_isoPress->y(m_pmax));
  m_tmax = m_isoPress->t(xmax, m_isoPress->y(m_pmax));
  
  }

/////////////////////////////////////////////////////////////////////////////
double SkewT::amax(const double &x, const double &y)
  {
  if (x > y)
    return x;
  else 
    return y;
  }

/////////////////////////////////////////////////////////////////////////////
double SkewT::amin(const double &x, const double &y)
  {
  if (x < y)
    return x;
  else
    return y;
  }

/////////////////////////////////////////////////////////////////////////////
void SkewT::brandNewPlot()
  {
  m_adapter.init();
  createRects();
  draw();
  
  }

/////////////////////////////////////////////////////////////////////////////
void SkewT::print()
  {
  m_adapter.print();
  }

/////////////////////////////////////////////////////////////////////////////
double 
SkewT::dewPt(double tdry, double rh) {
  
  // from James Franklin
  double tm = 0.0;
  double tk = tdry+273.16;
  double tn = tk;
  double es = pow(10.0,(9.4051-2353.0/tk) );
  double eo = 0.01*rh*es ;
  double ts = 1.0;
  do {
    double ep = 5417.98*es/(tn*tn);
    tn = tn + (eo-es)/ep;
    ts = fabs(tm-tn) ;
    tm =tn;
    es = pow(10.0,(9.4051-2353./tn));
    } while (ts >= 0.005);
  
  double dd = tk-tn;
  double dewpt=tk-273.16-dd;
  if (dewpt  > tdry) dewpt = tdry;
  return dewpt;
  
  // taken from the FMH 3.
  //	double dpdep = dewPtDepression(tdry, rh);
  //	double result = tdry + dpdep;
  //	return result;
  }

