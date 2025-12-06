CC= gcc
CFLAGS= -Wall -std=c99 -Wextra -Werror $(shell pkg-config --cflags gtk4)
LDFLAGS= $(shell pkg-config --libs gtk4)
SRC = main.c params.c extract_parms.c addarticles.c addarticlestraitement.c page2.c

OBJ = $(SRC:.c=.o)

BIN= app

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(BIN)  