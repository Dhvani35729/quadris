CXX = g++
CXXFLAGS = -Wall -MMD -std=c++17
OBJECTS = subject.o model.o controller.o interpreter.o view.o score.o level.o cell.o board.o block.o main.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = quadris

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}
