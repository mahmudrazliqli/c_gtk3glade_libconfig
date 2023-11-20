all:clean
ifeq ($(OS), Windows_NT)
	gcc main.c  `pkg-config --cflags --libs gtk+-3.0`  -c -o main.o
	windres -I.  -i winicon/resource.rc  -o   winicon/resource.o
	gcc  main.o winicon/resource.o `pkg-config --cflags --libs gtk+-3.0` -mwindows  -lhid -lsetupapi  -lconfig    -Wl,--export-all-symbols -o  main
else ifeq ($(shell uname -s), Linux)
	gcc -Wall -Os -c -o main.o main.c `pkg-config --cflags --libs gtk+-3.0` 
	gcc -o main main.o  -lusb `pkg-config --cflags --libs gtk+-3.0`  -Wl,--export-dynamic  -lconfig 
	strip main
else ifeq ($(shell uname -s), Darwin)
	gcc -Wall -Os -c -o main.o main.c `pkg-config --cflags --libs gtk+-3.0` 
	gcc -o main main.o  -lusb `pkg-config --cflags --libs gtk+-3.0` -Wl,--export-dynamic  -lconfig 
	strip main
endif
	rm -rf *.o
	
clean:
	@echo + OS = $(OS) 
	@echo - shell uname= $(shell uname -s)
	rm -rf *.o winicon/*.o *.exe main
	
program:all
	./main
	

#in msys2
# pacman -S mingw-w64-x86_64-libconfig