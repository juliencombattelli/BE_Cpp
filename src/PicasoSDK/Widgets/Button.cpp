#include "Button.h"
#include "PicasoSDK/Core/Events.h"

namespace Picaso
{

Button::Button(Serial_Commander& lcd,std::string text, Color border_color, Color fill_color, uint16_t x_origin, uint16_t y_origin, uint16_t width, uint16_t height, int font_size) :
		Widget(lcd), m_label(lcd, false)
{
	add_event_handler<Touch_Screen_Event>(&Button::touch_event_handler, this);

	m_label.change_alignment(Alignment_H::h_center, Alignment_V::v_center);

    m_boundingBox.origin.x = x_origin;
    m_boundingBox.origin.y = y_origin;
    m_label.change_origin(x_origin + border_width, y_origin + border_width);

    m_boundingBox.size.height = height;
    m_boundingBox.size.width = width;
    m_label.change_size(width, height);

    m_border_color = border_color;
    m_fill_color = fill_color;
    m_label.change_color(m_border_color, m_fill_color);

    m_label.change_text(text);
    m_label.change_font_size(font_size);

    touch = 0;

    set_button();
}

Button::Button(Serial_Commander& lcd) :
		Widget(lcd), m_label(lcd, false)
{
	m_label.change_alignment(Alignment_H::h_center, Alignment_V::v_center);

    m_boundingBox.origin.x = 0;
    m_boundingBox.origin.y = 0;
    m_label.change_origin(0,0);

    m_boundingBox.size.height = 20;
    m_boundingBox.size.width = 20;
    m_label.change_size(20 - 2*border_width, 20 - 2*border_width);

    m_border_color = Color::ORANGE;
    m_fill_color = Color::BLACK;
    m_label.change_color(m_border_color, m_fill_color);

    m_label.change_font_size(1);

    touch = 0;
}

Button::~Button()
{

}


/*
 * private functions
 *
 */

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
			m_border_color);

    m_lcd.gfx_draw_filled_rectangle(
    		m_boundingBox.origin.x + border_width,
			m_boundingBox.origin.y + border_width,
			m_boundingBox.origin.x + m_boundingBox.size.width - border_width,
			m_boundingBox.origin.y + m_boundingBox.size.height - border_width,
			m_fill_color);

    m_label.change_color(m_border_color, m_fill_color);
    m_label.show_label();
}

void Button::inverse_button()
{
    m_lcd.gfx_draw_filled_rectangle(
    		m_boundingBox.origin.x,
			m_boundingBox.origin.y,
			m_boundingBox.origin.x + m_boundingBox.size.width,
			m_boundingBox.origin.y + m_boundingBox.size.height,
			m_fill_color);

    m_lcd.gfx_draw_filled_rectangle(
    		m_boundingBox.origin.x + border_width,
			m_boundingBox.origin.y + border_width,
			m_boundingBox.origin.x + m_boundingBox.size.width - border_width,
			m_boundingBox.origin.y + m_boundingBox.size.height - border_width,
			m_border_color);

    m_label.change_color(m_fill_color, m_border_color);
    m_label.show_label();
}

void Button::change_color(Color border_color, Color fill_color)
{
	m_border_color = border_color;
	m_fill_color = fill_color;
    set_button();
}

void Button::change_size(uint16_t width, uint16_t height)
{
    m_boundingBox.size.height = height;
    m_boundingBox.size.width = width;
    m_label.change_size(width, height);
    set_button();
}

void Button::change_origin(uint16_t x_origin, uint16_t y_origin)
{
    m_boundingBox.origin.x = x_origin;
    m_boundingBox.origin.y = y_origin;
    m_label.change_origin(x_origin + border_width, y_origin + border_width);
    set_button();
}

void Button::change_font_size(int font_size)
{
    m_label.change_font_size(font_size);
    set_button();
}

void Button::change_text(const std::string& text)
{
    m_label.change_text(text);
    set_button();
}

void Button::create_button(const std::string& text, Color border_color, Color fill_color, uint16_t x_origin, uint16_t y_origin, uint16_t width, uint16_t height, int font_size)
{
    m_label.change_alignment(Alignment_H::h_center, Alignment_V::v_center);

    m_boundingBox.origin.x = x_origin;
    m_boundingBox.origin.y = y_origin;
    m_label.change_origin(x_origin + border_width, y_origin + border_width);

    m_boundingBox.size.height = height;
    m_boundingBox.size.width = width;
    m_label.change_size(width, height);

    m_border_color = border_color;
    m_fill_color = fill_color;
    m_label.change_color(m_border_color, m_fill_color);

    m_label.change_text(text);
    m_label.change_font_size(font_size);

    touch = 0;

    set_button();
}

} // namespace Picaso
