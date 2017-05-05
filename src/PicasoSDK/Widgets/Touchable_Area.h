//============================================================================
// Name        : Touchable_Area.h
// Authors     : Julien Combattelli & Guillaume Sarthou
// EMail       : open.pode@gmail.com
// Date		   : 30 avr. 2017
// Version     : 1.0.0
// Copyright   : This file is part of PicasoSDK project which is released under
//               MIT license. See file LICENSE.txt for full license details
// Description : It provides a touchable area widget
//============================================================================

#ifndef PICASOSDK_WIDGETS_TOUCHABLE_AREA_H_
#define PICASOSDK_WIDGETS_TOUCHABLE_AREA_H_

#include "PicasoSDK/Widgets/Touchable_Widget.h"

namespace Picaso
{

class Touchable_Area : public Touchable_Widget
{
public:
	Touchable_Area(Serial_Commander& lcd, uint16_t x_origin = 0, uint16_t y_origin = 0, uint16_t width = 20, uint16_t height = 20, uint16_t rel_x_origin = 0, uint16_t rel_y_origin = 0);

	virtual ~Touchable_Area();

	virtual void show() override;

	void change_size(uint16_t width, uint16_t height);
	void change_origin(uint16_t x_origin, uint16_t y_origin);

private:
    virtual void touch_event_handler(Sender&, const Event&) override;

    uint16_t m_rel_x_origin, m_rel_y_origin;
};

} //namespace Picaso


#endif /* PICASOSDK_WIDGETS_TOUCHABLE_AREA_H_ */
