/*
 * Window_Manager.h
 *
 *  Created on: 30 avr. 2017
 *      Author: guill
 */

#ifndef APPLICATION_WINDOWS_WINDOW_MANAGER_H_
#define APPLICATION_WINDOWS_WINDOW_MANAGER_H_

#include "PicasoSDK/Gui/Window_Manager_Base.h"

class Application;

class Window_Manager : public Picaso::Window_Manager_Base
{
public:
	Window_Manager();
	~Window_Manager();

	void Register_windows(Application& application);

private:
};



#endif /* APPLICATION_WINDOWS_WINDOW_MANAGER_H_ */
