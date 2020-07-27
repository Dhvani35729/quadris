CXX = g++
CXXFLAGS = -Wall -MMD -std=c++17
OBJECTS = subject.o model.o controller.o view.o main.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = quadris

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}