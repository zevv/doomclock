#ifndef msg_h
#define msg_h

#include <stdint.h>

#define MSG_MAX_BODY_LEN 64
#define MSG_MAX_HANDLERS 16

struct msg {
	char *seq;
	uint8_t argc;
	char **argv;
	char reply[MSG_MAX_BODY_LEN];
};

typedef uint8_t (*msg_handler)(struct msg *m);

void msg_init(void);
void msg_add_handler(const char *cmd, msg_handler fn, uint8_t nargs);
void msg_handle_char(char c);
void msg_reply(struct msg *m, char *fmt, ...);
void msg_send_event(const char *fmt, ...);

#endif
