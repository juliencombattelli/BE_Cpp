/*
 * Spreading_Window.cpp
 *
 *  Created on: 29 avr. 2017
 *      Author: guill
 */

#include "Application/Windows/Spreading_Window.h"
#include "Application/Events.h"
#include "iostream"

Spreading_Window::Spreading_Window(Picaso::Serial_Commander& lcd) : Window_Template(lcd),
m_title(lcd, "Spreading window", Picaso::Color::WHITE, 70, 20, 250, 40, 2, Picaso::Alignment_H::CENTER, Picaso::Alignment_V::CENTER, false),
m_heigth(lcd, Picaso::Color::WHITE, Picaso::Color::GRAY, Picaso::Color::WHITESMOKE, 20, 80, 40, 270-80-20, false),
m_spread(lcd, Picaso::Color::WHITE, Picaso::Color::GRAY, Picaso::Color::WHITESMOKE, 20 +40 +10, 80 + 270-80-20-40, 270, 40, false)
{
	m_touch_dispatcher.register_widget(m_heigth);
	m_touch_dispatcher.register_widget(m_spread);

	m_heigth.add_receiver(*this);
	m_spread.add_receiver(*this);

	add_event_handler<Picaso::Slider_Moved>(&Spreading_Window::slider_moved_handler, this);
}

Spreading_Window::~Spreading_Window()
{

}

void Spreading_Window::custom_show()
{
	m_title.show();
	m_heigth.show();
	m_spread.show();
}

void Spreading_Window::slider_moved_handler(Sender& s, const Event& event)
{
	unsigned int id = ((Picaso::Widget&)s).get_id();

	if(id==m_heigth.get_id())
		heigth_change(((Picaso::SliderV&)s).get_per_cent());
	else if(id==m_spread.get_id())
		spread_change(((Picaso::SliderH&)s).get_per_cent());
}

void Spreading_Window::heigth_change(float value)
{
	raise(spreading_change(m_spread.get_per_cent(), value));
}

void Spreading_Window::spread_change(float value)
{
	raise(spreading_change(value, m_heigth.get_per_cent()));
}
