/*
 * Window_Template.h
 *
 *  Created on: 25 avr. 2017
 *      Author: guill
 */

#ifndef APPLICATION_WINDOWS_WINDOW_TEMPLATE_H_
#define APPLICATION_WINDOWS_WINDOW_TEMPLATE_H_

#include "PicasoSDK/Gui/Touchable_Window.h"

#include "PicasoSDK/Widgets/Button.h"

class Window_Template : public Picaso::Touchable_Window
{
public:
	Window_Template(Picaso::Serial_Commander& lcd);
	virtual ~Window_Template();

	void show();

protected:
	virtual void custom_show() {};

	void button_pressed_handler(Sender& s, const Event& event);
	virtual void custom_button_pressed_handler(unsigned int button_id) {}

	Picaso::Button button_return;
	Picaso::Button button_next;
	Picaso::Button button_prev;

private:
	void button_return_pressed();
	void button_next_pressed();
	void button_prev_pressed();
};



#endif /* APPLICATION_WINDOWS_WINDOW_TEMPLATE_H_ */
