/*
 * Titl_Window.h
 *
 *  Created on: 29 avr. 2017
 *      Author: guill
 */

#ifndef APPLICATION_WINDOWS_TITL_WINDOW_H_
#define APPLICATION_WINDOWS_TITL_WINDOW_H_

#include "Application/Windows/Window_Template.h"

/*TODO : add touchable array*/

class Titl_Window : public Window_Template
{
public:
	Titl_Window(Picaso::Serial_Commander& lcd);
	virtual ~Titl_Window();

private:
	void custom_show();

	Picaso::Label m_title;
	Picaso::Label m_x_label;
	Picaso::Label m_y_label;
};



#endif /* APPLICATION_WINDOWS_TITL_WINDOW_H_ */
