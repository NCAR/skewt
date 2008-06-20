/************************************************************************\
	Copyright 2008 University Corporation for Atmospheric Research.
	All rights reserved.
	Use of this code is subject to UCAR's standard Terms of Use,
	which can be found at http://www.ucar.edu/legal/terms_of_use.shtml .
	By using this source code, you agree to abide by those Terms of Use.
\*************************************************************************/

// SkewTMetFormulas.cpp: implementation of the SkewTMetFormulas class.
//
//////////////////////////////////////////////////////////////////////

#include "SkewTMetFormulas.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace skewt;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SkewTMetFormulas::SkewTMetFormulas()
  {
  
  }

SkewTMetFormulas::~SkewTMetFormulas()
  {
  
  }

  /*
  * Derivation of meteorological parameters.
  * 
  * Unless otherwise noted, the formulas used herein are extracted
  * from the document "Formulation of Output Parameters for PAM II CMF Data"
  * compiled by Paul Herzegh (18 March 1988 revision).
*/
/*
*		Copyright (C) 1988-91 by UCAR
*	University Corporation for Atmospheric Research
*		   All rights reserved
*
* No part of this work covered by the copyrights herein may be reproduced
* or used in any form or by any means -- graphic, electronic, or mechanical,
* including photocopying, recording, taping, or information storage and
* retrieval systems -- without permission of the copyright owner.
* 
* This software and any accompanying written materials are provided "as is"
* without warranty of any kind.  UCAR expressly disclaims all warranties of
* any kind, either express or implied, including but not limited to the
* implied warranties of merchantibility and fitness for a particular purpose.
* UCAR does not indemnify any infringement of copyright, patent, or trademark
* through use or modification of this software.  UCAR does not provide 
* maintenance or updates for its software.
*/

# include <math.h>
//# include "met_formulas.h"

/*
* Constants
*/
# define _A_	5.0065
# define _B_	19.83923
# define C_P	1005.7
# define R_D	287.
# define E_3	6.1078
# define T_3	273.15
# define EPSILON	0.622

/*
* Lookup table of saturation vapor pressures (every 1/2 degree from 210 K 
* to 310 K)
*/
# define ETBL_MIN	210.0
# define ETBL_MAX	310.0
# define ETBL_STEP	0.5

