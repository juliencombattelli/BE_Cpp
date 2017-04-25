//============================================================================
// Name        : SliderH
// Authors     : Julien Combattelli & Guillaume Sarthou
// EMail       : open.pode@gmail.com
// Date		   : 19 avr. 2017
// Version     : 1.0.0
// Copyright   : This file is part of PicasoSDK project which is released under
//               MIT license. See file LICENSE.txt for full license details
// Description : It provides a slider widget
//============================================================================

#ifndef PICASO_SLIDERH_H_
#define PICASO_SLIDERH_H_

#include "PicasoSDK/Widgets/Slider.h"
#include "PicasoSDK/Widgets/Touchable_Widget.h"
#include <string>

namespace Picaso
{

class SliderH : public Slider
{
public:

    SliderH(Serial_Commander& lcd, Color border_color, Color fill_color = Color::BLACK, Color button_color = Color::GRAY, uint16_t origin_x = 0, uint16_t origin_y = 0, uint16_t width = 20, uint16_t height = 20, bool auto_update = false);
    SliderH(Serial_Commander& lcd, bool auto_update = false);

	virtual ~SliderH();

    virtual void show() override;
    virtual void create(Color border_color = Color::ORANGE, Color fill_color = Color::BLACK, Color button_color = Color::GRAY, uint16_t x_origin = 0, uint16_t y_origin = 0, uint16_t width = 20, uint16_t height = 20) override;

private:

    virtual void touch_event_handler(Sender&, const Event&) override;

    virtual void update_button() override;
};

} // namespace Picaso

#endif // PICASO_SLIDERH_H_
