/*
 * WindowManagerBase.h
 *
 *  Created on: 30 avr. 2017
 *      Author: JulienCombattelli
 */

#ifndef PICASOSDK_GUI_WINDOW_MANAGER_BASE_H_
#define PICASOSDK_GUI_WINDOW_MANAGER_BASE_H_

#include "PicasoSDK/Core/Event.h"
#include <vector>
#include <memory>

namespace Picaso
{

class Window_Manager_Base : public Receiver
{
public:

	Window_Manager_Base();



protected:

	Picaso::Touch_Dispatcher m_touch_dispatcher;
	Picaso::Serial_Commander m_lcd;
	std::vector<std::unique_ptr<Window_Base>> m_windows;
	size_t m_activeWindow;
};

}  // namespace Picaso

#endif /* PICASOSDK_GUI_WINDOW_MANAGER_BASE_H_ */
