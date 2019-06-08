
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ftdi.h>
#include <unistd.h>

int main(void)
{
	struct ftdi_context ftdic;
	int r, i;
	uint8_t bitmask[] = { 0xf0, 0x00 };

	if (ftdi_init(&ftdic) < 0) {
		fprintf(stderr, "ftdi_init failed\n");
		return EXIT_FAILURE;
	}

	r = ftdi_usb_open(&ftdic, 0x0403, 0x6001);

	if (r < 0 && r != -5) {
		fprintf(stderr, "unable to open ftdi device: %d (%s)\n", r, ftdi_get_error_string(&ftdic));
		exit(-1);
	}

	for(i=0; i<sizeof(bitmask); i++) {

		r = ftdi_set_bitmode(&ftdic, bitmask[i], BITMODE_CBUS);
		if (r < 0) {
			fprintf(stderr, "set_bitmode failed for 0x%x, error %d (%s)\n", bitmask[i], r, ftdi_get_error_string(&ftdic));
			exit(-1);
		}

	}
	
	ftdi_disable_bitbang(&ftdic);
	ftdi_usb_close(&ftdic);
	ftdi_deinit(&ftdic);

	FILE *f = fopen("/sys/bus/usb-serial/drivers/ftdi_sio/new_id", "w");
	if(f == NULL) {
		fprintf(stderr, "Error: %s\n", strerror(errno));
		exit(-1);
	}
	fprintf(f, "0403 6001\n");
	fclose(f);

	return 0;
}

/*
 * End
 */

