override CXX=clang++

all:  main

include sources.list

# OBJ = ${patsubst src/%.cpp, tmp/%.o, $(SRC)}
# DEPEND = ${OBJ:tmp/%.o=tmp/%.d} 

CXXFLAGS = -std=gnu++17 -g -O2
LDFLAGS = -lcurl -lstdc++fs -lpthread

include $(DEPEND) 

#tmp/%.o : src/%.cpp
#	$(CXX) $(CXXFLAGS) -c $< -o $@

sources.list:
	@bash build-list.sh > sources.list

# tmp/%.d: src/%.cpp
# 	@$(CXX) -MM $< | sed 's/^\(\S\)/tmp\/\1/' > $@
	# @echo -e '\t$$(CXX) $$(CXXFLAGS) -c $< -o ${patsubst src/%.cpp, tmp/%.o, $<}' >> $@

main: $(OBJ)
	$(CXX) $(OBJ) -o main $(LDFLAGS)

clean_depend:
	$(RM) $(DEPEND)

clean:
	bash cleanup.sh

.PHONY: clean clean_depend
