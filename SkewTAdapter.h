/************************************************************************\
	Copyright 2008 University Corporation for Atmospheric Research.
	All rights reserved.
	Use of this code is subject to UCAR's standard Terms of Use,
	which can be found at http://www.ucar.edu/legal/terms_of_use.shtml .
	By using this source code, you agree to abide by those Terms of Use.
\*************************************************************************/

// SkewTAdapter.h: interface for the SkewTAdapter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKEWTADAPTER_H__5813CCC1_D1A4_11D2_B5B6_ED3B095D6882__INCLUDED_)
#define AFX_SKEWTADAPTER_H__5813CCC1_D1A4_11D2_B5B6_ED3B095D6882__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SkewTdefs.h"
#include <vector>
#include <string>
//#include "Rect.h"

using namespace std;

namespace skewt {
	/**
	* SkewTAdapter provides a pure virtual interface between the generic SkewT class and a given 
	* graphics rendering component. SkewTAdapter is subclassed for each type of graphics component.
	* For instance, SkewTAdapterPesgo provides the implmentation for displaying SkewT in a
	* GigaSoft ProEssentials graphics component. Similarly, SkewTAdapterQt allows SkewT to render 
	* via a Qt QWidget.
	*
	* The list of member functions is somewhat bloated, but not all of them need to provide functionality. For instance, 
	* if savePlot() is not needed, the derived class function could be a noop. 
	*
	* In usage, a SkewTAdapter is created first, and this is provided to the constructor of the SkewT. Thus,
	* the SkewT does not know what kind of graphics component is being utilized.
	*
	* All coordinates in this interface reference a virtual drawing space 0 <= x <= 1, 0 <= y <= 1. The SkewTAdapter 
	* derived classes are responsible for comverting these values to actuall drawing coordinates.
	* 
	* It is legitimate for derived classes to add their own member functions which are specific to the graphics
	* component. These functions would then be accessed through the adapter, since SkewT will not be aware of them.
	*
	* Note that the SkewT class has two operational modes. Its constructor can be called with arrays of data to be
	* initially plotted; this is the normal static mode of operation. However, member functions are provided that allow data to 
	* be incrementally added, as in a real-time display. (See SkewT::drawTdry(), SkewT::drawDp() and SkewT::drawWind()).
	* 
	*/
	class SkewTAdapter  
	{
	public:
		enum PlotFileType {PNG, JPG};

		enum LineType {SolidLine, DashedLine};
		enum SymType {SmallPlus, SmallDot};

		SkewTAdapter();
		virtual ~SkewTAdapter();

		/**
		* Perform graphics component initialization, when a completely new plot is being created.
		*/
		virtual void          init() = 0;
		/**
		* Called when the drawing is completely finished, and the plot may be displayed. Depending 
		* on the graphics component, this function may be a noop.
		*/
		virtual void          draw_finished() = 0;
		/**
		* Add a dewpoint datum to the SkewT.
		* @param x X coordinate, between 0 and 1.
		* @param y Y coordinate, between 0 and 1.
		*/
		virtual void          addDp(double x, double y) = 0;
		/**
		* Add a tdry datum to the SkewT.
		* @param x X coordinate, between 0 and 1.
		* @param y Y coordinate, between 0 and 1.
		*/
		virtual void          addTdry(double x, double y) = 0;
		/**
		* Draw a symbol at the specified location. Note that this is not used to draw the 
		* tdry and dew point data. It can be used, for instance, to draw a small circle at the base of a windbarb.
		* @param x X coordinate, between 0 and 1.
		* @param y Y coordinate, between 0 and 1.
		* @param color Color of symbol.
		* @param st SkewT::SymType
		*/
		virtual void          symbol(double x, double y, unsigned int color, SymType st = SmallPlus) = 0;
		/**
		* Write the text string at the specified location.
		* @param s The text.
		* @param x X coordinate, between 0 and 1.
		* @param y Y coordinate, between 0 and 1.
		* @param color Color of the text, see color definitions in SkewTdefs.h.
		*/
		virtual void          Text(const string& s, const double x, const double y, unsigned int  color) = 0;
		/**
		* Return the limits of a zoomed selection area. This is provided so that SkewT can redraw a zoomed plot, 
		* showing just the region that has been zoomed into.
		* @param xmin Minimum x value.
		* @param xmax Maximum x value.
		* @param ymin Minimum y value.
		* @param ymax Maximum y value.
		*/
		virtual void          extents(double& xmin, double& xmax, double& ymin, double& ymax) = 0;
		/**
		* Draw a line of a spcified color. This is used to render the graph background artifacts, such as
		* isopleths. It is not used to display the tdry and dp traces.
		* @param x1 Starting x value.
		* @param y1 Starting y value.
		* @param x2 Ending x value.
		* @param y2 Ending y value.
		* @param color Color of the line, see color definitions in SkewTdefs.h.
		* @param lineType The type of line.
		*/
		virtual void          line(double x1, double y1, double x2, double y2, unsigned int color, LineType lineType = SolidLine) = 0;
		/**
		* Set the graph main  title.
		* @param s The title text.
		*/
		virtual void          title(std::string s) = 0;
		/**
		* Set the graph sub-title.
		* @param s The sub-title text.
		*/
		virtual void          subTitle(std::string s) = 0;
		/**
		* Enable/disable the marking of individual points.
		* @param flag Set true to display a symbol for each point.
		*/
		virtual void          markPoints (bool flag) = 0;
		/**
		* Return the plot window aspect ratio.
		* @return The aspect ratio of the the plotting window, height/width.
		*/
		virtual double        aspectRatio() = 0;
		/**
		* Print the skew-t. The adapter provide everything necessary, such as a printer selection dialog, etc.
		*/
		virtual void          print() = 0;
		/**
		* Restore the graph to an unzoomed state. This function will typically call the zoom facilities of the graphics adapter.
		*/
		virtual void          unzoom() = 0;
		/**
		* Maximize the plot within the window system.  This function will typically call the zoom facilities of the graphics adapter.
		*/
		virtual void          maximize() = 0;
		/**
		* Save an image of the skew-t to a file.
		* @param path Full file path to save the image.
		* @param xPixels Width of the image, in pixels.
		* @param yPixels Height of the image, in pixels.
		* @param fileType Type of file format.
		*/
		virtual void          savePlot(std::string path, int xPixels, int yPixels, PlotFileType fileType) = 0;

	protected:
		bool                  m_markPoints;     ///< Set true if individual pouints on the trace should be marked with symbols.
		string                m_title;          ///< The main title.
		string                m_subTitle;       ///< the sub-title.
	};
}
#endif // !defined(AFX_SKEWTADAPTER_H__5813CCC1_D1A4_11D2_B5B6_ED3B095D6882__INCLUDED_)
