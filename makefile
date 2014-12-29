all:
	gcc -I . -I src/ *.c src/*.c -o tests

gdb :
	gcc -ggdb -I . -I src/ *.c src/*.c -o tests

clean:
	rm tests