static double E_tbl[] = 
  {
  /* 210.0 */	0.01296,	0.01383,	0.01475,	0.01573,
  /* 212.0 */	0.01677,	0.01787,	0.01904,	0.02027,
  /* 214.0 */	0.02158,	0.02296,	0.02443,	0.02598,
  /* 216.0 */	0.02763,	0.02936,	0.03120,	0.03314,
  /* 218.0 */	0.03520,	0.03736,	0.03965,	0.04207,
  /* 220.0 */	0.04462,	0.04731,	0.05015,	0.05315,
  /* 222.0 */	0.05631,	0.05963,	0.06314,	0.06684,
  /* 224.0 */	0.07073,	0.07483,	0.07914,	0.08368,
  /* 226.0 */	0.08845,	0.09347,	0.09876,	0.10431,
  /* 228.0 */	0.11014,	0.11627,	0.12271,	0.12947,
  /* 230.0 */	0.13657,	0.14403,	0.15185,	0.16006,
  /* 232.0 */	0.16866,	0.17769,	0.18715,	0.19707,
  /* 234.0 */	0.20746,	0.21835,	0.22975,	0.24170,
  /* 236.0 */	0.25420,	0.26729,	0.28098,	0.29531,
  /* 238.0 */	0.31030,	0.32597,	0.34235,	0.35948,
  /* 240.0 */	0.37738,	0.39608,	0.41562,	0.43603,
  /* 242.0 */	0.45733,	0.47957,	0.50279,	0.52701,
  /* 244.0 */	0.55229,	0.57865,	0.60615,	0.63481,
  /* 246.0 */	0.66470,	0.69584,	0.72830,	0.76211,
  /* 248.0 */	0.79733,	0.83402,	0.87221,	0.91197,
  /* 250.0 */	0.95335,	0.99642,	1.04122,	1.08783,
  /* 252.0 */	1.13631,	1.18671,	1.23912,	1.29360,
  /* 254.0 */	1.35021,	1.40904,	1.47016,	1.53364,
  /* 256.0 */	1.59957,	1.66803,	1.73910,	1.81288,
  /* 258.0 */	1.88944,	1.96888,	2.05130,	2.13680,
  /* 260.0 */	2.22546,	2.31740,	2.41272,	2.51152,
  /* 262.0 */	2.61393,	2.72005,	2.82999,	2.94388,
  /* 264.0 */	3.06184,	3.18400,	3.31049,	3.44144,
  /* 266.0 */	3.57697,	3.71725,	3.86240,	4.01257,
  /* 268.0 */	4.16791,	4.32858,	4.49474,	4.66654,
  /* 270.0 */	4.84415,	5.02773,	5.21748,	5.41355,
  /* 272.0 */	5.61613,	5.82541,	6.04158,	6.26483,
  /* 274.0 */	6.49536,	6.73337,	6.97908,	7.23269,
  /* 276.0 */	7.49443,	7.76451,	8.04316,	8.33062,
  /* 278.0 */	8.62713,	8.93292,	9.24825,	9.57337,
  /* 280.0 */	9.90853,	10.25401,	10.61007,	10.97699,
  /* 282.0 */	11.35505,	11.74454,	12.14575,	12.55898,
  /* 284.0 */	12.98454,	13.42274,	13.87390,	14.33834,
  /* 286.0 */	14.81640,	15.30841,	15.81471,	16.33567,
  /* 288.0 */	16.87163,	17.42296,	17.99004,	18.57325,
  /* 290.0 */	19.17296,	19.78958,	20.42351,	21.07515,
  /* 292.0 */	21.74492,	22.43326,	23.14058,	23.86733,
  /* 294.0 */	24.61396,	25.38092,	26.16869,	26.97773,
  /* 296.0 */	27.80852,	28.66155,	29.53732,	30.43635,
  /* 298.0 */	31.35914,	32.30622,	33.27813,	34.27540,
  /* 300.0 */	35.29859,	36.34827,	37.42500,	38.52936,
  /* 302.0 */	39.66194,	40.82335,	42.01419,	43.23508,
  /* 304.0 */	44.48666,	45.76955,	47.08442,	48.43193,
  /* 306.0 */	49.81273,	51.22752,	52.67699,	54.16184,
  /* 308.0 */	55.68278,	57.24053,	58.83584,	60.46945,
  /* 310.0 */	62.14212
  };

//////////////////////////////////////////////////////////////////////
double
SkewTMetFormulas::w_sat (double t, double p)
/*
* Saturation mixing ratio in g/kg at t (deg. K) and p (mb)
*/
  {
  double	e = e_sw (t);
  
  return (1000.0 * EPSILON * e / (p - e));
  }

//////////////////////////////////////////////////////////////////////
double
SkewTMetFormulas::e_sw (double t)
/*
* Saturation vapor pressure in mb at temperature t (in deg. K)
*/
  {
  int	index;
  double	frac;
  /*
  * Interpolate from the table of vapor pressures if ETBL_MIN < t < ETBL_MAX
  */
  if (ETBL_MIN < t && t < ETBL_MAX)
    {
    index = (int)((t - ETBL_MIN) / ETBL_STEP);
    frac = fmod (t, ETBL_STEP) / ETBL_STEP;
    return ((1.0 - frac) * E_tbl[index] + frac * E_tbl[index+1]);
    }
    /*
    * Otherwise, use the exact (but slow) formula
  */
  else
    return (E_3 * exp (_A_ * log (T_3 / t)) * 
    exp ((_A_ + _B_) * (1 - T_3 / t)));
  }

