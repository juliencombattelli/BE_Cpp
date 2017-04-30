/*
 * Main_Window.h
 *
 *  Created on: 30 avr. 2017
 *      Author: guill
 */

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
