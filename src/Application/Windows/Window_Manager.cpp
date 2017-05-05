//============================================================================
// Name        : Window_Manager.cpp
// Authors     : Julien Combattelli & Guillaume Sarthou
// EMail       : open.pode@gmail.com
// Date		   : 30 avr. 2017
// Version     : 1.0.0
// Copyright   : This file is part of PicasoSDK project which is released under
//               MIT license. See file LICENSE.txt for full license details
// Description : It provides a window manager class responsible of the demo
//				 app windows lifetime
//============================================================================

#include "Application/Windows/Window_Manager.h"

#include "Application/Windows/Tilt_Window.h"
#include "Application/Windows/Moving_Window.h"
#include "Application/Windows/Spreading_Window.h"
#include "Application/Windows/Process_Monitor.h"
#include "Application/Windows/Main_Window.h"

#include "Application/Application.h"
#include "Application/Events.h"

Window_Manager::Window_Manager() :
	Window_Manager_Base(0, 13,9600)
{
	m_windows.emplace_back(std::make_unique<Main_Window>(m_lcd));
	m_windows.emplace_back(std::make_unique<Moving_Window>(m_lcd));
	m_windows.emplace_back(std::make_unique<Tilt_Window>(m_lcd));
	m_windows.emplace_back(std::make_unique<Spreading_Window>(m_lcd));
	m_windows.emplace_back(std::make_unique<Process_Monitor>(m_lcd));

	for(auto& window : m_windows)
		window->add_receiver(*this);

	add_event_handler<Navigation_Button_Pressed>(&Window_Manager::navigation_handler, this);
	add_event_handler<Navigation_Choise_Pressed>(&Window_Manager::navigation_choise_handler, this);

	m_lcd.touch_set(0);
	m_lcd.touch_detect_region(0,0,480,480);

	m_activeWindow = 0;
	m_windows[m_activeWindow]->show();
}

void Window_Manager::register_windows(Application& application)
{
	for(auto& window : m_windows)
		window->add_receiver(application);
}

void Window_Manager::update()
{
	if(m_activeWindow < m_windows.size())
		m_windows[m_activeWindow]->update();
}

void Window_Manager::navigation_handler(Sender& s, const Event& e)
{
	const Navigation_Button_Pressed& event = static_cast<decltype(event)>(e);

	if(event.type == Navigation_Button_Pressed::Return)
	{
		m_activeWindow = 0;
		m_windows[m_activeWindow]->show();
	}
	else if(event.type == Navigation_Button_Pressed::Previous)
	{
		m_activeWindow--;
		if(!m_activeWindow)
			m_activeWindow = 4;
		m_windows[m_activeWindow]->show();
	}
	else if(event.type == Navigation_Button_Pressed::Next)
	{
		m_activeWindow++;
		if(m_activeWindow>4)
			m_activeWindow = 1;
		m_windows[m_activeWindow]->show();
	}
}

void Window_Manager::navigation_choise_handler(Sender& s, const Event& e)
{
	const Navigation_Choise_Pressed& event = static_cast<decltype(event)>(e);

	m_activeWindow = event.index;
	m_windows[m_activeWindow]->show();
}
