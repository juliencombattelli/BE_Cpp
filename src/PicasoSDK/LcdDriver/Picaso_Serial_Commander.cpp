/*
* Serial_Commander.cpp
* This file is a part of Serial_Commander
* Copyright (c) 2015 juliencombattelli, SRTH
*/

#include "Picaso_Serial_Commander.h"

namespace Picaso
{

Serial_Commander::Serial_Commander(int uart, int reset_pin, uint32_t baud_rate) : m_serial(uart), m_rst(reset_pin)
{
	m_serial.setBaudRate(baud_rate);
	m_rst.write(0);
	usleep(500000);
    m_rst.write(1);
    sleep(4);
	clear_rx_buffer();
    uart_set_baud_rate(115200); //576000 marche à peu près
    media_init();
    //while(file_mount() == 0xFFFE);
    file_mount();
}

/*
* private function
*/

void Serial_Commander::clear_rx_buffer()
{
	while(m_serial.dataAvailable())
	{
		m_serial.readStr(1);
	}
}

void Serial_Commander::write_commande(const uint8_t* cmd, uint16_t size)
{
	m_serial.write((const char*)(cmd), size);
}

void Serial_Commander::read_commande(uint8_t* cmd, uint16_t size)
{
	uint32_t cpt = 0;
    clear_rx_buffer();
    for(uint8_t i = 0; i < size; i++)
	{
		cpt = 0;
        while (!m_serial.dataAvailable() && cpt < 500000)
        	cpt ++;
        if(cpt < 490000)
            m_serial.read((char*)&cmd[i], 1);
	}
}

	/*media function*/
uint16_t Serial_Commander::media_flush()
{
	uint8_t cmd[3];
	cmd[0] = 0x00;
	cmd[1] = 0x8A;

	write_commande(cmd, 2);
	read_commande(cmd, 3);
	if(cmd[0] != 0x06)
		return( 0xFFFF ); // error
	else
	{
		if( ((cmd[1] << 8) | cmd[2]) == 0x0000 )
			return( 0xFFFF );
		else
			return( 0x00 );

	}
}

	/*UART function*/
uint8_t Serial_Commander::code_baud_rate(uint32_t baud_rate)
{
    switch(baud_rate)
    {
        case 110:       return 0;
        case 300:       return 1;
        case 600:       return 2;
        case 1200:      return 3;
        case 2400:      return 4;
        case 4800:      return 5;
        case 9600:      return 6;
        case 14400:     return 7;
        case 19200:     return 8;
        case 31250:     return 9;
        case 38400:     return 10;
        case 56000:     return 11;
        case 57600:     return 12;
        case 115200:    return 13;
        case 128000:    return 14;
        case 256000:    return 15;
        case 300000:    return 16;
        case 400000:    return 17;
        case 500000:    return 18;
        case 700000:    return 19;
        case 576000: 	return 18;
        default:        return 20;
    }
}

/*
* public function
*/

