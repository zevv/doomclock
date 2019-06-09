#include <avr/io.h>
#include <avr/pgmspace.h>

#include "dpy.h"
#include "spi.h"
#include "printd.h"
#include "msg.h"

#define HAVE_FONTS


#ifdef HAVE_FONTS

#include "font-tiny.c"
#include "font-normal.c"
#include "font-bold.c"
#include "font-medium.c"

struct font {
	const struct img *img;
	uint8_t cw;
	uint8_t ch;
	uint8_t c_from;
	uint8_t c_to;
};


void dpy_tx(enum dc dc, void *data, size_t len);

struct font font_list[] = {
	[FONT_TINY] = {
		.img = &font_tiny,
		.cw = 5,
		.ch = 8,
		.c_from = '!',
		.c_to = '~',
	},
	[FONT_NORMAL] = {
		.img = &font_normal,
		.cw = 8,
		.ch = 16,
		.c_from = '!',
		.c_to = '~',
	},
	[FONT_BOLD] = {
		.img = &font_bold,
		.cw = 8,
		.ch = 16,
		.c_from = '!',
		.c_to = '~',
	},
	[FONT_MEDIUM] = {
		.img = &font_medium,
		.cw = 16,
		.ch = 20,
		.c_from = '0',
		.c_to = ':',
	},
};

#endif

/*
 * Connect display SSD1306:
 *
 * SSD1306 pin		AVR/system
 * -------------------------------
 * GND	 		
 * Vin	 		
 * 3v3   		
 * CS    		
 * RST 	 		
 * DC/SA0		
 * SS    		
 * CLK   		
 * DATA  		
 */


#define FONT_WIDTH 8
#define FONT_HEIGHT 14
#define FONT_DPY_OFFSET_X -1
#define FONT_DPY_OFFSET_Y -15

#define CMD_SETCONTRAST 0x81
#define CMD_DISPLAYALLON_RESUME 0xA4
#define CMD_DISPLAYALLON 0xA5
#define CMD_NORMALDISPLAY 0xA6
#define CMD_INVERTDISPLAY 0xA7
#define CMD_DISPLAYOFF 0xAE
#define CMD_DISPLAYON 0xAF
#define CMD_SETDISPLAYOFFSET 0xD3
#define CMD_SETCOMPINS 0xDA
#define CMD_SETVCOMDETECT 0xDB
#define CMD_SETDISPLAYCLOCKDIV 0xD5
#define CMD_SETPRECHARGE 0xD9
#define CMD_SETMULTIPLEX 0xA8
#define CMD_SETLOWCOLUMN 0x00
#define CMD_SETHIGHCOLUMN 0x10
#define CMD_SETSTARTLINE 0x40
#define CMD_MEMORYMODE 0x20
#define CMD_COLUMNADDR 0x21
#define CMD_PAGEADDR 0x22
#define CMD_COMSCANINC 0xC0
#define CMD_COMSCANDEC 0xC8
#define CMD_SEGREMAP 0xA0
#define CMD_CHARGEPUMP 0x8D
#define CMD_EXTERNALVCC 0x1
#define CMD_SWITCHCAPVCC 0x2
#define CMD_ACTIVATE_SCROLL 0x2F
#define CMD_DEACTIVATE_SCROLL 0x2E
#define CMD_SET_VERTICAL_SCROLL_AREA 0xA3
#define CMD_RIGHT_HORIZONTAL_SCROLL 0x26
#define CMD_LEFT_HORIZONTAL_SCROLL 0x27
#define CMD_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29
#define CMD_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL 0x2A


static void dpy_cmd(uint8_t c);

uint8_t fb[LCD_WIDTH * LCD_HEIGHT / 8];

static uint8_t fn_dpy(struct msg *m)
{
	if(m->argc < 1) return -1;
	char cmd = m->argv[0][0];

	if(cmd == 'c') {
		dpy_clear();
		return 0;
	}

	if(cmd == 't' && m->argc == 5) {
		int font = (m->argv[1][0] == '1') ? FONT_NORMAL : FONT_MEDIUM;
		int x = atoi(m->argv[2]);
		int y = atoi(m->argv[3]);
		dpy_text(font, x, y, m->argv[4]);
		dpy_flush();
	}
	return 0;
}


