CC ?= clang
CFLAGS ?= -Wall -Wpedantic -O2 -frtti
LDFLAGS ?= -lfftw3 -lm 

all: clean bin/gen.x86_64

.PHONY: clean
clean: 
	echo cleaning
	rm -rfv ./bin/
	rm -f main.x86_64

.PHONY: noise silent
noise: bin/gen.x86_64
	./bin/main.x86_64 | aplay --rate=44100 --format=S32_LE

silent: bin/gen.x86_64
	./bin/main.x86_64 > /dev/null

bin/%.x86_64: bin/A440.o bin/musical_utils.o bin/%.o
	g++ $^ $(CFLAGS) $(LOADLIBES) $(LDLIBS) -o $@

bin/%.o: src/%.c
	mkdir -p $(dir $@)
	gcc -c $(CFLAGS) $(CPPFLAGS) $< -o $@