	/*txt function*/
uint8_t Serial_Commander::txt_move_cursor(uint16_t line, uint16_t column)
{
	uint8_t cmd[6];
	cmd[0] = 0xFF;
	cmd[1] = 0xE9;
	cmd[2] = (uint8_t)(line >> 8);
	cmd[3] = (uint8_t)line;
	cmd[4] = (uint8_t)(column >> 8);
	cmd[5] = (uint8_t)column;

	write_commande(cmd, 6);
	read_commande(cmd, 1);
	if(cmd[0] == 0x06)
		return 0;
	else
		return 1;
}

uint8_t Serial_Commander::txt_put_char(uint8_t caractere)
{
	uint8_t cmd[4];
	cmd[0] = 0xFF;
	cmd[1] = 0xFE;
	cmd[2] = 0x00;
	cmd[3] = caractere;

	write_commande(cmd, 4);
	read_commande(cmd, 1);
	if(cmd[0] == 0x06)
		return 0;
	else
		return 1;
}

uint8_t Serial_Commander::txt_put_str(const std::string& str)
{
	uint16_t size = str.size();
	uint8_t cmd[3];
	cmd[0] = 0x00;
	cmd[1] = 0x18;
	cmd[2] = 0x00;

	write_commande(cmd, 2);
	write_commande((uint8_t*)str.c_str(), size);
	write_commande(&(cmd[2]), 1);
	read_commande(cmd, 3);
	if(cmd[0] == 0x06)
	{
		if( ((cmd[1]<<8) | cmd[2]) == size)
			return 0;
		else
			return 2;
	}
	else
		return 1;
}

uint16_t Serial_Commander::txt_char_width(uint8_t car)
{
	uint8_t cmd[3];
	cmd[0] = 0x00;
	cmd[1] = 0x1E;
	cmd[2] = car;

	write_commande(cmd, 3);
	read_commande(cmd, 3);
	if(cmd[0] == 0x06)
		return( (uint16_t)(cmd[1]<<8) | cmd[2]); // refert to datasheet
	else
		return 0xFFFF; // impossible value -> error
}

uint16_t Serial_Commander::txt_char_height(uint8_t car)
{
	uint8_t cmd[3];
	cmd[0] = 0x00;
	cmd[1] = 0x1D;
	cmd[2] = car;

	write_commande(cmd, 3);
	read_commande(cmd, 3);
	if(cmd[0] == 0x06)
		return( (uint16_t)(cmd[1]<<8) | cmd[2]); // refert to datasheet
	else
		return 0xFFFF; // impossible value -> error
}

uint16_t Serial_Commander::txt_foreground_color(Color color)
{
	uint8_t cmd[4];
	cmd[0] = 0xFF;
	cmd[1] = 0xE7;
	cmd[2] = (uint8_t)(Color_to_Integral(color) >> 8);
	cmd[3] = (uint8_t)Color_to_Integral(color);

	write_commande(cmd, 4);
	read_commande(cmd, 3);
	if(cmd[0] == 0x06)
		return( (uint16_t)(cmd[1]<<8) | cmd[2]); // previous color
	else
		return 0xFFFF; // error
}

uint16_t Serial_Commander::txt_background_color(Color color)
{
	uint8_t cmd[4];
	cmd[0] = 0xFF;
	cmd[1] = 0xE6;
	cmd[2] = (uint8_t)(Color_to_Integral(color) >> 8);
	cmd[3] = (uint8_t)Color_to_Integral(color);

	write_commande(cmd, 4);
	read_commande(cmd, 3);
	if(cmd[0] == 0x06)
		return( (uint16_t)(cmd[1]<<8) | cmd[2]); // previous color
	else
		return 0xFFFF; // error
}

uint16_t Serial_Commander::txt_set_font(uint8_t font)
{
	uint8_t cmd[4];
	cmd[0] = 0xFF;
	cmd[1] = 0xE5;
	cmd[2] = 0x00;
	if(font > 0 && font < 4)
		cmd[3] = font - 1; // adaptation for font id
	else
		return( 0xFFFE ); // invalid font

	write_commande(cmd, 4);
	read_commande(cmd, 3);
	if(cmd[0] == 0x06)
		return( (uint16_t)(cmd[1]<<8) | cmd[2]); // previous font
	else
		return 0xFFFF; // error
}

uint16_t Serial_Commander::txt_width_multiplier(uint8_t multiplier)
{
	uint8_t cmd[4];
	cmd[0] = 0xFF;
	cmd[1] = 0xE4;
	cmd[2] = 0x00;
	if(multiplier >= 1 && multiplier <= 16)
		cmd[3] = multiplier;
	else
		return( 0xFFFE ); // invalid multiplier

	write_commande(cmd, 4);
	read_commande(cmd, 3);
	if(cmd[0] == 0x06)
		return( (uint16_t)(cmd[1]<<8) | cmd[2]); // previous multiplier
	else
		return 0xFFFF; // error
}

uint16_t Serial_Commander::txt_height_multiplier(uint8_t multiplier)
{
	uint8_t cmd[4];
	cmd[0] = 0xFF;
	cmd[1] = 0xE3;
	cmd[2] = 0x00;
	if(multiplier >= 1 && multiplier <= 16)
		cmd[3] = multiplier;
	else
		return( 0xFFFE ); // invalid multiplier

	write_commande(cmd, 4);
	read_commande(cmd, 3);
	if(cmd[0] == 0x06)
		return( (uint16_t)(cmd[1]<<8) | cmd[2]); // previous multiplier
	else
		return 0xFFFF; // error
}

uint16_t Serial_Commander::txt_x_gap(uint8_t pixel_count)
{
	uint8_t cmd[4];
	cmd[0] = 0xFF;
	cmd[1] = 0xE2;
	cmd[2] = 0x00;
	if(pixel_count <= 32)
		cmd[3] = pixel_count;
	else
		return( 0xFFFE ); // invalid multiplier

	write_commande(cmd, 4);
	read_commande(cmd, 3);
	if(cmd[0] == 0x06)
		return( (uint16_t)(cmd[1]<<8) | cmd[2]); // previous x_gap
	else
		return 0xFFFF; // error
}

uint16_t Serial_Commander::txt_y_gap(uint8_t pixel_count)
{
	uint8_t cmd[4];
	cmd[0] = 0xFF;
	cmd[1] = 0xE1;
	cmd[2] = 0x00;
	if(pixel_count >= 1 && pixel_count <= 32)
		cmd[3] = pixel_count;
	else
		return( 0xFFFE ); // invalid multiplier

	write_commande(cmd, 4);
	read_commande(cmd, 3);
	if(cmd[0] == 0x06)
		return( (uint16_t)(cmd[1]<<8) | cmd[2]); // previous y_gap
	else
		return 0xFFFF; // error
}

uint16_t Serial_Commander::txt_bold(bool bold)
{
	uint8_t cmd[4];
	cmd[0] = 0xFF;
	cmd[1] = 0xDE;
	cmd[2] = 0x00;
	cmd[3] = bold ? 0x01 : 0x00;

	write_commande(cmd, 4);
	read_commande(cmd, 3);
	if(cmd[0] == 0x06)
		return( (uint16_t)(cmd[1]<<8) | cmd[2]); // previous bold mode
	else
		return 0xFFFF; // error
}

uint16_t Serial_Commander::txt_inverse(bool inverse)
{
	uint8_t cmd[4];
	cmd[0] = 0xFF;
	cmd[1] = 0xDC;
	cmd[2] = 0x00;
	cmd[3] = inverse ? 0x01 : 0x00;

	write_commande(cmd, 4);
	read_commande(cmd, 3);
	if(cmd[0] == 0x06)
		return( (uint16_t)(cmd[1]<<8) | cmd[2]); // previous inverse mode
	else
		return 0xFFFF; // error
}

uint16_t Serial_Commander::txt_italic(bool italic)
{
	uint8_t cmd[4];
	cmd[0] = 0xFF;
	cmd[1] = 0xDD;
	cmd[2] = 0x00;
	cmd[3] = italic ? 0x01 : 0x00;

	write_commande(cmd, 4);
	read_commande(cmd, 3);
	if(cmd[0] == 0x06)
		return( (uint16_t)(cmd[1]<<8) | cmd[2]); // previous italic mode
	else
		return 0xFFFF; // error
}

uint16_t Serial_Commander::txt_opacity(bool opaque)
{
	uint8_t cmd[4];
	cmd[0] = 0xFF;
	cmd[1] = 0xDF;
	cmd[2] = 0x00;
	if(opaque == false)
		cmd[3] = 0x00; //transparent
	else
		cmd[3] = 0x01; //opaque

	write_commande(cmd, 4);
	read_commande(cmd, 3);
	if(cmd[0] == 0x06)
	{
		return( (uint16_t)(cmd[1]<<8) | cmd[2]); // previous opacity mode
	}
	else
		return 0xFFFF; // error
}

uint16_t Serial_Commander::txt_underline(bool underline) //txt_y_gap command is required to be at least 2 for the underline to be visible
{
	uint8_t cmd[4];
	cmd[0] = 0xFF;
	cmd[1] = 0xDB;
	cmd[2] = 0x00;
	if(underline == false)
		cmd[3] = 0x00;
	else
		cmd[3] = 0x01;

	write_commande(cmd, 4);
	read_commande(cmd, 3);
	if(cmd[0] == 0x06)
	{
		return( (uint16_t)(cmd[1]<<8) | cmd[2]); // previous underline mode
	}
	else
		return 0xFFFF; // error
}

uint16_t Serial_Commander::txt_attributes(bool bold, bool italic, bool inverse, bool underline) //txt_y_gap command is required to be at least 2 for the underline to be visible
{
	uint8_t cmd[4];
	cmd[0] = 0xFF;
	cmd[1] = 0xDA;
	cmd[2] = 0x00;
	cmd[3] = 0x00;
	if(bold == true)
		cmd[3] = cmd[3] | (0x01 << 4);
	if(italic == true)
		cmd[3] = cmd[3] | (0x01 << 5);
	if(inverse == true)
		cmd[3] = cmd[3] | (0x01 << 6);
	if(underline == true)
		cmd[3] = cmd[3] | (0x01 << 7);

	write_commande(cmd, 4);
	read_commande(cmd, 3);
	if(cmd[0] == 0x06)
	{
		return( (uint16_t)(cmd[1]<<8) | cmd[2]); // previous attributes mode
	}
	else
		return 0xFFFF; // error
}

uint16_t Serial_Commander::txt_wrap(uint16_t wrap_pixel)
{
	uint8_t cmd[4];
	cmd[0] = 0xFF;
	cmd[1] = 0xD9;
	cmd[2] = (uint8_t)(wrap_pixel>>8);
	cmd[3] = (uint8_t)wrap_pixel;

	write_commande(cmd, 4);
	read_commande(cmd, 3);
	if(cmd[0] == 0x06)
	{
		return( (uint16_t)(cmd[1]<<8) | cmd[2]); // previous wrap pixel
	}
	else
		return 0xFFFF; // error
}

