//============================================================================
// Name        : Label.h
// Authors     : Julien Combattelli & Guillaume Sarthou
// EMail       : open.pode@gmail.com
// Date		   : 19 avr. 2017
// Version     : 1.0.0
// Copyright   : This file is part of PicasoSDK project which is released under
//               MIT license. See file LICENSE.txt for full license details
// Description : It provides a label widget
//============================================================================

#ifndef PICASO_LABEL_H_
#define PICASO_LABEL_H_

#include "PicasoSDK/Widgets/Widget.h"
#include <string>

namespace Picaso
{

enum class Alignment_H : uint8_t
{
    CENTER,
    RIGHT,
    LEFT
};

enum class Alignment_V : uint8_t
{
    CENTER,
    TOP,
    BOTTOM
};

struct Alignment
{
	Alignment_V v;
    Alignment_H h;
};

class Label : public Widget
{
public :

    Label(Serial_Commander& p_lcd, const std::string& text, Color foreground_color = Color::WHITE, uint16_t x_origin = 0, uint16_t y_origin = 0, uint16_t width = 20, uint16_t height = 20, int font_size = 1, Alignment_H h_alignment = Alignment_H::LEFT, Alignment_V v_alignment = Alignment_V::TOP, bool auto_update = false);
    Label(Serial_Commander& p_lcd, bool auto_update = false);

    ~Label();

    virtual void show() override;

    void create(const std::string& text, Color foreground_color = Color::WHITE, uint16_t x_origin = 0, uint16_t y_origin = 0, uint16_t width = 20, uint16_t height = 20, int font_size = 1, Alignment_H h_alignment = Alignment_H::LEFT, Alignment_V v_alignment = Alignment_V::TOP);

    void show_delimitation();
    void change_color(Color foreground_color, Color background_color);
    void change_size(uint16_t width, uint16_t height);
    void change_origin(uint16_t x_origin, uint16_t y_origin);
    void change_alignment(Alignment_H h_alignment, Alignment_V v_alignment);
    void change_font_size(int font);
    void change_text(const std::string& text);

    std::string get_text() const { return m_text; }

private :

    void write_text();
    void update_attributes();

    Alignment m_alignment;
	std::string m_text;
	Color m_foreground_color;
	Color m_background_color;
	int m_font_size;
	bool m_auto_update;
};

} // namespace Picaso

#endif // PICASO_LABEL_H_
