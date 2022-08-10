/************************************************************************\
	Copyright 2008 University Corporation for Atmospheric Research.
	All rights reserved.
	Use of this code is subject to UCAR's standard Terms of Use,
	which can be found at http://www.ucar.edu/legal/terms_of_use.shtml .
	By using this source code, you agree to abide by those Terms of Use.
\*************************************************************************/

// Rect.h: interface for the Rect class.
//
//////////////////////////////////////////////////////////////////////

#ifndef RECT_H
#define RECT_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "SkewTdefs.h"
#include "SkewTAdapter.h"

#include <cmath>
#include <string>

#define RED    RGB(255,0,0)
#define GREEN  RGB(0,200,0)
#define BLUE   RGB(0,0,200)
#define YELLOW RGB(255,255,0)
#define BROWN  0xCC9933
#define WHITE  RGB(255,255,255)
#define BLACK  RGB(0,0,0)
#define GREY   RGB(100,100,100)
#define LTGREY RGB(128,128,128)

namespace skewt {
	/**
	* Rect implements a virtual rectangle on the drawing page. 
	* The drawing page area is specified by boundaries 
	* in the range 0 and 1. Likewise, reference to locations
	* within the Rect are specified by coordinates in the range 0 to 1. 
	*
	* Rect is a virtual drawing class; it calls a SkewTAdapter to
	* actually render the drawing on a particular graphics component.
	*
	* Primatives are provided for drawing lines, symbols and text.
	* Lines can be automatically clipped to fall within the rectangle.
	* The clipping algorithm is really cool.
	*
	* Rect distinguishes drawing temperature and dewpoint data points
	* from the other graphic primitives, so that these requests can be passed
	* on and managed by the SkewTAdapter.
	*
	* Rect can be asked to save the endpoints of a clipped line, and provide them
	* so that labelling can be positioned in relation to the actually drawn line.
	*
	* <h3>The Clipping Algorithm</h3>
	* The clipping algorithm is assisted by the outcode class. Rect::outcode 
	* relates a point to the Rect, and can idicate whether a point is inside or outside of the Rect. If outside, 
	* Rect::outcode knows which boundary or boundaries the point is adjacent to.
	* 
	* To clip a line so that it is constrained within the Rect, the algorithm proceeds as follows:
	* <ul>
	* <li> If both endpoints of the line are outside of the Rect, and adjacent to the same boundary,
	* the line does not intersect the Rect.
	* <li> If both endpoints are within the Rect, the line does not need to be clipped.
	* <li> At this point, it is established that either: a) one endpoint is within the Rect, and one endpoint is outside, or
	* b) Both endpoints are outside of the boundary, and the line crosses the Rect. Iterate around the four sides of the 
	* Rect, looking for the intersection of the boundary and the line. Clip the line at these intersections. This is repeated 
	* a second time, for the new line, so that the possible second intersection is clipped.
	* </ul>
	*/
	class Rect
	{
	public:
		/**
		* Line types
		*/
		enum LineType {SolidLine, DashedLine};
		/**
		* Symbol types
		*/
		enum SymType {SmallPlus, SmallDot};

		/**
		* The coordinates of a point referenced to the coordinate system of this Rect.
		*/
		class point 
		{
		public:
			/**
			* Default constructor
			*/
			point();
			/**
			* @param x X coordinate
			* @param y Y coordinate
			*/
			point(double x, double y);
			/**
			* X coordinate
			*/
			double x;
			/**
			* Y coordinate
			*/
			double y;
		};
		/**
		* Contains two points specifying the endpoints of a line.
		*/
		class line 
		{
		public:
			/**
			* Default constructor
			*/
			line();
			/**
			* @param start Starting point of the line.
			* @param end Ending point of the line.
			*/
			line(point start, point end);
			/**
			* Starting point of the line.
			*/
			point p1;
			/**
			* Ending point of the line.
			*/
			point p2;
		};
		/**
		* This class relates a Rect::point to the boundaries of Rect.
		* It is used in the line clipping operation. If the point lies outside of 
		* a given boundary of the Rect, the corresponding codebit is set. If
		* all codebits are zero, then the point lies within the rectangle.
		* Similarly, if any of the codebits are set, the point is outside of the
		* Rect.
		* 
		*/
		class outcode
		{
			/**
			* A structure which records the boundaries of the Rect that
			* the point is outside of. For instance, if the point is outside
			* of the lower Y boundary, c2 will be set. Note that up to two 
			* codebits can be set.
			*/
			struct codebits {
				unsigned int c1: 1; ///< Set if Y is greater than Rect::m_ymax
				unsigned int c2: 1; ///< Set if Y is less than Rect::m_ymin
				unsigned int c3: 1; ///< Set if X is greater than Rect::m_xmax
				unsigned int c4: 1; ///< Set if X is less than Rect::m_xmin
			};
		public:
			/**
			* Default constructor.
			*/
			outcode();
			/**
			* Create the outcode for the specified point and Rect.
			* @param p The point
			* @param s The Rect that the point will be related to.
			*/
			outcode(point p, Rect& s);
			/**
			* OR() examines all of the codebits, and if any of them indicates that the
			* point is outside of the Rect, true is returned.
			* @returns True if the point is outside of the Rect.
			*/
			bool OR();
			/**
			* Compare my outcode with another outcode.
			* @returns True if my outcode and the other outcode are both outside of Rect,
			* and on the same side of the boundary. This indicates that the line is completely
			* outside of the Rect.
			*/
			bool reject(outcode &o);
			/**
			* Compare my outcode with another outcode.
			* @returns True if the outcodes indicate that both points are within the Rect, and
			* so the line is contained within the Rect.
			*/
			bool accept(outcode &o);
			/**
			*
			*/
			codebits code;
		};
		friend class outcode;
		/**
		* Define the limits that this Rect covers on the drawing page.
		*
		* xmin, xmax, ymin and ymax will run between 0 and 1 in the 
		* available graphing area.
		* @param adapter The adapter that renders this Rect on the graphics component.
		* @param xmin Left extent of the Rect on the graphics page.
		* @param xmax Right extent of the Rect on the graphics page.
		* @param ymin Bottom extent of the Rect on the graphics page.
		* @param ymax Top extent of the Rect on the graphics page.
		*/
		Rect(SkewTAdapter &adapter,
			double xmin,
			double xmax,
			double ymin,
			double ymax);

