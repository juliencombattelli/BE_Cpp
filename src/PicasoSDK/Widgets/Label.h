/*
 * ulcd_label.h
 *
 *
 *
 */

#ifndef ULCD_LABEL_H
#define ULCD_LABEL_H

#include "PicasoSDK/Widgets/Widget.h"
//#include <iostream>
#include <string>
#include <stdint.h>

/*
 * public types
 *
 */

namespace Picaso
{

enum class Alignment_H : uint8_t
{
    h_center,
    h_right,
    h_left
};

enum class Alignment_V : uint8_t
{
    v_center,
    v_top,
    v_bottom
};

struct Alignment
{
	Alignment_V v;
    Alignment_H h;
};

class Label : public Widget
{
public :

	// constructor
    Label(Serial_Commander& p_lcd,
    		std::string text,
			Color foreground_color = Color::WHITE,
			uint16_t x_origin = 0, uint16_t y_origin = 0,
			uint16_t width = 20, uint16_t height = 20,
			int font_size = 1,
			Alignment_H h_alignment = Alignment_H::h_left,
			Alignment_V v_alignment = Alignment_V::v_top);

    Label(Serial_Commander& p_lcd);

    ~Label();

    Alignment m_alignment;
    std::string m_text;
    Color m_foreground_color;
    Color m_background_color;
    int m_font_size;

    void update_attributes();

    void show_label();
    void show_delimitation();
    void change_color(Color foreground_color, Color background_color);
    void change_size(uint16_t width, uint16_t height);
    void change_origin(uint16_t x_origin, uint16_t y_origin);
    void change_alignment(Alignment_H h_alignment, Alignment_V v_alignment);
    void change_font_size(int font);
    void change_text(std::string text);
    void change_text2(std::string text);
    void new_label(std::string text, Color foreground_color, uint16_t x_origin, uint16_t y_origin, uint16_t width, uint16_t height, int font_size, Alignment_H h_alignment, Alignment_V v_alignment);

private :

    void write_text();
};

} // namespace Picaso

#endif
