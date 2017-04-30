/*
 * Touchable_Window.h
 *
 *  Created on: 25 avr. 2017
 *      Author: guill
 */

#ifndef PICASOSDK_GUI_TOUCHABLE_WINDOW_H_
#define PICASOSDK_GUI_TOUCHABLE_WINDOW_H_

#include "PicasoSDK/Gui/Window_Base.h"
#include "PicasoSDK/Gui/touch_dispatcher.h"

namespace Picaso
{

class Touchable_Window : public Window_Base, public Receiver
{
public:
	Touchable_Window(Serial_Commander& lcd) : Window_Base(lcd) {}
	virtual ~Touchable_Window() = default;

	virtual void show() = 0;
	void update() {m_touch_dispatcher.touch_periodic_task(m_lcd); custom_update(); }
protected:
	virtual void custom_update() {}
	Touch_Dispatcher m_touch_dispatcher;
};

} // namespace Picaso

#endif /* PICASOSDK_GUI_TOUCHABLE_WINDOW_H_ */
