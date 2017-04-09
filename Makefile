### Name: Nathan Zimmerman
### Date: 01/12/2017
### Makefile for lab1
### sources used: Harlan James <waldroha@oregonstate.edu> i.e.
### Harlan's makefile example in canvas under Make help module
### http://mrbook.org/blog/tutorials/make/

CXX = g++
CXXFLAGS = -std=c++11 -Wall -pedantic-errors -g -c

PROJ = Final
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
HEADERS = KeyZone.hpp Zombie.hpp StartZone.hpp Character.hpp FinalZone.hpp 
HEADERS += ChemicalZone.hpp SpeakerZone.hpp Game.hpp Building.hpp Student.hpp
HEADERS += WriteMessage.hpp Menu.hpp DarkZone.hpp

all: $(SRCS) $(PROJ)

$(PROJ): $(OBJS) $(HEADERS)
	$(CXX) $(OBJS) -o $@ -lncurses

.cpp.o:
	$(CXX) $(CXXFLAGS) -o $@ $<

zip:
	zip $(PROJ).zip *.cpp *.hpp *.pdf *.txt Makefile

.PHONY: clean	

clean:
	rm *.o $(PROJ)