void dpy_init(void)
{
	msg_add_handler("dpy", fn_dpy, 0);

	dpy_cmd(CMD_DISPLAYOFF);
	dpy_cmd(CMD_SETDISPLAYCLOCKDIV); dpy_cmd(0x80); 
	dpy_cmd(CMD_SETMULTIPLEX);       dpy_cmd(LCD_HEIGHT - 1);
	dpy_cmd(CMD_SETDISPLAYOFFSET);   dpy_cmd(0x00);
	dpy_cmd(CMD_SETSTARTLINE | 0x0);
	dpy_cmd(CMD_SETCOMPINS);         dpy_cmd(0x12);

	dpy_cmd(CMD_CHARGEPUMP);         dpy_cmd(0x14);

	dpy_cmd(CMD_MEMORYMODE);         dpy_cmd(0x00);
	dpy_cmd(CMD_SEGREMAP | 0x1);
	dpy_cmd(CMD_COMSCANDEC);

	dpy_cmd(CMD_SETPRECHARGE);       dpy_cmd(0x32);
	dpy_cmd(CMD_SETVCOMDETECT);      dpy_cmd(0x40);
	dpy_cmd(CMD_DISPLAYALLON_RESUME);
	dpy_cmd(CMD_NORMALDISPLAY);
	dpy_cmd(CMD_DISPLAYON);

//	dpy_brightness(255);
}


/*
 * Set display brightness from 0 to 255
 */

void dpy_brightness(uint8_t v)
{
	dpy_cmd(CMD_SETCONTRAST);
	dpy_cmd(v);
}


void dpy_tx(enum dc dc, void *data, size_t len)
{
	spi_tx(data, len, dc == DC_DATA);
}


static void dpy_cmd(uint8_t c)
{
	dpy_tx(DC_CMD, &c, 1);
}


void dpy_flush(void)
{
	dpy_cmd(CMD_PAGEADDR);
	dpy_cmd(0);
	dpy_cmd(7);

	dpy_cmd(CMD_COLUMNADDR);
	dpy_cmd(0);
	dpy_cmd(127);

	dpy_cmd(CMD_MEMORYMODE);
	dpy_cmd(0x00);

	dpy_tx(DC_DATA, fb, sizeof fb);
};


void dpy_clear(void)
{
	memset(fb, 0x00, sizeof fb);
}


void dpy_pset(uint8_t x, uint8_t y, uint8_t v)
{
	if(x < 128 && y < 64) {

		uint16_t o = (y/8) * LCD_WIDTH + x;
		uint8_t b = y & 0x07;

		if(v) {
			fb[o] |= (1<<b);
		} else {
			fb[o] &= ~(1<<b);
		}
	}
}

#define swap(a,b) { int _tmpswap = a; a = b; b = _tmpswap; } 

void dpy_line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t v)
{
	int i;
	int steep = 0;
	int sx, sy;	
	int dx, dy;
	int e;

	/*
	 * Draw the line using the bresenham algorithm. 
	 */

	dx = abs(x2 - x1);
	dy = abs(y2 - y1);

	sx = ((x2 - x1) > 0) ? 1 : -1;
	sy = ((y2 - y1) > 0) ? 1 : -1;

	if (dy > dx) {
		steep = 1;
		swap(x1, y1);
		swap(dx, dy);
		swap(sx, sy);
	}

	e = (dy << 1) - dx;
	for (i = 0; i <= dx; i++) {
		if (steep) {
			dpy_pset(y1, x1, v);
		} else {
			dpy_pset(x1, y1, v);
		}
		while (e >= 0) {
			y1 += sy;
			e -= (dx << 1);
		}
		x1 += sx;
		e += (dy << 1);
	}
}


void dpy_rect(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t v)
{

	dpy_line( x1, y1, x2, y1, v);   //  ---
	dpy_line( x1, y1, x1, y2, v);   //  |
	dpy_line( x2, y1, x2, y2, v);   //    |
	dpy_line( x1, y2, x2, y2 ,v);   //  ___

}


