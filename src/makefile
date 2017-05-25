CC=g++ -std=c++11 -Wall -g
CFLAGS=-I.
DEPS=Bitmap.h Complex.h Controller.h Expr.h Function.h Lexer.h Parser.h Power.h Product.h Sequence.h Sum.h Value.h Variable.h
OBJ=Bitmap.o Complex.o Controller.o Function.o Lexer.o main.o Parser.o Power.o Product.o Sequence.o Sum.o Value.o Variable.o

doco: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -f *.o *~ doco
