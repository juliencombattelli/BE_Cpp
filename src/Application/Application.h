/*
 * Application.h
 *
 *  Created on: 30 avr. 2017
 *      Author: guill
 */

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
