//============================================================================
// Name        : Widget.h
// Authors     : Julien Combattelli & Guillaume Sarthou
// EMail       : open.pode@gmail.com
// Date		   : 19 avr. 2017
// Version     : 1.0.0
// Copyright   : This file is part of PicasoSDK project which is released under
//               MIT license. See file LICENSE.txt for full license details
// Description : It provides a base class for all widgets use by PicasoSDK
//============================================================================

#ifndef PICASO_WIDGET_H_
#define PICASO_WIDGET_H_

#include "PicasoSDK/Core/Event.h"
#include "PicasoSDK/LcdDriver/Serial_Commander.h"
#include "PicasoSDK/Gui/Rect.h"

namespace Picaso
{

class Widget : public Receiver, public Sender
{
public:

	Widget(Serial_Commander& lcd) : m_lcd(lcd){}
	virtual ~Widget() = default;

	virtual void show() = 0;

protected:

	Serial_Commander& m_lcd;
	Rect m_boundingBox;
};

} // namespace Picaso

#endif // PICASO_WIDGET_H_
