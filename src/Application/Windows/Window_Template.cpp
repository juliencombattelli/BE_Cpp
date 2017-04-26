/*
 * Window_Template.cpp
 *
 *  Created on: 25 avr. 2017
 *      Author: guill
 */

#include "Application/Windows/Window_Template.h"
#include "iostream"

Window_Template::Window_Template(Picaso::Serial_Commander& lcd) : Touchable_Window(lcd),
button_return(lcd, "return", Picaso::Color::RED, Picaso::Color::BLACK, 340, 20, 80, 40),
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

Window_Template::~Window_Template()
{

}

void Window_Template::show()
{
	m_lcd.gfx_clear_screen();
	button_return.show();
	button_next.show();
	button_prev.show();
	custom_show();
}

void Window_Template::button_pressed_handler(Sender& s, const Event& event)
{
	unsigned int id = ((Picaso::Widget&)s).get_id();

	if(id == button_return.get_id())
		button_return_pressed();
	else if (id == button_next.get_id())
		button_next_pressed();
	else if(id == button_prev.get_id())
		button_prev_pressed();
	else
		custom_button_pressed_handler(((Picaso::Widget&)s).get_id());
}

void Window_Template::button_return_pressed()
{
	std::cout << "return" << std::endl;
}

void Window_Template::button_next_pressed()
{
	std::cout << "next" << std::endl;
}

void Window_Template::button_prev_pressed()
{
	std::cout << "prev" << std::endl;
}

