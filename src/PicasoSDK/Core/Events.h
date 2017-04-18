/*
 * Events.h
 *
 *  Created on: 16 avr. 2017
 *      Author: JulienCombattelli
 */

#ifndef PICASOSDK_CORE_EVENTS_H_
#define PICASOSDK_CORE_EVENTS_H_

#include "Event.h"

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

#endif /* PICASOSDK_CORE_EVENTS_H_ */
