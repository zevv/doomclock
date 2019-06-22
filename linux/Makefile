
BIN   	= doomclock
SRC 	= main.c serial.c sound.c io.c dpy.c
PKG	+= alure openal

CFLAGS  += -Wall -Werror -Wno-unused-variable
CFLAGS	+= -O3 -MMD
CFLAGS	+= -g
LDFLAGS += -g

CFLAGS	+= $(shell pkg-config --cflags $(PKG))
LIBS	+= $(shell pkg-config --libs $(PKG))

CROSS	=
OBJS    = $(subst .c,.o, $(SRC))
DEPS    = $(subst .c,.d, $(SRC))
CC 	= $(CROSS)gcc
LD 	= $(CROSS)gcc

$(BIN):	$(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

clean:
	rm -f $(OBJS) $(BIN) core

-include $(DEPS)
