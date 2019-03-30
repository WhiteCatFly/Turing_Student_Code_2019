override CXX=clang++

SRC = ${wildcard src/*.cpp}
OBJ = ${patsubst src/%.cpp, tmp/%.o, $(SRC)}
DEPEND = ${OBJ:tmp/%.o=tmp/%.d} 

CXXFLAGS = -std=gnu++17 -g -O2
LDFLAGS = -lcurl -lstdc++fs -lpthread

all:  main

include $(DEPEND) 

#tmp/%.o : src/%.cpp
#	$(CXX) $(CXXFLAGS) -c $< -o $@

tmp/%.d: src/%.cpp
	$(CXX) -MM $< | sed 's/^\(\S\)/tmp\/\1/' > $@
	echo -e '\t$$(CXX) $$(CXXFLAGS) -c $< -o ${patsubst src/%.cpp, tmp/%.o, $<}' >> $@

main: $(OBJ)
	$(CXX) $(OBJ) -o main $(LDFLAGS)

clean_depend:
	$(RM) $(DEPEND)

clean:
	$(RM) depend tmp/*.o main tmp/*.d

.PHONY: clean clean_depend
