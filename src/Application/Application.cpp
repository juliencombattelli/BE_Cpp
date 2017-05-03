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
	switch(((Moving_Button_Pressed)e).m_dir)
	{
	case Moving_Button_Pressed::front : packet.append(std::vector<char>{0x01, 0x01}); break;
	case Moving_Button_Pressed::back : packet.append(std::vector<char>{0x01, 0x02}); break;
	case Moving_Button_Pressed::left : packet.append(std::vector<char>{0x01, 0x03}); break;
	case Moving_Button_Pressed::right : packet.append(std::vector<char>{0x01, 0x04}); break;
	default : packet.append(std::vector<char>{0x01, 0x00}); break;
	}
	m_socket.send(packet);
}

void Application::send_tilt_command(Sender& s, const Event& e)
{
	bt::Packet packet;
	int8_t pitch = ((Tilt_Change)e).m_x;
	if(pitch > 100)
		pitch = 100;
	else if(pitch < -100)
		pitch = -100;
	int8_t roll = ((Tilt_Change)e).m_y;
	if(roll > 100)
		roll = 100;
	else if(roll < -100)
		roll = -100;
	packet.append(std::vector<char>{0x02, pitch, roll});
	m_socket.send(packet);
}

void Application::send_spreading_command(Sender& s, const Event& e)
{
	bt::Packet packet;
	uint8_t heigth = ((Spreading_Change)e).m_heigth;
	heigth = heigth*255;
	uint8_t spread = ((Spreading_Change)e).m_spread;
	spread = spread*255;
	packet.append(std::vector<char>{0x02, spread, heigth});
	m_socket.send(packet);
}

