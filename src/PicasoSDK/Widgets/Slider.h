/*
 * ulcd_slider.h
 *
 *
 *
 */

#ifndef PICASO_SLIDER_H
#define PICASO_SLIDER_H

#include "PicasoSDK/Widgets/Widget.h"
//#include <iostream>
#include <string>

namespace Picaso
{

class Slider : public Widget
{
public :

    // constructor
    Slider(Serial_Commander& lcd,
    		Color border_color,
			Color fill_color = Color::BLACK,
			Color button_color = Color::GRAY,
			uint16_t origin_x = 0,
			uint16_t origin_y = 0,
			uint16_t width = 20,
			uint16_t height = 20,
			bool auto_update = true);

    Slider(Serial_Commander& lcd, bool auto_update = true);

	~Slider();

    void show_slider();

    void change_color(Color border_color, Color fill_color);

    void change_size(uint16_t width, uint16_t height);

    void change_origin(uint16_t x_origin, uint16_t y_origin);

    void create_slider(Color border_color = Color::ORANGE, Color fill_color = Color::BLACK, Color button_color = Color::GRAY, uint16_t x_origin = 0, uint16_t y_origin = 0, uint16_t width = 20, uint16_t height = 20);

    float get_per_cent() const {return m_per_cent;}

    virtual void touch_event_handler(Sender& sender, const Event& event);

private :

    static const int border_width = 2;

    void update_button();

    Color m_border_color;
    Color m_fill_color;
    Color m_button_color;
    bool is_touch;
    float m_per_cent;
    Size m_size_standard;
    Size m_size_pressed;
    bool m_auto_update;
};

} // namespace Picaso

#endif // PICASO_SLIDER_H

