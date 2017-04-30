/*
 * Timer.h
 *
 *  Created on: 30 avr. 2017
 *      Author: JulienCombattelli
 */

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
