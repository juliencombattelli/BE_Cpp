/*
 * Moving_Window.cpp
 *
 *  Created on: 29 avr. 2017
 *      Author: guill
 */

#include "Application/Windows/Moving_Window.h"
#include "iostream"

Moving_Window::Moving_Window(Picaso::Serial_Commander& lcd) : Window_Template(lcd),
m_title(lcd, "Moving window", Picaso::Color::WHITE, 70, 20, 250, 40, 2, Picaso::Alignment_H::CENTER, Picaso::Alignment_V::CENTER, false),
m_front(lcd, "front", Picaso::Color::GRAY, Picaso::Color::WHITESMOKE, 480/2 - 50, 85, 100, 70, 2),
m_back(lcd, "back", Picaso::Color::GRAY, Picaso::Color::WHITESMOKE, 480/2 - 50, 85 + 10 + 70, 100, 70, 2),
m_left(lcd, "left", Picaso::Color::GRAY, Picaso::Color::WHITESMOKE, 480/2 - 50 - 10 - 100, 85 + 40, 100, 70, 2),
m_right(lcd, "right", Picaso::Color::GRAY, Picaso::Color::WHITESMOKE, 480/2 - 50 + 10 + 100, 85 + 40, 100, 70, 2)
{
	m_front.add_receiver(*this);
	m_back.add_receiver(*this);
	m_left.add_receiver(*this);
	m_right.add_receiver(*this);
	m_touch_dispatcher.register_widget(m_front);
	m_touch_dispatcher.register_widget(m_back);
	m_touch_dispatcher.register_widget(m_left);
	m_touch_dispatcher.register_widget(m_right);
}

Moving_Window::~Moving_Window()
{

}

void Moving_Window::custom_show()
{
	m_title.show();
	m_front.show();
	m_back.show();
	m_left.show();
	m_right.show();
}

void Moving_Window::custom_button_pressed_handler(unsigned int button_id)
{
	if(button_id == m_front.get_id())
		button_front_pressed();
	else if (button_id == m_back.get_id())
		button_back_pressed();
	else if(button_id == m_left.get_id())
		button_left_pressed();
	else if(button_id == m_right.get_id())
		button_right_pressed();
}

void Moving_Window::button_front_pressed()
{
	std::cout << "front" << std::endl;
}
void Moving_Window::button_back_pressed()
{
	std::cout << "back" << std::endl;
}

void Moving_Window::button_left_pressed()
{
	std::cout << "left" << std::endl;
}

void Moving_Window::button_right_pressed()
{
	std::cout << "right" << std::endl;
}
