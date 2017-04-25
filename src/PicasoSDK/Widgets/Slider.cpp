//============================================================================
// Name        : Slider.cpp
// Authors     : Julien Combattelli & Guillaume Sarthou
// EMail       : open.pode@gmail.com
// Date		   : 19 avr. 2017
// Version     : 1.0.0
// Copyright   : This file is part of PicasoSDK project which is released under
//               MIT license. See file LICENSE.txt for full license details
// Description : It provides a slider widget
//============================================================================

#include "PicasoSDK/Widgets/Slider.h"
#include "PicasoSDK/Core/Events.h"

namespace Picaso
{

Slider::Slider(Serial_Commander& lcd,
		Color border_color,
		Color fill_color,
		Color button_color,
		uint16_t origin_x,
		uint16_t origin_y,
		uint16_t width,
		uint16_t height,
		bool auto_update) :
		Touchable_Widget(lcd)
{
	m_auto_update = auto_update;
}

Slider::Slider(Serial_Commander& lcd, bool auto_update) :
		Touchable_Widget(lcd)
{
	m_auto_update = auto_update;
}

Slider::~Slider()
{

}

void Slider::change_color(Color border_color, Color fill_color)
{
    m_border_color = border_color;
    m_fill_color = fill_color;
    if(m_auto_update) show();
}

void Slider::change_size(uint16_t width, uint16_t height)
{
	m_boundingBox.size.height = height;
	m_boundingBox.size.width = width;
	if(m_auto_update) show();
}

void Slider::change_origin(uint16_t x_origin, uint16_t y_origin)
{
	m_boundingBox.origin.x = x_origin;
	m_boundingBox.origin.y = y_origin;
	if(m_auto_update) show();
}

} // namespace Picaso
