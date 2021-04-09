/************************************************************************\
	Copyright 2008 University Corporation for Atmospheric Research.
	All rights reserved.
	Use of this code is subject to UCAR's standard Terms of Use,
	which can be found at http://www.ucar.edu/legal/terms_of_use.shtml .
	By using this source code, you agree to abide by those Terms of Use.
\*************************************************************************/

// Adiabats.cpp: implementation of the Adiabats class.
//
//////////////////////////////////////////////////////////////////////

#include "Adiabats.h"

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
  
  Adiabats::Adiabats(SkewTAdapter& adapter,
    double xmin, double xmax, double ymin, double ymax, 
    double tmin, double tmax, double pmin, double pmax,
    double tSlope):
  IsoPleth(adapter, xmin, xmax, ymin, ymax, tmin, tmax, pmin, pmax, tSlope)
    {
    
    }
  
  //////////////////////////////////////////////////////////////////////
  Adiabats::~Adiabats()
    {
    
    }
  
  //////////////////////////////////////////////////////////////////////
  void Adiabats::draw()
    {
    
    double thetaMin   = -50.0;
    double thetaMax   = 300.0;
    double thetaDelta =  10.0;
    double logPresDelta = (log10(m_pmax)-log10(m_pmin))/15.0;
    
    unsigned int color = SKEWT_BLACK;
    
    double theta = thetaMin;
    
    while (theta <= thetaMax) {
      
      double pres = m_pmax;
      double t = tFromTheta(pres, theta);
      
      bool gotLabelPoint = 0;
      resetLastP2();
      
      point labelPoint;
      while (pres >= m_pmin) {
        double presnext = pow(10.0, log10(pres) - logPresDelta);
        double tnext = tFromTheta(presnext, theta);
        drawLine(t, pres, tnext, presnext, color);
        
        gotLabelPoint = lastP2(labelPoint);
        t = tnext;
        pres = presnext;
        }
      if (gotLabelPoint) {
        std::string s = "";
        char buf[100];
        sprintf(buf, "|c%.0f", theta);
        Rect::Text(buf, labelPoint, color);
        }
      theta += thetaDelta;
      }
    }
  
  //////////////////////////////////////////////////////////////////////
  double Adiabats::tFromTheta(double pres, double theta)
    {
    // theta is in deg C, pres in mb
    // return t in deg C
    
    double tda = (theta+273.15)*pow(pres/1000.0, 0.288);
    return tda - 273.15;
    
    }
  
