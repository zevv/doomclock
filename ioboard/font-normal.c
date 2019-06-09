#include "img.h"

const struct img font_normal PROGMEM = {
	.w = 752,
	.h = 16,
	.data = {
		0x00, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 
		0x20, 0xf8, 0x20, 0x20, 0xf8, 0x20, 0x00, 0x00, 0x60, 0x90, 0xf8, 0x90, 0x10, 0x00, 0x00, 0x00, 
		0x18, 0x24, 0x98, 0x60, 0x10, 0x0c, 0x00, 0x00, 0x30, 0xc8, 0xc8, 0x30, 0x00, 0x00, 0x00, 0x00, 
		0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x18, 0x04, 0x02, 0x00, 0x00, 
		0x02, 0x04, 0x18, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x80, 0xa0, 0xc0, 0xc0, 0xa0, 0x80, 0x00, 0x00, 
		0x80, 0x80, 0x80, 0xf0, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
		0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
		0x00, 0x00, 0x80, 0x60, 0x18, 0x06, 0x00, 0x00, 0xf0, 0x08, 0x84, 0x44, 0x08, 0xf0, 0x00, 0x00, 
		0x20, 0x10, 0x08, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x18, 0x04, 0x04, 0x84, 0x44, 0x38, 0x00, 0x00, 
		0x08, 0x04, 0x44, 0x44, 0x44, 0xb8, 0x00, 0x00, 0x80, 0x60, 0x18, 0x04, 0xfc, 0x00, 0x00, 0x00, 
		0x7c, 0x24, 0x24, 0x24, 0x24, 0xc4, 0x00, 0x00, 0xf8, 0x84, 0x44, 0x44, 0x44, 0x88, 0x00, 0x00, 
		0x04, 0x04, 0x04, 0xc4, 0x34, 0x0c, 0x00, 0x00, 0xb8, 0x44, 0x44, 0x44, 0x44, 0xb8, 0x00, 0x00, 
		0x78, 0x84, 0x84, 0x84, 0x44, 0xf8, 0x00, 0x00, 0x00, 0x20, 0x70, 0x20, 0x00, 0x00, 0x00, 0x00, 
		0x00, 0x20, 0x70, 0x20, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x10, 0x08, 0x00, 0x00, 0x00, 
		0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x00, 0x00, 0x00, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00, 
		0x04, 0x84, 0x44, 0x24, 0x18, 0x00, 0x00, 0x00, 0xf0, 0x08, 0xc4, 0x24, 0x24, 0xf8, 0x00, 0x00, 
		0xf8, 0x84, 0x84, 0x84, 0x84, 0xf8, 0x00, 0x00, 0xfc, 0x44, 0x44, 0x44, 0x78, 0x80, 0x00, 0x00, 
		0xf8, 0x04, 0x04, 0x04, 0x04, 0x18, 0x00, 0x00, 0xfc, 0x04, 0x04, 0x04, 0x08, 0xf0, 0x00, 0x00, 
		0xfc, 0x44, 0x44, 0x44, 0x44, 0x04, 0x00, 0x00, 0xfc, 0x44, 0x44, 0x44, 0x44, 0x04, 0x00, 0x00, 
		0xf8, 0x04, 0x04, 0x84, 0x84, 0x98, 0x00, 0x00, 0xfc, 0x40, 0x40, 0x40, 0x40, 0xfc, 0x00, 0x00, 
		0x04, 0x04, 0xfc, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x04, 0xfc, 0x00, 0x00, 
		0xfc, 0x40, 0x20, 0xd0, 0x08, 0x04, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
		0xfc, 0x18, 0x60, 0x80, 0x60, 0x18, 0xfc, 0x00, 0xfc, 0x18, 0x60, 0x80, 0x00, 0xfc, 0x00, 0x00, 
		0xf8, 0x04, 0x04, 0x04, 0x04, 0xf8, 0x00, 0x00, 0xfc, 0x84, 0x84, 0x84, 0x84, 0x78, 0x00, 0x00, 
		0xf8, 0x04, 0x04, 0x04, 0x04, 0xf8, 0x00, 0x00, 0xfc, 0x84, 0x84, 0x84, 0x84, 0x78, 0x00, 0x00, 
		0x38, 0x44, 0x44, 0x84, 0x84, 0x08, 0x00, 0x00, 0x04, 0x04, 0x04, 0xfc, 0x04, 0x04, 0x04, 0x00, 
		0xfc, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 
		0xfc, 0x00, 0x00, 0xc0, 0x00, 0x00, 0xfc, 0x00, 0x0c, 0x30, 0xc0, 0xc0, 0x30, 0x0c, 0x00, 0x00, 
		0x3c, 0x40, 0x80, 0x80, 0x40, 0x3c, 0x00, 0x00, 0x04, 0x04, 0x84, 0x44, 0x34, 0x0c, 0x00, 0x00, 
		0x00, 0x00, 0xfe, 0x02, 0x02, 0x02, 0x00, 0x00, 0x06, 0x18, 0x60, 0x80, 0x00, 0x00, 0x00, 0x00, 
		0x02, 0x02, 0x02, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x10, 0x08, 0x04, 0x04, 0x08, 0x10, 0x00, 0x00, 
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x0c, 0x18, 0x20, 0x00, 0x00, 0x00, 
		0x00, 0xa0, 0xa0, 0xa0, 0xa0, 0xc0, 0x00, 0x00, 0xfc, 0x40, 0x20, 0x20, 0x20, 0xc0, 0x00, 0x00, 
		0xc0, 0x20, 0x20, 0x20, 0x20, 0x40, 0x00, 0x00, 0xc0, 0x20, 0x20, 0x20, 0x40, 0xfc, 0x00, 0x00, 
		0xc0, 0x20, 0x20, 0x20, 0x20, 0xc0, 0x00, 0x00, 0x80, 0xf8, 0x84, 0x84, 0x84, 0x08, 0x00, 0x00, 
		0xc0, 0x20, 0x20, 0x20, 0x40, 0xe0, 0x00, 0x00, 0xfc, 0x40, 0x20, 0x20, 0x20, 0xc0, 0x00, 0x00, 
		0x00, 0x20, 0x20, 0xec, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0xec, 0x00, 0x00, 0x00, 
		0xfc, 0x00, 0x80, 0x40, 0x20, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
		0xe0, 0x20, 0x20, 0xc0, 0x20, 0x20, 0xc0, 0x00, 0xe0, 0x40, 0x20, 0x20, 0x20, 0xc0, 0x00, 0x00, 
		0xc0, 0x20, 0x20, 0x20, 0x20, 0xc0, 0x00, 0x00, 0xe0, 0x40, 0x20, 0x20, 0x20, 0xc0, 0x00, 0x00, 
		0xc0, 0x20, 0x20, 0x20, 0x40, 0xe0, 0x00, 0x00, 0xe0, 0x40, 0x20, 0x20, 0x20, 0x40, 0x00, 0x00, 
		0xc0, 0x20, 0x20, 0x20, 0x20, 0x40, 0x00, 0x00, 0x20, 0xf8, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 
		0xe0, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 
		0xe0, 0x00, 0x00, 0x80, 0x00, 0x00, 0xe0, 0x00, 0x20, 0x40, 0x80, 0x80, 0x40, 0x20, 0x00, 0x00, 
		0xe0, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x20, 0x20, 0x20, 0x20, 0xa0, 0x60, 0x00, 0x00, 
		0x00, 0x80, 0x80, 0x7c, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 
		0x02, 0x02, 0x7c, 0x80, 0x80, 0x00, 0x00, 0x00, 0x30, 0x08, 0x08, 0x10, 0x20, 0x20, 0x18, 0x00, 
		0x00, 0x00, 0x0d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
		0x01, 0x07, 0x01, 0x01, 0x07, 0x01, 0x00, 0x00, 0x04, 0x04, 0x0f, 0x04, 0x03, 0x00, 0x00, 0x00, 
		0x0c, 0x02, 0x01, 0x06, 0x09, 0x06, 0x00, 0x00, 0x07, 0x08, 0x08, 0x09, 0x06, 0x09, 0x00, 0x00, 
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0c, 0x10, 0x20, 0x00, 0x00, 
		0x20, 0x10, 0x0c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01, 0x01, 0x02, 0x00, 0x00, 0x00, 
		0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x20, 0x18, 0x0c, 0x04, 0x00, 0x00, 0x00, 0x00, 
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x1c, 0x08, 0x00, 0x00, 0x00, 0x00, 
		0x18, 0x06, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x08, 0x08, 0x04, 0x03, 0x00, 0x00, 
		0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x0a, 0x09, 0x08, 0x08, 0x08, 0x00, 0x00, 
		0x06, 0x08, 0x08, 0x08, 0x08, 0x07, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x0f, 0x01, 0x00, 0x00, 
		0x06, 0x08, 0x08, 0x08, 0x08, 0x07, 0x00, 0x00, 0x07, 0x08, 0x08, 0x08, 0x08, 0x07, 0x00, 0x00, 
		0x00, 0x0c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0x08, 0x08, 0x08, 0x07, 0x00, 0x00, 
		0x04, 0x08, 0x08, 0x08, 0x08, 0x07, 0x00, 0x00, 0x00, 0x08, 0x1c, 0x08, 0x00, 0x00, 0x00, 0x00, 
		0x20, 0x18, 0x0c, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x08, 0x00, 0x00, 0x00, 
		0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x00, 0x00, 0x00, 0x08, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 
		0x00, 0x0d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x09, 0x0a, 0x0a, 0x03, 0x00, 0x00, 
		0x0f, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x08, 0x08, 0x08, 0x08, 0x07, 0x00, 0x00, 
		0x07, 0x08, 0x08, 0x08, 0x08, 0x06, 0x00, 0x00, 0x0f, 0x08, 0x08, 0x08, 0x04, 0x03, 0x00, 0x00, 
		0x0f, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
		0x07, 0x08, 0x08, 0x08, 0x08, 0x07, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 
		0x08, 0x08, 0x0f, 0x08, 0x08, 0x00, 0x00, 0x00, 0x06, 0x08, 0x08, 0x08, 0x08, 0x07, 0x00, 0x00, 
		0x0f, 0x00, 0x00, 0x00, 0x03, 0x0c, 0x00, 0x00, 0x0f, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 
		0x0f, 0x00, 0x00, 0x01, 0x00, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x00, 0x01, 0x06, 0x0f, 0x00, 0x00, 
		0x07, 0x08, 0x08, 0x08, 0x08, 0x07, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
		0x07, 0x08, 0x08, 0x0e, 0x18, 0x17, 0x00, 0x00, 0x0f, 0x00, 0x01, 0x02, 0x04, 0x08, 0x00, 0x00, 
		0x04, 0x08, 0x08, 0x08, 0x08, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 
		0x07, 0x08, 0x08, 0x08, 0x08, 0x07, 0x00, 0x00, 0x00, 0x03, 0x0c, 0x0c, 0x03, 0x00, 0x00, 0x00, 
		0x03, 0x0c, 0x03, 0x00, 0x03, 0x0c, 0x03, 0x00, 0x0c, 0x03, 0x00, 0x00, 0x03, 0x0c, 0x00, 0x00, 
		0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x0a, 0x09, 0x08, 0x08, 0x08, 0x00, 0x00, 
		0x00, 0x00, 0x3f, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x06, 0x18, 0x00, 0x00, 
		0x20, 0x20, 0x20, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
		0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
		0x07, 0x08, 0x08, 0x08, 0x04, 0x0f, 0x00, 0x00, 0x0f, 0x04, 0x08, 0x08, 0x08, 0x07, 0x00, 0x00, 
		0x07, 0x08, 0x08, 0x08, 0x08, 0x04, 0x00, 0x00, 0x07, 0x08, 0x08, 0x08, 0x04, 0x0f, 0x00, 0x00, 
		0x07, 0x09, 0x09, 0x09, 0x09, 0x09, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
		0x23, 0x44, 0x44, 0x44, 0x42, 0x3f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 
		0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x10, 0x20, 0x20, 0x20, 0x1f, 0x00, 0x00, 0x00, 
		0x0f, 0x01, 0x01, 0x02, 0x04, 0x08, 0x00, 0x00, 0x00, 0x07, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 
		0x0f, 0x00, 0x00, 0x03, 0x00, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 
		0x07, 0x08, 0x08, 0x08, 0x08, 0x07, 0x00, 0x00, 0x7f, 0x02, 0x04, 0x04, 0x04, 0x03, 0x00, 0x00, 
		0x03, 0x04, 0x04, 0x04, 0x02, 0x7f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
		0x04, 0x09, 0x09, 0x09, 0x09, 0x06, 0x00, 0x00, 0x00, 0x07, 0x08, 0x08, 0x08, 0x04, 0x00, 0x00, 
		0x07, 0x08, 0x08, 0x08, 0x04, 0x0f, 0x00, 0x00, 0x00, 0x03, 0x0c, 0x0c, 0x03, 0x00, 0x00, 0x00, 
		0x07, 0x08, 0x04, 0x03, 0x04, 0x08, 0x07, 0x00, 0x08, 0x04, 0x02, 0x02, 0x04, 0x08, 0x00, 0x00, 
		0x23, 0x44, 0x44, 0x44, 0x42, 0x3f, 0x00, 0x00, 0x08, 0x0c, 0x0a, 0x09, 0x08, 0x08, 0x00, 0x00, 
		0x00, 0x00, 0x00, 0x1f, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 
		0x20, 0x20, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
				}
};