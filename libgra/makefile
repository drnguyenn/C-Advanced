CFLAGS = -O

all: libgra.a

OBJS = graph_jrb.o jval.o jrb.o

libfdr.a: $(OBJS)
	ar ru libgra.a $(OBJS)
	ranlib libgra.a 

clean:
	rm -f core *.o libgra.a

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $*.c

