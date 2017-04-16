/*
 * Point.h
 *
 *  Created on: 13 avr. 2017
 *      Author: JulienCombattelli
 */

#ifndef PICASOSDK_GUI_POINT_H_
#define PICASOSDK_GUI_POINT_H_

#include <cstdint>

namespace Picaso
{

struct Point
{
    uint16_t x;
    uint16_t y;
};

struct Size
{
	uint16_t width;
	uint16_t height;
};

} // namespace Picaso

#endif /* PICASOSDK_GUI_POINT_H_ */
