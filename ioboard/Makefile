
NAME		:= smartbox
VERSION_MAJ  	:= 1
VERSION_MIN  	:= 0
VERSION_GIT	:= $(shell git describe)
GITMODIFIED     := $(shell (git st | grep "modified:\|added:\|deleted:" -q) && echo "M")
VERSION      	:= $(VERSION_GIT)$(GITMODIFIED)
DATE		:= $(shell date +%Y%m%d)

BIN		:= $(NAME)-$(VERSION).elf
FHEX		:= $(NAME)-$(VERSION)-flash.ihx
EHEX		:= $(NAME)-$(VERSION)-eeprom.ihx
ZIP		:= $(NAME)-$(VERSION).zip
ZIPSRC		:= $(NAME)-$(VERSION)-source.zip
BAT		:= $(NAME)-$(VERSION).bat

SRC		+= main.c
SRC		+= msg.c
SRC		+= event.c
SRC		+= timer.c
SRC		+= printd.c
SRC		+= uart.c
SRC		+= gpio.c
SRC		+= spi.c
SRC		+= dpy.c

#
# Special options for each target
# 

CROSS		+= avr-
CFLAGS  	+= -DF_CPU=16000000
CFLAGS  	+= -mmcu=atmega328p -Os -I. -fshort-enums 
CFLAGS  	+= -DVERSION_GIT=\"$(VERSION_GIT)$(GITMODIFIED)\"
LDFLAGS 	+= -mmcu=atmega328p 

#############################################################################

OBJS		:= $(subst .c,.o, $(SRC))

CFLAGS  	+= -g -I. -I..
CFLAGS  	+= -Wall -Werror
LDFLAGS 	+= -g
CFLAGS  	+= -DNAME=\"$(NAME)\" -DVERSION=\"$(VERSION)\" -DDATE=\"$(DATE)\" 
ADFLAGS 	+= -p m328p -c stk500v1 -P /dev/ttyUSB0 -b 57600 -V -F

ifdef ccache
CROSS	:= ccache $(CROSS)
endif

CC 		:= $(CROSS)gcc
LCC 		:= gcc
LD 		:= $(CROSS)gcc
OBJCOPY 	:= $(CROSS)objcopy
OBJDUMP 	:= $(CROSS)objdump
STRIP		:= $(CROSS)strip
SIZE		:= $(CROSS)size
NSIS		:= makensis
AVRDUDE 	:= sudo avrdude


ifdef verbose
E	:= 
P	:= @true
else
E	:= @
P	:= @echo
endif

default: $(BIN) 

doc: protocol.html

protocol.html: protocol.txt
	asciidoc -b html5 -a toc2 -a theme=flask protocol.txt

reset: reset.c
	$(P) " [CC   ] $<"
	$(E) gcc -Wall -Werror $? -o $@ -lftdi

%.o: %.c
	$(P) " [CC   ] $<"
	$(E) $(CC) $(CFLAGS) -c $< -o $@

$(BIN): $(OBJS)
	$(P) " [LD   ] $@"
	$(E) $(LD) -o $@ $^ $(LDFLAGS)
	$(E) $(SIZE) $@

clean:
	$(P) " [CLEAN]" 
	$(E) rm -f *.o reset
	$(E) rm -f $(BIN) *.elf *.ihx tags $(BIN).elf .depend *.zip *.bat

.PHONY: tags
tags:
	$(P) " [CTAGS]"
	$(E) ctags $(SRC)
	
$(FHEX) $(EHEX): $(BIN)
	$(P) " [OBJCP] $@"
	$(E) $(OBJCOPY) -j .text -j .data -O ihex $(BIN) $(FHEX)
	$(E) #$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O ihex $(BIN) $(EHEX)

.PHONY: .depend
.depend:
	$(P) " [MKDEP]"
	$(E) makedepend -f - -- $(CFLAGS) -- $(SRC) > $@ 2>/dev/null

install: reset $(FHEX) $(EHEX)
	$(P) " [INST ] $^"
	$(E) sudo ./reset
	$(E) $(AVRDUDE) $(ADFLAGS) -U flash:w:$(FHEX):i -U eeprom:w:$(EHEX):i

install-fuses: $(FHEX) $(EHEX)
	$(P) " [INST ] $^"
	$(E) $(AVRDUDE) $(ADFLAGS) -e -U hfuse:w:0xd9:m -U lfuse:w:0xd6:m  -U efuse:w:0x04:m

strip:	$(BIN)
	$(P) " [STRIP]"
	$(E) $(STRIP) $(BIN)

bat: $(BAT)

$(BAT): $(FHEX) $(EHEX)
	$(P) " [BAT  ] $@"
	$(E) ./mkprogram $^ > $@

zip: $(ZIP)
zipsrc: $(ZIPSRC)

$(ZIP):	$(FHEX) $(EHEX)
	$(P) " [ZIP  ] $@"
	$(E) zip -q $(ZIP) $^

$(ZIPSRC): clean
	$(P) " [ZIP  ] $@"
	$(E) zip -qr $(ZIPSRC) *.c *.h Makefile .git

versions:
	git log | grep commit | awk '{print $$2}' | xargs git describe

-include .depend
