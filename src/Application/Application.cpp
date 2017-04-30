/*
 * Application.cpp
 *
 *  Created on: 30 avr. 2017
 *      Author: JulienCombattelli
 */

#include "Application/Application.h"
#include "Application/Events.h"
#include <exception>

Application::Application() : m_is_running(true)
{
	add_event_handler<Moving_Button_Pressed>(&Application::send_direction_command, this);
	add_event_handler<Tilt_Change>(&Application::send_tilt_command, this);
	add_event_handler<Spreading_Change>(&Application::send_spreading_command, this);
}

void Application::run(int period_ms)
{
	while(m_is_running)
	{
		if(m_timer.time_elapsed_ms() > period_ms)
		{
			m_timer.restart();
			try
			{
				m_window_manager.update();
			}
			catch(std::exception& e)
			{
				std::cerr << e.what() << std::endl;
				stop();
			}
		}
	}
}

void Application::stop()
{
	m_is_running = false;
}

void Application::send_direction_command(Sender& s, const Event& e)
{

}

void Application::send_tilt_command(Sender& s, const Event& e)
{

}

void Application::send_spreading_command(Sender& s, const Event& e)
{

}

