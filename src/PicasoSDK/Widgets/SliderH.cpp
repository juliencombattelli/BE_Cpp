/*
 * SliderH.cpp
 *
 *  Created on: 25 avr. 2017
 *      Author: guill
 */

#include "PicasoSDK/Widgets/SliderH.h"
#include "PicasoSDK/Core/Events.h"

namespace Picaso
{

SliderH::SliderH(Serial_Commander& lcd, Color border_color, Color fill_color, Color button_color, uint16_t origin_x, uint16_t origin_y, uint16_t width, uint16_t height, bool auto_update) :
Slider(lcd, border_color, fill_color, button_color, origin_x, origin_y, width, height, auto_update)
{
	create(border_color, fill_color, button_color, origin_x, origin_y, width, height);
	if(auto_update)
		show();
}

SliderH::SliderH(Serial_Commander& lcd, bool auto_update) : Slider(lcd, auto_update)
{
	create(Color::ORANGE, Color::BLACK, Color::GRAY, 0, 0, 20, 20);
}

SliderH::~SliderH()
{

}

void SliderH::show()
{
    m_lcd.gfx_draw_filled_rectangle(
    		m_boundingBox.origin.x,
			m_boundingBox.origin.y,
			m_boundingBox.origin.x + m_boundingBox.size.width,
			m_boundingBox.origin.y + m_boundingBox.size.height,
			m_border_color);

    m_lcd.gfx_draw_filled_rectangle(
    		m_boundingBox.origin.x + border_width,
			m_boundingBox.origin.y + border_width,
			m_boundingBox.origin.x + m_boundingBox.size.width - border_width,
			m_boundingBox.origin.y + m_boundingBox.size.height - border_width,
			m_fill_color);

    if(m_boundingBox.size.width*m_per_cent - m_size_standard.width/2 < 2)
        m_lcd.gfx_draw_filled_rectangle(
        		m_boundingBox.origin.x + 2,
				m_boundingBox.origin.y + 1,
				m_boundingBox.origin.x + (m_boundingBox.size.width - 4)*m_per_cent + m_size_standard.width/2,
				m_boundingBox.origin.y + m_boundingBox.size.height - 1,
				m_button_color);
    else if(m_boundingBox.size.width*m_per_cent + m_size_standard.width/2 > m_boundingBox.size.width - 2)
        m_lcd.gfx_draw_filled_rectangle(
        		m_boundingBox.origin.x + (m_boundingBox.size.width - 4)*m_per_cent - m_size_standard.width/2,
				m_boundingBox.origin.y + 1,
				m_boundingBox.origin.x + m_boundingBox.size.width - 2,
				m_boundingBox.origin.y + m_boundingBox.size.height - 1,
				m_button_color);
    else
        m_lcd.gfx_draw_filled_rectangle(
        		m_boundingBox.origin.x + (m_boundingBox.size.width - 4)*m_per_cent - m_size_standard.width/2,
				m_boundingBox.origin.y + 1,
				m_boundingBox.origin.x + (m_boundingBox.size.width - 4)*m_per_cent + m_size_standard.width/2,
				m_boundingBox.origin.y + m_boundingBox.size.height - 1,
				m_button_color);
}

void SliderH::create(Color border_color, Color fill_color, Color button_color, uint16_t x_origin, uint16_t y_origin, uint16_t width, uint16_t height)
{
	m_boundingBox.origin.x = x_origin;
	m_boundingBox.origin.y = y_origin;

	m_boundingBox.size.height = height;
	m_boundingBox.size.width = width;

    m_border_color = border_color;
    m_fill_color = fill_color;
    m_button_color = button_color;

    m_size_pressed.width = 6;
	m_size_pressed.height = m_boundingBox.size.height - 4;
	m_size_standard.width = 12;
	m_size_standard.height = m_boundingBox.size.height;

    m_is_touch = false;
	m_per_cent = 0.5;

	add_event_handler<Touch_Screen_Event>(&SliderH::touch_event_handler, this);
}

void SliderH::touch_event_handler(Sender& sender, const Event& event)
{
	const Touch_Screen_Event& touch_event = static_cast<decltype(touch_event)>(event);
    switch(touch_event.state)
    {
        case Touch_Event::touch_began:
            if(m_boundingBox.contains(touch_event.point))
            {
                m_per_cent = (float)(touch_event.point.x - m_boundingBox.origin.x) / (float)(m_boundingBox.size.width);

                m_lcd.gfx_draw_filled_rectangle(
                		m_boundingBox.origin.x,
						m_boundingBox.origin.y,
						m_boundingBox.origin.x + m_boundingBox.size.width,
						m_boundingBox.origin.y + m_boundingBox.size.height,
						m_border_color);
                update_button();
                raise(Slider_Moved(m_per_cent));
                m_is_touch = true;
            }
            break;

        case Touch_Event::touch_ended :
			if(m_is_touch == true)
			{
				show();
				m_is_touch=false;
			}
			break;

        case Touch_Event::touch_moved:
            if(m_boundingBox.contains(touch_event.point))
            {
                m_per_cent = (float)(touch_event.point.x - m_boundingBox.origin.x) / (float)(m_boundingBox.size.width - 4);
                update_button();
                raise(Slider_Moved(m_per_cent));
            }
            break;

        default :
        	break;
    }
}

void SliderH::update_button()
{
    m_lcd.gfx_draw_filled_rectangle(
    		m_boundingBox.origin.x + 2,
			m_boundingBox.origin.y + 2,
			m_boundingBox.origin.x + m_boundingBox.size.width - 2,
			m_boundingBox.origin.y + m_boundingBox.size.height - 2,
			m_fill_color);

    if(m_boundingBox.size.width*m_per_cent - m_size_pressed.width/2 < 2)
        m_lcd.gfx_draw_filled_rectangle(
        		m_boundingBox.origin.x + 2,
				m_boundingBox.origin.y + 2,
				m_boundingBox.origin.x + (m_boundingBox.size.width - 4)*m_per_cent + m_size_pressed.width/2,
				m_boundingBox.origin.y + m_boundingBox.size.height - 2,
				m_button_color);
    else if(m_boundingBox.size.width*m_per_cent + m_size_pressed.width/2 > m_boundingBox.size.width - 2)
        m_lcd.gfx_draw_filled_rectangle(
        		m_boundingBox.origin.x + (m_boundingBox.size.width - 4)*m_per_cent - m_size_pressed.width/2,
				m_boundingBox.origin.y + 2,
				m_boundingBox.origin.x + m_boundingBox.size.width - 2,
				m_boundingBox.origin.y + m_boundingBox.size.height - 2,
				m_button_color);
    else
        m_lcd.gfx_draw_filled_rectangle(
        		m_boundingBox.origin.x + (m_boundingBox.size.width - 4)*m_per_cent - m_size_pressed.width/2,
				m_boundingBox.origin.y + 2,
				m_boundingBox.origin.x + (m_boundingBox.size.width - 4)*m_per_cent + m_size_pressed.width/2,
				m_boundingBox.origin.y + m_boundingBox.size.height - 2,
				m_button_color);
}

} // namespace Picaso
