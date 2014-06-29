CC = gcc
FILES = src/server.c src/configuration.c src/hash_map.c
OUT_FOLDER = bin/
OUT_EXE = server

default: rebuild run

build: $(FILES)
	mkdir $(OUT_FOLDER)
	# Copy the configuration files
	mkdir $(OUT_FOLDER)/config
	cp src/config/*.conf $(OUT_FOLDER)config/
	$(CC) -o $(OUT_FOLDER)$(OUT_EXE) $(FILES)

clean:
	rm -fr $(OUT_FOLDER)
	rm -f *.o core

run:
	./$(OUT_FOLDER)server

rebuild: clean build
