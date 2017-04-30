/*
 * Process_Monitor.h
 *
 *  Created on: 30 avr. 2017
 *      Author: guill
 */

#ifndef APPLICATION_WINDOWS_PROCESS_MONITOR_H_
#define APPLICATION_WINDOWS_PROCESS_MONITOR_H_

#include "Application/Windows/Window_Template.h"

class Process_Monitor : public Window_Template
{
public:
	Process_Monitor(Picaso::Serial_Commander& lcd);
	virtual ~Process_Monitor();

private:
	void custom_show();

	Picaso::Label m_title;
	Picaso::Label m_process;
};


#endif /* APPLICATION_WINDOWS_PROCESS_MONITOR_H_ */
