/************************************************************************\
	Copyright 2008 University Corporation for Atmospheric Research.
	All rights reserved.
	Use of this code is subject to UCAR's standard Terms of Use,
	which can be found at http://www.ucar.edu/legal/terms_of_use.shtml .
	By using this source code, you agree to abide by those Terms of Use.
\*************************************************************************/

// IsoPleth.cpp: implementation of the IsoPleth class.
//
//////////////////////////////////////////////////////////////////////

#include "IsoPleth.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace skewt;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IsoPleth::IsoPleth(SkewTAdapter& adapter,
                   double xmin, double xmax, double ymin, double ymax, 
                   double tmin, double tmax, double pmin, double pmax,
                   double tSlope):
SkewTRect(adapter, xmin, xmax, ymin, ymax, tmin, tmax, pmin, pmax, tSlope)
  {
  
  }

//////////////////////////////////////////////////////////////////////
IsoPleth::~IsoPleth()
  {
  
  }
