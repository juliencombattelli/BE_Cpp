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
	Point() : x(0), y(0) {}
	Point(uint16_t _x, uint16_t _y) : x(_x), y(_y) {}
	Point(const Point& point) : x(point.x), y(point.y) {}
	Point& operator=(const Point& point) { x = point.x; y = point.y; return *this; }

    uint16_t x;
    uint16_t y;
};

struct Size
{
	Size() : width(0), height(0) {}
	Size(uint16_t _width, uint16_t _height) : width(_width), height(_height) {}
	Size(const Size& size) : width(size.width), height(size.height) {}
	Size& operator=(const Size& size) { width = size.width; height = size.height; return *this; }

	uint16_t width;
	uint16_t height;
};

struct Rect
{
	Rect() = default;
	Rect(const Point& _origin, const Size& _size) : origin(_origin), size(_size) {}
	Rect(const Rect& rect) : origin(rect.origin), size(rect.size) {}
	Rect& operator=(const Rect& rect) { origin = rect.origin; size = rect.size; return *this; }

    bool contains(const Point& point)
    {
        if( (point.x > origin.x && point.x < origin.x + size.width) &&
        	(point.y > origin.y && point.y < origin.y + size.height))
            return true;
        else
            return false;
    }

    Point origin;
    Size size;
};

} // namespace Picaso

#endif // PICASO_RECT_H_
