DEBUG	= -O3
CC	= g++
INCLUDE	= -I/usr/local/include
CFLAGS	= $(DEBUG) -Wall $(INCLUDE) -Winline -pipe

LDFLAGS	= -L/usr/local/lib
LDLIBS	= -lwiringPi -lwiringPiDev -lpthread -lm -lwiringPiPca9685

# Should not alter anything below this line
###############################################################################

SRC	=	main.cpp

OBJ	=	$(SRC:.cpp=.o)
BINS=	$(SRC:.cpp=)
all:	$(BINS)

main:	main.o
	@echo [link]
	@$(CC) -o $@ main.o $(LDFLAGS) $(LDLIBS)

install:
	@mv main ../hexapod

.cpp.o:
	@echo [CC] $<
	@$(CC) -c $(CFLAGS) $< -o $@
