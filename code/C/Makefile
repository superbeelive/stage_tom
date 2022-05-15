CC = gcc
CFLAGS = -Wall -g 
EXEC = main

all: $(EXEC)

main: arduinoUDP.o main.o
	$(CC) -o $@ $^ 

main.o: arduinoUDP.h

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS) 	

clean:
	rm *.o
	rm main
