/*
 * Moving_Window.h
 *
 *  Created on: 29 avr. 2017
 *      Author: guill
 */

#ifndef APPLICATION_WINDOWS_MOVING_WINDOW_H_
#define APPLICATION_WINDOWS_MOVING_WINDOW_H_

#include "Application/Windows/Window_Template.h"

class Moving_Window : public Window_Template
{
public:
	Moving_Window(Picaso::Serial_Commander& lcd);
	virtual ~Moving_Window();

private:
	void custom_show();
	void custom_button_pressed_handler(unsigned int button_id);

	void button_front_pressed();
	void button_back_pressed();
	void button_left_pressed();
	void button_right_pressed();

	Picaso::Label m_title;
	Picaso::Button m_front;
	Picaso::Button m_back;
	Picaso::Button m_left;
	Picaso::Button m_right;
};


#endif /* APPLICATION_WINDOWS_MOVING_WINDOW_H_ */
