FLAGS = -Wall -Wextra -pedantic

LASTNAME = Forker
BU_USERID = sforker1
GITHUB_USERID = sforker1
EXECUTABLE = test

test: test.o
	g++ $(FLAGS) test.o -o $(EXECUTABLE)

test.o: test.cpp
	g++ $(FLAGS) -c test.cpp
tar: clean
	cd .. && tar -cvzf CS440_$(LASTNAME)_$(BU_USERID).tar.gz

scrub: clean
	rm ~* *.swp *\#

run: $(EXECUTABLE)
	./$(EXECUTABLE)

memcheck: $(EXECUTABLE)
	valgrind ./$(EXECUTABLE)

clean:
	rm -f *.o $(EXECUTABLE)