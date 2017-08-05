CC ?= clang
CFLAGS ?= -Wall -Wpedantic -O2
LDFLAGS ?= -lm

all: clean bin/main.x86_64

.PHONY: clean
clean: 
	echo cleaning
	rm -rfv ./bin/
	rm -f main.x86_64

.PHONY: noise
noise: bin/main.x86_64
	./bin/main.x86_64 | aplay --rate=44100 --format=S32_LE

bin/main.x86_64: bin/A440.o bin/musical_utils.o bin/main.o
	$(LINK.o) $^ $(LOADLIBES) $(LDLIBS) -o $@

bin/%.o: src/%.c
	mkdir -p bin
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@
