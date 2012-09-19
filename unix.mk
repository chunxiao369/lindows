
# 
# compile tool
# compile param
# link    param
# exe file
# *.o file
# compile command 
# link command
#

CC = gcc
CFLAGS = -Wall -O2 -I./unix/
LDFLAGS = 
TARGET = test_lindows
OBJS = yun_sys.o \
yun_socket.o \
yun_files.o \
yun_time.o \
test_lindows.o

COMPILE  = $(CC) $(CFLAGS) -c -o $@ $<
LINK = $(CC) $(OBJS) $(LDFLAGS) -o $@

ALL:$(TARGET)

$(TARGET):$(OBJS)
	$(LINK)

%.o:unix/%.c
	$(COMPILE)
%.o:%.c
	$(COMPILE)

clean:
	rm -f  *~ *.d *.o $(TARGET)
