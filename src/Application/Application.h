//============================================================================
// Name        : Application.h
// Authors     : Julien Combattelli & Guillaume Sarthou
// EMail       : open.pode@gmail.com
// Date		   : 5 may 2017
// Version     : 1.0.0
// Copyright   : This file is part of PicasoSDK project which is released under
//               MIT license. See file LICENSE.txt for full license details
// Description : It provides a demo application class
//============================================================================

#ifndef APPLICATION_APPLICATION_H_
#define APPLICATION_APPLICATION_H_

#include "PicasoSDK/Core/Events.h"
#include "Application/Windows/Window_Manager.h"
#include "Application/Timer.h"
#include "Bluetooth/RfcommSocket.h"

class Application : public Receiver
{
public:

	Application();
	~Application();

	void run(int period_ms);
	void stop();

private:

	void send_direction_command(Sender& s, const Event& e);
	void send_tilt_command(Sender& s, const Event& e);
	void send_spreading_command(Sender& s, const Event& e);

	Window_Manager m_window_manager;
	Timer m_timer;

	bt::RfcommSocket m_socket;

	bool m_is_running;
};

#endif /* APPLICATION_APPLICATION_H_ */
