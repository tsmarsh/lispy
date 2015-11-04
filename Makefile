CFLAGS = -Wall

lispy: mpc.o builtin.o
	cc -std=c99 lispy.c lval.o builtin.o lenv.o mpc.o -ledit -lm -o lispy

lval.o: mpc.o
	cc -c lval.c

lenv.o:
	cc -c lenv.c

builtin.o: lenv.o lval.o
	cc -c builtin.c

mpc.o:
	cc -c mpc.c

clean:
	rm -f lispy mpc.o lval.o lenv.o builtin.o
