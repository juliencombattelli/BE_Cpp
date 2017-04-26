//============================================================================
// Name        : Events.h
// Authors     : Julien Combattelli & Guillaume Sarthou
// EMail       : open.pode@gmail.com
// Date		   : 19 avr. 2017
// Version     : 1.0.0
// Copyright   : This file is part of PicasoSDK project which is released under
//               MIT license. See file LICENSE.txt for full license details
// Description : It provides all necessary events used by PicasoSDK
//============================================================================

#ifndef PICASO_EVENTS_H_
#define PICASO_EVENTS_H_

#include "PicasoSDK/Core/Event.h"
#include "PicasoSDK/Gui/Rect.h"

namespace Picaso
{

enum class Touch_Event
{
    not_touched,
    touch_began,
    touch_moved,
    touch_ended
};

struct Touch_Screen_Event : public Event
{
	Touch_Screen_Event(Point touch_point, Touch_Event touch_state) :
		point(touch_point), state(touch_state) {}

	Point point;
	Touch_Event state;
};

struct Button_Pressed : public Event
{

};

struct Slider_Moved : public Event
{
	Slider_Moved(float current_per_cent) :
		m_current_per_cent(current_per_cent) {}

	float m_current_per_cent;
};

} // namespace Picaso

#endif // PICASO_EVENTS_H_