		virtual ~Rect();

	private:
		/**
		* The adapter that renders this Rect on the graphics component.
		*/
		SkewTAdapter& m_adapter;
		/**
		* Left extent of the Rect on the graphics page.
		*/
		double m_pageXmin;
		/**
		* Top extent of the Rect on the graphics page.
		*/
		double m_pageYmax;
		/**
		* Bottom extent of the Rect on the graphics page.
		*/
		double m_pageYmin;
		/**
		* Right extent of the Rect on the graphics page.
		*/
		double m_pageXmax;

		/**
		* Left limit of the x coordinate within this Rect.
		*/
		double m_xmin;
		/**
		* Right limit of the x coordinate within this Rect.
		*/
		double m_xmax;
		/**
		* Bottom limit of the x coordinate within this Rect.
		*/
		double m_ymax;
		/**
		* Top limit of the x coordinate within this Rect.
		*/
		double m_ymin;

	public:
		/**
		* Call the graphics adapter, to add a dewpoint point at the specified location.
		* @param x The x coordinate.
		* @param y The y coordinate.
		*/
		void addDp(double x, double y);
		/**
		* Call the graphics adapter, to add a temperature point at the specified location.
		* @param x The x coordinate.
		* @param y The y coordinate.
		*/
		void addTdry(double x,double y);
		/**
		* Determine the aspect ratio of the SkewTAdapter: width/height
		* @returns The aspect ratio.
		*/
		double aspectRatio();
		/**
		* Draw the text.
		* @param s The text to be drawn
		* @param p0 The point to draw it at.
		* @param color The color of the text.
		* @todo create a named color enumeration for SkewT.
		*/
		void Text(const std::string& s, const point p0, unsigned int color);
		/**
		* Draw the specified line. Clip it if requested.
		* @param l The line to be drawn.
		* @param color The color of the line.
		* @param lineType The line type.
		* @param doClip Set true if the line is to be clipped within this Rect.
		*/
		void drawLine(line l, unsigned int color = SKEWT_BLACK, LineType lineType = SolidLine, bool doClip = 1);
		/**
		* Draw the specified symbol
		* @param pp The point at which the symbol should be drawn.
		* @param color The color of the symbol.
		* @param st The symbol type.
		*/
		void symbol(point pp, unsigned int color, SymType st = SmallPlus);
		/**
		* Return the first endpoint of the clipped line.
		* @param p1 The endpoint, if available, will be returned here
		* @returns Return true if the point is available, false otherwise.
		*/
		bool firstP1(point& p1);
		/**
		* Return the lst endpoint of the clipped line.
		* @param p2 The endpoint, if available, will be returned here
		* @returns Return true if the point is available, false otherwise.
		*/
		bool lastP2(point& p2);
		/**
		* Reset the saving of the first endpoint of a clipped line,
		*/
		void resetFirstP1();
		/**
		* Reset the saving of the last endpoint of a clipped line,
		*/
		void resetLastP2();
		/**
		* Convert the endpoint coodinates of the line from Rect coordinates to the coordinates of the graphics page.
		* @param l the line to be converted.
		*/
		void convertToPage(line& l);
		/**
		* Convert the coodinates of the point from Rect coordinates to the coordinates of the graphics page.
		* @param p The point to be converted.
		*/
		void convertToPage(point& p);
		/**
		* Clip the line so that the endpoints fall within the Rect boundaries.
		* @param l The line to be clipped.
		*/
		bool clip(line& l);
		/**
		* The coordinates of the first point of a clipped line.
		*/
		point m_firstP1;
		/**
		* The coordinates of the last point of a clipped line.
		*/
		point m_lastP2;
		/**
		* Set true if we have the coordinates of the first point of a clipped line.
		*/
		bool m_haveFirstP1;
		/**
		* Set true if we have the coordinates of the last point of a clipped line.
		*/
		bool m_haveLastP2;
	};
}
#endif // !defined(AFX_RECT_H__71547560_DE0C_11D2_B034_00C04FA30B92__INCLUDED_)
