/*
 * Events.h
 *
 *  Created on: 30 avr. 2017
 *      Author: JulienCombattelli
 */

#ifndef APPLICATION_EVENTS_H_
#define APPLICATION_EVENTS_H_

#include "PicasoSDK/Core/Events.h"
#include "PicasoSDK/Core/Event.h"

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

struct Navigation_choise_Pressed : public Picaso::Button_Pressed
{
	Navigation_choise_Pressed(size_t i) : index(i) {}

	size_t index;
};

struct Moving_Button_Pressed : public Picaso::Button_Pressed
{
	enum X
	{
		front = 1,
		back = -1,
		none = 0,
	};

	enum Y
	{
		right = 1,
		left = -1,
		Return = 0,
	};

	Moving_Button_Pressed(X x, Y y) : m_x(x), m_y(y) {}

	X m_x;
	Y m_y;
};

struct Tilt_change : public Event
{
	Tilt_change(float x, float y) : m_x(x), m_y(y) {}

	float m_x;
	float m_y;
};

#endif /* APPLICATION_EVENTS_H_ */
