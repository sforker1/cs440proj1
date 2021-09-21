FLAGS = -Wall -Wextra -pedantic -ldl

LASTNAME = Forker
BU_USERID = sforker1
GITHUB_USERID = sforker1
EXECUTABLE = program1

test: clean test.o
	g++ $(FLAGS) test.o -o $(EXECUTABLE)

test.o: test.cpp
	g++ $(FLAGS) -c test.cpp

main: clean main.o
	g++ $(FLAGS) main.o -o main

main.o: main.cpp
	g++ $(FLAGS) -c main.cpp

tar: clean
	cd .. && tar -cvzf CS440_$(LASTNAME)_$(BU_USERID).tar.gz

scrub: clean
	rm ~* *.swp *\#

run: $(EXECUTABLE)
	./$(EXECUTABLE)

memcheck: $(EXECUTABLE)
	valgrind ./$(EXECUTABLE)

clean:
	rm -f *.o $(EXECUTABLE) main