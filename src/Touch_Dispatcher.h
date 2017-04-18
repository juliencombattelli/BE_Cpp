/*
 * touch_dispatcher.h
 *
 *
 *
 */
#ifndef TOUCH_DISPATCHER_H
#define TOUCH_DISPATCHER_H

#include <vector>
#include "PicasoSDK/LcdDriver/Serial_Commander.h"
#include "PicasoSDK/Core/Event.h"
#include "PicasoSDK/Widgets/Widget.h"

namespace Picaso
{

class Touch_Dispatcher : public Sender
{
public :

	Touch_Dispatcher();

	~Touch_Dispatcher();

    void touch_periodic_task(Serial_Commander& lcd);

    void register_widget(Widget& widget);

    void clear_components();

private :

    std::vector<Widget*> m_listening_components;
};

} // namespace Picaso

#endif
