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


