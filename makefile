main: main.o lib.o
	gcc main.o lib.o -o main

main.o: main.c header.h
	$(CC) $(CFLAGS) -c main.c

lib.o: lib.c header.h
	gcc  -c lib.c

clean:
	rm -f *.o $(TARGET)
