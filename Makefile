CFLAGS = -Wall

lispy: mpc.o
	cc -std=c99 lispy.c mpc.o -ledit -lm -o lispy
mpc.o:
	cc -c mpc.c
clean:
	rm lispy mpc.o
