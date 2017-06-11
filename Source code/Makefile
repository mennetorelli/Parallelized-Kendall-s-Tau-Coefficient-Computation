CXXFLAGS += -Wall -std=c++11 -fopenmp -O3 -march=native
EXE = KendallTau
OBJS = Starter.o Pair.o Naive.o GSE.o GSE_simd.o

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
GSE_simd.o: GSE_simd.h

clean:
	$(RM) *.o
	$(RM) $(EXE)

distclean: clean
	$(RM) *~