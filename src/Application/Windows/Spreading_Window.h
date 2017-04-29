/*
 * Spreading_Window.h
 *
 *  Created on: 29 avr. 2017
 *      Author: guill
 */

#ifndef APPLICATION_WINDOWS_SPREADING_WINDOW_H_
#define APPLICATION_WINDOWS_SPREADING_WINDOW_H_

#include "Application/Windows/Window_Template.h"
#include "PicasoSDK/Widgets/SliderH.h"
#include "PicasoSDK/Widgets/SliderV.h"

class Spreading_Window : public Window_Template
{
public:
	Spreading_Window(Picaso::Serial_Commander& lcd);
	virtual ~Spreading_Window();

private:
	void custom_show();

	void slider_moved_handler(Sender& s, const Event& event);

	void heigth_change(float value);
	void spread_change(float value);

	Picaso::Label m_title;
	Picaso::SliderV m_heigth;
	Picaso::SliderH m_spread;
};



#endif /* APPLICATION_WINDOWS_SPREADING_WINDOW_H_ */
