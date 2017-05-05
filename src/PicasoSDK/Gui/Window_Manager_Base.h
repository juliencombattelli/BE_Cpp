//============================================================================
// Name        : Window_Manager_Base.h
// Authors     : Julien Combattelli & Guillaume Sarthou
// EMail       : open.pode@gmail.com
// Date		   : 30 avr. 2017
// Version     : 1.0.0
// Copyright   : This file is part of PicasoSDK project which is released under
//               MIT license. See file LICENSE.txt for full license details
// Description : It provides a window manager base class
//============================================================================

#ifndef PICASOSDK_GUI_WINDOW_MANAGER_BASE_H_
#define PICASOSDK_GUI_WINDOW_MANAGER_BASE_H_

#include "PicasoSDK/Core/Event.h"
#include "PicasoSDK/LcdDriver/Serial_Commander.h"
#include "PicasoSDK/Gui/Window_Base.h"
#include <vector>
#include <memory>
#include <limits>

namespace Picaso
{

class Window_Manager_Base : public Receiver
{
public:

	Window_Manager_Base(int uart, int reset_pin, uint32_t baud_rate = 9600) : m_lcd(uart, reset_pin, baud_rate), m_activeWindow(NoActive) {}

	virtual ~Window_Manager_Base() = default;

	virtual void update() = 0;

protected:

	Serial_Commander m_lcd;
	std::vector<std::unique_ptr<Window_Base>> m_windows;
	size_t m_activeWindow;

	static const size_t NoActive = std::numeric_limits<size_t>::max();
};

}  // namespace Picaso

#endif /* PICASOSDK_GUI_WINDOW_MANAGER_BASE_H_ */
