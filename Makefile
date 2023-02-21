CFLAGS = -std=c99 -g -Wall -Wshadow -Wvla -pedantic -Werror
GCCALL = gcc -O3 -std=c99 -Wall -Wshadow -Wvla -pedantic
GCC = gcc $(CFLAGS)
EXEC = pa3
OBJS =  pa3.o unpack.o writeoutput.o helper.o
HOBJS = unpack.h writeoutput.h helper.h struct.h
VALGRIND = valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --verbose

$(EXEC): $(OBJS) $(HOBJS)
	$(GCC) $(OBJS) -o $(EXEC)

test: $(EXEC)
	mkdir outputs
	./$(EXEC) examples/8.po outputs/8.pr outputs/8.dim outputs/8.pck
	diff outputs/8.pr examples/8.pr
	diff outputs/8.dim examples/8.dim
	diff outputs/8.pck examples/8.pck
	./$(EXEC) examples/3.po outputs/3.pr outputs/3.dim outputs/3.pck
	./$(EXEC) examples/1K.po outputs/1K.pr outputs/1K.dim outputs/1K.pck

memory: $(EXEC)
	mkdir moutputs
	$(VALGRIND) ./$(EXEC) examples/8.po moutputs/8.pr moutputs/8.dim moutputs/8.pck
	$(VALGRIND) ./$(EXEC) examples/100.po moutputs/100.pr moutputs/100.dim moutputs/100.pck
	$(VALGRIND) ./$(EXEC) examples/1K.po moutputs/1K.pr moutputs/1K.dim moutputs/1K.pck

clean: 
	/bin/rm -f $(EXEC)
	/bin/rm -f *.o
	/bin/rm -rf outputs moutputs