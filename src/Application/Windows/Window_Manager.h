//============================================================================
// Name        : Window_Manager.h
// Authors     : Julien Combattelli & Guillaume Sarthou
// EMail       : open.pode@gmail.com
// Date		   : 30 avr. 2017
// Version     : 1.0.0
// Copyright   : This file is part of PicasoSDK project which is released under
//               MIT license. See file LICENSE.txt for full license details
// Description : It provides a window manager class responsible of the demo
//				 app windows lifetime
//============================================================================

#ifndef APPLICATION_WINDOWS_WINDOW_MANAGER_H_
#define APPLICATION_WINDOWS_WINDOW_MANAGER_H_

#include "PicasoSDK/Gui/Window_Manager_Base.h"

class Application;

class Window_Manager : public Picaso::Window_Manager_Base
{
public:
	Window_Manager();

	void register_windows(Application& application);

	void update();

private:
	void navigation_handler(Sender& s, const Event& event);
	void navigation_choise_handler(Sender& s, const Event& event);
};



#endif /* APPLICATION_WINDOWS_WINDOW_MANAGER_H_ */
