CXXFLAGS  = -Wall  -std=c++11 -pthread

all: wordfreq

wordfreq: input.o counter.o frequency.o

clean:
	rm -f wordfreq input.o counter.o frequency.o
