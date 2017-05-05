//============================================================================
// Name        : Main_Window.cpp
// Authors     : Julien Combattelli & Guillaume Sarthou
// EMail       : open.pode@gmail.com
// Date		   : 30 avr. 2017
// Version     : 1.0.0
// Copyright   : This file is part of PicasoSDK project which is released under
//               MIT license. See file LICENSE.txt for full license details
// Description : It provides a home screen for the demo app, allowing the user
//				 to choose control modes
//============================================================================

#include "Application/Windows/Main_Window.h"
#include "Application/Events.h"

Main_Window::Main_Window(Picaso::Serial_Commander& lcd) :
	Touchable_Window(lcd),
	m_button_moving(m_lcd, "Moving Window", Picaso::Color::RED, Picaso::Color::BLACK, 10, 70, 450/2, 90),
	m_button_monitor(m_lcd, "Process Monitor", Picaso::Color::RED, Picaso::Color::BLACK, 10, 70+100, 450/2, 90),
	m_button_spreading(m_lcd, "Spreading Window", Picaso::Color::RED, Picaso::Color::BLACK, 20 + 450/2, 70, 450/2, 90),
	m_button_tilt(m_lcd, "Tilt Window", Picaso::Color::RED, Picaso::Color::BLACK, 20 + 450/2, 70+100, 450/2, 90),
	m_title(m_lcd, "BE POO 2017", Picaso::Color::WHITE, 10, 10, 320, 60, 3, Picaso::Alignment_H::CENTER, Picaso::Alignment_V::CENTER, false),
	m_names(m_lcd, "Combattelli Julien \n\rSarthou Guillaume", Picaso::Color::WHITESMOKE, 320, 10, 480-320, 60, 1, Picaso::Alignment_H::CENTER, Picaso::Alignment_V::CENTER, false)
{
	m_button_moving.add_receiver(*this);
	m_button_monitor.add_receiver(*this);
	m_button_spreading.add_receiver(*this);
	m_button_tilt.add_receiver(*this);
	m_touch_dispatcher.register_widget(m_button_moving);
	m_touch_dispatcher.register_widget(m_button_monitor);
	m_touch_dispatcher.register_widget(m_button_spreading);
	m_touch_dispatcher.register_widget(m_button_tilt);

	add_event_handler<Picaso::Button_Pressed>(&Main_Window::button_pressed_handler, this);
}

void Main_Window::show()
{
	m_lcd.gfx_clear_screen();
	m_button_moving.show();
	m_button_monitor.show();
	m_button_spreading.show();
	m_button_tilt.show();
	m_title.show();
	m_names.show();
}

void Main_Window::button_pressed_handler(Sender& s, const Event& e)
{
	unsigned int id = static_cast<Picaso::Widget&>(s).get_id();

	if(id == m_button_moving.get_id())
		button_moving_pressed();
	else if (id == m_button_monitor.get_id())
		button_monitor_pressed();
	else if(id == m_button_spreading.get_id())
		button_spreading_pressed();
	else if(id == m_button_tilt.get_id())
		button_tilt_pressed();
}

void Main_Window::button_moving_pressed()
{
	raise(Navigation_Choise_Pressed(1));
}

void Main_Window::button_monitor_pressed()
{
	raise(Navigation_Choise_Pressed(4));
}

void Main_Window::button_spreading_pressed()
{
	raise(Navigation_Choise_Pressed(3));
}

void Main_Window::button_tilt_pressed()
{
	raise(Navigation_Choise_Pressed(2));
}
