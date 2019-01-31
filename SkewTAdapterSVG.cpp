/************************************************************************\
	Copyright 2008 University Corporation for Atmospheric Research.
	All rights reserved.
	Use of this code is subject to UCAR's standard Terms of Use,
	which can be found at http://www.ucar.edu/legal/terms_of_use.shtml .
	By using this source code, you agree to abide by those Terms of Use.
\*************************************************************************/

// SkewTAdapterSVG.cpp: implementation of the SkewTAdapterSVG class.
//
//////////////////////////////////////////////////////////////////////

#include <sstream>
#include "SkewTAdapterSVG.h"
#include "SkewT/SkewTdefs.h"
using namespace skewt;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SkewTAdapterSVG::SkewTAdapterSVG(std::ostream& file,
                                 int height,
                                 int width,
                                 int symbolSize) :
    _firstLineCall(true),
    _symbolSize(symbolSize),
    _pSkewT(0),
    _ready(false),
    _height(height),
    _width(width),
    _file(file)
{
}

//////////////////////////////////////////////////////////////////////
SkewTAdapterSVG::~SkewTAdapterSVG() {
    for (unsigned int i = 0; i < _pLines.size(); i++)
        delete _pLines[i];
}

//////////////////////////////////////////////////////////////////////
void SkewTAdapterSVG::line(double x1,
                           double y1,
                           double x2,
                           double y2,
                           unsigned int colorCode,
                           SkewTAdapter::LineType lineType) {

    // create polyline elements from the specified line segments. Save the polyline, and draw it.

    // The incoming segments are examined. If the color and line type don't change, and the end of
    // one segment matches the beginning of the next segment, the segments are consolidated into 
    // a single polyline.

    if (_firstLineCall) {
        _firstLineCall = false;
        _xvals.push_back(x1);
        _yvals.push_back(y1);
        _lastColorCode = colorCode;
    } else {
        if ((_lastX2 != x1) || (_lastY2 != y1) || colorCode != _lastColorCode) {

            _xvals.push_back(_lastX2);
            _yvals.push_back(_lastY2);

            SkewTSVGPolyline* pl = new SkewTSVGPolyline(_xvals, _yvals, _width, _height, colorCode);
            _pLines.push_back(pl);

            //      int h = _height;
            //      int w = _width;

            //      QPainter painter(this);
            //      pl->draw(painter, w, h);
            //      painter.end();

            _xvals.clear();
            _yvals.clear();
            _xvals.push_back(x1);
            _yvals.push_back(y1);
            _lastColorCode = colorCode;
        } else {
            _xvals.push_back(x1);
            _yvals.push_back(y1);
        }
    }
    _lastX2 = x2;
    _lastY2 = y2;

}

//////////////////////////////////////////////////////////////////////
void SkewTAdapterSVG::Text(const std::string &s,
                           const double x,
                           const double y,
                           unsigned int colorCode) {

    if (s.size() == 0)
        return;

    const char* label = s.c_str();

    // set the alignment, if the alignment codes are given as the 
    // first two characters of the text. They can be : |r, |c or |l
    SkewTSVGText::AlignType alignFlag = SkewTSVGText::AlignCenter;
    if (s[0] == '|') {
        // alignment flags can be any combination of 
        // AlignLeft, AlignRight, AlignTop, AlignBottom, AlignHCenter, AlignVCenter, AlignCenter
        // we have a formatting code at the beginning
        if (s.size() == 1)
            return;
        // we have the alignment codes, so skip past them for the labelling.
        label += 2;
        switch (s[1]) {
        case 'r':
            alignFlag = SkewTSVGText::AlignRight;
            break;
        case 'c':
            alignFlag = SkewTSVGText::AlignCenter;
            break;
        case 'l':
            alignFlag = SkewTSVGText::AlignLeft;
            break;
        default:
            break;
        }
    }

    // set the label color
    //QPen qpen(getQColor(colorCode), 1);

    // create the text graphic element
    std::string slabel(label);
    SkewTSVGText t(slabel, x, y, _width, _height, alignFlag, colorCode);

    // save it
    _texts.push_back(t);

    // int h = _height;
    // int w = _width;

    // and draw it
    //QPainter painter(this);
    //t.draw(painter, w, h);
    //painter.end();

}

//////////////////////////////////////////////////////////////////////
void SkewTAdapterSVG::init() {
    for (unsigned int i = 0; i < _pLines.size(); i++)
        delete _pLines[i];

    _pLines.clear();

    _tdryPoints.clear();

    _dpPoints.clear();

    _texts.clear();

    _symbols.clear();

    _ready = false;

}

//////////////////////////////////////////////////////////////////////
void SkewTAdapterSVG::setSkewT(SkewT* pSkewT) {
    _pSkewT = pSkewT;
}

