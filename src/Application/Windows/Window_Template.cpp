//============================================================================
// Name        : Window_Template.h
// Authors     : Julien Combattelli & Guillaume Sarthou
// EMail       : open.pode@gmail.com
// Date		   : 25 avr. 2017
// Version     : 1.0.0
// Copyright   : This file is part of PicasoSDK project which is released under
//               MIT license. See file LICENSE.txt for full license details
// Description : It provides a template window class used by the demo application
//============================================================================

#include "Application/Windows/Window_Template.h"
#include "Application/Events.h"

Window_Template::Window_Template(Picaso::Serial_Commander& lcd) :
	Touchable_Window(lcd),
	button_return(m_lcd, "return", Picaso::Color::RED, Picaso::Color::BLACK, 340, 20, 80, 40),
	button_next(m_lcd, ">", Picaso::Color::WHITE, Picaso::Color::RED, 430, 20, 40, 40, 1),
	button_prev(m_lcd, "<", Picaso::Color::WHITE, Picaso::Color::RED, 10, 20, 40, 40, 1)
{
	m_lcd = lcd;
	button_return.add_receiver(*this);
	button_next.add_receiver(*this);
	button_prev.add_receiver(*this);
	m_touch_dispatcher.register_widget(button_return);
	m_touch_dispatcher.register_widget(button_next);
	m_touch_dispatcher.register_widget(button_prev);

	add_event_handler<Picaso::Button_Pressed>(&Window_Template::button_pressed_handler, this);
}

void Window_Template::show()
{
	m_lcd.gfx_clear_screen();
	button_return.show();
	button_next.show();
	button_prev.show();
	custom_show();
}

void Window_Template::button_pressed_handler(Sender& s, const Event& e)
{
	Picaso::Widget& widget = static_cast<decltype(widget)>(s);
	unsigned int id = widget.get_id();

	if(id == button_return.get_id())
		button_return_pressed();
	else if (id == button_next.get_id())
		button_next_pressed();
	else if(id == button_prev.get_id())
		button_prev_pressed();
	else
		custom_button_pressed_handler(id);
}

void Window_Template::button_return_pressed()
{
	raise(Navigation_Button_Pressed(Navigation_Button_Pressed::Return));
}

void Window_Template::button_next_pressed()
{
	raise(Navigation_Button_Pressed(Navigation_Button_Pressed::Next));
}

void Window_Template::button_prev_pressed()
{
	raise(Navigation_Button_Pressed(Navigation_Button_Pressed::Previous));
}