//////////////////////////////////////////////////////////////////////
double
SkewTMetFormulas::theta_dry (double t, double p)
/*
* Potential temperature (deg. K) of dry air at t (deg. K) and p (mb)
* 
*			      (R /C )
*	                        d  p
*	theta = t * (1000 / p)
*/
  {
  double	u, diff, diff2, diff3;
  
  u = 1000. / p;
  /*
  * Use Taylor series expansion about 700mb for pressures down to 500mb
  */
  if (p > 500.)
    {
    diff = u - 1000. / 700.;
    diff2 = diff * diff;
    diff3 = diff * diff2;
    
    return (t * (1.10714599 +
      0.22116497 * diff + 
      -0.05531763 * diff2 + 
      0.02213146 * diff3 + 
      -0.01051376 * diff * diff3 + 
      0.00546766 * diff2 * diff3 +
      -0.00300743 * diff3 * diff3));
    }
    /*
    * Use Taylor series expansion about 350mb for pressures down to 250mb
  */
  else if (p > 250.)
    {
    diff = u - 1000. / 350.;
    diff2 = diff * diff;
    diff3 = diff * diff2;
    
    return (t * (1.34930719 +
      0.13476972 * diff +
      -0.01685425 * diff2 +
      0.00337152 * diff3 + 
      -0.00080084 * diff * diff3 + 
      0.00020824 * diff2 * diff3 +
      -0.00005727 * diff3 * diff3));
    
    }
    /*
    * Use Taylor series expansion about 175mb for pressures down to 125mb
  */
  else if (p > 125.)
    {
    diff = u - 1000. / 175.;
    diff2 = diff * diff;
    diff3 = diff * diff2;
    
    return (t * (1.64443524 +
      0.08212365 * diff +
      -0.00513518 * diff2 +
      0.00051362 * diff3 + 
      -0.00006100 * diff * diff3 + 
      0.00000793 * diff2 * diff3 + 
      -0.00000109 * diff3 * diff3));
    }
    /*
    * Otherwise, use the exact form
  */
  else
    return (t * pow (u, .28537338));
  }

//////////////////////////////////////////////////////////////////////
double
SkewTMetFormulas::lcl_temp (double temp, double dp)
/*
* Calculate the temperature (deg. K) of the lifting condensation 
* level from the surface temp (deg. K) and dewpoint (deg. K)
*/
  {
  if (dp > temp)
    return (0.0);	/* error */
  
  return (1. / (1. / (dp - 56.) + log (temp / dp) / 800.) + 56.);
  }

//////////////////////////////////////////////////////////////////////
double
SkewTMetFormulas::lcl_pres (double temp, double dp, double pres)
/*
* Find the pressure (mb) of the lifting condensation level from the 
* surface dewpoint (deg. K), temperature (deg. K), and pressure (mb).
*
* Adapted from Carl Mohr's RSANAL program.
*/
  {
  double	w = w_sat (dp, pres);	/* mixing ratio */
  double	theta = theta_dry (temp, pres);
  double	plcl = pres, test = 1.0;
  
  if (dp > temp)
    return (0.0);	/* error */
  
  while (test > 0.01 || test < -0.01)
    {
    test = t_mr (plcl, w) - theta_to_t (theta, plcl);
    plcl *= pow (2.0, (0.02 * test));
    }
  
  return (plcl);
  }

//////////////////////////////////////////////////////////////////////
double
SkewTMetFormulas::t_mr (double p, double w)
/*
* Calculate the temperature (deg. K) of saturated air at
* pressure p (in mb) and with mixing ratio w (in g/kg)
*
* The vapor pressure e is calculated using Note 2 of the Herzegh memo.
* The formula for the temperature was derived from Note 6 by substituting
* a two term Taylor series expansion for the ln(T_3/T) term and solving for
* T.
*/
  {
  double	e = (p * w) / (1000. * EPSILON + w);
  
  return (T_3 * _A_ / 
    (_A_ - _B_ + sqrt (square (_B_) + 2 * _A_ * log (E_3 / e))));
  }

//////////////////////////////////////////////////////////////////////
double
SkewTMetFormulas::theta_to_t (double theta, double p)
/*
* Temperature of dry air (deg. K) at potential temperature (deg. K) and p (mb)
*/
  {
  return (theta * pow ((1000.0 / p), -R_D / C_P));
  }

