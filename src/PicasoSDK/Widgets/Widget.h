/*
 * Widget.h
 *
 *  Created on: 13 avr. 2017
 *      Author: JulienCombattelli
 */

#ifndef PICASOSDK_WIDGETS_WIDGET_H_
#define PICASOSDK_WIDGETS_WIDGET_H_

#include "PicasoSDK/Core/Event.h"
#include "PicasoSDK/LcdDriver/Picaso_Serial_Commander.h"
#include "PicasoSDK/Gui/Rect.h"

namespace Picaso
{

class Widget : public Receiver, public Sender
{
public:

	Widget(Serial_Commander& lcd) : m_lcd(lcd){}
	virtual ~Widget() = default;

protected:

	virtual void touch_event_handler(Sender&, Event const&) {}

	Serial_Commander& m_lcd;
	Rect m_boundingBox;
};

} // namespace Picaso

#endif /* PICASOSDK_WIDGETS_WIDGET_H_ */
