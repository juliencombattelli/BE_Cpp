//============================================================================
// Name        : Touch_Dispatcher.cpp
// Authors     : Julien Combattelli & Guillaume Sarthou
// EMail       : open.pode@gmail.com
// Date		   : 19 avr. 2017
// Version     : 1.0.0
// Copyright   : This file is part of PicasoSDK project which is released under
//               MIT license. See file LICENSE.txt for full license details
// Description : It provides a class responsible of touch event notification to widgets
//============================================================================

#include "PicasoSDK/Gui/Touch_Dispatcher.h"
#include "PicasoSDK/Gui/Rect.h"
#include "PicasoSDK/Core/Events.h"
#include "PicasoSDK/LcdDriver/Serial_Commander.h"
#include "PicasoSDK/Widgets/Widget.h"

namespace Picaso
{

Touch_Dispatcher::Touch_Dispatcher()
{
}

Touch_Dispatcher::~Touch_Dispatcher()
{
}

void Touch_Dispatcher::touch_periodic_task(Serial_Commander& lcd)
{
	Touch_Event touch_state;
   
    switch(lcd.touch_get(0))
    {
        case 1 :
            touch_state = Touch_Event::touch_began;
            break;
        case 2 :
            touch_state = Touch_Event::touch_ended;
            break;
        case 3 :
        	touch_state = Touch_Event::touch_moved;
        	break;
        default :
        	touch_state = Touch_Event::not_touched;
        	break;
    }
    
    if(touch_state != Touch_Event::not_touched)
    {
    	Point touch_point;
        touch_point.x = lcd.touch_get(1);
        touch_point.y = lcd.touch_get(2);
        
        raise(Touch_Screen_Event(touch_point, touch_state));
    }
}
    
void Touch_Dispatcher::register_widget(Widget& widget)
{
    add_receiver(widget);
}

} // namespace Picaso
