//============================================================================
// Name        : Button.h
// Authors     : Julien Combattelli & Guillaume Sarthou
// EMail       : open.pode@gmail.com
// Date		   : 19 avr. 2017
// Version     : 1.0.0
// Copyright   : This file is part of PicasoSDK project which is released under
//               MIT license. See file LICENSE.txt for full license details
// Description : It provides a button widget
//============================================================================

#ifndef PICASO_BUTTON_H_
#define PICASO_BUTTON_H_

#include "PicasoSDK/Widgets/Touchable_Widget.h"
#include "PicasoSDK/Widgets/Label.h"
#include <string>

namespace Picaso
{

class Button : public Touchable_Widget
{
public:

	Button(Serial_Commander& lcd, const std::string& text, Color color1 = Color::ORANGE, Color color2 = Color::BLACK, uint16_t x_origin = 0, uint16_t y_origin = 0, uint16_t width = 20, uint16_t height = 20, int font_size = 1);
	Button(Serial_Commander& lcd);

	virtual ~Button();

    virtual void show() override;

    void create(const std::string& text, Color border_color, Color fill_color, uint16_t x_origin, uint16_t y_origin, uint16_t width, uint16_t height, int font_size);

    void inverse_button();
    void change_color(Color border_color, Color fill_color);
    void change_size(uint16_t width, uint16_t height);
    void change_origin(uint16_t x_origin, uint16_t y_origin);
    void change_font_size(int font_size);
    void change_text(const std::string& text);

    std::string get_label() const { return m_label.get_text(); }

private:

    virtual void touch_event_handler(Sender&, const Event&) override;

    static const int border_width = 2;

    Label m_label;
    Color m_border_color;
    Color m_fill_color;
};

} // namespace Picaso

#endif // PICASO_BUTTON_H_
