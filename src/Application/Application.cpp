/*
 * Application.cpp
 *
 *  Created on: 30 avr. 2017
 *      Author: JulienCombattelli
 */

#include "Application/Application.h"
#include "Application/Events.h"
#include <exception>
#include <initializer_list>

Application::Application() : m_is_running(true)
{
	add_event_handler<Moving_Button_Pressed>(&Application::send_direction_command, this);
	add_event_handler<Tilt_Change>(&Application::send_tilt_command, this);
	add_event_handler<Spreading_Change>(&Application::send_spreading_command, this);
}

Application::~Application()
{
	std::cout << "Closing application" << std::endl;
}

void Application::run(int period_ms)
{
	m_socket.connect("B8:27:EB:7C:3D:9D", 1);
	std::cout << "Connected on B8:27:EB:7C:3D:9D" << std::endl;

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
	bt::Packet packet;
	packet.append(std::vector<char>{0x01, 0x02, 0x03, 0x04});
	m_socket.send(packet);
}

void Application::send_tilt_command(Sender& s, const Event& e)
{
	bt::Packet packet;
	packet.append(std::vector<char>{0x01, 0x02, 0x03, 0x04});
	m_socket.send(packet);
}

void Application::send_spreading_command(Sender& s, const Event& e)
{
	bt::Packet packet;
	packet.append(std::vector<char>{0x01, 0x02, 0x03, 0x04});
	m_socket.send(packet);
}

