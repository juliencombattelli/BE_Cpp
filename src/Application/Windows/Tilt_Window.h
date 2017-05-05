//============================================================================
// Name        : Tilt_Window.h
// Authors     : Julien Combattelli & Guillaume Sarthou
// EMail       : open.pode@gmail.com
// Date		   : 29 avr. 2017
// Version     : 1.0.0
// Copyright   : This file is part of PicasoSDK project which is released under
//               MIT license. See file LICENSE.txt for full license details
// Description : It provides a window enabling tilt control of target
//============================================================================

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
