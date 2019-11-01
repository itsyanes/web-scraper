CC=gcc
CFLAGS=-Wall -O2 -I"src" -pedantic -lcurl
BIN=wscrap
OBJ_PATH=obj
BIN_PATH=bin

all:
	$(CC) -o $(BIN_PATH)/$(BIN) main.c $(CFLAGS)

clean:
	rm -f $(OBJ_PATH)/*.o

mrproper: clean
	rm -f $(BIN_PATH)/*