//============================================================================
// Name        : Main_Window.h
// Authors     : Julien Combattelli & Guillaume Sarthou
// EMail       : open.pode@gmail.com
// Date		   : 30 avr. 2017
// Version     : 1.0.0
// Copyright   : This file is part of PicasoSDK project which is released under
//               MIT license. See file LICENSE.txt for full license details
// Description : It provides a home screen for the demo app, allowing the user
//				 to choose control modes
//============================================================================

#ifndef APPLICATION_WINDOWS_MAIN_WINDOW_H_
#define APPLICATION_WINDOWS_MAIN_WINDOW_H_

#include "PicasoSDK/Gui/Touchable_Window.h"

#include "PicasoSDK/Widgets/Button.h"

class Main_Window : public Picaso::Touchable_Window
{
public:
	Main_Window(Picaso::Serial_Commander& lcd);
	virtual ~Main_Window();

	void show();

private:
	void button_pressed_handler(Sender& s, const Event& event);

	Picaso::Button button_moving;
	Picaso::Button button_monitor;
	Picaso::Button button_spreading;
	Picaso::Button button_tilt;
	Picaso::Label m_title;
	Picaso::Label m_names;

	void button_moving_pressed();
	void button_monitor_pressed();
	void button_spreading_pressed();
	void button_tilt_pressed();
};



#endif /* APPLICATION_WINDOWS_MAIN_WINDOW_H_ */
