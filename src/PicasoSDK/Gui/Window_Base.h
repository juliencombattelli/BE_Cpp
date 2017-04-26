/*
 * Window_Base.h
 *
 *  Created on: 25 avr. 2017
 *      Author: guill
 */

#ifndef PICASOSDK_GUI_WINDOW_BASE_H_
#define PICASOSDK_GUI_WINDOW_BASE_H_

#include "PicasoSDK/LcdDriver/Serial_Commander.h"

namespace Picaso
{

class Window_Base
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
