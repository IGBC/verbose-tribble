CC ?= clang
CFLAGS ?= -Wall -Wpedantic
LDFLAGS ?= -lm

all: clean main.x86_64

.PHONY: clean
clean: 
	rm -rfv ./bin/
	rm -f main.x86_64

.PHONY: noise
noise: main.x86_64
	./main.x86_64 | aplay --rate=44100 --format=S32_LE

main.x86_64: bin/A440.o bin/musical_utils.o bin/main.o

bin/%.o: src/%.c
	mkdir -p bin
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@
