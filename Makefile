CC = gcc
FILES = src/server.c src/configuration.c src/hash_map.c
OUT_FOLDER = bin/
OUT_EXE = server

default: rebuild run

build:
	mkdir $(OUT_FOLDER)
	# Copy the configuration files
	mkdir $(OUT_FOLDER)/config
	mkdir $(OUT_FOLDER)/www
	cp src/config/*.conf $(OUT_FOLDER)config/
	cp www/*.html $(OUT_FOLDER)www/
	$(CC) -o $(OUT_FOLDER)$(OUT_EXE) $(FILES)

debug: clean
	mkdir $(OUT_FOLDER)
	# Copy the configuration files
	mkdir $(OUT_FOLDER)/config
	mkdir $(OUT_FOLDER)/www
	cp src/config/*.conf $(OUT_FOLDER)config/
	cp www/*.html $(OUT_FOLDER)www/
	$(CC) -o $(OUT_FOLDER)$(OUT_EXE) -g $(FILES)
	gdb ./$(OUT_FOLDER)server

clean:
	rm -fr $(OUT_FOLDER)
	rm -f *.o core

run:
	./$(OUT_FOLDER)server

rebuild: clean build
