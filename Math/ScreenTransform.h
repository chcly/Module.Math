/*
-------------------------------------------------------------------------------
    Copyright (c) Charles Carley.

  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
-------------------------------------------------------------------------------
*/
#pragma once

#include "Math/Rectangle.h"
#include "Math/Vector2.h"
namespace Rt2::Math
{
    /// <summary>
    /// Utility class for handling screen transforms like zoom, and pan
    /// </summary>
    class ScreenTransform
    {
    private:
        Vector2   m_origin;         // (0,0) of the coordinate system
        Vector2   m_center;         // offset from viewport center
        Rectangle m_viewport;       // fixed bounds of the viewport ([x] [x] [L] [L])
        Vector2   m_extent;         // storage to compute the change in m_viewport.getSize()
        Real    m_zoom;           // computed viewport change
        Real    m_scale;          // the current amount to scale the viewport by
        Vector2   m_scaleLimit;     // the range of the scale function
        Vector2   m_initialOrigin;  // the 'home' origin

    public:
        ScreenTransform() :
            m_zoom(1),
            m_scale(1)
        {
            m_scaleLimit = Vector2::Unit;
        }

        void zoom(const Real factor, bool negate)
        {
            m_scale += factor * m_zoom * (negate ? Real(-1) : Real(1));

            if (m_scale < m_scaleLimit.x)
                m_scale = m_scaleLimit.x;
            if (m_scale > m_scaleLimit.y)
                m_scale = m_scaleLimit.y;

            if (m_scale > 0)
            {
                m_extent = m_viewport.size() + m_scale;
                m_zoom   = m_extent.x / m_viewport.width;
                if (m_zoom < 1)
                    m_zoom = 1;
            }
        }


        void zoomLarge(const Real factor, bool negate)
        {
            m_scale += factor * m_zoom * (negate ? Real(-1) : Real(1));

            m_extent = m_viewport.size() + m_scale;
            m_zoom   = m_extent.x / m_viewport.width;
            if (eq(m_zoom, 0, RT_EPSILON))
                m_zoom = RT_EPSILON;
        }

        void pan(const Real px, const Real py)
        {
            m_origin.x += px * m_zoom;
            m_origin.y += py * m_zoom;
        }

        void setOrigin(const Real px, const Real py)
        {
            m_origin.x = px;
            m_origin.y = py;
        }

        void reset()
        {
            m_scale  = 1;
            m_origin = m_initialOrigin;
            m_extent = m_viewport.size();
            m_center = m_extent / 2;
            if (m_viewport.width > 0)
                m_zoom = m_extent.x / m_viewport.width;
            else
                m_zoom = 1;
        }

        inline const Real& getZoom() const
        {
            return m_zoom;
        }

        inline const Real& getScale() const
        {
            return m_scale;
        }

        inline Real xOffs() const
        {
            return (-m_center.x + m_origin.x + m_extent.x / Real(2)) / m_zoom;
        }

        inline Real yOffs() const
        {
            return (-m_center.y + m_origin.y + m_extent.y / Real(2)) / m_zoom;
        }

        inline void xToView(Real& x) const
        {
            x = x / m_zoom + xOffs();
        }

        Real getViewX(const Real& x) const
        {
            Real xCpy = x;
            xToView(xCpy);
            return xCpy;
        }

        inline void yToView(Real& y) const
        {
            y = y / m_zoom + yOffs();
        }

        Real getViewY(const Real& y) const
        {
            Real yCpy = y;
            yToView(yCpy);
            return yCpy;
        }

        inline void xToScreen(Real& x) const
        {
            x = (x - xOffs()) * m_zoom;
        }

        Real getScreenX(const Real& x) const
        {
            Real xCpy = x;
            xToScreen(xCpy);
            return xCpy;
        }

        inline void yToScreen(Real& y) const
        {
            y = (y - yOffs()) * m_zoom;
        }

        Real getScreenY(const Real& y) const
        {
            Real xCpy = y;
            yToScreen(xCpy);
            return xCpy;
        }

        void pointToScreen(Vector2& pt) const
        {
            xToScreen(pt.x);
            yToScreen(pt.y);
        }

        void pointToView(Vector2& pt) const
        {
            xToView(pt.x);
            yToView(pt.y);
        }

        Vector2 getOffset() const
        {
            return Vector2(xOffs(), yOffs());
        }

        inline const Vector2& getOrigin() const
        {
            return m_origin;
        }

        inline const Vector2& getExtent() const
        {
            return m_extent;
        }

        inline const Vector2& getCenter() const
        {
            return m_center;
        }

        inline const Rectangle& getViewport() const
        {
            return m_viewport;
        }

        inline const Real& viewportLeft() const
        {
            return m_viewport.x;
        }

        inline const Real& viewportTop() const
        {
            return m_viewport.y;
        }

        inline Real viewportRight() const
        {
            return m_viewport.right();
        }

        inline Real viewportBottom() const
        {
            return m_viewport.bottom();
        }

        inline const Real& viewportWidth() const
        {
            return m_viewport.width;
        }

        inline const Real& viewportHeight() const
        {
            return m_viewport.height;
        }

        void setScaleLimit(const Real& lMin, const Real& lMax)
        {
            m_scaleLimit.x = lMin;
            m_scaleLimit.y = lMax;
        }

        void setInitialOrigin(const Real& oX, const Real& oY)
        {
            m_initialOrigin.x = oX;
            m_initialOrigin.y = oY;
        }

        void setViewport(const Rectangle& vp)
        {
            m_viewport = vp;
        }

        void setViewport(const Real& x,
                         const Real& y,
                         const Real& width,
                         const Real& height)
        {
            m_viewport.x      = x;
            m_viewport.y      = y;
            m_viewport.width  = width;
            m_viewport.height = height;
        }

        bool isInViewport(const Real& x1, const Real& y1, const Real& x2, const Real& y2) const
        {
            Rectangle r1, r2;
            r1.setSize(m_viewport.width, m_viewport.height);
            r2.setCorners(x1, y1, x2, y2);
            return r1.contains(r2);
        }
    };
}  // namespace Rt2::Math