	/*graphics function*/

uint8_t Serial_Commander::gfx_clear_screen()
{
    uint8_t cmd[2];
    cmd[0] = 0xFF;
    cmd[1] = 0xCD;

    write_commande(cmd, 2);
    read_commande(cmd, 1);
    if(cmd[0] == 0x06)
        return 0;
    else
        return 1; // error
}

uint8_t Serial_Commander::gfx_change_color(Color old_color, Color new_color)
{
    uint8_t cmd[6];
    cmd[0] = 0xFF;
    cmd[1] = 0xFE;
    cmd[2] = uint8_t(Color_to_Integral(old_color) >> 8);
    cmd[3] = uint8_t(Color_to_Integral(old_color));
    cmd[4] = uint8_t(Color_to_Integral(new_color) >> 8);
    cmd[5] = uint8_t(Color_to_Integral(new_color));

    write_commande(cmd, 6);
    read_commande(cmd, 1);
    if(cmd[0] == 0x06)
        return 0;
    else
        return 1; // error
}

uint8_t Serial_Commander::gfx_draw_circle(uint16_t center_x, uint16_t center_y, uint16_t radius, Color color)
{
    uint8_t cmd[10];
    cmd[0] = 0xFF;
    cmd[1] = 0xC3;
    cmd[2] = uint8_t(center_x >> 8);
    cmd[3] = uint8_t(center_x);
    cmd[4] = uint8_t(center_y >> 8);
    cmd[5] = uint8_t(center_y);
    cmd[6] = uint8_t(radius >> 8);
    cmd[7] = uint8_t(radius);
    cmd[8] = uint8_t(Color_to_Integral(color) >> 8);
    cmd[9] = uint8_t(Color_to_Integral(color));

    write_commande(cmd, 10);
    read_commande(cmd, 1);
    if(cmd[0] == 0x06)
        return 0;
    else
        return 1; // error
}

uint8_t Serial_Commander::gfx_draw_filled_circle(uint16_t center_x, uint16_t center_y, uint16_t radius, Color color)
{
    uint8_t cmd[10];
    cmd[0] = 0xFF;
    cmd[1] = 0xC2;
    cmd[2] = uint8_t(center_x >> 8);
    cmd[3] = uint8_t(center_x);
    cmd[4] = uint8_t(center_y >> 8);
    cmd[5] = uint8_t(center_y);
    cmd[6] = uint8_t(radius >> 8);
    cmd[7] = uint8_t(radius);
    cmd[8] = uint8_t(Color_to_Integral(color) >> 8);
    cmd[9] = uint8_t(Color_to_Integral(color));

    write_commande(cmd, 10);
    read_commande(cmd, 1);
    if(cmd[0] == 0x06)
        return 0;
    else
        return 1; // error
}

uint8_t Serial_Commander::gfx_draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, Color color)
{
    uint8_t cmd[12];
    cmd[0] = 0xFF;
    cmd[1] = 0xC8;
    cmd[2] = uint8_t(x1 >> 8);
    cmd[3] = uint8_t(x1);
    cmd[4] = uint8_t(y1 >> 8);
    cmd[5] = uint8_t(y1);
    cmd[6] = uint8_t(x2 >> 8);
    cmd[7] = uint8_t(x2);
    cmd[8] = uint8_t(y2 >> 8);
    cmd[9] = uint8_t(y2);
    cmd[10] = uint8_t(Color_to_Integral(color) >> 8);
    cmd[11] = uint8_t(Color_to_Integral(color));

    write_commande(cmd, 12);
    read_commande(cmd, 1);
    if(cmd[0] == 0x06)
        return 0;
    else
        return 1; // error
}

uint8_t Serial_Commander::gfx_draw_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, Color color)
{
    uint8_t cmd[12];
    cmd[0] = 0xFF;
    cmd[1] = 0xC5;
    cmd[2] = uint8_t(x1 >> 8);
    cmd[3] = uint8_t(x1);
    cmd[4] = uint8_t(y1 >> 8);
    cmd[5] = uint8_t(y1);
    cmd[6] = uint8_t(x2 >> 8);
    cmd[7] = uint8_t(x2);
    cmd[8] = uint8_t(y2 >> 8);
    cmd[9] = uint8_t(y2);
    cmd[10] = uint8_t(Color_to_Integral(color) >> 8);
    cmd[11] = uint8_t(Color_to_Integral(color));

    write_commande(cmd, 12);
    read_commande(cmd, 1);
    if(cmd[0] == 0x06)
        return 0;
    else
        return 1; // error
}

uint8_t Serial_Commander::gfx_draw_filled_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, Color color)
{
    uint8_t cmd[12];

    cmd[0] = 0xFF;
    cmd[1] = 0xC4;
    cmd[2] = uint8_t(x1 >> 8);
    cmd[3] = uint8_t(x1);
    cmd[4] = uint8_t(y1 >> 8);
    cmd[5] = uint8_t(y1);
    cmd[6] = uint8_t(x2 >> 8);
    cmd[7] = uint8_t(x2);
    cmd[8] = uint8_t(y2 >> 8);
    cmd[9] = uint8_t(y2);
    cmd[10] = uint8_t(Color_to_Integral(color) >> 8);
    cmd[11] = uint8_t(Color_to_Integral(color));

    write_commande(cmd, 12);
    read_commande(cmd, 1);
    if(cmd[0] == 0x06)
        return 0;
    else
        return 1; // error
}

/*uint8_t Serial_Commander::gfx_draw_polyline(uint16_t n, uint16_t* x_array, uint16_t* y_array, uint16_t colour)
{
    uint32_t array_size = n*sizeof(uint16_t);
    uint32_t cmd_size = 4+array_size*2+2;

    uint8_t cmd[cmd_size];

    cmd[0] = 0x00;
    cmd[1] = 0x15;
    cmd[2] = uint8_t(n>>8);
    cmd[3] = uint8_t(n);

    memcpy(&cmd[4], x_array, array_size);
    memcpy(&cmd[4+array_size], y_array, array_size);

    cmd[cmd_size-2] = uint8_t(colour >> 8);
    cmd[cmd_size-1] = uint8_t(colour);

    write_commande(cmd, cmd_size);
    read_commande(cmd, 1);
    if(cmd[0] == 0x06)
        return 0;
    else
        return 1; // error
}*/
/*
uint8_t Serial_Commander::gfx_draw_polygon(uint16_t n, uint16_t* x_array, uint16_t* y_array, uint16_t colour)
{
    uint32_t array_size = n*sizeof(uint16_t);
    uint32_t cmd_size = 4+array_size*2+2;

    uint8_t cmd[cmd_size];

    cmd[0] = 0x00;
    cmd[1] = 0x13;
    cmd[2] = uint8_t(n>>8);
    cmd[3] = uint8_t(n);

    memcpy(&cmd[4], x_array, array_size);
    memcpy(&cmd[4+array_size], y_array, array_size);

    cmd[cmd_size-2] = uint8_t(colour >> 8);
    cmd[cmd_size-1] = uint8_t(colour);

    write_commande(cmd, cmd_size);
    read_commande(cmd, 1);
    if(cmd[0] == 0x06)
        return 0;
    else
        return 1; // error
}*/
/*
uint8_t Serial_Commander::gfx_draw_filled_polygon(uint16_t n, uint16_t* x_array, uint16_t* y_array, uint16_t colour)
{
    uint32_t array_size = n*sizeof(uint16_t);
    uint32_t cmd_size = 4+array_size*2+2;

    uint8_t cmd[cmd_size];

    cmd[0] = 0x00;
    cmd[1] = 0x14;
    cmd[2] = uint8_t(n>>8);
    cmd[3] = uint8_t(n);

    memcpy(&cmd[4], x_array, array_size);
    memcpy(&cmd[4+array_size], y_array, array_size);

    cmd[cmd_size-2] = uint8_t(colour >> 8);
    cmd[cmd_size-1] = uint8_t(colour);

    write_commande(cmd, cmd_size);
    read_commande(cmd, 1);
    if(cmd[0] == 0x06)
        return 0;
    else
        return 1; // error
}*/

