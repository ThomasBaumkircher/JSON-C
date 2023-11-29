# The main all target
all: Parser.o Composer.o
	gcc -shared -o libcjson.so Parser.o Composer.o

	sudo cp libcjson.so /usr/lib
	sudo cp include/*.h /usr/include
	sudo ldconfig

Parser.o: src/Parser.c
	gcc -Wall -Werror -pedantic -fpic -c -o Parser.o src/Parser.c

Composer.o: src/Composer.c
	gcc -Wall -Werror -pedantic -fpic -c -o Composer.o src/Composer.c