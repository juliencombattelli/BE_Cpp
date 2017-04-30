/*
 * Touchable_Area.cpp
 *
 *  Created on: 30 avr. 2017
 *      Author: guill
 */

#include "PicasoSDK/Widgets/Touchable_Area.h"
#include "PicasoSDK/Core/Events.h"

namespace Picaso
{

Touchable_Area::Touchable_Area(Serial_Commander& lcd, uint16_t x_origin, uint16_t y_origin, uint16_t width, uint16_t height) :
		Touchable_Widget(lcd)
{
	m_boundingBox.origin.x = x_origin;
	m_boundingBox.origin.y = y_origin;

	m_boundingBox.size.height = height;
	m_boundingBox.size.width = width;
}

Touchable_Area::~Touchable_Area()
{

}

void Touchable_Area::show()
{

}

void Touchable_Area::change_size(uint16_t width, uint16_t height)
{
    m_boundingBox.size.height = height;
    m_boundingBox.size.width = width;
}

void Touchable_Area::change_origin(uint16_t x_origin, uint16_t y_origin)
{
    m_boundingBox.origin.x = x_origin;
    m_boundingBox.origin.y = y_origin;
}

void Touchable_Area::touch_event_handler(Sender& sender, const Event& event)
{
	const Touch_Screen_Event& touch_event = static_cast<decltype(touch_event)>(event);
    switch(touch_event.state)
    {
        case Touch_Event::touch_began:
            if(m_boundingBox.contains(touch_event.point))
            {
                m_is_touch = true;
                raise(Area_Touched(touch_event.point.x - m_boundingBox.origin.x, touch_event.point.y - m_boundingBox.origin.y));
            }
            break;

        case Touch_Event::touch_moved:
        	if(m_is_touch == true)
        	{
        		if(m_boundingBox.contains(touch_event.point))
        			raise(Area_Touched(touch_event.point.x - m_boundingBox.origin.x, touch_event.point.y - m_boundingBox.origin.y));
        	}
        	break;

        case Touch_Event::touch_ended :
            if(m_is_touch == true)
            {
                if(m_boundingBox.contains(touch_event.point))
                	raise(Area_Touched(touch_event.point.x - m_boundingBox.origin.x, touch_event.point.y - m_boundingBox.origin.y));
                m_is_touch = false;
            }
            break;

        default :
        	break;
    }
}

}//namespace Picaso