//////////////////////////////////////////////////////////////////////
double
SkewTMetFormulas::theta_e (double t, double dp, double p)
/*
* Equivalent potential temperature at temperature t (K), dewpoint dp (K),
* and pressure p (mb)
*/
  {
  double	w = w_sat (dp, p);
  double	theta = theta_dry (t, p);
  double	t_l = lcl_temp (t, dp);
  
  return (theta * exp ((3.376 / t_l - 0.00254) * w * (1 + 0.00081 * w)));
  }

//////////////////////////////////////////////////////////////////////
double
SkewTMetFormulas::t_sat (double ept, double p)
/*
* Temperature of saturated air (deg. K) with equivalent potential
* temperature ept (deg. K) and pressure p (mb)
*/
  {
  double	t_s = T_3, delta = 60.0, x;
  
  x = ept - theta_e (t_s, t_s, p);
  
  while (x > 0.01 || x < -0.01)
    {
    t_s += x > 0.0 ? delta : -delta;
    delta /= 2.0;
    if (delta == 0.0)
      delta = 60.0;
    x = ept - theta_e (t_s, t_s, p);
    }
  
  return (t_s);
  }

//////////////////////////////////////////////////////////////////////
double
SkewTMetFormulas::dewpoint (double e)
/*
* Calculate the dewpoint from the vapor pressure
*/
  {
  double	u = log (e / E_3);
  
  return (237.3 * u / (17.2694 - u) + T_3);
  }

//////////////////////////////////////////////////////////////////////
double
SkewTMetFormulas::e_from_dp (double dp)
/*
* Calculate the vapor pressure from the dewpoint
* (This uses Note 5 from the Herzegh memo, inverted to represent e in
*  terms of the dewpoint)
*/
  {
  return (E_3 * exp (17.2694 * (1.0 - 237.3 / (dp - T_3 + 237.3))));
  }

//////////////////////////////////////////////////////////////////////
double
SkewTMetFormulas::t_v (double t, double p, double e)
/*
* Calculate the virtual temperature from the temperature (K), pressure (mb), 
* and vapor pressure (mb)
*/
  {
  return (t / (1 - (e / p) * (1 - EPSILON)));
  }

//////////////////////////////////////////////////////////////////////
double
SkewTMetFormulas::t_wet (double t, double p, double rh)
/*
* Calculate wet bulb temperature from temperature (K), pressure (mb), and 
* relative humidity (%).
* 
* This is an iterative solution using notes 3 and 6 of the Herzegh
* memo of 18 March 88 and tweaking t_wet until we're close (This seems
* like a poor algorithm, but I don't have time to make it better)
*/
  {
  double	e_sat, e, e_left, e_right, e_guess;
  double	tw_left, tw_right, tw_guess;
  /*
  * Find our vapor pressure
  */
  e_sat = e_sw (t);
  e = rh * 0.01 * e_sat;
  /*
  * Initialize
  */
  tw_left = t - 80; /* Assume t_w is within 80 deg. of t */
  e_left = e_sw (tw_left) - p * (t - tw_left) * 0.00066 * 
    (0.6859 + 0.00115 * tw_left);
  
  tw_right = t;
  e_right = e_sat;
  
  while (1)
    {
    tw_guess = tw_left + (e - e_left) / (e_right - e_left) * 
      (tw_right - tw_left);
    
    e_guess = e_sw (tw_guess) - p * (t - tw_guess) * 0.00066 * 
      (0.6859 + 0.00115 * tw_guess);
    
      /*
      * Quit when the vapor pressure for our guess is within 0.01 mb of the 
      * actual
    */
    if (fabs (e_guess - e) < 0.01)	
      break;
    
    if (e_guess < e)
      {
      tw_left = tw_guess;
      e_left = e_guess;
      }
    else
      {
      tw_right = tw_guess;
      e_right = e_guess;
      }
    }
  
  return (tw_guess);
  }


//////////////////////////////////////////////////////////////////////
double
SkewTMetFormulas::square (double x)
  {
  return (x * x);
  }

//////////////////////////////////////////////////////////////////////
double
SkewTMetFormulas::ten_to_the (double x)
  {
  return (pow (10.0, x));
  }
