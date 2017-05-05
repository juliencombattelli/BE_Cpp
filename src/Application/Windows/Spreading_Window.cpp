//============================================================================
// Name        : Spreading_Window.cpp
// Authors     : Julien Combattelli & Guillaume Sarthou
// EMail       : open.pode@gmail.com
// Date		   : 29 avr. 2017
// Version     : 1.0.0
// Copyright   : This file is part of PicasoSDK project which is released under
//               MIT license. See file LICENSE.txt for full license details
// Description : It provides a window enabling spreading and height control
//				 of target
//============================================================================

#include "Application/Windows/Spreading_Window.h"
#include "Application/Events.h"

Spreading_Window::Spreading_Window(Picaso::Serial_Commander& lcd) :
	Window_Template(lcd),
	m_title(lcd, "Spreading window", Picaso::Color::WHITE, 70, 20, 250, 40, 2, Picaso::Alignment_H::CENTER, Picaso::Alignment_V::CENTER, false),
	m_height(lcd, Picaso::Color::WHITE, Picaso::Color::GRAY, Picaso::Color::WHITESMOKE, 20, 80, 40, 270-80-20, false),
	m_spread(lcd, Picaso::Color::WHITE, Picaso::Color::GRAY, Picaso::Color::WHITESMOKE, 20 +40 +10, 80 + 270-80-20-40, 270, 40, false)
{
	m_touch_dispatcher.register_widget(m_height);
	m_touch_dispatcher.register_widget(m_spread);

	m_height.add_receiver(*this);
	m_spread.add_receiver(*this);

	add_event_handler<Picaso::Slider_Moved>(&Spreading_Window::slider_moved_handler, this);
}

void Spreading_Window::custom_show()
{
	m_title.show();
	m_height.show();
	m_spread.show();
}

void Spreading_Window::slider_moved_handler(Sender& s, const Event& e)
{
	Picaso::Slider& sender = static_cast<decltype(sender)>(s);
	unsigned int id = sender.get_id();

	if(id==m_height.get_id())
		height_change(sender.get_per_cent());
	else if(id==m_spread.get_id())
		spread_change(sender.get_per_cent());
}

void Spreading_Window::height_change(float value)
{
	raise(Spreading_Change(m_spread.get_per_cent(), value));
}

void Spreading_Window::spread_change(float value)
{
	raise(Spreading_Change(value, m_height.get_per_cent()));
}
