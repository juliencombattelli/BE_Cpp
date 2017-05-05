//============================================================================
// Name        : Process_Monitor.h
// Authors     : Julien Combattelli & Guillaume Sarthou
// EMail       : open.pode@gmail.com
// Date		   : 30 avr. 2017
// Version     : 1.0.0
// Copyright   : This file is part of PicasoSDK project which is released under
//               MIT license. See file LICENSE.txt for full license details
// Description : It provides a window enabling process monitoring of the target
// 				 Linux environment
//============================================================================

#ifndef APPLICATION_WINDOWS_PROCESS_MONITOR_H_
#define APPLICATION_WINDOWS_PROCESS_MONITOR_H_

#include "Application/Windows/Window_Template.h"

class Process_Monitor : public Window_Template
{
public:
	Process_Monitor(Picaso::Serial_Commander& lcd);

private:
	virtual void custom_show() override;

	Picaso::Label m_title;
	Picaso::Label m_process;
};


#endif /* APPLICATION_WINDOWS_PROCESS_MONITOR_H_ */
