/************************************************************************\
	Copyright 2008 University Corporation for Atmospheric Research.
	All rights reserved.
	Use of this code is subject to UCAR's standard Terms of Use,
	which can be found at http://www.ucar.edu/legal/terms_of_use.shtml .
	By using this source code, you agree to abide by those Terms of Use.
\*************************************************************************/

// SkewTAdapterSVG.h: interface for the SkewTAdapterSVG class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(SkewTAdapterSVG_INCLUDED_)
#define SkewTAdapterSVG_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <string>
#include <fstream>

#include "SkewT/SkewT.h"
#include "SkewT/SkewTAdapter.h"

namespace skewt {

#define DEFAULTSVGFONTSIZE 12

class SkewTSVGDatum;
class SkewTSVGPolyline;
class SkewTSVGText;

/**
 * This implementation of SkewTAdapter draws the SkewT using SVG.
 * SkewTAdapterSVG is derived from SkewTAdapter.
 *
 * At the heart of this adapter, all drawing activities are broken down into a small
 * number of graphic elements. These are strictly graphic constructs; SkewTAdapterSVG
 * really has very little (but some) specialized knowledge of what a skew-t graph is.
 *
 * All coordinates are given as a value between 0 and 1. Whenever drawing takse place, 
 * these are converted to screen coordinates through scaling by the height or
 * width.
 *
 * The elements that are stored within SkewTAdapterSVG are:
 *<ul>
 *<li> Texts: strings for labelling anything on the graph
 *<li> Polylines: arbitrary lines with specified color and characteristics.
 * These are used for isopleths and any other fixed lines.
 *<li> Tdry points: A collection of temperature values to be plotted as the temperature trace.
 *<li> DP points: A collection of dew point values to be plotted as the dew point trace.
 *</ul>
 *
 * SkewTAdapterSVG defines some helper classes (SkewTSVGText, SkewTSVGPolyline, and
 * SkewTSVGDatum) which facilitate the storage and rendering of the graphic elements.
 * Lists of these elemnts are managed by standard STL containers.
 *
 */
class SkewTAdapterSVG : public SkewTAdapter {
    public:
        /**
         * Construct the adapter. 
         * @param heght The plot height
         * @param width The plot width
         * @param symbolSize The size, in pixels, that symbols will be drawn at.
         */
        SkewTAdapterSVG(std::ostream& file,
                        int height,
                        int width,
                        int symbolSize = 5);

        /**
         * Destructor
         */
        ~SkewTAdapterSVG();

        void addDp(double x,
                   double y);

        void addTdry(double x,
                     double y);

        void markPoints(bool flag);

        double aspectRatio();

        void subTitle(std::string s);

        void title(std::string s);

        void symbol(double x,
                    double y,
                    unsigned int color,
                    SymType st = SmallPlus);

        void Text(const std::string& s,
                  const double x,
                  const double y,
                  unsigned int color);

        void extents(double& xmin,
                     double& xmax,
                     double& ymin,
                     double& ymax);

        void unzoom();

        void maximize();

        void draw_finished();

        void init();

        void print();

        unsigned int  getSymbolSize() {
            return _symbolSize;
        }
        void setSymbolSize(int s) {
            _symbolSize = s;
        }

        /**
         * This function is clever. It tracks the incoming requests,
         * and consolidates them into a single polyline when  possible.
         */
        void line(double x1,
                  double y1,
                  double x2,
                  double y2,
                  unsigned int colorCode,
                  SkewTAdapter::LineType lineType = SkewTAdapter::SolidLine);

        void savePlot(std::string path,
                      int xPixels,
                      int yPixels,
                      PlotFileType fileType);

        void setSkewT(SkewT* pSkewT);

        /// @param code The color code from SkewTdefs.h
        /// @returns A string with the color name corresponding to the
        /// skewt color definitions found in SkewTdefs.h. If an unrecognized 
        /// code is received, black is returned.
        static std::string colorName(unsigned int code);
        
    protected:

        /**
         * draw all of the graphic elements.
         */
        void drawElements();
        /**
         * remove all of the graphic elements.
         */
        void removeElements();

        std::vector<SkewTSVGText> _texts; ///< Text graphic elements
        std::vector<SkewTSVGPolyline*> _pLines; ///< Polyline graphic elements. (Note that these are pointers, and so must be deleted during destruction).
        std::vector<SkewTSVGDatum> _tdryPoints; ///< Tdry datum graphic elements
        std::vector<SkewTSVGDatum> _dpPoints; ///< Dew point datum graphic elements
        std::vector<SkewTSVGDatum> _symbols; ///< Symbol datum graphic elements
        std::string _title; ///< The title text; appears top center, first line.
        std::string _subTitle; ///< The sub title text, appears top center, second line

