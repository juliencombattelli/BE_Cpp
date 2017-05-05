//============================================================================
// Name        : Button.cpp
// Authors     : Julien Combattelli & Guillaume Sarthou
// EMail       : open.pode@gmail.com
// Date		   : 19 avr. 2017
// Version     : 1.0.0
// Copyright   : This file is part of PicasoSDK project which is released under
//               MIT license. See file LICENSE.txt for full license details
// Description : It provides a button widget
//============================================================================

#include "PicasoSDK/Widgets/Button.h"
#include "PicasoSDK/Core/Events.h"

namespace Picaso
{

Button::Button(Serial_Commander& lcd, const std::string& text, Color border_color, Color fill_color, uint16_t x_origin, uint16_t y_origin, uint16_t width, uint16_t height, int font_size) :
		Touchable_Widget(lcd), m_label(lcd, false)
{
    create(text, border_color, fill_color, x_origin, y_origin, width, height, font_size);

    //show();
}

Button::Button(Serial_Commander& lcd) :
		Touchable_Widget(lcd), m_label(lcd, false)
{
    create("", Color::ORANGE, Color::BLACK, 0, 0, 20, 20, 1);
}

void Button::touch_event_handler(Sender& sender, const Event& event)
{
	const Touch_Screen_Event& touch_event = static_cast<decltype(touch_event)>(event);
    switch(touch_event.state)
    {
        case Touch_Event::touch_began:
            if(m_boundingBox.contains(touch_event.point))
            {
                inverse_button();
                m_is_touch = true;
                raise(Button_Pressing());
            }
            break;

        case Touch_Event::touch_moved:
        	if(m_is_touch == true)
        	{
        		raise(Button_Pressing());
        	}
        	break;

        case Touch_Event::touch_ended :
            if(m_is_touch == true)
            {
                show();
                if(m_boundingBox.contains(touch_event.point))
                {
                	raise(Button_Pressed());
                }
                m_is_touch = false;
            }
            break;

        default :
        	break;
    }
}

void Button::show()
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

    m_label.change_color(m_border_color, m_fill_color);
    m_label.show();
}

void Button::inverse_button()
{
    m_lcd.gfx_draw_filled_rectangle(
    		m_boundingBox.origin.x,
			m_boundingBox.origin.y,
			m_boundingBox.origin.x + m_boundingBox.size.width,
			m_boundingBox.origin.y + m_boundingBox.size.height,
			m_fill_color);

    m_lcd.gfx_draw_filled_rectangle(
    		m_boundingBox.origin.x + border_width,
			m_boundingBox.origin.y + border_width,
			m_boundingBox.origin.x + m_boundingBox.size.width - border_width,
			m_boundingBox.origin.y + m_boundingBox.size.height - border_width,
			m_border_color);

    m_label.change_color(m_fill_color, m_border_color);
    m_label.show();
}

void Button::change_color(Color border_color, Color fill_color)
{
	m_border_color = border_color;
	m_fill_color = fill_color;
	show();
}

void Button::change_size(uint16_t width, uint16_t height)
{
    m_boundingBox.size.height = height;
    m_boundingBox.size.width = width;
    m_label.change_size(width, height);
    show();
}

void Button::change_origin(uint16_t x_origin, uint16_t y_origin)
{
    m_boundingBox.origin.x = x_origin;
    m_boundingBox.origin.y = y_origin;
    m_label.change_origin(x_origin + border_width, y_origin + border_width);
    show();
}

void Button::change_font_size(int font_size)
{
    m_label.change_font_size(font_size);
    show();
}

void Button::change_text(const std::string& text)
{
    m_label.change_text(text);
    show();
}

void Button::create(const std::string& text, Color border_color, Color fill_color, uint16_t x_origin, uint16_t y_origin, uint16_t width, uint16_t height, int font_size)
{
    m_label.change_alignment(Alignment_H::CENTER, Alignment_V::CENTER);

    m_boundingBox.origin.x = x_origin;
    m_boundingBox.origin.y = y_origin;
    m_label.change_origin(x_origin + border_width, y_origin + border_width);

    m_boundingBox.size.height = height;
    m_boundingBox.size.width = width;
    m_label.change_size(width, height);

    m_border_color = border_color;
    m_fill_color = fill_color;
    m_label.change_color(m_border_color, m_fill_color);

    m_label.change_text(text);
    m_label.change_font_size(font_size);

    m_is_touch = false;

    add_event_handler<Touch_Screen_Event>(&Button::touch_event_handler, this);
}

} // namespace Picaso
