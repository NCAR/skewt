/************************************************************************\
	Copyright 2008 University Corporation for Atmospheric Research.
	All rights reserved.
	Use of this code is subject to UCAR's standard Terms of Use,
	which can be found at http://www.ucar.edu/legal/terms_of_use.shtml .
	By using this source code, you agree to abide by those Terms of Use.
\*************************************************************************/

// SkewT.h: interface for the SkewT class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKEWT_H__5813CCBD_D1A4_11D2_B5B6_ED3B095D6882__INCLUDED_)
#define AFX_SKEWT_H__5813CCBD_D1A4_11D2_B5B6_ED3B095D6882__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SkewTdefs.h"
#include "SkewTAdapter.h"
#include "IsoTherms.h"
#include "Adiabats.h"
#include "IsoPress.h"
#include "PAdiabats.h"
#include "IsoMR.h"
#include "SkewTtrace.h"
#include "WindBarbs.h"

namespace skewt {
	/**
	* Create a generic skewT-logP diagram. SkewT is independent of any particular 
	* output device, and uses a SkewTAdapter to render the diagram on a specific graphics
	* component.
	*
	* SkewT considers the drawing to be performed on a virtual "page", having x and y dimensions running 
	* between 0 and 1. The SkewTAdapter can be interogated for it's current aspect ratio, so that 
	* objects requiring true angle representation, such as wind barbs, can be drawn correctly.
	*
	* SkewT extensively uses the Rect class and it's subclasses to build the graph. Rect and subclasses
	* handle the translation from pressure and temperature coordinates to the virtual cartessian 
	* coordinates of the page. The SkewTAdapter translates the virtual cartessian coordinates into
	* the coordinate space of the graphics device.
	*/
	class SkewT  
	{
	public:
		/**
		* @param adapter The adapter that will display the diagram.
		* @param n The number of data points supplied in the following arrays.
		* @param pTdry Pointer to an array of temperature data, or 0 if none.
		* @param pDP Pointer to an array of DP data, or 0 if none.
		* @param pWspd Pointer to an array of wind speed data, or 0 if none.
		* @param pWdir Pointer to an array of wind direction data, or 0 if none.
		* @param pPres Pointer to an array of pressure data, or 0 if none.
		* @param nWindBarbs Number of wind barbs to be drawn.
		* @param title Title 
		* @param subTitle Subtitle
		* @param credit Credit
        * @param tmin Minimum temperature, along the x axis
        * @param tmax Maximum temperature, along the x axis
        * @param pmin Minimum pressure, along the y axis
        * @param pmax Maximum pressure, along the y axis
		*/
		SkewT(SkewTAdapter& adapter, int n,
			double* pTdry, double* pDP, double* pWspd, double* pWdir, double* pPres,
			int nWindBarbs, std::string title, std::string subTitle, std::string credit,
            double tmin = -40.0, double tmax = 40.0, double pmin = 100.0, double pmax = 1050.0);
		virtual ~SkewT();
		/**
		* draw the graph
		*/
		void draw();
		/**
		* Call this to ask the adapter to print the display
		*/
		void print();
		/**
		* Call this to ask the adapter to resize on the display
		*/
		void resize();
		/**
		* Call this to ask the adapter to zoom in on the display
		*/
		void zoomin();
		/**
		* Call this to ask the adapter to zoom out on the display
		*/
		void unzoom();
		/**
		* Call this to ask the adapter to maximize the display
		*/
		void maximize();
		/**
		* add a temperature point to the graph
		*/
		void drawTdry(double pres, double tdry);
		/**
		* add a dewpoint to the display
		*/
		void drawDp  (double pres, double DP);
		/**
		* add a wind barb to the display
		*/
		void drawWind(double pres, double wspd, double wdir);

	protected:
		std::string m_subTitleString;
		std::string m_titleString;
		std::string m_creditString;
		void brandNewPlot();
		double amin(const double& x, const double& y);
		double amax(const double& x, const double& y);
		void rescaleLimits();
		void createRects();
		void destroyRects();
		void initialLimits();

		IsoMR*        m_isoMR;
		IsoTherms*    m_isoTherms;
		Adiabats*     m_adiabats;
		IsoPress*     m_isoPress;
		PAdiabats*    m_padiabats;
		WindBarbs*    m_windBarbs;
		SkewTtrace*   m_tdryTrace;
		SkewTtrace*   m_dewptTrace;

		SkewTAdapter& m_adapter;

		double m_thermoPageXmin;
		double m_thermoPageXmax;
		double m_windsPageXmin;
		double m_windsPageXmax;
		double m_pageYmin;
		double m_pageYmax;

		double m_tmin;
		double m_tmax;
		double m_pmin;
		double m_pmax;
		double m_defaultTmin;
		double m_defaultTmax;
		double m_defaultPmin;
		double m_defaultPmax;
		double m_tSlope;
		int m_nWindBarbs;


		vector<double> m_tdry;
		vector<double> m_presTdry;
		vector<double> m_dewpt;
		vector<double> m_presDewpt;
		vector<double> m_wspd;
		vector<double> m_wdir;
		vector<double> m_presWinds;

	};
}
#endif // !defined(AFX_SKEWT_H__5813CCBD_D1A4_11D2_B5B6_ED3B095D6882__INCLUDED_)
