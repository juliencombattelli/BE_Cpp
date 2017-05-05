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
#include <algorithm>

namespace Picaso
{

Label::Label(Serial_Commander& lcd, const std::string& text, Color foreground_color, uint16_t x_origin, uint16_t y_origin, uint16_t width, uint16_t height, int font_size, Alignment_H h_alignment, Alignment_V v_alignment, bool auto_update) :
	Widget(lcd)
{
    m_auto_update = auto_update;

    create(text, foreground_color, x_origin, y_origin, width, height, font_size, h_alignment, v_alignment);

    if(auto_update)
    	show();
}

Label::Label(Serial_Commander& lcd, bool auto_update) : Widget(lcd)
{
    m_auto_update = auto_update;

    create("", Color::WHITE, 0, 0, 20, 20, 1, Alignment_H::LEFT, Alignment_V::TOP);
}

void Label::update_attributes()
{
    m_lcd.txt_set_font(3);
    m_lcd.txt_width_multiplier(m_font_size);
    m_lcd.txt_height_multiplier(m_font_size);
    m_lcd.txt_foreground_color(m_foreground_color);
    m_lcd.txt_background_color(m_background_color);
}

inline std::string trim(const std::string &s)
{
	auto wsfront = std::find_if_not(s.begin(),s.end(),[](int c){return std::isspace(c);});
	auto wsback = std::find_if_not(s.rbegin(),s.rend(),[](int c){return std::isspace(c);}).base();
	return (wsback <= wsfront ? std::string() : std::string(wsfront,wsback));
}

void Label::write_text()
{
    uint8_t character_width = m_lcd.txt_char_width('0');
    uint8_t character_height = m_lcd.txt_char_height('0');
    uint8_t max_char_per_line = m_boundingBox.size.width/character_width;

    if(max_char_per_line == 0)
    	return;

	size_t space_pos = 0;
	size_t index = 0;
	Point text_location{m_boundingBox.origin.x, m_boundingBox.origin.x};
	std::string tmp{m_text};
	std::vector<std::string> str_vect;
	tmp += " ";

	while(space_pos != std::string::npos)
	{
		space_pos = tmp.find(" ", index);
		if(space_pos > max_char_per_line)
		{
			str_vect.emplace_back(trim(tmp.substr(0, index)));
			tmp.erase(0, index);
		}
		else
			index = space_pos + 1;
	}

	size_t line_count = str_vect.size();

	switch(m_alignment.v)
	{
		case Alignment_V::TOP:
			text_location.y = m_boundingBox.origin.y;
			break;

		case Alignment_V::BOTTOM:
			text_location.y = (m_boundingBox.origin.y + m_boundingBox.size.height) - line_count*character_height;
			break;

		case Alignment_V::CENTER:
			text_location.y = ((m_boundingBox.size.height - line_count*character_height) / 2) + m_boundingBox.origin.y;
			break;
	}

	for(unsigned i = 0; i < line_count; i++)
	{
		switch(m_alignment.h)
		{
			case Alignment_H::LEFT:
				text_location.x = m_boundingBox.origin.x;
				break;

			case Alignment_H::RIGHT:
				text_location.x = (m_boundingBox.origin.x + m_boundingBox.size.width) - str_vect[i].size()*character_height;
				break;

			case Alignment_H::CENTER:
				text_location.x = ((m_boundingBox.size.width - str_vect[i].size()*character_width)/2) + m_boundingBox.origin.x;
				break;
		}

		m_lcd.gfx_move_origin(text_location.x, text_location.y);
		m_lcd.txt_put_str(str_vect[i]);

		text_location.y += character_height;
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
    if(m_auto_update)
    	write_text();
}

} // namespace Picaso
