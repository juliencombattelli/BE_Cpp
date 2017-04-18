//============================================================================
// Name        : Touch_Dispatcher.h
// Authors     : Julien Combattelli & Guillaume Sarthou
// EMail       : open.pode@gmail.com
// Date		   : 19 avr. 2017
// Version     : 1.0.0
// Copyright   : This file is part of PicasoSDK project which is released under
//               MIT license. See file LICENSE.txt for full license details
// Description : It provides a class responsible of touch event notification to widgets
//============================================================================

#ifndef PICASO_TOUCH_DISPATCHER_H_
#define PICASO_TOUCH_DISPATCHER_H_

#include "PicasoSDK/Core/Event.h"

namespace Picaso
{

class Serial_Commander;
class Widget;

class Touch_Dispatcher : public Sender
{
public :

	Touch_Dispatcher();

	~Touch_Dispatcher();

    void touch_periodic_task(Serial_Commander& lcd);

    void register_widget(Widget& widget);
};

} // namespace Picaso

#endif // PICASO_TOUCH_DISPATCHER_H_
