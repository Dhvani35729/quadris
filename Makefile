CXX = g++
CXXFLAGS = -Wall -MMD -std=c++17
GTKFLAGS = `pkg-config gtkmm-3.0 --cflags --libs glibmm-2.4`
SOURCES = $(wildcard *.cpp) # list of all .cpp files in the current directory
OBJECTS = ${SOURCES:.cpp=.o} # .o files depend upon .cc files with same names
DEPENDS = ${OBJECTS:.o=.d}
EXEC = quadris

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}  $(GTKFLAGS)

%.o: %.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(GTKFLAGS)

-include ${DEPENDS}

clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}
