# základ tohoto Makefilu je převzat ze cvičení (Radek Hušek)

LOGIN = fiedlpe5
CXX = g++
FLAGS = -std=c++17 -O2 -Wall -pedantic -Wno-long-long -Wextra -g

DIRS = $(wildcard src/*/) src/
SOURCES = $(wildcard $(addsuffix *.cpp, $(DIRS)))
OBJECTS = $(patsubst src/%.cpp, build/%.o, ${SOURCES})
DEPS = $(patsubst src/%.cpp, build/%.dep, ${SOURCES})

.PHONY: all compile run doc clean

all: compile

compile: ${LOGIN}

${LOGIN}: ${OBJECTS}
	@mkdir -p $(subst src, build, $(DIRS))
	${CXX} ${FLAGS} $^ -o $@

run: compile
	./${LOGIN}

doc: ${SOURCES}
	doxygen Doxyfile

clean:
	rm -rf build
	rm -rf doc
	rm -f ${LOGIN}

build/%.o: src/%.cpp 
	@mkdir -p $(subst src, build, $(DIRS))
	${CXX} ${FLAGS} -c $< -o $@

build/%.dep: src/%.cpp src/*
	@mkdir -p $(subst src, build, $(DIRS))
	${CXX} -MM -MT $(patsubst src/%.cpp, build/%.o, $<) $< > $@

include ${DEPS}

