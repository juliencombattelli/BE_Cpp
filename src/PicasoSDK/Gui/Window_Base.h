//============================================================================
// Name        : Window_Base.h
// Authors     : Julien Combattelli & Guillaume Sarthou
// EMail       : open.pode@gmail.com
// Date		   : 25 avr. 2017
// Version     : 1.0.0
// Copyright   : This file is part of PicasoSDK project which is released under
//               MIT license. See file LICENSE.txt for full license details
// Description : It provides a window base class
//============================================================================

#ifndef PICASOSDK_GUI_WINDOW_BASE_H_
#define PICASOSDK_GUI_WINDOW_BASE_H_

#include "PicasoSDK/LcdDriver/Serial_Commander.h"
#include "PicasoSDK/Core/Events.h"

namespace Picaso
{

class Window_Base : public Sender
{
public:
	Window_Base(Serial_Commander& lcd) : m_lcd(lcd) {}
	virtual ~Window_Base() = default;

	virtual void show() = 0;
	virtual void update() {}

protected:
	Serial_Commander& m_lcd;
};

} // namespace Picaso



#endif /* PICASOSDK_GUI_WINDOW_BASE_H_ */
