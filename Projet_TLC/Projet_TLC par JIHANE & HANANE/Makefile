CC = gcc
CFLAGS = -Wall -g -Isrc
FLEX = flex
BISON = bison

TARGET = ensa
OBJS = lex.yy.o parser.tab.o semantique.o AST.o table.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

parser.tab.c parser.tab.h: src/parser.y
	$(BISON) -d src/parser.y

lex.yy.c: src/lexer.l parser.tab.h
	$(FLEX) src/lexer.l

lex.yy.o: lex.yy.c
	$(CC) $(CFLAGS) -c lex.yy.c

parser.tab.o: parser.tab.c
	$(CC) $(CFLAGS) -c parser.tab.c

semantique.o: src/semantique.c src/semantique.h src/AST.h src/table.h
	$(CC) $(CFLAGS) -c src/semantique.c

AST.o: src/AST.c src/AST.h
	$(CC) $(CFLAGS) -c src/AST.c

table.o: src/table.c src/table.h
	$(CC) $(CFLAGS) -c src/table.c

clean:
	rm -f $(TARGET) $(OBJS) lex.yy.c parser.tab.c parser.tab.h *.exe

.PHONY: all clean
