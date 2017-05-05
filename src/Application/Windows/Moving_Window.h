//============================================================================
// Name        : Moving_Window.h
// Authors     : Julien Combattelli & Guillaume Sarthou
// EMail       : open.pode@gmail.com
// Date		   : 29 avr. 2017
// Version     : 1.0.0
// Copyright   : This file is part of PicasoSDK project which is released under
//               MIT license. See file LICENSE.txt for full license details
// Description : It provides a window enabling movement control of target
//============================================================================

#ifndef APPLICATION_WINDOWS_MOVING_WINDOW_H_
#define APPLICATION_WINDOWS_MOVING_WINDOW_H_

#include "Application/Windows/Window_Template.h"

class Moving_Window : public Window_Template
{
public:
	Moving_Window(Picaso::Serial_Commander& lcd);

private:
	virtual void custom_show() override;
	virtual void custom_button_pressed_handler(unsigned int button_id) override;
	void button_pressing_handler(Sender& s, const Event& event);

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
