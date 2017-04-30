/*
 * Process_Monitor.cpp
 *
 *  Created on: 30 avr. 2017
 *      Author: guill
 */

#include "Application/Windows/Process_Monitor.h"

Process_Monitor::Process_Monitor(Picaso::Serial_Commander& lcd) : Window_Template(lcd),
m_title(lcd, "Process Monitor", Picaso::Color::WHITE, 70, 20, 250, 40, 2, Picaso::Alignment_H::CENTER, Picaso::Alignment_V::CENTER, false),
m_process(lcd, "Process :", Picaso::Color::RED, 15, 75, 480-20-10, 272-80-10-10, 1, Picaso::Alignment_H::LEFT, Picaso::Alignment_V::TOP, false)
{

}

Process_Monitor::~Process_Monitor()
{

}

void Process_Monitor::custom_show()
{
	m_title.show();
	m_lcd.gfx_draw_rectangle(10, 70, 480-10, 272-10, Picaso::Color::GRAY);
	m_process.show();
}


