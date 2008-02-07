//
//
// $Id: Rect.cpp,v 1.12 2005/06/12 02:12:13 martinc Exp $
//
//////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2003
// University Corporation for Atmospheric Research, UCAR
//
// Permission to use, copy, modify, distribute and sell this software and
// its documentation for any purpose is hereby granted without fee,
// provided that the above copyright notice appear in all copies and that
// both that copyright notice and this permission notice appear in
// supporting documentation.  UCAR makes no representations about the
// suitability of this software for any purpose.  It is provided "as is"
// without express or implied warranty.
// 
// Note from the author:
//
// Where possible, you are encouraged to follow the GNU General Public
// License, or at least the spirit of the license, for the distribution and
// licensing of this software and any derived works.  See
// http://www.gnu.org/copyleft/gpl.html.
//

// Rect.cpp: implementation of the Rect class.
//
//////////////////////////////////////////////////////////////////////

#include "Rect.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace skewt;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Rect::Rect(SkewTAdapter& adapter,
           double xmin, double xmax, double ymin, double ymax):
m_adapter(adapter),
m_pageXmin(xmin), m_pageYmax(ymax), m_pageYmin(ymin), m_pageXmax(xmax),
m_haveFirstP1(0), m_haveLastP2(0)

  {
  
  m_xmax = 1.0;
  m_xmin = 0.0;
  m_ymax = 1.0;
  m_ymin = 0.0;
  
  }

//////////////////////////////////////////////////////////////////////
Rect::~Rect()
  {
  
  }

//////////////////////////////////////////////////////////////////////
void Rect::drawLine(Rect::line l, unsigned int color, Rect::LineType lineType, bool doClip)
  {
  
  bool drawIt = 1;
  if (doClip)
    drawIt = clip(l);
  
  // we will draw the line only if the clipping indicated that some of
  // it falls within the Rect.
  if (drawIt) {
    if (!m_haveFirstP1) {
      // save endpoints before before page conversion
      m_haveFirstP1 = 1;
      m_firstP1 = l.p1;
      }
    m_haveLastP2 = 1;
    m_lastP2 = l.p2;  
    
    // convert to page coordinates
    convertToPage(l);
    
    SkewTAdapter::LineType skLineType;
    switch (lineType) {
      case DashedLine:
        skLineType = SkewTAdapter::DashedLine;
        break;
      case SolidLine:
      default:
        skLineType = SkewTAdapter::SolidLine;
        break;
      }
    
    // send it to the page
    m_adapter.line(l.p1.x, l.p1.y, l.p2.x, l.p2.y, color, skLineType);
    }
  
  }

//////////////////////////////////////////////////////////////////////
Rect::line::line() {
  }

