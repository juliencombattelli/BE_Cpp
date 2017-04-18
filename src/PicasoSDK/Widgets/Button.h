/*
 * ulcd_button.h
 *
 *
 *
 */

#ifndef ULCD_BUTTON_H
#define ULCD_BUTTON_H

#include "Widget.h"
//#include <iostream>
#include <string>
#include "PicasoSDK/LcdDriver/Picaso_Serial_Commander.h"
#include "Label.h"

namespace Picaso
{

class Button : public Widget
{
public :

	Button(Serial_Commander& lcd, std::string text, Color color1 = Color::ORANGE, Color color2 = Color::BLACK, uint16_t x_origin = 0, uint16_t y_origin = 0, uint16_t width = 20, uint16_t height = 20, int font_size = 1);

	Button(Serial_Commander& lcd);

	~Button();

    void set_button();

    void inverse_button();

    void change_color(Color color1, Color color2);

    void change_size(uint16_t width, uint16_t height);

    void change_origin(uint16_t x_origin, uint16_t y_origin);

    void change_font_size(int font_size);

    void change_text(std::string text);

    void create_button(std::string text, Color color1, Color color2, uint16_t x_origin, uint16_t y_origin, uint16_t width, uint16_t height, int font_size);

    std::string get_label() const {return m_label.get_text();}

private :

    Label m_label;

    static const int border_width = 2;

    Color m_border_color;
    Color m_fill_color;
    uint16_t x_release;
    uint16_t y_release;
	uint16_t touch;

    virtual void touch_event_handler(Sender&, const Event&);

};

} // namespace Picaso

#endif
