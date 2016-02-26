FILES :=                              \
    .travis.yml                       \
    voting-tests/dao384-RunVoting.in   \
    voting-tests/dao384-RunVoting.out  \
    voting-tests/dao384-TestVoting.c++ \
    voting-tests/dao384-TestVoting.out \
    Voting.c++                       \
    Voting.h                         \
    Voting.log                       \
    html                              \
    RunVoting.c++                    \
    RunVoting.in                     \
    RunVoting.out                    \
    TestVoting.c++                   \
    TestVoting.out

CXX        := g++-4.8
CXXFLAGS   := -pedantic -std=c++11 -Wall
LDFLAGS    := -lgtest -lgtest_main -pthread
GCOV       := gcov-4.8
GCOVFLAGS  := -fprofile-arcs -ftest-coverage
VALGRIND   := valgrind

check:
	@not_found=0;                                 \
    for i in $(FILES);                            \
    do                                            \
        if [ -e $$i ];                            \
        then                                      \
            echo "$$i found";                     \
        else                                      \
            echo "$$i NOT FOUND";                 \
            not_found=`expr "$$not_found" + "1"`; \
        fi                                        \
    done;                                         \
    if [ $$not_found -ne 0 ];                     \
    then                                          \
        echo "$$not_found failures";              \
        exit 1;                                   \
    fi;                                           \
    echo "success";

clean:
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.gcov
	rm -f RunVoting
	rm -f RunVoting.tmp
	rm -f TestVoting
	rm -f TestVoting.tmp
	rm -f UVaVoting

config:
	git config -l

scrub:
	make clean
	rm -f  Voting.log
	rm -rf voting-tests
	rm -rf html
	rm -rf latex

status:
	make clean
	@echo
	git branch
	git remote -v
	git status

test: RunVoting.tmp TestVoting.tmp

online-test: UVaVoting.tmp

voting-tests:
	git clone https://github.com/cs371p-spring-2016/voting-tests.git

html: Doxyfile Voting.h Voting.c++ RunVoting.c++ TestVoting.c++
	doxygen Doxyfile

Voting.log:
	git log > Voting.log

Doxyfile:
	doxygen -g

UVaVoting: UVaVoting.c++
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) UVaVoting.c++ -o UVaVoting

RunVoting: Voting.h Voting.c++ RunVoting.c++
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) Voting.c++ RunVoting.c++ -o RunVoting

UVaVoting.tmp: UVaVoting
	./UVaVoting < RunVoting.in > UVaVoting.tmp
	diff UVaVoting.tmp RunVoting.out 

RunVoting.tmp: RunVoting
	./RunVoting < RunVoting.in > RunVoting.tmp
	diff RunVoting.tmp RunVoting.out

TestVoting: Voting.h Voting.c++ TestVoting.c++
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) Voting.c++ TestVoting.c++ -o TestVoting $(LDFLAGS)

TestVoting.tmp: TestVoting
	$(VALGRIND) ./TestVoting                                       >  TestVoting.tmp 2>&1
	$(GCOV) -b Voting.c++     | grep -A 5 "File 'Voting.c++'"     >> TestVoting.tmp
	$(GCOV) -b TestVoting.c++ | grep -A 5 "File 'TestVoting.c++'" >> TestVoting.tmp
	cat TestVoting.tmp