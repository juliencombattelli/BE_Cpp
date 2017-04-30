/*
 * Events.h
 *
 *  Created on: 30 avr. 2017
 *      Author: JulienCombattelli
 */

#ifndef APPLICATION_EVENTS_H_
#define APPLICATION_EVENTS_H_

#include "PicasoSDK/Core/Events.h"

struct Navigation_Button_Pressed : public Picaso::Button_Pressed
{
	enum Type
	{
		Previous = -1,
		Next = 1,
		Return = 0,
	};

	Navigation_Button_Pressed(Type t) : type(t) {}

	Type type;
};

#endif /* APPLICATION_EVENTS_H_ */
