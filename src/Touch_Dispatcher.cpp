#include "touch_dispatcher.h"
#include "PicasoSDK/Gui/Point.h"
#include "PicasoSDK/Core/Events.h"

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
    
void Touch_Dispatcher::clear_components()
{
    m_listening_components.clear();
}

} // namespace Picaso
