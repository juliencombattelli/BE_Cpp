/*
 * Window_Manager.cpp
 *
 *  Created on: 30 avr. 2017
 *      Author: guill
 */

#include "Application/Windows/Window_Manager.h"

#include "Application/Windows/Tilt_Window.h"
#include "Application/Windows/Moving_Window.h"
#include "Application/Windows/Spreading_Window.h"
#include "Application/Windows/Process_Monitor.h"
#include "Application/Windows/Main_Window.h"

#include "Application/Application.h"
#include "Application/Events.h"

Window_Manager::Window_Manager() : Window_Manager_Base(0, 13,9600)
{
	m_windows.emplace_back(std::make_unique<Main_Window>(m_lcd));
	m_windows.emplace_back(std::make_unique<Moving_Window>(m_lcd));
	m_windows.emplace_back(std::make_unique<Tilt_Window>(m_lcd));
	m_windows.emplace_back(std::make_unique<Spreading_Window>(m_lcd));
	m_windows.emplace_back(std::make_unique<Process_Monitor>(m_lcd));

	m_windows[0]->add_receiver(*this);
	m_windows[1]->add_receiver(*this);
	m_windows[2]->add_receiver(*this);
	m_windows[3]->add_receiver(*this);
	m_windows[4]->add_receiver(*this);

	add_event_handler<Navigation_Button_Pressed>(&Window_Manager::navigation_handler, this);

	m_windows[0]->show();
	m_activeWindow = 0;
}

Window_Manager::~Window_Manager()
{

}

void Window_Manager::Register_windows(Application& application)
{
	m_windows[0]->add_receiver(application);
	m_windows[1]->add_receiver(application);
	m_windows[2]->add_receiver(application);
	m_windows[3]->add_receiver(application);
	m_windows[4]->add_receiver(application);
}

void Window_Manager::update()
{
	m_windows[m_activeWindow]->update();
}

void Window_Manager::navigation_handler(Sender& s, const Event& event)
{
	Navigation_Button_Pressed& e = (Navigation_Button_Pressed&)event;

	if(e.type == Navigation_Button_Pressed::Return)
	{
		m_activeWindow = 0;
		m_windows[m_activeWindow]->show();
	}
	else if(e.type == Navigation_Button_Pressed::Previous)
	{
		m_activeWindow--;
		if(!m_activeWindow)
			m_activeWindow = 4;
		m_windows[m_activeWindow]->show();
	}
	else if(e.type == Navigation_Button_Pressed::Next)
	{
		m_activeWindow++;
		if(!m_activeWindow>=4)
			m_activeWindow = 1;
		m_windows[m_activeWindow]->show();
	}
}