//////////////////////////////////////////////////////////////////////
void SkewTAdapterSVG::addTdry(double x,
                              double y) {

    // create the datum
    SkewTSVGDatum t(x, y, _width, _height, _symbolSize, SKEWT_RED);

    // save it
    _tdryPoints.push_back(t);

    // int h = _height;
    // int w = _width;

    // and draw it
    //QPainter painter(this);
    //t.draw(painter, w, h);
    //painter.end();

}

//////////////////////////////////////////////////////////////////////
void SkewTAdapterSVG::addDp(double x,
                            double y) {

    // create the datum
    SkewTSVGDatum t(x, y, _width, _height, _symbolSize, SKEWT_BLUE);

    // save it
    _dpPoints.push_back(t);

    // int h = _height;
    // int w = _width;

    // and draw it
    //QPainter painter(this);
    //t.draw(painter, w, h);
    //painter.end();

}

//////////////////////////////////////////////////////////////////////
void SkewTAdapterSVG::drawElements() {

    // redraw all of the graphic elements.

    int h = _height;
    int w = _width;

    SkewTSVGText title(_title, 0.5, 0.96, w, h, SkewTSVGText::AlignHCenter, 
    SKEWT_BLUE, 1.5);

    SkewTSVGText subTitle(_subTitle,
                           0.5,
                           0.93,
                          w,
                          h,
                          SkewTSVGText::AlignHCenter,
                           SKEWT_BLUE,
                          1.25);

    _file << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n";
    _file << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"";
    _file << "  \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n";
    _file << "<svg \n";
    _file << "  xmlns=\"http://www.w3.org/2000/svg\"";
    _file << " version=\"1.0\"";
    _file << " width=\"" << w << "\"";
    _file << " height=\"" << h << "\"";
    _file << ">\n";

    _file << title.draw();

    _file << subTitle.draw();

    for (unsigned int i = 0; i < _pLines.size(); i++) {
        _file << _pLines[i]->draw();
    }

    for (unsigned int j = 0; j < _tdryPoints.size(); j++) {
        _file << _tdryPoints[j].draw();
    }

    for (unsigned int d = 0; d < _dpPoints.size(); d++) {
        _file << _dpPoints[d].draw();
    }

    for (unsigned int t = 0; t < _texts.size(); t++) {
        _file << _texts[t].draw();
    }

    for (unsigned int s = 0; s < _symbols.size(); s++) {
        _file << _symbols[s].draw();
    }

    _file << "</svg>\n";

}

//////////////////////////////////////////////////////////////////////
void SkewTAdapterSVG::draw_finished() {

    _ready = true;
    drawElements();

}

//////////////////////////////////////////////////////////////////////
void SkewTAdapterSVG::maximize() {
}

//////////////////////////////////////////////////////////////////////
void SkewTAdapterSVG::unzoom() {
    init();
}

//////////////////////////////////////////////////////////////////////
void SkewTAdapterSVG::extents(double &xmin,
                              double &xmax,
                              double &ymin,
                              double &ymax) {
    xmin = 0;
    ymin = 0;
    xmax = _width;
    ymax = _height;
}

//////////////////////////////////////////////////////////////////////
void SkewTAdapterSVG::symbol(double x,
                             double y,
                             unsigned int colorCode,
                             SymType st) {
    // create the datum
    SkewTSVGDatum t(x, y, _width, _height, _symbolSize, colorCode);

    // save it
    _symbols.push_back(t);

    // int h = _height;
    // int w = _width;

    // and draw it
    //QPainter painter(this);
    //t.draw(painter, w, h);
    //painter.end();

}

//////////////////////////////////////////////////////////////////////
void SkewTAdapterSVG::title(std::string s) {
    _title = s;

    SkewTSVGText title(s,
                        0.50,
                        0.98,
                       _width,
                       _height,
                       SkewTSVGText::AlignCenter,
                        SKEWT_BLUE);
}

//////////////////////////////////////////////////////////////////////
void SkewTAdapterSVG::subTitle(std::string s) {
    _subTitle = s;
    SkewTSVGText subTitle(s,
                           0.50,
                           0.94,
                          _width,
                          _height,
                          SkewTSVGText::AlignCenter,
                           SKEWT_BLUE);
}

//////////////////////////////////////////////////////////////////////
double SkewTAdapterSVG::aspectRatio() {
    int h = _height;
    int w = _width;

    if (w == 0)
        return 0.0;

    return ((double)h)/((double) w);
}

//////////////////////////////////////////////////////////////////////
void SkewTAdapterSVG::markPoints(bool flag) {
}

//////////////////////////////////////////////////////////////////////
void SkewTAdapterSVG::savePlot(std::string path,
                               int xPixels,
                               int yPixels,
                               PlotFileType fileType) {
}

//////////////////////////////////////////////////////////////////////
void SkewTAdapterSVG::removeElements() {

    for (unsigned int i = 0; i < _pLines.size(); i++)
        delete _pLines[i];
    _pLines.clear();

    _tdryPoints.clear();

    _dpPoints.clear();

    _symbols.clear();

    _texts.clear();

}

