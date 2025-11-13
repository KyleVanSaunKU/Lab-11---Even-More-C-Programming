CC = g++
CFLAGS = -Wall -g

all: myprogram

myprogram: Main.o Matrix.o
    $(CC) $(CFLAGS) Main.o Matrix.o -o myprogram

Main.o: Main.cpp Matrix.h
    $(CC) $(CFLAGS) -c Main.cpp -o Main.o

Matrix.o: Matrix.cpp Matrix.h
    $(CC) $(CFLAGS) -c Matrix.cpp -o Matrix.o

clean:
    rm -f *.o myprogram

