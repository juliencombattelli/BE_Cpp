//============================================================================
// Name        : Touchable_Widget.h
// Authors     : Julien Combattelli & Guillaume Sarthou
// EMail       : open.pode@gmail.com
// Date		   : 19 avr. 2017
// Version     : 1.0.0
// Copyright   : This file is part of PicasoSDK project which is released under
//               MIT license. See file LICENSE.txt for full license details
// Description : It provides a base class for touchable widget
//============================================================================

#ifndef PICASO_TOUCHABLE_WIDGET_H_
#define PICASO_TOUCHABLE_WIDGET_H_

#include "PicasoSDK/Widgets/Widget.h"

namespace Picaso
{

class Serial_Commander;

class Touchable_Widget : public Widget
{
public:

	Touchable_Widget(Serial_Commander& lcd) : Widget(lcd), m_is_touch(false) {}
	virtual ~Touchable_Widget() = default;

	bool is_touch() const { return m_is_touch; }

protected:

	virtual void touch_event_handler(Sender&, Event const&) = 0;

	bool m_is_touch;
};

} // namespace Picaso

#endif // PICASO_TOUCHABLE_WIDGET_H_
