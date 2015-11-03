CFLAGS = -Wall

lispy: mpc.o lval.o
	cc -std=c99 lispy.c lval.o builtin.o mpc.o -ledit -lm -o lispy

lval.o: builtin.o mpc.o
	cc -c lval.c

builtin.o:
	cc -c builtin.c

mpc.o:
	cc -c mpc.c

clean:
	rm -f lispy mpc.o lval.o builtin.o
