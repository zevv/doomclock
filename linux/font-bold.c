#include "img.h"

const struct img font_bold = {
	.w = 752,
	.h = 16,
	.data = {
		0x00, 0x00, 0xfc, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x3c, 0x3c, 0x3c, 0x00, 0x00, 0x00, 
		0x20, 0xf8, 0xf8, 0x20, 0xf8, 0xf8, 0x20, 0x00, 0x60, 0xf0, 0xf8, 0xf8, 0x90, 0x10, 0x00, 0x00, 
		0x18, 0x3c, 0xbc, 0xf8, 0x70, 0x1c, 0x0c, 0x00, 0x30, 0xf8, 0xc8, 0xf8, 0x30, 0x00, 0x00, 0x00, 
		0x00, 0x00, 0x3c, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xf8, 0x1c, 0x06, 0x02, 0x00, 
		0x02, 0x06, 0x1c, 0xf8, 0xe0, 0x00, 0x00, 0x00, 0x80, 0xa0, 0xe0, 0xc0, 0xe0, 0xa0, 0x80, 0x00, 
		0x80, 0x80, 0x80, 0xf0, 0xf0, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
		0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
		0x00, 0x00, 0x80, 0xe0, 0x78, 0x1e, 0x06, 0x00, 0xf0, 0xf8, 0x8c, 0xc4, 0x4c, 0xf8, 0xf0, 0x00, 
		0x20, 0x30, 0x18, 0xfc, 0xfc, 0x00, 0x00, 0x00, 0x18, 0x1c, 0x04, 0x84, 0xc4, 0x7c, 0x38, 0x00, 
		0x08, 0x0c, 0x44, 0x44, 0x44, 0xfc, 0xb8, 0x00, 0x80, 0xe0, 0x78, 0x1c, 0xfc, 0xfc, 0x00, 0x00, 
		0x7c, 0x7c, 0x24, 0x24, 0x24, 0xe4, 0xc4, 0x00, 0xf8, 0xfc, 0xc4, 0x44, 0x44, 0xcc, 0x88, 0x00, 
		0x04, 0x04, 0x04, 0xc4, 0xf4, 0x3c, 0x0c, 0x00, 0xb8, 0xfc, 0x44, 0x44, 0x44, 0xfc, 0xb8, 0x00, 
		0x78, 0xfc, 0x84, 0x84, 0xc4, 0xfc, 0xf8, 0x00, 0x00, 0x20, 0x70, 0x70, 0x20, 0x00, 0x00, 0x00, 
		0x00, 0x20, 0x70, 0x70, 0x20, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x60, 0x30, 0x18, 0x08, 0x00, 0x00, 
		0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x00, 0x00, 0x08, 0x18, 0x30, 0x60, 0xc0, 0x80, 0x00, 
		0x04, 0x84, 0xc4, 0x64, 0x3c, 0x18, 0x00, 0x00, 0xf0, 0xf8, 0xcc, 0xe4, 0x24, 0xfc, 0xf8, 0x00, 
		0xf8, 0xfc, 0x84, 0x84, 0x84, 0xfc, 0xf8, 0x00, 0xfc, 0xfc, 0x44, 0x44, 0x7c, 0xf8, 0x80, 0x00, 
		0xf8, 0xfc, 0x04, 0x04, 0x04, 0x1c, 0x18, 0x00, 0xfc, 0xfc, 0x04, 0x04, 0x0c, 0xf8, 0xf0, 0x00, 
		0xfc, 0xfc, 0x44, 0x44, 0x44, 0x44, 0x04, 0x00, 0xfc, 0xfc, 0x44, 0x44, 0x44, 0x44, 0x04, 0x00, 
		0xf8, 0xfc, 0x04, 0x84, 0x84, 0x9c, 0x98, 0x00, 0xfc, 0xfc, 0x40, 0x40, 0x40, 0xfc, 0xfc, 0x00, 
		0x04, 0x04, 0xfc, 0xfc, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x04, 0xfc, 0xfc, 0x00, 
		0xfc, 0xfc, 0x60, 0xf0, 0xd8, 0x0c, 0x04, 0x00, 0xfc, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
		0xfc, 0xfc, 0x78, 0xe0, 0xe0, 0x78, 0xfc, 0xfc, 0xfc, 0xfc, 0x78, 0xe0, 0x80, 0xfc, 0xfc, 0x00, 
		0xf8, 0xfc, 0x04, 0x04, 0x04, 0xfc, 0xf8, 0x00, 0xfc, 0xfc, 0x84, 0x84, 0x84, 0xfc, 0x78, 0x00, 
		0xf8, 0xfc, 0x04, 0x04, 0x04, 0xfc, 0xf8, 0x00, 0xfc, 0xfc, 0x84, 0x84, 0x84, 0xfc, 0x78, 0x00, 
		0x38, 0x7c, 0x44, 0xc4, 0x84, 0x8c, 0x08, 0x00, 0x04, 0x04, 0x04, 0xfc, 0xfc, 0x04, 0x04, 0x04, 
		0xfc, 0xfc, 0x00, 0x00, 0x00, 0xfc, 0xfc, 0x00, 0xfc, 0xfc, 0x00, 0x00, 0x00, 0xfc, 0xfc, 0x00, 
		0xfc, 0xfc, 0x00, 0xc0, 0xc0, 0x00, 0xfc, 0xfc, 0x0c, 0x3c, 0xf0, 0xc0, 0xf0, 0x3c, 0x0c, 0x00, 
		0x3c, 0x7c, 0xc0, 0x80, 0xc0, 0x7c, 0x3c, 0x00, 0x04, 0x04, 0x84, 0xc4, 0x74, 0x3c, 0x0c, 0x00, 
		0x00, 0x00, 0xfe, 0xfe, 0x02, 0x02, 0x02, 0x00, 0x06, 0x1e, 0x78, 0xe0, 0x80, 0x00, 0x00, 0x00, 
		0x02, 0x02, 0x02, 0xfe, 0xfe, 0x00, 0x00, 0x00, 0x10, 0x18, 0x0c, 0x04, 0x0c, 0x18, 0x10, 0x00, 
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x0c, 0x1c, 0x38, 0x20, 0x00, 0x00, 
		0x00, 0xa0, 0xa0, 0xa0, 0xa0, 0xe0, 0xc0, 0x00, 0xfc, 0xfc, 0x60, 0x20, 0x20, 0xe0, 0xc0, 0x00, 
		0xc0, 0xe0, 0x20, 0x20, 0x20, 0x60, 0x40, 0x00, 0xc0, 0xe0, 0x20, 0x20, 0x60, 0xfc, 0xfc, 0x00, 
		0xc0, 0xe0, 0x20, 0x20, 0x20, 0xe0, 0xc0, 0x00, 0x80, 0xf8, 0xfc, 0x84, 0x84, 0x8c, 0x08, 0x00, 
		0xc0, 0xe0, 0x20, 0x20, 0x60, 0xe0, 0xe0, 0x00, 0xfc, 0xfc, 0x60, 0x20, 0x20, 0xe0, 0xc0, 0x00, 
		0x00, 0x20, 0x20, 0xec, 0xec, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0xec, 0xec, 0x00, 0x00, 
		0xfc, 0xfc, 0x80, 0xc0, 0x60, 0x20, 0x00, 0x00, 0x00, 0xfc, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 
		0xe0, 0xe0, 0x20, 0xe0, 0xe0, 0x20, 0xe0, 0xc0, 0xe0, 0xe0, 0x60, 0x20, 0x20, 0xe0, 0xc0, 0x00, 
		0xc0, 0xe0, 0x20, 0x20, 0x20, 0xe0, 0xc0, 0x00, 0xe0, 0xe0, 0x60, 0x20, 0x20, 0xe0, 0xc0, 0x00, 
		0xc0, 0xe0, 0x20, 0x20, 0x60, 0xe0, 0xe0, 0x00, 0xe0, 0xe0, 0x60, 0x20, 0x20, 0x60, 0x40, 0x00, 
		0xc0, 0xe0, 0x20, 0x20, 0x20, 0x60, 0x40, 0x00, 0x20, 0xf8, 0xf8, 0x20, 0x20, 0x20, 0x00, 0x00, 
		0xe0, 0xe0, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0x00, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0x00, 
		0xe0, 0xe0, 0x00, 0x80, 0x80, 0x00, 0xe0, 0xe0, 0x20, 0x60, 0xc0, 0x80, 0xc0, 0x60, 0x20, 0x00, 
		0xe0, 0xe0, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0x00, 0x20, 0x20, 0x20, 0x20, 0xa0, 0xe0, 0x60, 0x00, 
		0x00, 0x80, 0x80, 0xfc, 0x7e, 0x02, 0x02, 0x00, 0x00, 0x00, 0xfe, 0xfe, 0x00, 0x00, 0x00, 0x00, 
		0x02, 0x02, 0x7e, 0xfc, 0x80, 0x80, 0x00, 0x00, 0x30, 0x38, 0x08, 0x18, 0x30, 0x20, 0x38, 0x18, 
		0x00, 0x00, 0x0d, 0x0d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
		0x01, 0x07, 0x07, 0x01, 0x07, 0x07, 0x01, 0x00, 0x04, 0x04, 0x0f, 0x0f, 0x07, 0x03, 0x00, 0x00, 
		0x0c, 0x0e, 0x03, 0x07, 0x0f, 0x0f, 0x06, 0x00, 0x07, 0x0f, 0x08, 0x09, 0x0f, 0x0f, 0x09, 0x00, 
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0f, 0x1c, 0x30, 0x20, 0x00, 
		0x20, 0x30, 0x1c, 0x0f, 0x03, 0x00, 0x00, 0x00, 0x00, 0x02, 0x03, 0x01, 0x03, 0x02, 0x00, 0x00, 
		0x00, 0x00, 0x00, 0x07, 0x07, 0x00, 0x00, 0x00, 0x20, 0x38, 0x1c, 0x0c, 0x04, 0x00, 0x00, 0x00, 
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x1c, 0x1c, 0x08, 0x00, 0x00, 0x00, 
		0x18, 0x1e, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x0c, 0x08, 0x0c, 0x07, 0x03, 0x00, 
		0x00, 0x00, 0x00, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x0c, 0x0e, 0x0b, 0x09, 0x08, 0x08, 0x08, 0x00, 
		0x06, 0x0e, 0x08, 0x08, 0x08, 0x0f, 0x07, 0x80, 0x81, 0x81, 0x81, 0x81, 0x8f, 0x8f, 0x81, 0x80, 
		0x06, 0x0e, 0x08, 0x08, 0x08, 0x0f, 0x07, 0x00, 0x07, 0x0f, 0x08, 0x08, 0x08, 0x0f, 0x07, 0x00, 
		0x00, 0x0c, 0x0f, 0x03, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0f, 0x08, 0x08, 0x08, 0x0f, 0x07, 0x00, 
		0x04, 0x0c, 0x08, 0x08, 0x08, 0x0f, 0x07, 0x00, 0x00, 0x08, 0x1c, 0x1c, 0x08, 0x00, 0x00, 0x00, 
		0x20, 0x38, 0x1c, 0x0c, 0x04, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x06, 0x0c, 0x08, 0x00, 0x00, 
		0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x00, 0x00, 0x08, 0x0c, 0x06, 0x03, 0x01, 0x00, 0x00, 
		0x00, 0x0d, 0x0d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x0d, 0x0b, 0x0a, 0x0b, 0x03, 0x00, 
		0x0f, 0x0f, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x00, 0x0f, 0x0f, 0x08, 0x08, 0x08, 0x0f, 0x07, 0x00, 
		0x07, 0x0f, 0x08, 0x08, 0x08, 0x0e, 0x06, 0x00, 0x0f, 0x0f, 0x08, 0x08, 0x0c, 0x07, 0x03, 0x00, 
		0x0f, 0x0f, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
		0x07, 0x0f, 0x08, 0x08, 0x08, 0x0f, 0x07, 0x00, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x00, 
		0x08, 0x08, 0x0f, 0x0f, 0x08, 0x08, 0x00, 0x00, 0x06, 0x0e, 0x08, 0x08, 0x08, 0x0f, 0x07, 0x00, 
		0x0f, 0x0f, 0x00, 0x00, 0x03, 0x0f, 0x0c, 0x00, 0x0f, 0x0f, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 
		0x0f, 0x0f, 0x00, 0x01, 0x01, 0x00, 0x0f, 0x0f, 0x0f, 0x0f, 0x00, 0x01, 0x07, 0x0f, 0x0f, 0x00, 
		0x07, 0x0f, 0x08, 0x08, 0x08, 0x0f, 0x07, 0x00, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
		0x07, 0x0f, 0x08, 0x0e, 0x1e, 0x1f, 0x17, 0x00, 0x0f, 0x0f, 0x01, 0x03, 0x06, 0x0c, 0x08, 0x00, 
		0x04, 0x0c, 0x08, 0x08, 0x08, 0x0f, 0x07, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x00, 0x00, 0x00, 
		0x07, 0x0f, 0x08, 0x08, 0x08, 0x0f, 0x07, 0x00, 0x00, 0x03, 0x0f, 0x0c, 0x0f, 0x03, 0x00, 0x00, 
		0x03, 0x0f, 0x0f, 0x03, 0x03, 0x0f, 0x0f, 0x03, 0x0c, 0x0f, 0x03, 0x00, 0x03, 0x0f, 0x0c, 0x00, 
		0x00, 0x00, 0x00, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x0c, 0x0e, 0x0b, 0x09, 0x08, 0x08, 0x08, 0x00, 
		0x00, 0x00, 0x3f, 0x3f, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0x1e, 0x18, 0x00, 
		0x20, 0x20, 0x20, 0x3f, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
		0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
		0x07, 0x0f, 0x08, 0x08, 0x0c, 0x0f, 0x0f, 0x00, 0x0f, 0x0f, 0x0c, 0x08, 0x08, 0x0f, 0x07, 0x00, 
		0x07, 0x0f, 0x08, 0x08, 0x08, 0x0c, 0x04, 0x00, 0x07, 0x0f, 0x08, 0x08, 0x0c, 0x0f, 0x0f, 0x00, 
		0x07, 0x0f, 0x09, 0x09, 0x09, 0x09, 0x09, 0x00, 0x00, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 
		0x23, 0x67, 0x44, 0x44, 0x46, 0x7f, 0x3f, 0x00, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x00, 
		0x00, 0x00, 0x00, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x10, 0x30, 0x20, 0x20, 0x3f, 0x1f, 0x00, 0x00, 
		0x0f, 0x0f, 0x01, 0x03, 0x06, 0x0c, 0x08, 0x00, 0x00, 0x07, 0x0f, 0x08, 0x08, 0x08, 0x00, 0x00, 
		0x0f, 0x0f, 0x00, 0x03, 0x03, 0x00, 0x0f, 0x0f, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x00, 
		0x07, 0x0f, 0x08, 0x08, 0x08, 0x0f, 0x07, 0x00, 0x7f, 0x7f, 0x06, 0x04, 0x04, 0x07, 0x03, 0x00, 
		0x03, 0x07, 0x04, 0x04, 0x06, 0x7f, 0x7f, 0x00, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
		0x04, 0x0d, 0x09, 0x09, 0x09, 0x0f, 0x06, 0x00, 0x00, 0x07, 0x0f, 0x08, 0x08, 0x0c, 0x04, 0x00, 
		0x07, 0x0f, 0x08, 0x08, 0x0c, 0x0f, 0x0f, 0x00, 0x00, 0x03, 0x0f, 0x0c, 0x0f, 0x03, 0x00, 0x00, 
		0x07, 0x0f, 0x0c, 0x07, 0x07, 0x0c, 0x0f, 0x07, 0x08, 0x0c, 0x06, 0x02, 0x06, 0x0c, 0x08, 0x00, 
		0x23, 0x67, 0x44, 0x44, 0x46, 0x7f, 0x3f, 0x00, 0x08, 0x0c, 0x0e, 0x0b, 0x09, 0x08, 0x08, 0x00, 
		0x00, 0x00, 0x00, 0x1f, 0x3f, 0x20, 0x20, 0x00, 0x00, 0x00, 0x1f, 0x1f, 0x00, 0x00, 0x00, 0x00, 
		0x20, 0x20, 0x3f, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
				}
};
