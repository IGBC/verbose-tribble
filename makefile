CC ?= clang
CFLAGS ?= -Wall -Wpedantic -O2 -frtti
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

bin/main.x86_64: bin/A440.o bin/musical_utils.o bin/audiosink.o bin/main.o bin/streaming_interface.o bin/blocks/ossilator.o
	g++ $^ $(CFLAGS) $(LOADLIBES) $(LDLIBS) -o $@

bin/%.o: src/%.c
	mkdir -p $(dir $@)
	gcc -c $(CFLAGS) $(CPPFLAGS) $< -o $@

bin/%.o: src/%.cpp
	mkdir -p $(dir $@)
	g++ -c $(CFLAGS) $(CPPFLAGS) $< -o $@
