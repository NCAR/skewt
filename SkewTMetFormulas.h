/************************************************************************\
	Copyright 2008 University Corporation for Atmospheric Research.
	All rights reserved.
	Use of this code is subject to UCAR's standard Terms of Use,
	which can be found at http://www.ucar.edu/legal/terms_of_use.shtml .
	By using this source code, you agree to abide by those Terms of Use.
\*************************************************************************/

//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SkewTMetFormulas_H__1A3C4A41_3DDA_11D3_BE80_00C04FA30B92__INCLUDED_)
#define AFX_SkewTMetFormulas_H__1A3C4A41_3DDA_11D3_BE80_00C04FA30B92__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace skewt {
	/**
	* SkewTMetFormulas provides meteorlogical formulas for use in the SkewT package. 
	* This class was created and added to the SkewT package so that SkewT could
	* be distributed without dependency on a seperate package of formulas.
	*/
	class SkewTMetFormulas  
	{
	public:
		SkewTMetFormulas();
		virtual ~SkewTMetFormulas();

		/**
		* @param t temperature (deg K).
		* @param p Pressure (mb).
		* @returns Saturation mixing ratio in g/kg.
		*/
		double	w_sat (double t, double p);
		/**
		* @param t Temperature (deg K).
		* @returns  Saturation vapor pressure in mb.
		*/
		double	e_sw_herzegh_1988 (double t);
		/**
		 * @param t Temperature (deg K).
		 * @returns Saturation vapor pressure in mb.
		 */
		double e_sw_hardy_1998(double t);
		/**
		* @param p Pressure (mb).
		* @param w Mixing Ratio (g/kg).
		* @returns  Temperature (deg. K) of saturated air.
		*/
		double	t_mr (double p, double w);
		/**
		* @param theta Potential temperature (deg K).
		* @param p Pressure (mb).
		* @returns Temperature of dry air (deg. K)
		*/
		double	theta_to_t (double theta, double p);
		/**
		* @param t temperature (deg K)
		* @param dp Dewpoint (deg K)
		* @param p Pressure (mb)
		* @returns  * Equivalent potential temperature (deg K)
		*/
		double	theta_e (double t, double dp, double p);
		/**
		* @param ept Equivalent potential temperature (deg K)
		* @param p Pressure (mb)
		* @returns * Temperature of saturated air (deg. K)
		*/
		double	t_sat (double ept, double p);
		/**
		* @param x Value to be squared.
		* @returns Square of x
		*/
		double	square (double x);
		/**
		* @param x Input value.
		* @returns 10 raised to the xth power.
		*/
		double	ten_to_the (double x);
		/**
		* @param temp Temperature (deg K)
		* @param dp Dewpoint (deg K)
		* @param pres Pressure (mb).
		* @returns Pressure (mb) of the lifting condensation level.
		*/
		double	lcl_pres (double temp, double dp, double pres);
		/**
		* @param temp Surface temperature (deg K).
		* @param dp Dewpoint (deg K).
		* @returns Temperature (deg. K) of the lifting condensation 
		* level
		*/
		double	lcl_temp (double temp, double dp);
		/**
		* @param t Temperature (deg K).
		* @param p Pressure (mb).
		* @returns Potential temperature (deg. K) of dry air.
		*/
		double	theta_dry (double t, double p);
		/**
		* @param e Vapor Pressure (mb).
		* @returns Dewpoint (deg K).
		*/
		double	dewpoint (double e);
		/**
		* @param dp Dewpoint (deg K)
		* @returns Vapor pressure (mb)
		*/
		double	e_from_dp (double dp);
		/**
		* @param t Termperature (deg K).
		* @param p Pressure (mb).
		* @param e Vapor pressure (mb).
		* @returns Virtual temperature (deg K)
		*/
		double	t_v (double t, double p, double e);
		/**
		* @param t Temperature (deg K).
		* @param p Pressure (mb).
		* @param rh Relative humidity (\%).
		* @returns Wet bulb temperature (deg K).
		*/
		double	t_wet (double t, double p, double rh);
	};
}
#endif // !defined(AFX_SkewTMetFormulas_H__1A3C4A41_3DDA_11D3_BE80_00C04FA30B92__INCLUDED_)
