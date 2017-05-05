//============================================================================
// Name        : Spreading_Window.h
// Authors     : Julien Combattelli & Guillaume Sarthou
// EMail       : open.pode@gmail.com
// Date		   : 29 avr. 2017
// Version     : 1.0.0
// Copyright   : This file is part of PicasoSDK project which is released under
//               MIT license. See file LICENSE.txt for full license details
// Description : It provides a window enabling spreading and height control
//				 of target
//============================================================================

#ifndef APPLICATION_WINDOWS_SPREADING_WINDOW_H_
#define APPLICATION_WINDOWS_SPREADING_WINDOW_H_

#include "Application/Windows/Window_Template.h"
#include "PicasoSDK/Widgets/SliderH.h"
#include "PicasoSDK/Widgets/SliderV.h"

class Spreading_Window : public Window_Template
{
public:
	Spreading_Window(Picaso::Serial_Commander& lcd);
	virtual ~Spreading_Window();

private:
	void custom_show();

	void slider_moved_handler(Sender& s, const Event& event);

	void height_change(float value);
	void spread_change(float value);

	Picaso::Label m_title;
	Picaso::SliderV m_height;
	Picaso::SliderH m_spread;
};



#endif /* APPLICATION_WINDOWS_SPREADING_WINDOW_H_ */
