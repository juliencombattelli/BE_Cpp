//============================================================================
// Name        : Label.cpp
// Authors     : Julien Combattelli & Guillaume Sarthou
// EMail       : open.pode@gmail.com
// Date		   : 19 avr. 2017
// Version     : 1.0.0
// Copyright   : This file is part of PicasoSDK project which is released under
//               MIT license. See file LICENSE.txt for full license details
// Description : It provides a label widget
//============================================================================

#include "PicasoSDK/Widgets/Label.h"

namespace Picaso
{

Label::Label(Serial_Commander& lcd, const std::string& text, Color foreground_color, uint16_t x_origin, uint16_t y_origin, uint16_t width, uint16_t height, int font_size, Alignment_H h_alignment, Alignment_V v_alignment, bool auto_update) :
	Widget(lcd)
{
    m_auto_update = auto_update;

    create(text, foreground_color, x_origin, y_origin, width, height, font_size, h_alignment, v_alignment);

    show();
}

Label::Label(Serial_Commander& lcd, bool auto_update) : Widget(lcd)
{
    m_auto_update = auto_update;

    create("", Color::WHITE, 0, 0, 20, 20, 1, Alignment_H::LEFT, Alignment_V::TOP);
}

Label::~Label()
{

}

void Label::update_attributes()
{
    m_lcd.txt_set_font(3);
    m_lcd.txt_width_multiplier(m_font_size);
    m_lcd.txt_height_multiplier(m_font_size);
    m_lcd.txt_foreground_color(m_foreground_color);
    m_lcd.txt_background_color(m_background_color);
}

void Label::write_text()
{
    uint8_t sector = 0;
    uint8_t u = m_lcd.txt_char_width('0');
    uint8_t nb_car_max = m_boundingBox.size.width/u;
    uint8_t nb_car_per_sector[100];
    uint8_t car_index_total = 0;
    uint8_t car_index = 0;
    uint16_t size_text = m_text.size();
    std::string text_cpy;
    std::string buffer;
    text_cpy = m_text;

    uint16_t y_location = 0, x_location = 0;
    if(nb_car_max != 0)
    {
        while(car_index_total < size_text)
        {
            car_index += nb_car_max;

            if(car_index < size_text)
            {
                while((text_cpy[car_index] != ' ') && (car_index_total != car_index))
                    car_index --;

                if(car_index_total == car_index)
                {
                    car_index += nb_car_max;
                }
                else
                {
                    text_cpy.erase(car_index,1);
                    size_text = text_cpy.size();
                }
            }
            else
                car_index = size_text;

            nb_car_per_sector[sector] = car_index - car_index_total;
            sector ++;
            car_index_total = car_index;
        }

        switch(m_alignment.v)
        {
            case Alignment_V::TOP:
                y_location = m_boundingBox.origin.y;
                break;

            case Alignment_V::BOTTOM:
                y_location = (m_boundingBox.origin.y + m_boundingBox.size.height) - sector*m_lcd.txt_char_height('0');
                break;

            case Alignment_V::CENTER:
                y_location = ((m_boundingBox.size.height - sector*m_lcd.txt_char_height('0')) / 2) + m_boundingBox.origin.y;
                break;
        }

        car_index = 0;
        for(uint8_t i = 0; i < sector; i++)
        {
             switch(m_alignment.h)
            {
                case Alignment_H::LEFT:
                    x_location = m_boundingBox.origin.x;
                    break;

                case Alignment_H::RIGHT:
                	x_location = (m_boundingBox.origin.x + m_boundingBox.size.width) - nb_car_per_sector[i]*m_lcd.txt_char_width('0');
                	break;

                case Alignment_H::CENTER:
                	x_location = ((m_boundingBox.size.width - nb_car_per_sector[i]*m_lcd.txt_char_width('0'))/2) + m_boundingBox.origin.x;
                	break;
            }
            buffer = text_cpy.substr(car_index, nb_car_per_sector[i]);
            car_index += nb_car_per_sector[i];

            m_lcd.gfx_move_origin(x_location, y_location);
            m_lcd.txt_put_str(buffer);

            y_location += m_lcd.txt_char_height('0');
        }
    }
}

void Label::show()
{
    update_attributes();
    write_text();
}

void Label::show_delimitation()
{
    m_lcd.gfx_draw_filled_rectangle(
    		m_boundingBox.origin.x,
			m_boundingBox.origin.y,
			m_boundingBox.origin.x + m_boundingBox.size.width,
			m_boundingBox.origin.y + m_boundingBox.size.height,
			m_background_color);
    write_text();
}

void Label::change_color(Color foreground_color, Color background_color)
{
    m_foreground_color = foreground_color;
    m_background_color = background_color;
    if(m_auto_update)
    {
		update_attributes();
		write_text();
    }
}

void Label::change_size(uint16_t width, uint16_t height)
{
	m_boundingBox.size.width = width;
	m_boundingBox.size.height = height;
	if(m_auto_update)
	{
		update_attributes();
		write_text();
	}
}

void Label::change_origin(uint16_t x_origin, uint16_t y_origin)
{
	m_boundingBox.origin.x = x_origin;
	m_boundingBox.origin.y = y_origin;
	if(m_auto_update)
	{
		update_attributes();
		write_text();
	}
}

void Label::change_alignment(Alignment_H h_alignment, Alignment_V v_alignment)
{
    m_alignment.h = h_alignment;
    m_alignment.v = v_alignment;
    if(m_auto_update)
    {
		update_attributes();
		write_text();
    }
}

void Label::change_font_size(int font_size)
{
    m_font_size = font_size;
    if(m_auto_update)
    {
		update_attributes();
		write_text();
    }
}

void Label::change_text(const std::string& text)
{
    m_text = text;
    if(m_auto_update)
    {
		update_attributes();
		write_text();
    }
}

void Label::create(const std::string& text, Color foreground_color, uint16_t x_origin, uint16_t y_origin, uint16_t width, uint16_t height, int font_size, Alignment_H h_alignment, Alignment_V v_alignment)
{
    m_alignment.h = h_alignment;
    m_alignment.v = v_alignment;
    m_boundingBox.origin.x = x_origin;
    m_boundingBox.origin.y = y_origin;
    m_boundingBox.size.width = width;
    m_boundingBox.size.height = height;
    m_foreground_color = foreground_color;
    m_background_color = Color::BLACK;
    m_font_size = font_size;
    m_text = text;

    update_attributes();
    write_text();
}

} // namespace Picaso
