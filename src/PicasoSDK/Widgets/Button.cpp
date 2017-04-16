#include "Button.h"
#include "PicasoSDK/Core/Events.h"

namespace Picaso
{

Button::Button(Serial_Commander& lcd,std::string text, Color color1, Color color2, uint16_t x_origin, uint16_t y_origin, uint16_t width, uint16_t height, int font_size) :
		Widget(lcd), m_label(lcd)
{
	add_event_handler<Touch_Screen_Event>(&Button::touch_event_handler, this);

    m_label.m_alignment.h = Alignment_H::h_center;
    m_label.m_alignment.v = Alignment_V::v_center;

    //m_label.m_boundingBox.origin.x = x_origin + 2;
    m_boundingBox.origin.x = x_origin;
    //m_label.m_boundingBox.origin.y = y_origin + 2;
    m_boundingBox.origin.y = y_origin;
    m_label.change_origin(x_origin + 2, y_origin + 2);

    //m_label.m_boundingBox.size.height = height;
    m_boundingBox.size.height = height;
    //m_label.m_boundingBox.size.width = width;
    m_boundingBox.size.width = width;
    m_label.change_size(width, height);

    m_color1 = color1;
    m_label.m_foreground_color = color1;
    m_color2 = color2;

    m_label.m_text = text;
    m_label.m_font_size = font_size;

    touch = 0;

    set_button();
}

Button::Button(Serial_Commander& lcd) :
		Widget(lcd), m_label(lcd)
{
	m_label.m_alignment.h = Alignment_H::h_center;
	m_label.m_alignment.v = Alignment_V::v_center;

    //m_label.m_boundingBox.origin.x = 0;
    m_boundingBox.origin.x = 0;
    //m_label.m_boundingBox.origin.y = 0;
    m_boundingBox.origin.y = 0;
    m_label.change_origin(0,0);

    //m_label.m_boundingBox.size.height = 20 - 4;
    m_boundingBox.size.height = 20;
    //m_label.m_boundingBox.size.width = 20 - 4;
    m_boundingBox.size.width = 20;
    m_label.change_size(20 - 4, 20 - 4);

    m_color1 = Color::ORANGE;
    m_label.m_foreground_color = Color::ORANGE;
    m_color2 = Color::BLACK;

    m_label.m_font_size = 1;

    touch = 0;
}

Button::~Button()
{

}


/*
 * private functions
 *
 */
void Button::round_angle(Color color)
{
    Color pixel_color;

    pixel_color = m_lcd.gfx_read_pixel(m_boundingBox.origin.x-1, m_boundingBox.origin.y-1);
    m_lcd.gfx_draw_pixel(m_boundingBox.origin.x, m_boundingBox.origin.y, pixel_color);
    m_lcd.gfx_draw_pixel(m_boundingBox.origin.x+1, m_boundingBox.origin.y, pixel_color);
    m_lcd.gfx_draw_pixel(m_boundingBox.origin.x, m_boundingBox.origin.y+1, pixel_color);

    pixel_color = m_lcd.gfx_read_pixel(m_boundingBox.origin.x + m_boundingBox.size.width +1, m_boundingBox.origin.y-1);
    m_lcd.gfx_draw_pixel(m_boundingBox.origin.x + m_boundingBox.size.width, m_boundingBox.origin.y, pixel_color);
    m_lcd.gfx_draw_pixel(m_boundingBox.origin.x + m_boundingBox.size.width - 1, m_boundingBox.origin.y, pixel_color);
    m_lcd.gfx_draw_pixel(m_boundingBox.origin.x + m_boundingBox.size.width , m_boundingBox.origin.y+1, pixel_color);

    pixel_color = m_lcd.gfx_read_pixel(m_boundingBox.origin.x-1, m_boundingBox.origin.y + m_boundingBox.size.height + 1);
    m_lcd.gfx_draw_pixel(m_boundingBox.origin.x, m_boundingBox.origin.y + m_boundingBox.size.height, pixel_color);
    m_lcd.gfx_draw_pixel(m_boundingBox.origin.x+1, m_boundingBox.origin.y + m_boundingBox.size.height, pixel_color);
    m_lcd.gfx_draw_pixel(m_boundingBox.origin.x, m_boundingBox.origin.y + m_boundingBox.size.height - 1, pixel_color);

    pixel_color = m_lcd.gfx_read_pixel(m_boundingBox.origin.x + m_boundingBox.size.width +1, m_boundingBox.origin.y + m_boundingBox.size.height + 1);
    m_lcd.gfx_draw_pixel(m_boundingBox.origin.x + m_boundingBox.size.width, m_boundingBox.origin.y + m_boundingBox.size.height, pixel_color);
    m_lcd.gfx_draw_pixel(m_boundingBox.origin.x + m_boundingBox.size.width - 1, m_boundingBox.origin.y +m_boundingBox.size.height, pixel_color);
    m_lcd.gfx_draw_pixel(m_boundingBox.origin.x + m_boundingBox.size.width, m_boundingBox.origin.y + m_boundingBox.size.height - 1, pixel_color);

    m_lcd.gfx_draw_pixel(m_boundingBox.origin.x + 2, m_boundingBox.origin.y + 2, color);
    m_lcd.gfx_draw_pixel(m_boundingBox.origin.x + m_boundingBox.size.width - 2, m_boundingBox.origin.y + 2, color);
    m_lcd.gfx_draw_pixel(m_boundingBox.origin.x + 2, m_boundingBox.origin.y + m_boundingBox.size.height - 2, color);
    m_lcd.gfx_draw_pixel(m_boundingBox.origin.x + m_boundingBox.size.width - 2, m_boundingBox.origin.y + m_boundingBox.size.height - 2, color);
}

void Button::touch_event_handler(Sender& sender, const Event& event)
{
	const Touch_Screen_Event& touch_event = static_cast<decltype(touch_event)>(event);
    switch(touch_event.state)
    {
        case Touch_Event::touch_began:
        {
            if(Rect::is_inside(touch_event.point, m_boundingBox))
            {
                inverse_button();
                touch = 1;
            }
        }
        break;
        case Touch_Event::touch_ended :
        {
            if(touch == 1)
            {
                set_button();
                if(Rect::is_inside(touch_event.point, m_boundingBox))
                {
                    //m_delegate->did_select_button(this);
                	raise(Button_Pressed());
                }
                touch=0;
            }
        }
        break;
        default :
        {

        }
        break;
    }
}

/*
 * public functions
 *
 */

void Button::set_button()
{
    m_lcd.gfx_draw_filled_rectangle(
    		m_boundingBox.origin.x,
			m_boundingBox.origin.y,
			m_boundingBox.origin.x + m_boundingBox.size.width,
			m_boundingBox.origin.y + m_boundingBox.size.height,
			m_color1);

    m_lcd.gfx_draw_filled_rectangle(
    		m_boundingBox.origin.x + 2,
			m_boundingBox.origin.y + 2,
			m_boundingBox.origin.x + m_boundingBox.size.width - 2,
			m_boundingBox.origin.y + m_boundingBox.size.height - 2,
			m_color2);

    m_label.change_color(m_color1, m_color2);
    round_angle(m_color1);
}

void Button::inverse_button()
{
    m_lcd.gfx_draw_filled_rectangle(
    		m_boundingBox.origin.x,
			m_boundingBox.origin.y,
			m_boundingBox.origin.x + m_boundingBox.size.width,
			m_boundingBox.origin.y + m_boundingBox.size.height,
			m_color2);

    m_lcd.gfx_draw_filled_rectangle(
    		m_boundingBox.origin.x + 2,
			m_boundingBox.origin.y + 2,
			m_boundingBox.origin.x + m_boundingBox.size.width - 2,
			m_boundingBox.origin.y + m_boundingBox.size.height - 2,
			m_color1);

    m_label.change_color(m_color2, m_color1);
    round_angle(m_color2);
}

void Button::change_color(Color color1, Color color2)
{
    m_color1 = color1;
    m_color2 = color2;
    set_button();
}

void Button::change_size(uint16_t width, uint16_t height)
{
    //m_label.rect.size.height = height;
    m_boundingBox.size.height = height;
    //m_label.rect.size.width = width;
    m_boundingBox.size.width = width;
    m_label.change_size(width, height);
    set_button();
}

void Button::change_origin(uint16_t x_origin, uint16_t y_origin)
{
    //m_label.rect.origin.x = x_origin + 2;
    m_boundingBox.origin.x = x_origin;
    //m_label.rect.origin.y = y_origin + 2;
    m_boundingBox.origin.y = y_origin;
    m_label.change_origin(x_origin + 2, y_origin + 2);
    set_button();
}

void Button::change_font_size(int font_size)
{
    m_label.m_font_size = font_size;
    set_button();
}

void Button::change_text(std::string text)
{
    m_label.m_text = text;
    set_button();
}

void Button::create_button(std::string text, Color color1, Color color2, uint16_t x_origin, uint16_t y_origin, uint16_t width, uint16_t height, int font_size)
{
    m_label.m_alignment.h = Alignment_H::h_center;
    m_label.m_alignment.v = Alignment_V::v_center;

    //m_label.m_boundingBox.origin.x = x_origin + 2;
    m_boundingBox.origin.x = x_origin;
    //m_label.m_boundingBox.origin.y = y_origin + 2;
    m_boundingBox.origin.y = y_origin;
    m_label.change_origin(x_origin + 2, y_origin + 2);

    //m_label.m_boundingBox.size.height = height;
    m_boundingBox.size.height = height;
    //m_label.m_boundingBox.size.width = width;
    m_boundingBox.size.width = width;
    m_label.change_size(width, height);

    m_color1 = color1;
    m_label.m_foreground_color = color1;
    m_color2 = color2;

    m_label.m_text = text;
    m_label.m_font_size = font_size;

    touch = 0;

    set_button();
}

} // namespace Picaso
