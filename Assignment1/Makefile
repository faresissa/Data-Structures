CC = gcc
CFLAGS = -Wall -pedantic -std=c99
OBJFILES = carbon.o ackermannFunction.o main.o newton.o
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES)

clean:
	rm -f $(OBJFILES) $(TARGET) *~
