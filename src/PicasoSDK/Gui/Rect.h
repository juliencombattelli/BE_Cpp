//============================================================================
// Name        : Rect.h
// Authors     : Julien Combattelli & Guillaume Sarthou
// EMail       : open.pode@gmail.com
// Date		   : 19 avr. 2017
// Version     : 1.0.0
// Copyright   : This file is part of PicasoSDK project which is released under
//               MIT license. See file LICENSE.txt for full license details
// Description : It provides some geometric classes
//============================================================================

#ifndef PICASO_RECT_H_
#define PICASO_RECT_H_

#include <cstdint>

namespace Picaso
{

struct Point
{
    uint16_t x;
    uint16_t y;
};

struct Size
{
	uint16_t width;
	uint16_t height;
};

struct Rect
{
    Point origin;
    Size size;

    static bool is_inside(const Point& point, const Rect& rect)
    {
        if( (point.x > rect.origin.x && point.x < rect.origin.x + rect.size.width) &&
        	(point.y > rect.origin.y && point.y < rect.origin.y + rect.size.height))
            return true;
        else
            return false;
    }
};

} // namespace Picaso

#endif // PICASO_RECT_H_
