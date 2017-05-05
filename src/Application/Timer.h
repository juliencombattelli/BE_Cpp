//============================================================================
// Name        : Timer.h
// Authors     : Julien Combattelli & Guillaume Sarthou
// EMail       : open.pode@gmail.com
// Date		   : 5 avr. 2017
// Version     : 1.0.0
// Copyright   : This file is part of PicasoSDK project which is released under
//               MIT license. See file LICENSE.txt for full license details
// Description : It provides a simple timer class based on C++11 std::chrono
//============================================================================

#ifndef APPLICATION_TIMER_H_
#define APPLICATION_TIMER_H_

#include <chrono>
#include <iostream>

class Timer
{
public:
	using Clock = std::chrono::high_resolution_clock;

	// Constructeur
	Timer() { restart(); }

	// Reset la durée du timer
	void restart() { m_epoch = Clock::now(); }

	// Donne le temps écoulé depuis le dernier restart en millisecondes
	int time_elapsed_ms() const { return std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - m_epoch).count(); }

private:

	Clock::time_point m_epoch;
};

#endif /* APPLICATION_TIMER_H_ */
