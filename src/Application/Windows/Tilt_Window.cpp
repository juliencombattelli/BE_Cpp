//============================================================================
// Name        : Tilt_Window.h
// Authors     : Julien Combattelli & Guillaume Sarthou
// EMail       : open.pode@gmail.com
// Date		   : 29 avr. 2017
// Version     : 1.0.0
// Copyright   : This file is part of PicasoSDK project which is released under
//               MIT license. See file LICENSE.txt for full license details
// Description : It provides a window enabling tilt control of target
//============================================================================

#include "Application/Windows/Tilt_Window.h"
#include "Application/Events.h"
#include <iostream>

Tilt_Window::Tilt_Window(Picaso::Serial_Commander& lcd) : Window_Template(lcd),
m_title(lcd, "Tilt window", Picaso::Color::WHITE, 70, 20, 250, 40, 2, Picaso::Alignment_H::CENTER, Picaso::Alignment_V::CENTER, false),
m_x_label(lcd, "X", Picaso::Color::WHITE, 480-20, 80+(272-80)/2 - 10, 20, 20, 1, Picaso::Alignment_H::CENTER, Picaso::Alignment_V::CENTER, false),
m_y_label(lcd, "Y", Picaso::Color::WHITE, 480/2-10, 60, 20, 20, 1, Picaso::Alignment_H::CENTER, Picaso::Alignment_V::CENTER, false),
m_area(lcd, 20, 80, 480-40, 272-80-20, (480-40)/2, (272-80-20)/2)
{
	m_area.add_receiver(*this);
	m_touch_dispatcher.register_widget(m_area);
	add_event_handler<Picaso::Area_Touched>(&Tilt_Window::area_touched_handler, this);
}

Tilt_Window::~Tilt_Window()
{

}

void Tilt_Window::custom_show()
{
	m_title.show();
	m_lcd.gfx_draw_line(480/2, 80, 480/2, 272-20, Picaso::Color::GRAY);
	m_lcd.gfx_draw_line(20, 80 + (272-80)/2, 460, 80 + (272-80)/2, Picaso::Color::GRAY);
	m_x_label.show();
	m_y_label.show();
}

void Tilt_Window::area_touched_handler(Sender& s, const Event& event)
{
	unsigned int id = ((Picaso::Widget&)s).get_id();

	if(id == m_area.get_id())
	{
		raise(Tilt_Change(((Picaso::Area_Touched&)event).m_x, ((Picaso::Area_Touched&)event).m_y));
	}
}
