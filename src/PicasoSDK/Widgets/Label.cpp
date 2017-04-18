#include "Label.h"

namespace Picaso
{

Label::Label(Serial_Commander& lcd,std::string text, Color foreground_color, uint16_t x_origin, uint16_t y_origin, uint16_t width, uint16_t height, int font_size, Alignment_H h_alignment, Alignment_V v_alignment, bool auto_update) :
	Widget(lcd)
{
    m_lcd = lcd;

    m_alignment.h = h_alignment;
    m_alignment.v = v_alignment;
    m_boundingBox.origin.x = x_origin;
    m_boundingBox.origin.y = y_origin;
    m_boundingBox.size.width = width;
    m_boundingBox.size.height = height;
    m_foreground_color = foreground_color;
    m_background_color = Color::BLACK;
    m_font_size = font_size;
    m_text = text;
    m_auto_update = auto_update;

    update_attributes();
    write_text();
}

Label::Label(Serial_Commander& lcd, bool auto_update) : Widget(lcd)
{
    m_alignment.h = Alignment_H::h_left;
    m_alignment.v = Alignment_V::v_top;
    m_boundingBox.origin.x = 0;
    m_boundingBox.origin.y = 0;
    m_boundingBox.size.width = 20;
    m_boundingBox.size.height = 20;
    m_foreground_color = Color::WHITE;
    m_background_color = Color::BLACK;
    m_font_size = 1;
    m_auto_update = auto_update;
}

Label::~Label()
{

}


/*
 * private functions
 *
 */
void Label::update_attributes()
{
    m_lcd.txt_set_font(3);
    m_lcd.txt_width_multiplier(m_font_size);
    m_lcd.txt_height_multiplier(m_font_size);
    m_lcd.txt_foreground_color(m_foreground_color);
    m_lcd.txt_background_color(m_background_color);
}

void Label::write_text()
{
    uint8_t sector = 0;
    uint8_t u = m_lcd.txt_char_width('0');
    uint8_t nb_car_max = m_boundingBox.size.width/u;
    uint8_t nb_car_per_sector[100];
    uint8_t car_index_total = 0;
    uint8_t car_index = 0;
    uint16_t size_text = m_text.size();
    std::string text_cpy;
    char buffer[100];
    text_cpy = m_text;

    uint16_t y_location = 0, x_location = 0;
    if(nb_car_max != 0)
    {
        while(car_index_total < size_text)
        {
            car_index += nb_car_max;

            if(car_index < size_text)
            {
                while((text_cpy[car_index] != ' ') && (car_index_total != car_index))
                    car_index --;

                if(car_index_total == car_index)
                {
                    car_index += nb_car_max;
                }
                else
                {
                    text_cpy.erase(car_index,1);
                    size_text = text_cpy.size();
                }
            }
            else
                car_index = size_text;

            nb_car_per_sector[sector] = car_index - car_index_total;
            sector ++;
            car_index_total = car_index;
        }

        switch(m_alignment.v)
        {
            case Alignment_V::v_top:
                y_location = m_boundingBox.origin.y;
                break;

            case Alignment_V::v_bottom:
                y_location = (m_boundingBox.origin.y + m_boundingBox.size.height) - sector*m_lcd.txt_char_height('0');
                break;

            case Alignment_V::v_center:
                y_location = ((m_boundingBox.size.height - sector*m_lcd.txt_char_height('0')) / 2) + m_boundingBox.origin.y;
                break;
        }

        car_index = 0;
        for(uint8_t i = 0; i < sector; i++)
        {
             switch(m_alignment.h)
            {
                case Alignment_H::h_left:
                    x_location = m_boundingBox.origin.x;
                    break;

                case Alignment_H::h_right:
                	x_location = (m_boundingBox.origin.x + m_boundingBox.size.width) - nb_car_per_sector[i]*m_lcd.txt_char_width('0');
                	break;

                case Alignment_H::h_center:
                	x_location = ((m_boundingBox.size.width - nb_car_per_sector[i]*m_lcd.txt_char_width('0'))/2) + m_boundingBox.origin.x;
                	break;
            }
            text_cpy.copy(buffer,nb_car_per_sector[i], car_index);
            buffer[nb_car_per_sector[i]] = 0;
            car_index += nb_car_per_sector[i];

            m_lcd.gfx_move_origin(x_location, y_location);
            m_lcd.txt_put_str((uint8_t*)buffer);

            y_location += m_lcd.txt_char_height('0');
        }
    }
}

/*
 * public functions
 *
 */

void Label::show_label()
{
    update_attributes();
    write_text();
}

void Label::show_delimitation()
{
    m_lcd.gfx_draw_filled_rectangle(
    		m_boundingBox.origin.x,
			m_boundingBox.origin.y,
			m_boundingBox.origin.x + m_boundingBox.size.width,
			m_boundingBox.origin.y + m_boundingBox.size.height,
			m_background_color);
    write_text();
}

void Label::change_color(Color foreground_color, Color background_color)
{
    m_foreground_color = foreground_color;
    m_background_color = background_color;
    if(m_auto_update)
    {
		update_attributes();
		write_text();
    }
}

void Label::change_size(uint16_t width, uint16_t height)
{
	m_boundingBox.size.width = width;
	m_boundingBox.size.height = height;
	if(m_auto_update)
	{
		update_attributes();
		write_text();
	}
}

void Label::change_origin(uint16_t x_origin, uint16_t y_origin)
{
	m_boundingBox.origin.x = x_origin;
	m_boundingBox.origin.y = y_origin;
	if(m_auto_update)
	{
		update_attributes();
		write_text();
	}
}

void Label::change_alignment(Alignment_H h_alignment, Alignment_V v_alignment)
{
    m_alignment.h = h_alignment;
    m_alignment.v = v_alignment;
    if(m_auto_update)
    {
		update_attributes();
		write_text();
    }
}

void Label::change_font_size(int font_size)
{
    m_font_size = font_size;
    if(m_auto_update)
    {
		update_attributes();
		write_text();
    }
}

void Label::change_text(std::string text)
{
    m_text = text;
    if(m_auto_update)
    {
		update_attributes();
		write_text();
    }
}

void Label::new_label(std::string text, Color foreground_color, uint16_t x_origin, uint16_t y_origin, uint16_t width, uint16_t height, int font_size, Alignment_H h_alignment, Alignment_V v_alignment)
{
    m_alignment.h = h_alignment;
    m_alignment.v = v_alignment;
    m_boundingBox.origin.x = x_origin;
    m_boundingBox.origin.y = y_origin;
    m_boundingBox.size.width = width;
    m_boundingBox.size.height = height;
    m_foreground_color = foreground_color;
    m_font_size = font_size;
    m_text = text;

    update_attributes();
    write_text();
}

} // namespace Picaso
