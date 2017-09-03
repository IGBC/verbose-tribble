CC ?= clang
CFLAGS ?= -Wall -Wpedantic -O2
LDFLAGS ?= -lfftw3 -lm 

all: clean bin/main.x86_64

.PHONY: clean
clean: 
	echo cleaning
	rm -rfv ./bin/
	rm -f main.x86_64

.PHONY: noise silent
noise: bin/main.x86_64
	./bin/main.x86_64 | aplay --rate=44100 --format=S32_LE

silent: bin/main.x86_64
	./bin/main.x86_64 > /dev/null

bin/main.x86_64: bin/A440.o bin/musical_utils.o bin/gen.o
	$(LINK.o) $^ $(LOADLIBES) $(LDLIBS) -o $@

bin/%.o: src/%.c
	mkdir -p bin
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@
