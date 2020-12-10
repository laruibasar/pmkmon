CC = cc
PROG = pmkmon
CFLAGS = -c -Wall -Werror -g
DEPS = utils.h
OBJ = utils.o

.PHONY: all
all: app test

.PHONY: app
app: $(OBJ) $(PROG)

.PHONY: test
test:  test

.PHONY: clean
clean: clean-app clean-test

clean-app:
	@echo "Cleaning app *.o"
	rm -f utils.o pmkmon.o
	@echo "Removing pmkmon"
	rm -f pmkmon

clean-test:
	@echo "Cleaning test *.o"
	rm -f utils.o test.o
	@echo "Removing test"
	rm -f test

utils.o: utils.c $(DEPS)
	@echo "Compiling " $@
	$(CC) $(CFLAGS) -o $@ $<

pmkmon: pmkmon.o
	@echo "Linking and create executable " $(PROG)
	$(CC) -g -o $@ $(OBJ) pmkmon.o

pmkmon.o: pmkmon.c $(DEPS)
	@echo "Compiling " $<
	$(CC) $(CFLAGS) -o $@ $<

test: test.o $(OBJ)
	@echo "Linking and create test executable " 
	$(CC) -o $@ $(OBJ) test.o

test.o: test.c $(DEPS)
	@echo "Compiling " $<
	$(CC) $(CFLAGS) -o $@ $<
