#include "PicasoSDK/Widgets/Slider.h"
#include "PicasoSDK/Core/Events.h"

namespace Picaso
{

Slider::Slider(Serial_Commander& lcd,
		Color border_color,
		Color fill_color,
		Color button_color,
		uint16_t origin_x,
		uint16_t origin_y,
		uint16_t width,
		uint16_t height) :
	Widget(lcd)
{
	add_event_handler<Touch_Screen_Event>(&Slider::touch_event_handler, this);

    m_boundingBox.origin.x = origin_x;
    m_boundingBox.origin.y = origin_y;

    m_boundingBox.size.height = height;
    m_boundingBox.size.width = width;

    m_border_color = border_color;
    m_fill_color = fill_color;
    m_button_color = button_color;

    m_size_pressed.width = 6;
    m_size_pressed.height = height - 4;
    m_size_standard.width = 12;
    m_size_standard.height = height;

    touch = 0;
    m_per_cent = 0.5;

    set_slider();
}

Slider::Slider(Serial_Commander& lcd) :
		Widget(lcd)
{
	add_event_handler<Touch_Screen_Event>(&Slider::touch_event_handler, this);

    m_boundingBox.origin.x = 0;
    m_boundingBox.origin.y = 0;

    m_boundingBox.size.height = 20;
    m_boundingBox.size.width = 20;

    m_border_color = Color::ORANGE;
    m_fill_color = Color::BLACK;
    m_button_color = Color::GRAY;

    m_size_pressed.width = 6;
    m_size_pressed.height = m_boundingBox.size.height - 4;
    m_size_standard.width = 12;
    m_size_standard.height = m_boundingBox.size.height;

    touch = 0;
    m_per_cent = 0.5;
}

Slider::~Slider()
{

}

void Slider::round_angle(Color color)
{
    /*uint16_t pixel_color;

    pixel_color = m_lcd->gfx_read_pixel(rect.origin.x-1, rect.origin.y-1);
    m_lcd->gfx_draw_pixel(rect.origin.x, rect.origin.y, pixel_color);
    m_lcd->gfx_draw_pixel(rect.origin.x+1, rect.origin.y, pixel_color);
    m_lcd->gfx_draw_pixel(rect.origin.x, rect.origin.y+1, pixel_color);

    pixel_color = m_lcd->gfx_read_pixel(rect.origin.x + rect.size.width +1, rect.origin.y-1);
    m_lcd->gfx_draw_pixel(rect.origin.x + rect.size.width, rect.origin.y, pixel_color);
    m_lcd->gfx_draw_pixel(rect.origin.x + rect.size.width - 1, rect.origin.y, pixel_color);
    m_lcd->gfx_draw_pixel(rect.origin.x + rect.size.width , rect.origin.y+1, pixel_color);

    pixel_color = m_lcd->gfx_read_pixel(rect.origin.x-1, rect.origin.y + rect.size.height + 1);
    m_lcd->gfx_draw_pixel(rect.origin.x, rect.origin.y + rect.size.height, pixel_color);
    m_lcd->gfx_draw_pixel(rect.origin.x+1, rect.origin.y + rect.size.height, pixel_color);
    m_lcd->gfx_draw_pixel(rect.origin.x, rect.origin.y + rect.size.height - 1, pixel_color);

    pixel_color = m_lcd->gfx_read_pixel(rect.origin.x + rect.size.width +1, rect.origin.y + rect.size.height + 1);
    m_lcd->gfx_draw_pixel(rect.origin.x + rect.size.width, rect.origin.y + rect.size.height, pixel_color);
    m_lcd->gfx_draw_pixel(rect.origin.x + rect.size.width - 1, rect.origin.y +rect.size.height, pixel_color);
    m_lcd->gfx_draw_pixel(rect.origin.x + rect.size.width, rect.origin.y + rect.size.height - 1, pixel_color);*/
}

void Slider::touch_event_handler(Sender& sender, const Event& event)
{
	const Touch_Screen_Event& touch_event = static_cast<decltype(touch_event)>(event);
    switch(touch_event.state)
    {
        case Touch_Event::touch_began:
            if(Rect::is_inside(touch_event.point, m_boundingBox))
            {
                m_per_cent = (float)(touch_event.point.x - m_boundingBox.origin.x) / (float)(m_boundingBox.size.width);

                m_lcd.gfx_draw_filled_rectangle(
                		m_boundingBox.origin.x,
						m_boundingBox.origin.y,
						m_boundingBox.origin.x + m_boundingBox.size.width,
						m_boundingBox.origin.y + m_boundingBox.size.height,
						m_border_color);
                round_angle(m_border_color);
                update_button();
                //m_delegate->did_move_slider(this, m_per_cent);
                raise(Slider_Moved(m_per_cent));
                touch = 1;
            }
            break;

        case Touch_Event::touch_ended :
			if(touch == 1)
			{
				set_slider();
				touch=0;
			}
			break;

        case Touch_Event::touch_moved:
            if(Rect::is_inside(touch_event.point, m_boundingBox))
            {
                m_per_cent = (float)(touch_event.point.x - m_boundingBox.origin.x) / (float)(m_boundingBox.size.width - 4);
                update_button();
                //m_delegate->did_move_slider(this, m_per_cent);
                raise(Slider_Moved(m_per_cent));
            }
            break;

        default :
        	break;
    }
}

void Slider::set_slider()
{
    m_lcd.gfx_draw_filled_rectangle(
    		m_boundingBox.origin.x,
			m_boundingBox.origin.y,
			m_boundingBox.origin.x + m_boundingBox.size.width,
			m_boundingBox.origin.y + m_boundingBox.size.height,
			m_border_color);

    m_lcd.gfx_draw_filled_rectangle(
    		m_boundingBox.origin.x + 2,
			m_boundingBox.origin.y + 2,
			m_boundingBox.origin.x + m_boundingBox.size.width - 2,
			m_boundingBox.origin.y + m_boundingBox.size.height - 2,
			m_fill_color);

    round_angle(m_border_color);

    if(m_boundingBox.size.width*m_per_cent - m_size_standard.width/2 < 2)
        m_lcd.gfx_draw_filled_rectangle(
        		m_boundingBox.origin.x + 2,
				m_boundingBox.origin.y + 1,
				m_boundingBox.origin.x + (m_boundingBox.size.width - 4)*m_per_cent + m_size_standard.width/2,
				m_boundingBox.origin.y + m_boundingBox.size.height - 1,
				m_button_color);
    else if(m_boundingBox.size.width*m_per_cent + m_size_standard.width/2 > m_boundingBox.size.width - 2)
        m_lcd.gfx_draw_filled_rectangle(
        		m_boundingBox.origin.x + (m_boundingBox.size.width - 4)*m_per_cent - m_size_standard.width/2,
				m_boundingBox.origin.y + 1,
				m_boundingBox.origin.x + m_boundingBox.size.width - 2,
				m_boundingBox.origin.y + m_boundingBox.size.height - 1,
				m_button_color);
    else
        m_lcd.gfx_draw_filled_rectangle(
        		m_boundingBox.origin.x + (m_boundingBox.size.width - 4)*m_per_cent - m_size_standard.width/2,
				m_boundingBox.origin.y + 1,
				m_boundingBox.origin.x + (m_boundingBox.size.width - 4)*m_per_cent + m_size_standard.width/2,
				m_boundingBox.origin.y + m_boundingBox.size.height - 1,
				m_button_color);
}

void Slider::update_button()
{
    m_lcd.gfx_draw_filled_rectangle(
    		m_boundingBox.origin.x + 2,
			m_boundingBox.origin.y + 2,
			m_boundingBox.origin.x + m_boundingBox.size.width - 2,
			m_boundingBox.origin.y + m_boundingBox.size.height - 2,
			m_fill_color);

    if(m_boundingBox.size.width*m_per_cent - m_size_pressed.width/2 < 2)
        m_lcd.gfx_draw_filled_rectangle(
        		m_boundingBox.origin.x + 2,
				m_boundingBox.origin.y + 2,
				m_boundingBox.origin.x + (m_boundingBox.size.width - 4)*m_per_cent + m_size_pressed.width/2,
				m_boundingBox.origin.y + m_boundingBox.size.height - 2,
				m_button_color);
    else if(m_boundingBox.size.width*m_per_cent + m_size_pressed.width/2 > m_boundingBox.size.width - 2)
        m_lcd.gfx_draw_filled_rectangle(
        		m_boundingBox.origin.x + (m_boundingBox.size.width - 4)*m_per_cent - m_size_pressed.width/2,
				m_boundingBox.origin.y + 2,
				m_boundingBox.origin.x + m_boundingBox.size.width - 2,
				m_boundingBox.origin.y + m_boundingBox.size.height - 2,
				m_button_color);
    else
        m_lcd.gfx_draw_filled_rectangle(
        		m_boundingBox.origin.x + (m_boundingBox.size.width - 4)*m_per_cent - m_size_pressed.width/2,
				m_boundingBox.origin.y + 2,
				m_boundingBox.origin.x + (m_boundingBox.size.width - 4)*m_per_cent + m_size_pressed.width/2,
				m_boundingBox.origin.y + m_boundingBox.size.height - 2,
				m_button_color);
}

void Slider::change_color(Color border_color, Color fill_color)
{
    m_border_color = border_color;
    m_fill_color = fill_color;
    set_slider();
}

void Slider::change_size(uint16_t width, uint16_t height)
{
	m_boundingBox.size.height = height;
	m_boundingBox.size.width = width;
    set_slider();
}

void Slider::change_origin(uint16_t x_origin, uint16_t y_origin)
{
	m_boundingBox.origin.x = x_origin;
	m_boundingBox.origin.y = y_origin;
    set_slider();
}

void Slider::create_slider(Color border_color, Color fill_color, Color button_color, uint16_t x_origin, uint16_t y_origin, uint16_t width, uint16_t height)
{
	m_boundingBox.origin.x = x_origin;
	m_boundingBox.origin.y = y_origin;

	m_boundingBox.size.height = height;
	m_boundingBox.size.width = width;

    m_border_color = border_color;
    m_fill_color = fill_color;

    touch = 0;

    set_slider();
}

} // namespace Picaso
