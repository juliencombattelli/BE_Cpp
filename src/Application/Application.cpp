//============================================================================
// Name        : Application.cpp
// Authors     : Julien Combattelli & Guillaume Sarthou
// EMail       : open.pode@gmail.com
// Date		   : 5 may 2017
// Version     : 1.0.0
// Copyright   : This file is part of PicasoSDK project which is released under
//               MIT license. See file LICENSE.txt for full license details
// Description : It provides a demo application class
//============================================================================

#include "Application/Application.h"
#include "Application/Events.h"
#include <exception>
#include <initializer_list>

Application::Application() :
	m_is_running(true)
{
	add_event_handler<Moving_Button_Pressed>(&Application::send_direction_command, this);
	add_event_handler<Tilt_Change>(&Application::send_tilt_command, this);
	add_event_handler<Spreading_Change>(&Application::send_spreading_command, this);

	m_window_manager.register_windows(*this);
}

Application::~Application()
{
	std::cout << "Closing application" << std::endl;
}

void Application::run(int period_ms)
{
	std::cout << "Try to connect to B8:27:EB:7C:3D:9D" << std::endl;
	bt::Status status = m_socket.connect("B8:27:EB:7C:3D:9D", 1);

	if(status == bt::Status::Done)
		std::cout << "Connected to B8:27:EB:7C:3D:9D" << std::endl;
	else
		std::cout << "Failed to connect to B8:27:EB:7C:3D:9D" << std::endl;

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
	const Moving_Button_Pressed& event = static_cast<decltype(event)>(e);

	std::vector<int8_t> data;

	switch(event.dir)
	{
	case Moving_Button_Pressed::front :
		data.push_back(0x01);
		data.push_back(0x01);
		break;
	case Moving_Button_Pressed::back :
		data.push_back(0x01);
		data.push_back(0x02);
		break;
	case Moving_Button_Pressed::left :
		data.push_back(0x01);
		data.push_back(0x03);
		break;
	case Moving_Button_Pressed::right :
		data.push_back(0x01);
		data.push_back(0x04);
		break;
	default :
		data.push_back(0x01);
		data.push_back(0x00);
		break;
	}

	std::cout << "Sending direction command ..." << std::endl;

	size_t sent = 0;
	bt::Status status = m_socket.send(data.data(), data.size(), sent);

	if(status == bt::Status::Done)
		std::cout << "Direction command sent" << std::endl;
	else
		std::cout << "Failed to send direction command; code = " << bt::StatusStr[static_cast<int>(status)] << std::endl;
}

void Application::send_tilt_command(Sender& s, const Event& e)
{
	const Tilt_Change& event = static_cast<decltype(event)>(e);

	float pitch = event.x;
	if(pitch > 100)
		pitch = 100;
	else if(pitch < -100)
		pitch = -100;

	float roll = event.y;
	if(roll > 100)
		roll = 100;
	else if(roll < -100)
		roll = -100;

	std::vector<int8_t> data{0x03, int8_t(pitch), int8_t(roll)};

	std::cout << "Sending tilt command ..." << std::endl;

	size_t sent = 0;
	bt::Status status = m_socket.send(data.data(), data.size(), sent);

	if(status == bt::Status::Done)
		std::cout << "Tilt command sent" << std::endl;
	else
		std::cout << "Failed to send tilt command; code = " << bt::StatusStr[static_cast<int>(status)] << std::endl;
}

void Application::send_spreading_command(Sender& s, const Event& e)
{
	const Spreading_Change& event = static_cast<decltype(event)>(e);

	uint8_t height = event.height*255;

	uint8_t spread = event.spread*255;

	std::vector<uint8_t> data{0x02, spread, height};

	std::cout << "Sending spreading command ..." << std::endl;

	size_t sent = 0;
	bt::Status status = m_socket.send(data.data(), data.size(), sent);

	if(status == bt::Status::Done)
		std::cout << "Spreading command sent" << std::endl;
	else
		std::cout << "Failed to send spreading command; code = " << bt::StatusStr[static_cast<int>(status)] << std::endl;
}

