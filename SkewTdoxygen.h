/************************************************************************\
	Copyright 2008 University Corporation for Atmospheric Research.
	All rights reserved.
	Use of this code is subject to UCAR's standard Terms of Use,
	which can be found at http://www.ucar.edu/legal/terms_of_use.shtml .
	By using this source code, you agree to abide by those Terms of Use.
\*************************************************************************/

/** \page SkewToverview SkewT Overview
 * \section SkewTintroduction SkewT Introduction
 * 
 * SkewT provides a generic implementation of the aerological diagram 
 * which utilizes a skewed temperature scale for the horizontal axis and 
 * an inverted logrithmic pressure scale for the vertical axis. For a
 * good reference on aerological diagrams, see:
 * J. V. Iribarne and W. L. Godson, <i>Atmospheric Thermodynamics</i>,
 * D. Reidel, Boston (1973).
 *
 * SkewT formulates the diagram in a virtual coordinate space, and then
 * calls a class derived from SkewTAdapter, to render the diagram 
 * for a particular graphics environment. Example enviroments might be
 * Trolltech Qt, or a Microsoft Windows graphing component.
 *
 * The only data required by SkewT are pressure, temperature, 
 * relative humidity, wind speed and wind direction.
 *
 * The functionality of SkewT is somewhat dependent upon the SkewTAdapter,
 * which is correspondingly dependent on the graphics subsystem that it is
 * designed for. In some cases, all of the graph data must be provided at 
 * construction time, and a static graph will be created. In other cases, 
 * a "real-time" update mode is possible, where data points may be incrementally
 * added to the graph. 
 * 
 * \section SkewTusage SkewT Usage
 *
 * To create a SkewT, the user first creates an appropriate SkewTAdapter. 
 * The adapter is then provided to the SkewT constructor. Arrays of data 
 * can optionally be provided at construction time, along with 
 * labelling information.
 *
 * After construction, the graph is drawn by calling SkewT::draw(). If the adapter supports 
 * real-time updates, SkewT::drawTdry(double pres, double tdry) and 
 * SkewT::drawDp(double pres, double tdry, double RH) can be called to 
 * add data points to the plot.
 * 
 * The SkewT::print(), SkewT::maximize(), SkewT::zoomin(), and SkewT::unzoom()
 * methods will call the corresponding methods in the adapter. It is up to the 
 * adapter implementation as to whether or not these functions are supported.
 *
 * @todo SkewT::drawDp(double pres, double tdry, double RH) should really be changed 
 * to drawRH() in order to maintain consistency with the constructor.
 * 
 *
 * \section SkewTinternals How It Works
 *
 * SkewT thinks of the drawing area as a rectilinear "page", with x and y coordinates 
 * spanning 0.0 to 1.0. Upon this page there can be multiple rectangles (Rect),
 * occupying a fraction of the main drawing page, and 
 * each having its own x and y virtual coordinate space spanning 0.0 to 1.0. The 
 * rectangles allow the page to be broken up into  independent areas for the thermodynamic 
 * data, the wind barbs, and labelling.
 *
 * The only way to draw on the SkewT page is through a Rect. It provides 
 * methods for drawing symbols, text, and lines. It will also perform clipping 
 * on a line draw request, and only render the segment within the rectangle. This
 * is very useful when drawing the weird and wonderful isopleths that make up  a
 * skewt. The user of the rectangle can assume a much larger drawing area, based on
 * a physical (e.g. thermodynamic) range, and let the Rect constrain the
 * drawing to fall within the rectangle. Note that multiple Rect objects can
 * be drawing on the same page area of the graph. Rect calls the SkewTAdapter
 * to perform the drawing.
 *
 * Classes derived from Rect implement coordinate transformations. For instance,
 * PresRect (derived from Rect) transforms a pressure coordinate into 
 * a logrithmic y value. SkewTRect (derived from PresRect) transforms
 * a temperature coordinate into an x coordinate, and passes the pressure coordinate onto
 * PresRect.
 *
 * Classes derived from Rect (or more typically, its subclasses) are used 
 * to draw families of objects, such as adiabats, isotherms, isopleths of mixing
 * ration, and so on.
 *
 * For the most part, the SkewTAdapter does not know much about what it is drawing; i.e. it
 * implements drawing primatives for simple objects such as lines, text and symbols.
 * However, there are member functions that are called to render the actual temperature and
 * dewpoint data. This is because some graphics packages will have higher level 
 * abstractions for data curves, and the adapter may wish to take advantage of this
 * functionality. A SkewTtrace collects data values, and will iteratively call the
 * corresponding temperature or dewpoint drawing method.
 *
 * The major components contained within a completed SkewT are:
 * <ul>
 * <li> A number of objects derived from SkewTRect, used to render the various 
 * isopleths.
 * <li> Two SkewTtrace objects, for the temperature and dewpoint traces.
 * <li> A WindBarbs object, which will draw the wind barbs.
 * <li> A reference to a SkewTAdapter.
 * </ul>
 * 
 * 
 */
