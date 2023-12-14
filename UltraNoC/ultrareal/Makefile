# makefile

# architecture
TARGET_ARCH = linux64

# compiler
CC     = g++ 

# debug flag
DEBUG  = -g2
OTHER  = -Wall
#LDFLAG = -rdynamic

#CFLAGS = $(DEBUG) $(OTHER) $(LDFLAG)
CFLAGS = $(DEBUG) #$(LDFLAG)

MODULE = ultramulti

SRCS = main.cpp buffer.cpp globalstatus.cpp noc.cpp power.cpp processingelement.cpp hub.cpp gatewayinterface.cpp status.cpp arbiter.cpp circularbuffer.cpp benchmark.cpp

OBJS = $(SRCS:.cc=.o)

include Makefile.defs
# DO NOT DELETE