//////////////////////////////////////////////////////////////////////
Rect::line::line(Rect::point start, Rect::point end):
  p1(start), p2(end)
    {
    }
  
  //////////////////////////////////////////////////////////////////////
  Rect::point::point():
    x(0.0),
      y(0.0)
      {
      }
    
    //////////////////////////////////////////////////////////////////////
    Rect::point::point(double xx, double yy):
      x(xx), y(yy)
        {
        }
      
      
      //////////////////////////////////////////////////////////////////////
      bool Rect::clip(Rect::line& l)
        {
        
        bool done = 0;
        bool accept = 0;
        bool reject = 0;
        bool flipped = false;
        
        point p1 = l.p1;
        point p2 = l.p2;
        
        do {
          
          outcode o1(p1, *this);
          outcode o2(p2, *this);
          reject = o1.reject(o2);
          if (reject)   // check trivial reject
            {
            done = 1;
            } 
          else
            {   // possible accept
            accept = o1.accept(o2);   // check trivial accept
            if (accept) {
              done = 1;
              }
            else 
              {   
              // subdivide line since at most one endpoint is inside
              // First, if P1 is inside window, exchange p1 and p2 and their 
              // outcodes to guarentee that p1 is outside the window.
              if (!o1.OR()) {
                point p = p1;
                p1 = p2; 
                p2 = p;
                outcode o;
                o = o1;
                o1 = o2;
                o2 = o;
                flipped = !flipped;
                }
              
              // now perform a subdivision, move P1 to the intersection point;
              // use the formulas y = y1 + slope*(x-x1, x = x1+(1/slope)*(y-y1).
              if (o1.code.c1) 
                { //divide line at top of window
                p1.x = p1.x + (p2.x-p1.x)*(m_ymax-p1.y)/(p2.y-p1.y);
                p1.y = m_ymax;
                } 
              else 
                if (o1.code.c2)
                  {// divide line at bottom of window
                  p1.x = p1.x +(p2.x-p1.x)*(m_ymin-p1.y)/(p2.y-p1.y);
                  p1.y = m_ymin;
                  }
                else
                  if (o1.code.c3)
                    { // divide line at right edge of window
                    p1.y = p1.y + (p2.y-p1.y)*(m_xmax-p1.x)/(p2.x-p1.x);
                    p1.x = m_xmax;
                    }
                  else 
                    if (o1.code.c4) 
                      { // divide line at left edge of window
                      p1.y = p1.y + (p2.y-p1.y)*(m_xmin-p1.x)/(p2.x-p1.x);
                      p1.x = m_xmin;
                      }
              }  // end subdivide
            }  // end possible accept
          } while (!done);
        
        if (accept) {
          if (!flipped) {
            l.p1 = p1;
            l.p2 = p2;
            } else {
            l.p1 = p2;
            l.p2 = p1;
              }
            
            return 1;
          }
        
        return 0;
        
        }
      
      //////////////////////////////////////////////////////////////////////
      Rect::outcode::outcode() {
        }
      
      //////////////////////////////////////////////////////////////////////
      Rect::outcode::outcode(Rect::point p, Rect& rect)
        {
        code.c1 = 0;
        code.c2 = 0;
        code.c3 = 0;
        code.c4 = 0;
        
        if (p.y > rect.m_ymax)
          code.c1 = 1;
        else 
          if (p.y < rect.m_ymin)
            code.c2 = 1;
          
          if (p.x > rect.m_xmax)
            code.c3 = 1;
          else
            if (p.x < rect.m_xmin)
              code.c4 = 1;
            
        }
      
      //////////////////////////////////////////////////////////////////////
      bool Rect::outcode::accept(Rect::outcode& o)
        {
        return (  
          code.c1 == 0 &&
          code.c2 == 0 &&
          code.c3 == 0 &&
          code.c4 == 0 &&
          o.code.c1 == 0 &&
          o.code.c2 == 0 &&
          o.code.c3 == 0 &&
          o.code.c4 == 0 );
        }
      
      //////////////////////////////////////////////////////////////////////
      bool Rect::outcode::reject(Rect::outcode& o)
        {
        return (
          (code.c1 && o.code.c1 ) ||
          (code.c2 && o.code.c2 ) ||
          (code.c3 && o.code.c3 ) ||
          (code.c4 && o.code.c4 ));
        }
      
      //////////////////////////////////////////////////////////////////////
      bool Rect::outcode::OR() {
        
        return (code.c1 || code.c2 || code.c3 || code.c4) ;
        }
      
      //////////////////////////////////////////////////////////////////////
      void Rect::convertToPage(point &p)
        {
        p.x = (p.x - m_xmin)*(m_pageXmax-m_pageXmin)/(m_xmax-m_xmin) + m_pageXmin;
        p.y = (p.y - m_ymin)*(m_pageYmax-m_pageYmin)/(m_ymax-m_ymin) + m_pageYmin;
        
        }
      
      //////////////////////////////////////////////////////////////////////
      void Rect::convertToPage(line &l)
        {
        convertToPage(l.p1);
        convertToPage(l.p2);
        }
      
      //////////////////////////////////////////////////////////////////////
      void Rect::Text(const std::string &s, const point p0, unsigned int color)
        {
        point pp = p0;
        convertToPage(pp);
        
        std::string ss = s;
        
        m_adapter.Text(ss, pp.x, pp.y, color);
        
        }
      
      //////////////////////////////////////////////////////////////////////
      void Rect::resetFirstP1() {
        m_haveFirstP1 = 0;
        }
      
      //////////////////////////////////////////////////////////////////////
      bool Rect::firstP1(Rect::point& p1) {
        if (m_haveFirstP1) {
          p1 = m_firstP1;
          return 1;
          }
        
        return 0;
        }
      
      //////////////////////////////////////////////////////////////////////
      void Rect::resetLastP2() {
        m_haveLastP2 = 0;
        }
      
      //////////////////////////////////////////////////////////////////////
      bool Rect::lastP2(Rect::point& p2) {
        if (m_haveLastP2) {
          p2 = m_lastP2;
          return 1;
          }
        
        return 0;
        }
      
      //////////////////////////////////////////////////////////////////////
      void Rect::symbol(Rect::point pp, unsigned int color, SymType st) {
        
        SkewTAdapter::SymType symType;
        
        switch (st) {
          case SmallPlus:
            symType = SkewTAdapter::SmallPlus;
            break;
          case SmallDot:
          default:
            symType = SkewTAdapter::SmallDot;
            break;
          }
        
        if (pp.x >= m_xmin && pp.x <= m_xmax &&
          pp.y >= m_ymin && pp.y <= m_ymax) {
          
          convertToPage(pp);
          m_adapter.symbol(pp.x, pp.y, color, symType);
          }
        }
      
      //////////////////////////////////////////////////////////////////////
      double Rect::aspectRatio()
        {
        
        double rectAspectRatio = (m_pageYmax - m_pageYmin) / (m_pageXmax - m_pageXmin);
        
        double adapterAspectRatio = m_adapter.aspectRatio();
        
        return adapterAspectRatio * rectAspectRatio;
        
        }
      
      //////////////////////////////////////////////////////////////////////
      void Rect::addTdry(double xx, double yy)
        {
        point pp(xx, yy);
        line l(pp,pp);
        if (clip(l)){
          convertToPage(pp);
          m_adapter.addTdry(pp.x, pp.y);
          }
        }
      
      //////////////////////////////////////////////////////////////////////
      void Rect::addDp(double xx, double yy)
        {
        point pp(xx, yy);
        line l(pp,pp);
        if (clip(l)){
          convertToPage(pp);
          m_adapter.addDp(pp.x, pp.y);
          }
        }
      
      //////////////////////////////////////////////////////////////////////
      
