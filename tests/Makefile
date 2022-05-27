# základ tohoto Makefilu je převzat ze cvičení (Radek Hušek)

FILENAME = tests
CXX = g++
FLAGS = -std=c++17 -O2 -Wall -pedantic -Wno-long-long -Wextra -g

DIRS = $(wildcard ../src/*/) ./
SOURCES = $(wildcard $(addsuffix *.cpp, $(DIRS)))
OBJECTS = $(patsubst ./%.cpp, build/%.o, $(patsubst ../src/%.cpp, ./%.cpp, ${SOURCES}))
DEPS = $(patsubst ./%.cpp, build/%.dep, $(patsubst ../src/%.cpp, ./%.cpp, ${SOURCES}))

.PHONY: all compile run clean

all: compile

compile: ${FILENAME}

${FILENAME}: ${OBJECTS}
	@mkdir -p $(subst ../src, build, $(DIRS))
	${CXX} ${FLAGS} $^ -o $@

run: compile
	./${FILENAME}

clean:
	rm -rf build
	rm -rf doc
	rm -f ${FILENAME}

build/main.o: ./main.cpp
	@mkdir -p build
	${CXX} ${FLAGS} -c ./main.cpp -o build/main.o

build/%.o: ../src/%.cpp
	@mkdir -p $(subst ../src, build, $(DIRS))
	${CXX} ${FLAGS} -c $< -o $@

build/main.dep: ./main.cpp
	@mkdir -p build
	${CXX} -MM -MT build/main.o ./main.cpp > build/main.dep

build/%.dep: ../src/%.cpp
	@mkdir -p $(subst ../src, build, $(DIRS))
	${CXX} -MM -MT $(patsubst ../src/%.cpp, build/%.o, $<) $< > $@


include ${DEPS}