uint8_t Serial_Commander::gfx_draw_triangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, Color color)
{
    uint8_t cmd[16];
    cmd[0] = 0xFF;
    cmd[1] = 0xC4;
    cmd[2] = uint8_t(x1 >> 8);
    cmd[3] = uint8_t(x1);
    cmd[4] = uint8_t(y1 >> 8);
    cmd[5] = uint8_t(y1);
    cmd[6] = uint8_t(x2 >> 8);
    cmd[7] = uint8_t(x2);
    cmd[8] = uint8_t(y2 >> 8);
    cmd[9] = uint8_t(y2);
    cmd[10] = uint8_t(x3 >> 8);
    cmd[11] = uint8_t(x3);
    cmd[12] = uint8_t(y3 >> 8);
    cmd[13] = uint8_t(y3);
    cmd[14] = uint8_t(Color_to_Integral(color) >> 8);
    cmd[15] = uint8_t(Color_to_Integral(color));

    write_commande(cmd, 16);
    read_commande(cmd, 1);
    if(cmd[0] == 0x06)
        return 0;
    else
        return 1; // error
}

uint8_t Serial_Commander::gfx_draw_pixel(uint16_t center_x, uint16_t center_y, Color color)
{
    uint8_t cmd[8];
    cmd[0] = 0xFF;
    cmd[1] = 0xC1;
    cmd[2] = uint8_t(center_x >> 8);
    cmd[3] = uint8_t(center_x);
    cmd[4] = uint8_t(center_y >> 8);
    cmd[5] = uint8_t(center_y);
    cmd[6] = uint8_t(Color_to_Integral(color) >> 8);
    cmd[7] = uint8_t(Color_to_Integral(color));

    write_commande(cmd, 8);
    read_commande(cmd, 1);
    if(cmd[0] == 0x06)
        return 0;
    else
        return 1; // error
}

Color Serial_Commander::gfx_read_pixel(uint16_t center_x, uint16_t center_y)
{
    uint8_t cmd[6];
    cmd[0] = 0xFF;
    cmd[1] = 0xC0;
    cmd[2] = uint8_t(center_x >> 8);
    cmd[3] = uint8_t(center_x);
    cmd[4] = uint8_t(center_y >> 8);
    cmd[5] = uint8_t(center_y);

    write_commande(cmd, 6);
    read_commande(cmd, 3);
    if(cmd[0] == 0x06)
        return Integral_to_Color( (cmd[1] << 8) | cmd[2] );
    else
        return Color::BLACK; // error
}

uint8_t Serial_Commander::gfx_move_origin(uint16_t x, uint16_t y)
{
    uint8_t cmd[6];
    cmd[0] = 0xFF;
    cmd[1] = 0xCC;
    cmd[2] = uint8_t(x >> 8);
    cmd[3] = uint8_t(x);
    cmd[4] = uint8_t(y >> 8);
    cmd[5] = uint8_t(y);

    write_commande(cmd, 6);
    read_commande(cmd, 1);
    if(cmd[0] == 0x06)
        return 0;
    else
        return 0xff; // error
}

	/*media function*/
uint16_t Serial_Commander::media_init()
{
	uint8_t cmd[3];
	cmd[0] = 0xFF;
	cmd[1] = 0x89;

	write_commande(cmd, 2);
	read_commande(cmd, 3);
	if(cmd[0] == 0x06)
	{
		if(cmd[2] == 0x01)
			return( 0x00 );
		else
			return( 0xFFFE); // no card is presentor not able to initialise.
	}
	else
		return 0xFFFF; // error
}

uint16_t Serial_Commander::media_set_addr(uint32_t addr)
{
	uint8_t cmd[6];
	cmd[0] = 0xFF;
	cmd[1] = 0x93;
	cmd[2] = (uint8_t)(addr >> 24);
	cmd[3] = (uint8_t)(addr >> 16);
	cmd[4] = (uint8_t)(addr >> 8);
	cmd[5] = (uint8_t)addr;

	write_commande(cmd, 6);
	read_commande(cmd, 1);
	if(cmd[0] == 0x06)
			return( 0x00 );
	else
		return( 0xFFFF ); // error
}

uint16_t Serial_Commander::media_set_sector(uint32_t sector)
{
	uint8_t cmd[6];
	cmd[0] = 0xFF;
	cmd[1] = 0x92;
	cmd[2] = (uint8_t)(sector >> 24);
	cmd[3] = (uint8_t)(sector >> 16);
	cmd[4] = (uint8_t)(sector >> 8);
	cmd[5] = (uint8_t)sector;

	write_commande(cmd, 6);
	read_commande(cmd, 1);
	if(cmd[0] == 0x06)
			return( 0x00 );
	else
		return( 0xFFFF ); // error
}

uint16_t Serial_Commander::media_read_sector(uint8_t* sector)
{
	uint8_t cmd[3];
	cmd[0] = 0x00;
	cmd[1] = 0x16;

	write_commande(cmd, 2);
	read_commande(cmd, 1);
	if(cmd[0] != 0x06)
		return( 0xFFFF ); // error
	else
	{
		read_commande(cmd, 2);
		if(cmd[2] != 0x01)
			return( 0xFFFF ); // error
		else
		{
			read_commande(sector, 512);
			return( 0x00 );
		}
	}
}

uint16_t Serial_Commander::media_write_sector(uint8_t* sector)
{
	uint8_t cmd[3];
	cmd[0] = 0x00;
	cmd[1] = 0x17;

	write_commande(cmd, 2);
	write_commande(sector, 512);
	read_commande(cmd, 3);
	if(cmd[0] != 0x06)
		return( 0xFFFF ); // error
	else
	{
		if( ((cmd[1] << 8) | cmd[2]) == 0x0000 )
			return( 0xFFFF );
		else if(media_flush() != 0x00)
			return( 0x00 ); // sector that is being written is correctly
		else
			return(0xFFFE); // sector that isn't being written is correctly
	}
}

