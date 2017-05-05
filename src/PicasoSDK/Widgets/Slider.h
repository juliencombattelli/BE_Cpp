//============================================================================
// Name        : Slider.h
// Authors     : Julien Combattelli & Guillaume Sarthou
// EMail       : open.pode@gmail.com
// Date		   : 19 avr. 2017
// Version     : 1.0.0
// Copyright   : This file is part of PicasoSDK project which is released under
//               MIT license. See file LICENSE.txt for full license details
// Description : It provides a slider base widget
//============================================================================

#ifndef PICASO_SLIDER_H_
#define PICASO_SLIDER_H_

#include "PicasoSDK/Widgets/Touchable_Widget.h"
#include <string>

namespace Picaso
{

class Slider : public Touchable_Widget
{
public:

    Slider(Serial_Commander& lcd, Color border_color, Color fill_color = Color::BLACK, Color button_color = Color::GRAY, uint16_t origin_x = 0, uint16_t origin_y = 0, uint16_t width = 20, uint16_t height = 20, bool auto_update = true);
    Slider(Serial_Commander& lcd, bool auto_update = true);

	virtual ~Slider() = default;

    virtual void create(Color border_color = Color::ORANGE, Color fill_color = Color::BLACK, Color button_color = Color::GRAY, uint16_t x_origin = 0, uint16_t y_origin = 0, uint16_t width = 20, uint16_t height = 20) = 0;

    void change_color(Color border_color, Color fill_color);
    void change_size(uint16_t width, uint16_t height);
    void change_origin(uint16_t x_origin, uint16_t y_origin);

    float get_per_cent() const { return m_per_cent; }

protected:

    virtual void update_button() = 0;

    static const int border_width = 2;

    Color m_border_color;
    Color m_fill_color;
    Color m_button_color;
    float m_per_cent;
    Size m_size_standard;
    Size m_size_pressed;
    bool m_auto_update;
};

} // namespace Picaso

#endif // PICASO_SLIDER_H_

