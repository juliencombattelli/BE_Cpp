/*
 * Titl_Window.cpp
 *
 *  Created on: 29 avr. 2017
 *      Author: guill
 */

#include "Application/Windows/Titl_Window.h"

Titl_Window::Titl_Window(Picaso::Serial_Commander& lcd) : Window_Template(lcd),
m_title(lcd, "Tilt window", Picaso::Color::WHITE, 70, 20, 250, 40, 2, Picaso::Alignment_H::CENTER, Picaso::Alignment_V::CENTER, false),
m_x_label(lcd, "X", Picaso::Color::WHITE, 480-20, 80+(272-80)/2 - 10, 20, 20, 1, Picaso::Alignment_H::CENTER, Picaso::Alignment_V::CENTER, false),
m_y_label(lcd, "Y", Picaso::Color::WHITE, 480/2-10, 60, 20, 20, 1, Picaso::Alignment_H::CENTER, Picaso::Alignment_V::CENTER, false)
{

}

Titl_Window::~Titl_Window()
{

}

void Titl_Window::custom_show()
{
	m_title.show();
	m_lcd.gfx_draw_line(480/2, 80, 480/2, 272-20, Picaso::Color::GRAY);
	m_lcd.gfx_draw_line(20, 80 + (272-80)/2, 460, 80 + (272-80)/2, Picaso::Color::GRAY);
	m_x_label.show();
	m_y_label.show();
}