uint16_t Serial_Commander::media_read_byte()
{
	uint8_t cmd[2];
	cmd[0] = 0xFF;
	cmd[1] = 0x8F;

	write_commande(cmd, 2);
	read_commande(cmd, 1);
	if(cmd[0] != 0x06)
		return( 0xFFFF ); // error
	else
	{
		read_commande(cmd, 2);
		return( (cmd[0] << 8) | cmd[1] );
	}
}

uint16_t Serial_Commander::media_read_word()
{
	uint8_t cmd[2];
	cmd[0] = 0xFF;
	cmd[1] = 0x8E;

	write_commande(cmd, 2);
	read_commande(cmd, 1);
	if(cmd[0] != 0x06)
		return( 0xFFFF ); // error /!\ it's also a possible value
	else
	{
		read_commande(cmd, 2);
		return( (cmd[0] << 8) | cmd[1] );
	}
}

uint16_t Serial_Commander::media_write_byte(uint8_t byte)
{
	uint8_t cmd[4];
	cmd[0] = 0x00;
	cmd[1] = 0x8D;
	cmd[2] = 0x00;
	cmd[3] = byte;

	write_commande(cmd, 4);
	read_commande(cmd, 3);
	if(cmd[0] != 0x06)
		return( 0xFFFF ); // error
	else
	{
		if( ((cmd[1] << 8) | cmd[2]) == 0x0000 )
			return( 0xFFFF );
		else if(media_flush() != 0x00)
			return( 0x00 ); // sector that is being written is correctly
		else
			return(0xFFFE); // sector that isn't being written is correctly
	}
}

uint16_t Serial_Commander::media_write_word(uint16_t word)
{
	uint8_t cmd[4];
	cmd[0] = 0x00;
	cmd[1] = 0x8C;
	cmd[2] = (uint8_t)(word >> 8);
	cmd[3] = (uint8_t)word;

	write_commande(cmd, 4);
	read_commande(cmd, 3);
	if(cmd[0] != 0x06)
		return( 0xFFFF ); // error
	else
	{
		if( ((cmd[1] << 8) | cmd[2]) == 0x0000 )
			return( 0xFFFF );
		else if(media_flush() != 0x00)
			return( 0x00 ); // sector that is being written is correctly
		else
			return(0xFFFE); // sector that isn't being written is correctly
	}
}

uint16_t Serial_Commander::media_display_image(uint16_t x, uint16_t y)
{
	uint8_t cmd[6];
	cmd[0] = 0x00;
	cmd[1] = 0x8B;
	cmd[2] = (uint8_t)(x >> 8);
	cmd[3] = (uint8_t)x;
	cmd[4] = (uint8_t)(y >> 8);
	cmd[5] = (uint8_t)y;

	write_commande(cmd, 6);
	read_commande(cmd, 1);
	if(cmd[0] != 0x06)
		return( 0xFFFF ); // error
	else
	{
		return( 0x00 );
	}
}

uint16_t Serial_Commander::media_display_video(uint16_t x, uint16_t y)
{
	uint8_t cmd[6];
	cmd[0] = 0x00;
	cmd[1] = 0x95;
	cmd[2] = (uint8_t)(x >> 8);
	cmd[3] = (uint8_t)x;
	cmd[4] = (uint8_t)(y >> 8);
	cmd[5] = (uint8_t)y;

	write_commande(cmd, 6);
	read_commande(cmd, 1);
	if(cmd[0] != 0x06)
		return( 0xFFFF ); // error
	else
	{
		return( 0x00 );
	}
}

uint16_t Serial_Commander::media_display_video_frame(uint16_t x, uint16_t y, uint16_t frame_number)
{
	uint8_t cmd[8];
	cmd[0] = 0x00;
	cmd[1] = 0x94;
	cmd[2] = (uint8_t)(x >> 8);
	cmd[3] = (uint8_t)x;
	cmd[4] = (uint8_t)(y >> 8);
	cmd[5] = (uint8_t)y;
	cmd[4] = (uint8_t)(frame_number >> 8);
	cmd[5] = (uint8_t)frame_number;

	write_commande(cmd, 8);
	read_commande(cmd, 1);
	if(cmd[0] != 0x06)
		return( 0xFFFF ); // error
	else
	{
		return( 0x00 );
	}
}

	/* UART function*/
uint16_t Serial_Commander::uart_set_baud_rate(uint32_t baud_rate)
{
	uint8_t cmd[4];
	cmd[0] = 0x00;
	cmd[1] = 0x26;
	cmd[2] = 0x00;
	cmd[3] = code_baud_rate(baud_rate);
	if(cmd[3] != 20)
	{
		write_commande(cmd, 4);
		read_commande(cmd, 1);
		if(cmd[0] != 0x06)
        {
            m_serial.setBaudRate(baud_rate);
			return( 0xFFFF ); // error
        }
		else
		{
			m_serial.setBaudRate(baud_rate);
			return( 0x00 );
		}
	}
	else
		return( 0xFFFE ); //invalid baud_rate
}

	/* timer function*/
uint16_t Serial_Commander::timer_sleep_systeme(uint16_t units)
{
	uint8_t cmd[4];
	cmd[0] = 0xFF;
	cmd[1] = 0x3B;
	cmd[2] = (uint8_t)(units >> 8);
	cmd[3] = (uint8_t)units;

	write_commande(cmd, 4);
	read_commande(cmd, 1);
	if(cmd[0] != 0x06)
		return( 0xFFFF ); // error
	else
	{
		return( 0x00 );
	}
}

	/* file function*/
uint16_t Serial_Commander::file_last_error()
{
	uint8_t cmd[3];
	cmd[0] = 0xFF;
	cmd[1] = 0x1F;

	write_commande(cmd, 2);
	read_commande(cmd, 3);
	if(cmd[0] != 0x06)
		return( 0xFFFF ); // error
	else
	{
		return( (cmd[1] << 8) | cmd[2] );
	}
}

uint16_t Serial_Commander::file_file_count(const int8_t* file_name)
{
	uint16_t size = strlen((const char*)file_name);
	uint8_t cmd[3];
	cmd[0] = 0x00;
	cmd[1] = 0x01;
	cmd[2] = 0x00;

	write_commande(cmd, 2);
	write_commande((uint8_t*)file_name, size);
	write_commande(&(cmd[2]), 1);
	read_commande(cmd, 3);
	if(cmd[0] == 0x06)
		return((cmd[1]<<8) | cmd[2]);
	else
		return 0xFFFF;
}

uint16_t Serial_Commander::file_file_count_and_display(const int8_t* file_name)
{
	uint16_t size = strlen((const char*)file_name);
	uint8_t cmd[3];
	cmd[0] = 0x00;
	cmd[1] = 0x02;
	cmd[2] = 0x00;

	write_commande(cmd, 2);
	write_commande((uint8_t*)file_name, size);
	write_commande(&(cmd[2]), 1);
	read_commande(cmd, 3);
	if(cmd[0] == 0x06)
		return((cmd[1]<<8) | cmd[2]);
	else
		return 0xFFFF;
}

