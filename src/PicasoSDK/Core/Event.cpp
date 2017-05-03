//============================================================================
// Name        : Event.cpp
// Authors     : Julien Combattelli & Guillaume Sarthou
// EMail       : open.pode@gmail.com
// Date		   : 19 avr. 2017
// Version     : 1.0.0
// Copyright   : This file is part of PicasoSDK project which is released under
//               MIT license. See file LICENSE.txt for full license details
// Description : It provides an observer implementation to handling events
//============================================================================

#include "PicasoSDK/Core/Event.h"
#include <algorithm>
#include <stdexcept>

void Sender::add_receiver(Receiver& observer)
{
	if(std::find(std::begin(m_receivers), std::end(m_receivers), &observer) != std::end(m_receivers))
	{
		throw std::runtime_error("addReceiver(): receiver already registered");
	}
	m_receivers.push_back(&observer);
}

void Sender::pop_receiver(Receiver& observer)
{
	m_receivers.erase(std::remove(std::begin(m_receivers), std::end(m_receivers),&observer), std::end(m_receivers));
}

void Sender::raise(Event const& event)
{
	std::vector<Receiver*> deadReceivers;
	for(Receiver* receiver : m_receivers)
	{
		if(receiver->on_notify(*this, event) == Notify_Action::Un_Register)
		{
			// TODO : check if receiver is listening other event (aka it has other entries in m_handler)
			//deadReceivers.push_back(receiver);
		}
	}

	/*auto newEnd = std::end(m_receivers);
	for(Receiver* dead : deadReceivers)
	{
		newEnd = std::remove(std::begin(m_receivers), newEnd, dead);
	}
	m_receivers.erase(newEnd, std::end(m_receivers));*/
}

Notify_Action Receiver::on_notify(Sender& sender, Event const& event)
{
	auto find = m_handlers.find(typeid(event));

	if(find != m_handlers.end())
	{
		find->second(sender, event);
		return Notify_Action::Done;
	}
	else
	{
		return Notify_Action::Un_Register;
	}

}
