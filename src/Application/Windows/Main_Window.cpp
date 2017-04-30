/*
 * Main_Window.cpp
 *
 *  Created on: 30 avr. 2017
 *      Author: guill
 */

#include "Application/Windows/Main_Window.h"

Main_Window::Main_Window(Picaso::Serial_Commander& lcd) : Touchable_Window(lcd),
button_moving(m_lcd, "Moving Window", Picaso::Color::RED, Picaso::Color::BLACK, 10, 70, 450/2, 90),
button_monitor(m_lcd, "Process Monitor", Picaso::Color::RED, Picaso::Color::BLACK, 10, 70+100, 450/2, 90),
button_spreading(m_lcd, "Spreading Window", Picaso::Color::RED, Picaso::Color::BLACK, 20 + 450/2, 70, 450/2, 90),
button_tilt(m_lcd, "Tilt Window", Picaso::Color::RED, Picaso::Color::BLACK, 20 + 450/2, 70+100, 450/2, 90),
m_title(m_lcd, "BE POO 2017", Picaso::Color::WHITE, 10, 10, 320, 60, 3, Picaso::Alignment_H::CENTER, Picaso::Alignment_V::CENTER, false),
m_names(m_lcd, "Combattelli Julien \n\rSarthou Guillaume", Picaso::Color::WHITESMOKE, 320, 10, 480-320, 60, 1, Picaso::Alignment_H::CENTER, Picaso::Alignment_V::CENTER, false)
{
	m_lcd = lcd;
	button_moving.add_receiver(*this);
	button_monitor.add_receiver(*this);
	button_spreading.add_receiver(*this);
	button_tilt.add_receiver(*this);
	m_touch_dispatcher.register_widget(button_moving);
	m_touch_dispatcher.register_widget(button_monitor);
	m_touch_dispatcher.register_widget(button_spreading);
	m_touch_dispatcher.register_widget(button_tilt);

	add_event_handler<Picaso::Button_Pressed>(&Main_Window::button_pressed_handler, this);
}

Main_Window::~Main_Window()
{

}

void Main_Window::show()
{
	m_lcd.gfx_clear_screen();
	button_moving.show();
	button_monitor.show();
	button_spreading.show();
	button_tilt.show();
	m_title.show();
	m_names.show();
}

void Main_Window::button_pressed_handler(Sender& s, const Event& event)
{
	unsigned int id = ((Picaso::Widget&)s).get_id();

	if(id == button_moving.get_id())
		button_moving_pressed();
	else if (id == button_monitor.get_id())
		button_monitor_pressed();
	else if(id == button_spreading.get_id())
		button_spreading_pressed();
	else if(id == button_tilt.get_id())
		button_tilt_pressed();
}

void Main_Window::button_moving_pressed()
{

}

void Main_Window::button_monitor_pressed()
{

}

void Main_Window::button_spreading_pressed()
{

}

void Main_Window::button_tilt_pressed()
{

}
