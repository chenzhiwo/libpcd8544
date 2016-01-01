CC = gcc
CFLAGS += -Wall 
#CFLAGS += -DDEBUG_MESG -g -O0

.PHONY: clean exec debug rebuild

pcd8544:main.o pcd8544.o gfx.o
	$(CC) $(CFLAGS) -lwiringPi $^ -o $@

clean:
	@echo Cleaning workspace.....
	-rm ./*.o ./pcd8544

exec:pcd8544
	./pcd8544

debug:pcd8544
	gdb ./pcd8544

rebuild:clean pcd8544

gfx.o: gfx.c gfx.h color.h
main.o: main.c pcd8544.h color.h gfx.h bitmap.h
pcd8544.o: pcd8544.c pcd8544.h color.h
