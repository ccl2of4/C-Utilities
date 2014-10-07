all:
	gcc -I . -I src/ *.c src/*.c -o tests
clean:
	rm tests