        unsigned int _lastColorCode; ///< Used by the line() function, to detect a change in a line color. and thus complete a polyline.
        bool _firstLineCall; ///< Set true before line() has been called; Use to initialize the consolidation algorithm within line().
        double _lastX2; ///< Used by the line() function, to detect a change in a break in the line. and thus complete a polyline.
        double _lastY2; ///< Used by the line() function, to detect a change in a break in the line. and thus complete a polyline.
        std::vector<double> _xvals; ///< USed by line() to accumlate x values.
        std::vector<double> _yvals; ///< Used by line() to accumlate y values.

        int _symbolSize; ///< the edge length of a symbol, for tdry and dp points, in pixels
        SkewT* _pSkewT; ///< Set to the SkewT that we are controlling, if zooming is desired. Null otherwise.

        bool _ready; ///< Set true after SkewT calls draw_finished(). 

        int _alignFlag; ///< Current alignment

        int _height; ///< Plot height
        int _width; ///< Plot width
        

        std::ostream& _file;
};
/**
 * A text graphic element.
 */
class SkewTSVGText {

    public:
        enum AlignType {AlignLeft, AlignRight, AlignCenter, AlignHCenter, AlignTop, AlignVCenter};
        /**
         * Constructor.
         * @param text The text.
         * @param x coordinate, in relative space (0-1)
         * @param y Y coordinate, in relative space  (0-1)
         * @param width The width of the drawing area.
         * @param height The height of the drawing area.
         * @param colorCode The color code, from SkewTdefs.h
         * @parameter fontScale An optional font size scaling factor
         */
        SkewTSVGText(std::string text,
                     double x,
                     double y,
                     int w,
                     int h,
                     AlignType alignFlag,
                     unsigned int colorCode,
                     double fontScale = 1.0);
        /**
         * Default constructor
         */
        //          SkewTSVGText();
        /**
         * Destructor
         */
        virtual ~SkewTSVGText();
        /** 
         * Draw the text.
         * @param x coordinate, in relative space (0-1)
         * @param y Y coordinate, in relative space  (0-1)
         * @param width The width of the drawing area.
         * @param height The height of the drawing area.
         * @returns The SVG drawing commands.
         */
        std::string draw();
        /**
         * @returns The color name
         **/
        std::string color();
        
    protected:
        std::string _text;
        double _x;        ///< x coordinate, in relative space (0-1)
        double _y;        ///< y coordinate, in relative space (0-1)
        int _w;           ///< width of the drawing area
        int _h;           ///< height of the drawing area
        AlignType _alignFlag;
        std::string _colorName; ///< The color name
        double _fontSize; ///< The desired font size

};
/**
 * A polyline graphic element. It contains a series of points which will
 * be connected by a line,
 */
class SkewTSVGPolyline {
    public:
        /**
         * Constructor.
         * @param x coordinate, in relative space (0-1)
         * @param y Y coordinate, in relative space  (0-1)
         * @param width The width of the drawing area.
         * @param height The height of the drawing area.
         * @param colorCode The color code, from SkewTdefs.h
         */
        SkewTSVGPolyline(std::vector<double> x,
                         std::vector<double> y,
                         int w,
                         int h,
                         unsigned int colorCode);
        /**
         * Destructor
         */
        virtual ~SkewTSVGPolyline();
        /** 
         * Draw the polyline.
         * @param width The width of the drawing area.
         * @param height The height of the drawing area.
         * @returns The SVG drawing commands.
         * @todo Implement dashed line drawing.
         */
        std::string draw();
        /**
         * @returns The color name
         **/
        std::string color();
    protected:
        std::vector<double> _x; ///< The x values.
        std::vector<double> _y; ///< The y values.
        int _w;           ///< width of the drawing area
        int _h;           ///< height of the drawing area
        std::string _colorName; ///< The color name
        
};

/**
 * A graphic element, used to represent a data point. A collection 
 * of SkewTSVGDatum will represent the tdry trace; another collection
 * will represent the dew point trace.
 */
class SkewTSVGDatum {
    public:
        /**
         * Constructor.
         * @param x coordinate, in relative space (0-1)
         * @param y Y coordinate, in relative space  (0-1)
         * @param width The width of the drawing area.
         * @param height The height of the drawing area.
         * @param size The size of the symbol, in pixels.
         * @param colorCode The color code, from SkewTdefs.h
         */
        SkewTSVGDatum(double x,
                      double y,
                      int w,
                      int h,
                      int size,
                      unsigned int colorCode);
        /**
         * Destructor.
         */
        virtual ~SkewTSVGDatum();
        /** 
         * Draw the datum.
         * @param width The width of the drawing area.
         * @param height The height of the drawing area.
         * @returns The SVG drawing commands.
         */
        std::string draw();
        /**
         * @returns The color name
         **/
        std::string color();
    protected:
        double _x;        ///< x coordinate, in relative space (0-1)
        double _y;        ///< y coordinate, in relative space (0-1)
        int _w;           ///< width of the drawing area
        int _h;           ///< height of the drawing area
        int _size; ///< The size of the symbol, in pixels
        std::string _colorName; ///< The color name
        
};

}

#endif 