uint16_t Serial_Commander::file_find_first_file_and_display(const int8_t* file_name)
{
	uint16_t size = strlen((const char*)file_name);
	uint8_t cmd[3];
	cmd[0] = 0x00;
	cmd[1] = 0x06;
	cmd[2] = 0x00;

	write_commande(cmd, 2);
	write_commande((uint8_t*)file_name, size);
	write_commande(&(cmd[2]), 1);
	read_commande(cmd, 3);
	if(cmd[0] == 0x06)
		return((cmd[1]<<8) | cmd[2]);
	else
		return 0xFFFF;
}

uint16_t Serial_Commander::file_find_first_file_and_report(const int8_t* file_name_search, uint8_t* file_name_found)
{
	uint16_t size = strlen((const char*)file_name_search);
	uint8_t cmd[3];
	cmd[0] = 0x00;
	cmd[1] = 0x24;
	cmd[2] = 0x00;

	write_commande(cmd, 2);
	write_commande((uint8_t*)file_name_search, size);
	write_commande(&(cmd[2]), 1);
	read_commande(cmd, 3);
	if(cmd[0] == 0x06)
	{
		read_commande(file_name_found,((cmd[1]<<8) | cmd[2]));
		return((cmd[1]<<8) | cmd[2]); // return stringlength
	}
	else
		return 0xFFFF;
}

uint16_t Serial_Commander::file_find_next_file_and_display()
{
	uint8_t cmd[3];
	cmd[0] = 0xFF;
	cmd[1] = 0x1B;

	write_commande(cmd, 2);
	read_commande(cmd, 3);
	if(cmd[0] == 0x06)
		return((cmd[1]<<8) | cmd[2]); // return file  status
	else
		return 0xFFFF;
}

uint16_t Serial_Commander::file_find_next_file_and_report(uint8_t* file_name_found)
{
	uint8_t cmd[3];
	cmd[0] = 0x00;
	cmd[1] = 0x25;

	write_commande(cmd, 2);
	read_commande(cmd, 3);
	if(cmd[0] == 0x06)
	{
		read_commande(file_name_found,((cmd[1]<<8) | cmd[2]));
		return((cmd[1]<<8) | cmd[2]); // return stringlength
	}
	else
		return 0xFFFF;
}

uint16_t Serial_Commander::file_file_exist(const int8_t* file_name)
{
	uint16_t size = strlen((const char*)file_name);
	uint8_t cmd[3];
	cmd[0] = 0x00;
	cmd[1] = 0x05;
	cmd[2] = 0x00;

	write_commande(cmd, 2);
	write_commande((uint8_t*)file_name, size);
	write_commande(&(cmd[2]), 1);
	read_commande(cmd, 3);
	if(cmd[0] == 0x06)
		return((cmd[1]<<8) | cmd[2]); // return file exist status
	else
		return 0xFFFF;
}

uint16_t Serial_Commander::file_open_file(const int8_t* file_name, uint8_t mode)
{
	uint16_t size = strlen((const char*)file_name);
	uint8_t cmd[4];
	if((mode == 'r') | (mode == 'w') | (mode == 'a') | (mode == 'R') | (mode == 'W') | (mode == 'A'))
	{
		cmd[0] = 0x00;
		cmd[1] = 0x0A;
		cmd[2] = 0x00;
		cmd[3] = mode;

		write_commande(cmd, 2);
		write_commande((uint8_t*)file_name, size);
		write_commande(&(cmd[2]), 2);
		read_commande(cmd, 3);
		if(cmd[0] == 0x06)
			return((cmd[1]<<8) | cmd[2]); // return handle /!\ keep it for closing file
		else
			return 0xFFFF;
	}
	else
		return 0xFFFE; // invalid mode
}

uint16_t Serial_Commander::file_close_file(uint16_t handle)
{
	uint8_t cmd[4];
	cmd[0] = 0xFF;
	cmd[1] = 0x18;
	cmd[2] = (uint8_t)(handle >> 8);
	cmd[3] = (uint8_t)handle;

	write_commande(cmd, 4);
	read_commande(cmd, 3);
	if(cmd[0] != 0x06)
		return( 0xFFFF ); // error
	else
	{
		return( (cmd[1]<<8) | cmd[2] ); // return status
	}
}

uint16_t Serial_Commander::file_read_file(uint16_t size, uint16_t handle, uint8_t* read_file)
{
	uint8_t cmd[6];
	cmd[0] = 0x00;
	cmd[1] = 0x0C;
	cmd[2] = (uint8_t)(size >> 8);
	cmd[3] = (uint8_t)size;
	cmd[4] = (uint8_t)(handle >> 8);
	cmd[5] = (uint8_t)handle;

	write_commande(cmd, 6);
	read_commande(cmd, 3);
	if(cmd[0] == 0x06)
	{
		read_commande(read_file,((cmd[1]<<8) | cmd[2]));
		return((cmd[1]<<8) | cmd[2]); // return number of bytes read
	}
	else
		return 0xFFFF;
}

uint16_t Serial_Commander::file_file_seek(uint16_t handle, uint32_t byte_position)
{
	uint8_t cmd[8];
	cmd[0] = 0xFF;
	cmd[1] = 0x16;
	cmd[2] = (uint8_t)(handle >> 8);
	cmd[3] = (uint8_t)handle;
	cmd[4] = (uint8_t)(byte_position >> 24);
	cmd[5] = (uint8_t)(byte_position >> 16);
	cmd[6] = (uint8_t)(byte_position >> 8);
	cmd[7] = (uint8_t)byte_position;

	write_commande(cmd, 8);
	read_commande(cmd, 3);
	if(cmd[0] == 0x06)
	{
		return((cmd[1]<<8) | cmd[2]); // return status
	}
	else
		return 0xFFFF;
}

uint16_t Serial_Commander::file_file_index(uint16_t handle, uint32_t record_size, uint16_t records_number)
{
	uint8_t cmd[10];
	cmd[0] = 0xFF;
	cmd[1] = 0x15;
	cmd[2] = (uint8_t)(handle >> 8);
	cmd[3] = (uint8_t)handle;
	cmd[4] = (uint8_t)(record_size >> 24);
	cmd[5] = (uint8_t)(record_size >> 16);
	cmd[6] = (uint8_t)(record_size >> 8);
	cmd[7] = (uint8_t)record_size;
	cmd[8] = (uint8_t)(records_number >> 8);
	cmd[9] = (uint8_t)records_number;

	write_commande(cmd, 10);
	read_commande(cmd, 3);
	if(cmd[0] == 0x06)
	{
		return((cmd[1]<<8) | cmd[2]); // return status
	}
	else
		return 0xFFFF;
}

uint32_t Serial_Commander::file_file_index(uint16_t handle)
{
	uint8_t cmd[7];
	cmd[0] = 0x00;
	cmd[1] = 0x0F;
	cmd[2] = (uint8_t)(handle >> 8);
	cmd[3] = (uint8_t)handle;

	write_commande(cmd, 4);
	read_commande(cmd, 7);
	if(cmd[0] == 0x06)
	{
		if(((cmd[1]<<8) | cmd[2]) == 0x0001)
			return((cmd[3]<<24) | (cmd[4]<<16) | (cmd[5]<<8) | cmd[6]); // return current index pointer
		else
			return 0xFFFF;
	}
	else
		return 0xFFFF;
}

