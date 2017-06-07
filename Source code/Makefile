CXXFLAGS += -Wall -std=c++11 -O2 -fopenmp
EXE = KendallTau
OBJS = Starter.o Pair.o Naive.o GSE.o

.DEFAULT_GOAL = all

all: build

.PHONY: all build clean distclean

build: $(EXE)

$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) $^ $(OUTPUT_OPTION)

Starter.o: Starter.h
Pair.o: Pair.h
Naive.o: Naive.h
GSE.o: GSE.h

clean:
	$(RM) *.o
	$(RM) $(EXE)

distclean: clean
	$(RM) *~