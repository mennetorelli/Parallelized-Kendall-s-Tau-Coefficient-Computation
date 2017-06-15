CXXFLAGS += -Wall -std=c++11 -fopenmp -O2 -march=native  -fdump-tree-vect-all
EXE = KendallTau
OBJS = Starter.o Pair.o Naive.o GSE.o Naive_simd.o

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
Naive_simd.o: Naive_simd.h

clean:
	$(RM) *.o
	$(RM) $(EXE)

distclean: clean
	$(RM) *~