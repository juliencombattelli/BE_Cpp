

#include "touch_dispatcher.h"
#include "PicasoSDK/LcdDriver/Picaso_Serial_Commander.h"
#include "PicasoSDK/Widgets/Button.h"
#include "PicasoSDK/Core/Events.h"
#include <iostream>
#include <utility>

class WindowBase : public Receiver
{
public:
	virtual ~WindowBase() = default;
};

class WindowHello : public WindowBase
{

};

class WindowManager : public Receiver
{
public:
	WindowManager() : m_lcd(0, 13,9600)
	{
		m_lcd.touch_set(0);
		m_lcd.touch_detect_region(0,0,480,480);
		add_event_handler<Picaso::Button_Pressed>(&WindowManager::button_pressed_handler, this);
	}

	template<class TWidget, typename...Args>
	TWidget& createWidget(Args&&... args)
	{
		TWidget& widget = *new TWidget(m_lcd, std::forward<Args>(args)...);
		m_touch_dispatcher.register_widget(widget);
		return widget;
	}

	void run()
	{
		Picaso::Button button(m_lcd, "hello", Picaso::Color::WHITE, Picaso::Color::RED, 0, 0, 200, 100, 1);
		button.add_receiver(*this);
		m_touch_dispatcher.register_widget(button);
		while(1)
		{
			//std::cout << "a" << std::endl;
			m_touch_dispatcher.touch_periodic_task(m_lcd);
		}
	}

	void button_pressed_handler(Sender& s, const Event& event)
	{
		std::cout << "button pressed" << std::endl;
	}

private:
	Picaso::Touch_Dispatcher m_touch_dispatcher;
	Picaso::Serial_Commander m_lcd;
};

int main(void)
{
	std::cout << "start !" << std::endl;
	WindowManager mgr;
	//mgr.createWidget<Picaso::Button>("hello", );

	mgr.run();

	return 0;
}

