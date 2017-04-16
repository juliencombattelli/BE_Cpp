/*
 * Rect.h
 *
 *  Created on: 13 avr. 2017
 *      Author: JulienCombattelli
 */

#ifndef PICASOSDK_GUI_RECT_H_
#define PICASOSDK_GUI_RECT_H_

#include "PicasoSDK/Gui/Point.h"

namespace Picaso
{

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



#endif /* PICASOSDK_GUI_RECT_H_ */