//////////////////////////////////////////////////////////////////////
void SkewTAdapterSVG::print() {

}

//////////////////////////////////////////////////////////////////////
std::string SkewTAdapterSVG::colorName(unsigned int code) {
    switch (code) {
    case SKEWT_RED:
        return "red";
    case SKEWT_GREEN:
        return "green";
    case SKEWT_BLUE:
        return "blue";
    case SKEWT_GREY:
        return "grey";
    case SKEWT_BLACK:
    default:
        return "black";
    }
}

//////////////////////////////////////////////////////////////////////
SkewTSVGPolyline::SkewTSVGPolyline(std::vector<double> x,
                                   std::vector<double> y,
                                   int w,
                                   int h,
                                   unsigned int colorCode) :
    _x(x), _y(y), _w(w), _h(h),
            _colorName(SkewTAdapterSVG::colorName(colorCode)) {

}

//////////////////////////////////////////////////////////////////////
SkewTSVGPolyline::~SkewTSVGPolyline() {
}

//////////////////////////////////////////////////////////////////////
std::string SkewTSVGPolyline::draw() {

    std::string result;

    // draw a polyline, using our collected points.
    int nPoints = _x.size();

    result = "<path d=\n";
    result += "\"M ";
    for (int i = 0; i < nPoints; i++) {
        double x;
        double y;
        x = (_w * _x[i]);
        y = (_h - _h*_y[i]);
        std::ostringstream s;
        s << x << " " << y;
        result += s.str();
        if (i != nPoints-1) {
            result += "\nL ";
        }
    }
    result += "\"\n";
    result += "stroke=\"" + color()
            + "\" stroke-width=\"0.5\" fill=\"none\" />\n";

    return result;
}
//////////////////////////////////////////////////////////////////////
std::string SkewTSVGPolyline::color() {
    return _colorName;
}
//////////////////////////////////////////////////////////////////////
SkewTSVGText::SkewTSVGText(std::string text,
                           double x,
                           double y,
                           int w,
                           int h,
                           SkewTSVGText::AlignType alignFlag,
                           unsigned int colorCode,
                           double fontScale) :
    _text(text), _x(x), _y(y), _w(w), _h(h), _alignFlag(alignFlag),
            _colorName(SkewTAdapterSVG::colorName(colorCode)),
            _fontSize(DEFAULTSVGFONTSIZE*fontScale) {
}

//////////////////////////////////////////////////////////////////////
SkewTSVGText::~SkewTSVGText() {
}

//////////////////////////////////////////////////////////////////////
std::string SkewTSVGText::draw() {

    double x = _w * _x;
    double y = _h - _h*_y;

    std::string anchor;
    // adjust according to the alignment flags

    if (_alignFlag & SkewTSVGText::AlignRight)
        anchor = " text-anchor=\"right\" ";

    if ((_alignFlag & SkewTSVGText::AlignHCenter) ||
    		(_alignFlag & SkewTSVGText::AlignCenter))
        anchor = " text-anchor=\"middle\" ";

    //    if (_alignFlag & SkewTSVGText::AlignTop)
    //        dy -= 1.0;

    //    if (_alignFlag & SkewTSVGText::AlignVCenter || _alignFlag
    //            & SkewTSVGText::AlignCenter)
    //        dy -= 1.0;

    std::ostringstream s;
    s << "<text" << " x=\"" << x << "\"" << " y=\"" << y << "\""
            << " font-size=\"" << _fontSize << "\" fill=\"" << _colorName
            << "\"" << anchor << ">";
    s << _text << "</text>\n";

    return s.str();
}
//////////////////////////////////////////////////////////////////////
std::string SkewTSVGText::color() {
    return _colorName;
}
//////////////////////////////////////////////////////////////////////
SkewTSVGDatum::SkewTSVGDatum(double x,
                             double y,
                             int w,
                             int h,
                             int size,
                             unsigned int colorCode) :
    _x(x), _y(y), _w(w), _h(h), _size(size),
            _colorName(SkewTAdapterSVG::colorName(colorCode)) {
}

//////////////////////////////////////////////////////////////////////
SkewTSVGDatum::~SkewTSVGDatum() {
}

//////////////////////////////////////////////////////////////////////
std::string SkewTSVGDatum::draw() {

    // symbol radius
    double r = _size/2;

    double x = (_w * _x);
    double y = (_h - _h*_y);

    std::ostringstream s;

    s << "<circle cx=\"" << x << "\" cy=\"" << y << "\" r=\"" << r
            << "\" stroke=\"none\" fill=\"" << color() << "\"/>\n";

    return s.str();

}

//////////////////////////////////////////////////////////////////////
std::string SkewTSVGDatum::color() {
    return _colorName;
}