void dpy_circle(int8_t x0, int8_t y0, int8_t radius, uint8_t v)
{
	int8_t x = radius, y = 0;
	int8_t radiusError = 1-x;

	while(x >= y)
	{
		dpy_pset( x + x0,  y + y0, v);
		dpy_pset( y + x0,  x + y0, v);
		dpy_pset(-x + x0,  y + y0, v);
		dpy_pset(-y + x0,  x + y0, v);
		dpy_pset(-x + x0, -y + y0, v);
		dpy_pset(-y + x0, -x + y0, v);
		dpy_pset( x + x0, -y + y0, v);
		dpy_pset( y + x0, -x + y0, v);

		y++;

		if (radiusError<0) {
			radiusError += 2 * y + 1;
		} else {
			x--;
			radiusError += 2 * (y - x + 1);
		}
	}
}


uint8_t rev(uint8_t x)
{
	x = ((x >> 1) & 0x55) | ((x << 1) & 0xaa);
	x = ((x >> 2) & 0x33) | ((x << 2) & 0xcc);
	x = ((x >> 4) & 0x0f) | ((x << 4) & 0xf0);
	return x;
}


/*
 * Clear area. assume mulitple of 8 
 */

void dpy_clear_rect(uint8_t dx, uint8_t dy, uint8_t w, uint8_t h)
{
	uint8_t x, y;
	for(y=0; y<h; y+=8) {
		uint8_t *pd = fb + LCD_WIDTH * (dy + y) / 8 + dx;
		for(x=0; x<w; x++) {
			*pd++ = 0;
		}
	}
}


/*
 * Blit img to framebuffer. dy and h should be multiple of 8.
 */

void dpy_blit(const struct img *src, uint16_t sx, uint8_t sy, uint8_t dx, uint8_t dy, uint8_t w, uint8_t h)
{
	uint8_t x, y;

	uint16_t sw = pgm_read_word(&src->w);
	uint16_t sh = pgm_read_word(&src->h);

	if(w > sw) w = sw;
	if(h > sh) h = sh;

	for(y=0; y<h; y+=8) {

		const uint8_t *ps = src->data + sw * (sy + y) / 8 + sx;
		uint8_t *pd = fb + LCD_WIDTH * (dy + y) / 8 + dx;

		for(x=0; x<w; x++) {
			*pd++ = pgm_read_byte(ps++);
		}
	}
}

#ifdef HAVE_FONTS

int dpy_text(enum font_id font_id, int xpos, int ypos, char *s)
{
	struct font *font = &font_list[font_id];

	while(*s) {
		if(*s < font->c_from || *s > font->c_to) {
			dpy_clear_rect(xpos, ypos, font->cw, font->ch);
		} else {
			uint16_t sx = (*s - font->c_from) * font->cw;
			dpy_blit(font->img, sx, 0, xpos, ypos, font->cw, font->ch);
		}
		xpos += font->cw;
		s++;
	}

	return font->ch;
}


void dpy_printf(enum font_id font_id, int xpos, int ypos, char *fmt, ...)
{
	//char buf[26];
	//va_list va;
	//va_start(va, fmt);
	//vsnprintf(buf, sizeof buf, fmt, va);
	//va_end(va);
	dpy_text(font_id, xpos, ypos, fmt);
}

#endif

void dpy_invert(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
	uint8_t y, x;
	for(y=y1; y<y2; y+=8) {
		for(x=x1; x<x2; x++) {
			int o = (y/8) * LCD_WIDTH + x;
			fb[o] ^= 0xff;
		}
	}
}

static void corner(uint8_t x, uint8_t y, uint8_t *mask)
{
	uint8_t i;
	uint8_t *p = fb + (y/8) * LCD_WIDTH + x;
	for(i=0; i<4; i++) *p++ ^= *mask++;
}


void dpy_invert2(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
	dpy_invert(x1, y1, x2, y2);

	uint8_t mask[4][4] = {
		{ 0x0f, 0x03, 0x01, 0x01 },
		{ 0x01, 0x01, 0x03, 0x0f },
		{ 0xf0, 0xc0, 0x80, 0x80 },
		{ 0x80, 0x80, 0xc0, 0xf0 },
	};

	corner(x1,   y1,   mask[0]);
	corner(x2-4, y1,   mask[1]);
	corner(x1,   y2-8, mask[2]);
	corner(x2-4, y2-8, mask[3]);
}


/*
 * End
 */
