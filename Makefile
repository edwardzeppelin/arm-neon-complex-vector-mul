CFLAGS = -MMD -march=armv7-a -marm -mfpu=neon -g0 -O2 -DNDEBUG -save-temps 
LDFLAGS = -g0 -O2
LOADLIBES = -lm -lc

.PHONY: all test clean realclean

all: mul_vector_tb test

add_vector_tb: mul_vector_tb.o mul_vector.o mul_vector_ref.o mul_vector_fast.o

test:
	./mul_vector_tb

clean:
	-rm *.d *.o *.i *.s

realclean: clean
	-rm mul_vector_tb

-include $(wildcard *.d)
