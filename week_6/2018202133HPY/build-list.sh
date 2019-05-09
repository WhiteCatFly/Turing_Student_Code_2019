#! /bin/bash

SRCS=`find src/ -regex ".*\.cpp"`
OBJS=
DEPENDS=

for src in $SRCS 
do
	obj=tmp/`basename $src .cpp`.o
	depend=tmp/`basename $src .cpp`.d
	
	OBJS="$OBJS $obj"
	DEPENDS="$DEPENDS $depend"

	#echo $obj
	#echo $depend
	#'\t$$(CXX) $$(CXXFLAGS) -c $< -o ${patsubst src/%.cpp, tmp/%.o, $<}'

	echo -e "$depend: $src" 
	echo -e "\t\$(CXX) -MM $src | sed 's,^,tmp/,' > $depend"
	echo -e "\techo  '\t\$\$(CXX) \$\$(CXXFLAGS) -c $src -o $obj' >> $depend"
	echo
done

echo "OBJ=$OBJS"
echo "DEPEND=$DEPENDS"
