//============================================================================
// Name        : Event.hpp
// Author      : Julien Combattelli
// EMail       : julien.combattelli@hotmail.com
// Date		   : 19 avr. 2016
// Version     : 1.0.0
// Copyright   : This file is part of MUL project which is released under
//               MIT license. See file LICENSE.txt for full license details
// Description : It provides an observer implementation to handling events
//============================================================================

#ifndef EVENT_H_
#define EVENT_H_

#include <vector>
#include <unordered_map>
#include <typeindex>
#include <functional>

class Receiver;

class Event
{
public:
	virtual ~Event() = default;
};

enum class Notify_Action
{
	Done,
	Un_Register
};

class Sender
{
public:
	void add_receiver(Receiver& observer);
	void pop_receiver(Receiver& observer);
	void raise(Event const& event);

private:
	std::vector<Receiver*> m_receivers;
};

class Receiver
{
public:
	virtual ~Receiver() {}
	virtual Notify_Action on_notify(Sender& sender, Event const& event);

	template<typename TEvent, typename TMethod, typename TObject>
	void add_event_handler(TMethod&& method, TObject&& obj)
	{
		m_handlers[typeid(TEvent)] = std::bind(method, obj, std::placeholders::_1, std::placeholders::_2);
	}

private:
	std::unordered_map<std::type_index,std::function<void(Sender&, Event const&)>> m_handlers;
};

#endif // EVENT_H_
