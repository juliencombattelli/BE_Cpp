/*
 * uLCD_4DLibrary.hpp
 * This file is a part of uLCD_4DLibrary
 * Copyright (c) 2015 juliencombattelli, SRTH
 */
#ifndef ULCD_LIB
#define ULCD_LIB

#include "mraa.hpp"
#include "PicasoSDK/Gui/Color.h"

namespace Picaso
{

class Serial_Commander
{
public :

	/*Constructors*/

	Serial_Commander(int uart, int reset_pin, uint32_t baud_rate = 9600);

	/*txt function*/

	uint8_t txt_move_cursor(uint16_t line, uint16_t column);

	uint8_t txt_put_char(uint8_t caractere);

	uint8_t txt_put_str(const uint8_t* str);

	uint16_t txt_char_width(uint8_t car);

	uint16_t txt_char_height(uint8_t car);

	uint16_t txt_foreground_color(Color color);

	uint16_t txt_background_color(Color color);

	uint16_t txt_set_font(uint8_t font);

	uint16_t txt_width_multiplier(uint8_t multiplier);

	uint16_t txt_height_multiplier(uint8_t multiplier);

	uint16_t txt_x_gap(uint8_t pixel_count);

	uint16_t txt_y_gap(uint8_t pixel_count);

	uint16_t txt_bold(bool bold);

	uint16_t txt_inverse(bool inverse);

	uint16_t txt_italic(bool italic);

	uint16_t txt_opacity(bool opaque);

	uint16_t txt_underline(bool underline); //txt_y_gap command is required to be at least 2 for the underline to be visible

	uint16_t txt_attributes(bool bold, bool italic, bool inverse, bool underline); //txt_y_gap command is required to be at least 2 for the underline to be visible

	uint16_t txt_wrap(uint16_t wrap_pixel);

	/*graphics function*/

	uint8_t gfx_clear_screen();

	uint8_t gfx_change_color(Color old_color, Color new_color);

	uint8_t gfx_draw_circle(uint16_t center_x, uint16_t center_y, uint16_t radius, Color color);

	uint8_t gfx_draw_filled_circle(uint16_t center_x, uint16_t center_y, uint16_t radius, Color color);

	uint8_t gfx_draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, Color color);

	uint8_t gfx_draw_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, Color color);

	uint8_t gfx_draw_filled_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, Color color);

	uint8_t gfx_draw_polyline(uint16_t n, uint16_t* x_array, uint16_t* y_array, Color color);

	uint8_t gfx_draw_polygon(uint16_t n, uint16_t* x_array, uint16_t* y_array, Color color);

	uint8_t gfx_draw_filled_polygon(uint16_t n, uint16_t* x_array, uint16_t* y_array, Color color);

	uint8_t gfx_draw_triangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, Color color);

	uint8_t gfx_draw_pixel(uint16_t center_x, uint16_t center_y, Color color);

    Color gfx_read_pixel(uint16_t center_x, uint16_t center_y);

    uint8_t gfx_move_origin(uint16_t x, uint16_t y);

	/*media function*/

	uint16_t media_init();

	uint16_t media_set_addr(uint32_t addr);

	uint16_t media_set_sector(uint32_t sector);

	uint16_t media_read_sector(uint8_t* sector); // sector must be a 512 areas map / set sector before

	uint16_t media_write_sector(uint8_t* sector); // sector must be a 512 areas map / set sector before

	uint16_t media_read_byte(); // set addr before

	uint16_t media_read_word(); // set addr before

	uint16_t media_write_byte(uint8_t byte); // set addr before

	uint16_t media_write_word(uint16_t word); // set addr before

	uint16_t media_display_image(uint16_t x, uint16_t y); // set addr or sector before

	uint16_t media_display_video(uint16_t x, uint16_t y); // set addr or sector before

	uint16_t media_display_video_frame(uint16_t x, uint16_t y, uint16_t frame_number); // set addr or sector before

	/*UART function*/

	uint16_t uart_set_baud_rate(uint32_t baud_rate);

	/* timer function*/

	uint16_t timer_sleep_systeme(uint16_t units); // 1 unit = approximatly 1 second

	/* file function*/

	uint16_t file_last_error();

	uint16_t file_file_count(const int8_t* file_name);

	uint16_t file_file_count_and_display(const int8_t* file_name);

	uint16_t file_find_first_file_and_display(const int8_t* file_name);

	uint16_t file_find_first_file_and_report(const int8_t* file_name_search, uint8_t* file_name_found);

	uint16_t file_find_next_file_and_display();

	uint16_t file_find_next_file_and_report(uint8_t* file_name_found);

	uint16_t file_file_exist(const int8_t* file_name);

	uint16_t file_open_file(const int8_t* file_name, uint8_t mode); // return handle /!\ keep it for closing file or other

	uint16_t file_close_file(uint16_t handle); // use the opening handle

	uint16_t file_read_file(uint16_t size, uint16_t handle, uint8_t* read_file); // use the opening handle

	uint16_t file_file_seek(uint16_t handle, uint32_t byte_position); // use the opening handle

	uint16_t file_file_index(uint16_t handle, uint32_t record_size, uint16_t records_number); // use the opening handle

	uint32_t file_file_index(uint16_t handle); // use the opening handle

	uint16_t file_write_file(uint16_t size, uint16_t handle, const int8_t* write_file); // use the opening handle

	uint32_t file_file_size(uint16_t handle); // use the opening handle

	uint16_t file_display_image(uint16_t handle, uint16_t x, uint16_t y); // use the opening handle

	uint16_t file_screen_capture(uint16_t handle, uint16_t x, uint16_t y, uint16_t width, uint16_t height); // use the opening handle

	uint16_t file_write_char_to_file(uint16_t handle, uint8_t charactere); // use the opening handle

	uint8_t file_read_char_to_file(uint16_t handle); // use the opening handle

	uint16_t file_write_word_to_file(uint16_t handle, uint16_t word); // use the opening handle

	uint16_t file_read_word_to_file(uint16_t handle); // use the opening handle

	uint16_t file_write_string_to_file(const int8_t* str, uint8_t handle); // use the opening handle

	uint16_t file_read_string_from_file(uint16_t size, uint16_t handle, uint8_t* str); // use the opening handle

	uint16_t file_file_erase(const int8_t* file_name);

	uint8_t file_rewind(uint16_t handle); // use the opening handle

    uint16_t file_mount();

    uint16_t file_Unmount();

    uint16_t file_PlayWAV(const char* str);

    /* sound */

    uint8_t snd_Volume(float per_cent);

    uint16_t snd_Pitch(uint16_t pitch); //must be between 4000 and 65535

    uint8_t snd_BufSize(uint8_t bufsize);

    uint8_t snd_Stop();

    uint8_t snd_Pause();

    uint8_t snd_Continue();

    uint16_t snd_Playing();

    /* touch screen function*/

    uint8_t touch_detect_region(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

    uint8_t touch_set(uint8_t mode);

    uint16_t touch_get(uint8_t mode);

private :

	mraa::Uart m_serial;
	mraa::Gpio m_rst;

	void clear_rx_buffer();

	void write_commande(const uint8_t* cmd, uint16_t size);

	void read_commande(uint8_t* cmd, uint16_t size);

	/*media function*/
	uint16_t media_flush();

	/*UART function*/
	uint8_t code_baud_rate(uint32_t baud_rate);
};

} // namespace Picaso

#endif
