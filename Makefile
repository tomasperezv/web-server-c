CC = gcc
FILES = src/server.c
OUT_FOLDER = bin/
OUT_EXE = server

build: $(FILES)
	mkdir $(OUT_FOLDER)
	# Copy the configuration files
	mkdir $(OUT_FOLDER)/config
	cp src/config/*.conf $(OUT_FOLDER)/config/
	$(CC) -o $(OUT_FOLDER)$(OUT_EXE) $(FILES)

clean:
	rm -fr $(OUT_FOLDER)
	rm -f *.o core

rebuild: clean build
