
# 
# compile tool
# compile param
# link    param
# exe file
# *.o file
# compile command 
# link command
#
#!include <win32.mak>
CC = cc 
CFLAGS = /Tx86-coff -Ze -Zx -Go -O2 -c /Iwin32
LDFLAGS = kernel32.lib shlwapi.lib
TARGET = test_lindows.exe 
OBJS = yun_sys.obj \
yun_socket.obj \
yun_files.obj \
yun_time.obj \
test_lindows.obj

COMPILE  = $(CC) $(CFLAGS) $< -Fo$@ 
LINK = polink $(OBJS) $(LDFLAGS) -OUT:$@

ALL:$(TARGET)

$(TARGET):$(OBJS)
	$(LINK)

{.\win32\}.c.obj:
	$(COMPILE)
.c.obj:
	$(COMPILE)

clean:
	del *~ *.d *.obj $(TARGET)
