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
	enum direction
	{
		front = 1,
		back = -1,
		right = 2,
		left = -2,
		none = 0,
	};

	Moving_Button_Pressed(direction dir) : m_dir(dir) {}

	direction m_dir;
};

struct Tilt_change : public Event
{
	Tilt_change(float x, float y) : m_x(x), m_y(y) {}

	float m_x;
	float m_y;
};

struct spreading_change : public Event
{
	spreading_change(float spread, float heigth) : m_spread(spread), m_heigth(heigth) {}

	float m_spread;
	float m_heigth;
};

#endif /* APPLICATION_EVENTS_H_ */
