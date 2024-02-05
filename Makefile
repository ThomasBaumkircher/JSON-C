# The main all target
all: init Parser.o Composer.o Dict.o
	gcc -shared -o libcjson.so build/Parser.o build/Composer.o build/Dict.o

	sudo cp libcjson.so /usr/lib
	sudo cp include/*.h /usr/include
	sudo ldconfig

Dict.o: src/Dict.c
	gcc -Iinclude -Wall -Werror -pedantic -fpic -c -o build/Dict.o src/Dict.c

Parser.o: src/Parser.c
	gcc -Iinclude -Wall -Werror -pedantic -fpic -c -o build/Parser.o src/Parser.c

Composer.o: src/Composer.c
	gcc -Iinclude -Wall -Werror -pedantic -fpic -c -o build/Composer.o src/Composer.c

init:
	mkdir -p build

clean:
	rm -rf build/*
