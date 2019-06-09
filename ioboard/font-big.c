#include "img.h"

const PROGMEM struct img image = {
	.w = 200,
	.h = 21,
	.data = {
		0x00, 0x00, 0x00, 0xc0, 0xf8, 0xfc, 0x1e, 0x07, 0x07, 0x03, 0x03, 0x07, 0x07, 0x1e, 0xfc, 0xf8, 
		0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x38, 0x1c, 0x0e, 0x06, 0xff, 0xff, 0xff, 0x00, 
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x0c, 0x0e, 0x06, 0x07, 0x03, 0x03, 0x03, 0x07, 
		0x07, 0xfe, 0xfc, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x0e, 0x06, 0x07, 0x07, 0x03, 0x03, 
		0x07, 0x07, 0xfe, 0xfe, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 
		0xf0, 0x38, 0x1e, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xff, 
		0xff, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 
		0xf0, 0xf8, 0x3c, 0x0e, 0x06, 0x07, 0x07, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 
		0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0xc3, 0xf3, 0xff, 0x3f, 0x07, 0x00, 
		0x00, 0x00, 0x00, 0x00, 0x78, 0xfe, 0xfe, 0x87, 0x03, 0x03, 0x03, 0x03, 0x87, 0xfe, 0xfe, 0x78, 
		0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xfc, 0xfe, 0x0e, 0x07, 0x03, 0x03, 0x03, 0x07, 0x06, 0x0e, 
		0xfc, 0xf8, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x78, 0x78, 0x78, 
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0x00, 0x00, 
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
		0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
		0x00, 0x00, 0x80, 0xc0, 0xe0, 0x70, 0x38, 0x1c, 0x0e, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 
		0x00, 0x00, 0x00, 0x00, 0x06, 0x06, 0x06, 0x06, 0x0f, 0x0f, 0x1d, 0xf9, 0xf8, 0xe0, 0x00, 0x00, 
		0x00, 0x00, 0xe0, 0xf0, 0xfc, 0xde, 0xc7, 0xc3, 0xc0, 0xc0, 0xc0, 0xff, 0xff, 0xff, 0xc0, 0xc0, 
		0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x07, 0x03, 0x03, 0x03, 0x07, 0x07, 0x0e, 0xfe, 
		0xfc, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x0c, 0x06, 0x03, 0x03, 0x03, 0x03, 
		0x07, 0x06, 0xfe, 0xfc, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 
		0xf8, 0x7e, 0x1f, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xf0, 0xf8, 0x1d, 0x0f, 
		0x0f, 0x06, 0x06, 0x0f, 0x0f, 0x1d, 0xf8, 0xf0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x0f, 
		0x1c, 0x1c, 0x18, 0x18, 0x18, 0x18, 0x0c, 0x86, 0xff, 0xff, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 
		0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	}
};
