PNG_LIBS = -I /usr/include/libpng16 -D_REENTRANT

CFLAGS = $(PNG_LIBS) -I include

LIBS = -lpng

OPTION = -fsanitize=address

BIN_NAME = img

compile:
	gcc $(CFLAGS) -c src/*.c $(LIBS) $(OPTIONS)
	gcc $(CFLAGS) -c main.c $(LIBS) $(OPTIONS)
	gcc $(CFLAGS) $(LIBS) -o $(BIN_NAME) *.o $(OPTIONS)
	rm *.o

remove:
	rm $(BIN_NAME)
	clear

run:
	./$(BIN_NAME) 
