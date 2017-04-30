/*
 * Titl_Window.h
 *
 *  Created on: 29 avr. 2017
 *      Author: guill
 */

#ifndef APPLICATION_WINDOWS_TILT_WINDOW_H_
#define APPLICATION_WINDOWS_TILT_WINDOW_H_

#include "Application/Windows/Window_Template.h"
#include "PicasoSDK/Widgets/Touchable_Area.h"

/*TODO : add touchable array*/

class Tilt_Window : public Window_Template
{
public:
	Tilt_Window(Picaso::Serial_Commander& lcd);
	virtual ~Tilt_Window();

private:
	void custom_show();
	void area_touched_handler(Sender& s, const Event& event);

	Picaso::Label m_title;
	Picaso::Label m_x_label;
	Picaso::Label m_y_label;
	Picaso::Touchable_Area m_area;
};



#endif /* APPLICATION_WINDOWS_TILT_WINDOW_H_ */
