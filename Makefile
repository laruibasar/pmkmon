CC = cc
PROG = pmkmon
CFLAGS = -c -Wall -Werror -O3
DEPS = utils.h
OBJ = utils.o

.PHONY: all
all: app test

.PHONY: app
app: $(OBJ) $(PROG)

.PHONY: clean
clean: clean-app clean-test

clean-app:
	@echo "Cleaning app *.o"
	rm -f utils.o pmkmon.o

clean-test:
	@echo "Cleaning test *.o"

utils.o: utils.c $(DEPS)
	@echo "Compiling " $<
	$(CC) $(CFLAGS) -o $@ $<

pmkmon: pmkmon.o
	@echo "Linking and create executable " $<
	$(CC) -o $@ $(OBJ) $< 

pmkmon.o: pmkmon.c $(DEPS)
	@echo "Compiling " $<
	$(CC) $(CFLAGS) -o $@ $<

