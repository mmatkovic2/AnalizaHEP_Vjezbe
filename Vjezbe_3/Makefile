CC=g++
CFLAGS=-I.
DEPS = ElementaryParticle.h

analyzer: analyzer.o ElementaryParticle.o
	$(CC) -o analyzer analyzer.o ElementaryParticle.o

%.o: %.cpp $ (DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