uint16_t Serial_Commander::file_write_file(uint16_t size, uint16_t handle, const int8_t* write_file)
{
	uint16_t sizes = strlen((const char*)write_file);
	uint8_t cmd[4];
	cmd[0] = 0x00;
	cmd[1] = 0x10;
	cmd[2] = (uint8_t)(size >> 8);
	cmd[3] = (uint8_t)size;
	write_commande(cmd, 4);
	write_commande((uint8_t*)write_file, sizes);
	cmd[0] = (uint8_t)(handle >> 8);
	cmd[1] = (uint8_t)handle;

	write_commande(cmd, 2);
	read_commande(cmd, 3);
	if(cmd[0] == 0x06)
	{
		if(((cmd[1]<<8) | cmd[2]) == size)
			return 0xFFFF;
		else
			return 0;
	}
	else
		return 0xFFFF;
}

uint32_t Serial_Commander::file_file_size(uint16_t handle)
{
	uint8_t cmd[7];
	cmd[0] = 0x00;
	cmd[1] = 0x0E;
	cmd[2] = (uint8_t)(handle >> 8);
	cmd[3] = (uint8_t)handle;

	write_commande(cmd, 4);
	read_commande(cmd, 7);
	if(cmd[0] == 0x06)
	{
		if(((cmd[1]<<8) | cmd[2]) == 0x0001)
			return((cmd[3]<<24) | (cmd[4]<<16) | (cmd[5]<<8) | cmd[6]); // return file size
		else
			return 0xFFFF;
	}
	else
		return 0xFFFF;
}

uint16_t Serial_Commander::file_display_image(uint16_t handle, uint16_t x, uint16_t y)
{
	uint8_t cmd[8];
	cmd[0] = 0xFF;
	cmd[1] = 0x11;
	cmd[2] = (uint8_t)(x >> 8);
	cmd[3] = (uint8_t)x;
	cmd[4] = (uint8_t)(y >> 8);
	cmd[5] = (uint8_t)y;
	cmd[6] = (uint8_t)(handle >> 8);
	cmd[7] = (uint8_t)handle;

	write_commande(cmd, 8);
	read_commande(cmd, 3);
	if(cmd[0] == 0x06)
	{
		return((cmd[1]<<8) | cmd[2]); // return code error
	}
	else
		return 0xFFFF;
}

uint16_t Serial_Commander::file_screen_capture(uint16_t handle, uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
	uint8_t cmd[12];
	cmd[0] = 0xFF;
	cmd[1] = 0x10;
	cmd[2] = (uint8_t)(x >> 8);
	cmd[3] = (uint8_t)x;
	cmd[4] = (uint8_t)(y >> 8);
	cmd[5] = (uint8_t)y;
	cmd[6] = (uint8_t)(width >> 8);
	cmd[7] = (uint8_t)width;
	cmd[8] = (uint8_t)(height >> 8);
	cmd[9] = (uint8_t)height;
	cmd[10] = (uint8_t)(handle >> 8);
	cmd[11] = (uint8_t)handle;

	write_commande(cmd, 12);
	read_commande(cmd, 3);
	if(cmd[0] == 0x06)
	{
		return((cmd[1]<<8) | cmd[2]); // return code error, 0 if success
	}
	else
		return 0xFFFF;
}

uint16_t Serial_Commander::file_write_char_to_file(uint16_t handle, uint8_t charactere)
{
	uint8_t cmd[6];
	cmd[0] = 0xFF;
	cmd[1] = 0x11;
	cmd[2] = 0x00;
	cmd[3] = (uint8_t)charactere;
	cmd[4] = (uint8_t)(handle >> 8);
	cmd[5] = (uint8_t)handle;

	write_commande(cmd, 6);
	read_commande(cmd, 3);
	if(cmd[0] == 0x06)
	{
		return((cmd[1]<<8) | cmd[2]); // return status
	}
	else
		return 0xFFFF;
}

uint8_t Serial_Commander::file_read_char_to_file(uint16_t handle)
{
	uint8_t cmd[4];
	cmd[0] = 0xFF;
	cmd[1] = 0x0E;
	cmd[2] = (uint8_t)(handle >> 8);
	cmd[3] = (uint8_t)handle;

	write_commande(cmd, 4);
	read_commande(cmd, 3);
	if(cmd[0] == 0x06)
	{
		return(cmd[2]); // return charactere
	}
	else
		return 0xFF;
}

uint16_t Serial_Commander::file_write_word_to_file(uint16_t handle, uint16_t word)
{
	uint8_t cmd[6];
	cmd[0] = 0xFF;
	cmd[1] = 0x0D;
	cmd[2] = (uint8_t)(word >> 8);;
	cmd[3] = (uint8_t)word;
	cmd[4] = (uint8_t)(handle >> 8);
	cmd[5] = (uint8_t)handle;

	write_commande(cmd, 6);
	read_commande(cmd, 3);
	if(cmd[0] == 0x06)
	{
		return((cmd[1]<<8) | cmd[2]); // return status
	}
	else
		return 0xFFFF;
}

uint16_t Serial_Commander::file_read_word_to_file(uint16_t handle)
{
	uint8_t cmd[4];
	cmd[0] = 0xFF;
	cmd[1] = 0x0C;
	cmd[2] = (uint8_t)(handle >> 8);
	cmd[3] = (uint8_t)handle;

	write_commande(cmd, 4);
	read_commande(cmd, 3);
	if(cmd[0] == 0x06)
	{
		return((cmd[1]<<8) | cmd[2]); // return word
	}
	else
		return 0xFFFF;
}

uint16_t Serial_Commander::file_write_string_to_file(const int8_t* str, uint8_t handle)
{
	uint16_t size = strlen((const char*)str);
	uint8_t cmd[5];
	cmd[0] = 0x00;
	cmd[1] = 0x20;
	cmd[2] = 0x00;
	cmd[3] = (uint8_t)(handle >> 8);
	cmd[4] = (uint8_t)handle;

	write_commande(cmd, 2);
	write_commande((uint8_t*)str, size);
	write_commande(&(cmd[2]), 3);
	read_commande(cmd, 3);
	if(cmd[0] == 0x06)
		if(((cmd[1]<<8) | cmd[2]) == size)
			return(0x00);
		else
			return (0xFFFF);
	else
		return 0xFFFF;
}

uint16_t Serial_Commander::file_read_string_from_file(uint16_t size, uint16_t handle, uint8_t* str)
{
	uint8_t cmd[6];
	cmd[0] = 0x00;
	cmd[1] = 0x07;
	cmd[2] = (uint8_t)(size >> 8);
	cmd[3] = (uint8_t)size;
	cmd[4] = (uint8_t)(handle >> 8);
	cmd[5] = (uint8_t)handle;

	write_commande(cmd, 6);
	read_commande(cmd, 3);
	if(cmd[0] == 0x06)
	{
		read_commande(str,((cmd[1]<<8) | cmd[2]));
		return((cmd[1]<<8) | cmd[2]); // return number of bytes read
	}
	else
		return 0xFFFF;
}

