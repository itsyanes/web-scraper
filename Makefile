CC=gcc
CFLAGS=-Wall -O3 -I"src" -pedantic
LDFLAGS=-lcurl -lm
BIN=wscrap
OBJ_PATH=obj
BIN_PATH=bin
SRC_PATH=src
SRC=struct.c utils.c
OBJ=$(SRC:.c=.o)

all: main $(OBJ)
	$(CC) -o $(BIN_PATH)/$(BIN) $(OBJ_PATH)/main.o $(patsubst %,$(OBJ_PATH)/%,$(OBJ)) $(LDFLAGS)

main:
	$(CC) $(CFLAGS) -c main.c -o $(OBJ_PATH)/main.o

%.o:
	$(CC) $(CFLAGS) -c $(SRC_PATH)/$(basename $@)/$(basename $@).c -o $(OBJ_PATH)/$@

clean:
	rm -f $(OBJ_PATH)/*.o

mrproper: clean
	rm -f $(BIN_PATH)/*