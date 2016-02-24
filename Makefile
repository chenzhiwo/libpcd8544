LIB_NAME=libpcd8544.so
DEMO_NAME=demo
PERFIX=/usr

CC=gcc
CFLAGS=-O0 -Wall
LDFLAGS=-lwiringPi -ltftgfx

.PHONY:clean rebuild exec debug install

all:$(LIB_NAME)

clean:
	@echo "Cleaning workspace.........."
	-rm ./*.o ./$(LIB_NAME) ./$(DEMO_NAME)

rebuild:clean all

exec:all install $(DEMO_NAME)
	./$(DEMO_NAME)

debug:CFLAGS+=-g
debug:rebuild
	gdb ./$(DEMO_NAME)

install:$(LIB_NAME)
	install --mode=0644 libpcd8544.h  $(PERFIX)/include/
	install --mode=0644 libpcd8544.so $(PERFIX)/lib/

uninstall:
	-rm  $(PERFIX)/include/libpcd8544.h
	-rm  $(PERFIX)/lib/libpcd8544.so

$(LIB_NAME):libpcd8544.o
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS) -shared -fPIC

$(DEMO_NAME):demo.o 
	$(CC) $^ -o $@ -lpcd8544 -ltftgfx -lwiringPi
