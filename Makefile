button.o: button.c
	gcc -c button.c -o button.o

main.o: main.c
	gcc -c main.c -o main.o

all: button.o main.o
	gcc -lusb-1.0 -o button_tool button.o main.o

clean:
	rm *.o