uint16_t Serial_Commander::file_file_erase(const int8_t* file_name)
{
	uint16_t size = strlen((const char*)file_name);
	uint8_t cmd[3];
	cmd[0] = 0x00;
	cmd[1] = 0x03;
	cmd[2] = 0x00;

	write_commande(cmd, 2);
	write_commande((uint8_t*)file_name, size);
	write_commande(&(cmd[2]), 1);
	read_commande(cmd, 3);
	if(cmd[0] == 0x06)
		return((cmd[1]<<8) | cmd[2]); // return file erase status
	else
		return 0xFFFF;
}

uint8_t Serial_Commander::file_rewind(uint16_t handle)
{
	uint8_t cmd[4];
	cmd[0] = 0xFF;
	cmd[1] = 0x08;
	cmd[2] = (uint8_t)(handle >> 8);
	cmd[3] = (uint8_t)handle;

	write_commande(cmd, 4);
	read_commande(cmd, 3);
	if(cmd[0] == 0x06)
	{
		return(cmd[2]); // return rewin status
	}
	else
		return 0xFF;
}

uint16_t Serial_Commander::file_mount()
{
	uint8_t cmd[3];
	cmd[0] = 0xFF;
	cmd[1] = 0x03;

	write_commande(cmd, 2);
	read_commande(cmd, 3);
	if(cmd[0] == 0x06)
	{
		if(cmd[2] == 0x01)
			return( 0x00 );
		else
			return( 0xFFFE); // no card is presentor not able to initialise.
	}
	else
		return 0xFFFF; // error
}

uint16_t Serial_Commander::file_Unmount()
{
    uint8_t cmd[2];
	cmd[0] = 0xFF;
	cmd[1] = 0x02;

	write_commande(cmd, 2);
	read_commande(cmd, 1);
	if(cmd[0] == 0x06)
		return 0;
	else
		return 0xFFFF; // error
}

uint16_t Serial_Commander::file_PlayWAV(const char* str)
{
    uint16_t size = strlen((const char*)str);
	uint8_t cmd[3];
	cmd[0] = 0x00;
	cmd[1] = 0x0B;
	cmd[2] = 0x00;

	write_commande(cmd, 2);
	write_commande((uint8_t*)str, size);
	write_commande(&(cmd[2]), 1);
	read_commande(cmd, 3);

	if(cmd[0] == 0x06)
		return((cmd[1]<<8) | cmd[2]); // return error status
	else
		return 0xFFFF;
}

/* sound */
uint8_t Serial_Commander::snd_Volume(float per_cent)
{
    uint8_t cmd[4];
	cmd[0] = 0xFF;
	cmd[1] = 0x00;

	uint16_t volume = (uint16_t)(per_cent*127.);
	cmd[2] = (uint8_t)(volume >> 4);
	cmd[3] = (uint8_t)(volume & 0xFF);

	write_commande(cmd, 4);
	read_commande(cmd, 1);
	if(cmd[0] == 0x06)
        return (cmd[0] == 0x06);
	else
		return 0xFF; // error
}

uint16_t Serial_Commander::snd_Pitch(uint16_t pitch)
{
    uint8_t cmd[4];
	cmd[0] = 0xFE;
	cmd[1] = 0xFF;
	cmd[2] = (uint8_t)(pitch >> 4);
	cmd[3] = (uint8_t)(pitch & 0xFF);

	write_commande(cmd, 4);
	read_commande(cmd, 3);
	if(cmd[0] != 0x06)
        return ((cmd[1]<<8) | cmd[2]);
	else
		return 0x0000; // error
}

uint8_t Serial_Commander::snd_BufSize(uint8_t bufsize)
{
    uint8_t cmd[4];
	cmd[0] = 0xFF;
	cmd[1] = 0x00;
	cmd[2] = 0x00;
	cmd[3] = bufsize;

	write_commande(cmd, 4);
	read_commande(cmd, 1);
	if(cmd[0] == 0x06)
        return 0;
	else
		return 0xFF; // error
}

uint8_t Serial_Commander::snd_Stop()
{
    uint8_t cmd[2];
	cmd[0] = 0xFE;
	cmd[1] = 0xFD;

	write_commande(cmd, 2);
	read_commande(cmd, 1);
	if(cmd[0] == 0x06)
        return 0;
	else
		return 0xFF; // error
}

uint8_t Serial_Commander::snd_Pause()
{
    uint8_t cmd[2];
	cmd[0] = 0xFE;
	cmd[1] = 0xFC;

	write_commande(cmd, 2);
	read_commande(cmd, 1);
	if(cmd[0] == 0x06)
        return 0;
	else
		return 0xFF; // error
}

uint8_t Serial_Commander::snd_Continue()
{
    uint8_t cmd[2];
	cmd[0] = 0xFE;
	cmd[1] = 0xFB;

	write_commande(cmd, 2);
	read_commande(cmd, 1);
	if(cmd[0] == 0x06)
        return 0;
	else
		return 0xFF; // error
}

uint16_t Serial_Commander::snd_Playing()
{
    uint8_t cmd[3];
	cmd[0] = 0xFE;
	cmd[1] = 0xFA;

	write_commande(cmd, 2);
	read_commande(cmd, 3);
	if(cmd[0] == 0x06)
        return ((cmd[1]<<8) | cmd[2]);
	else
		return 0xFF; // error
}

/* touch screen function*/

uint8_t Serial_Commander::touch_detect_region(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    uint8_t cmd[10];
    cmd[0] = 0xFF;
    cmd[1] = 0x39;
    cmd[2] = uint8_t(x1 >> 8);
    cmd[3] = uint8_t(x1);
    cmd[4] = uint8_t(y1 >> 8);
    cmd[5] = uint8_t(y1);
    cmd[6] = uint8_t(x2 >> 8);
    cmd[7] = uint8_t(x2);
    cmd[8] = uint8_t(y2 >> 8);
    cmd[9] = uint8_t(y2);

    write_commande(cmd, 10);
    read_commande(cmd, 1);
    if(cmd[0] == 0x06)
        return 0;
    else
        return 0xff; // error
}

uint8_t Serial_Commander::touch_set(uint8_t mode)
{
    uint8_t cmd[4];
    cmd[0] = 0xFF;
    cmd[1] = 0x38;
    cmd[2] = 0x00;
    cmd[3] = mode;

    write_commande(cmd, 4);
    read_commande(cmd, 1);
    if(cmd[0] == 0x06)
        return 0;
    else
        return 0xff; // error
}

uint16_t Serial_Commander::touch_get(uint8_t mode)
{
    uint8_t cmd[4];
    cmd[0] = 0xFF;
    cmd[1] = 0x37;
    cmd[2] = 0x00;
    cmd[3] = mode;

    write_commande(cmd, 4);
    read_commande(cmd, 3);
    if(cmd[0] == 0x06)
        return((cmd[1]<<8) | cmd[2]);
    else
        return 0xff; // error
}

} // namespace Picaso
