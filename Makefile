CC=gcc
CFLAGS=-Iinclude -std=c99 -Wall -Wextra -O2
SRC=src/serializer.c
EXAMPLES=examples/main.c
OUT=demo

all: $(OUT)

$(OUT): $(SRC) $(EXAMPLES)
	$(CC) $(CFLAGS) $(SRC) $(EXAMPLES) -o $(OUT)

clean:
	rm -f $(OUT)
