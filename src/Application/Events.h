//============================================================================
// Name        : Events.h
// Authors     : Julien Combattelli & Guillaume Sarthou
// EMail       : open.pode@gmail.com
// Date		   : 5 may 2017
// Version     : 1.0.0
// Copyright   : This file is part of PicasoSDK project which is released under
//               MIT license. See file LICENSE.txt for full license details
// Description : It provides all event classes used by the demo application
//============================================================================

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

struct Navigation_Choise_Pressed : public Picaso::Button_Pressed
{
	Navigation_Choise_Pressed(size_t i) : index(i) {}

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

	Moving_Button_Pressed(direction _dir) : dir(_dir) {}

	direction dir;
};

struct Tilt_Change : public Event
{
	Tilt_Change(float _x, float _y) : x(_x), y(_y) {}

	float x;
	float y;
};

struct Spreading_Change : public Event
{
	Spreading_Change(float _spread, float _height) : spread(_spread), height(_height) {}

	float spread;
	float height;
};

#endif /* APPLICATION_EVENTS_H_ */
