CC = gcc
CFLAGS = -Wall  -Wextra -Werror -std=c11
SRC = s21_*.c
OBJ = s21_*.o
LIB = s21_string.a
CHECKS_FLAGS = -lcheck -lm -lsubunit
TEST_SRC = tests.c
GCOV_FLAGS = --coverage
GCOVR_PATH = gcovr
REPORT = report/index.html

all: r test gcov_report

clang:
	clang-format -n *.c *.h

s21_string.a:
	gcc -c  s21_*.c
	ar rc s21_string.a *.o
	ranlib s21_string.a
	rm -rf *.o

test: clean ${LIB}
	$(CC) $(CFLAGS) -L. -l:s21_string.a   $(GCOV_FLAGS) $(SRC) ${TEST_SRC} -o test $(LIBSFLAGS)
	./test

gcov_report: test
	mkdir report
	${GCOVR_PATH} -r . --html  --html-details  -o $(REPORT)  -e ${TEST_SRC}
	xdg-open $(REPORT)

val: test
	valgrind --tool=memcheck --leak-check=yes ./test
	

clean:
	rm -rf a.out
	rm -rf *.o
	rm -rf *.a
	rm -rf *.gcda *.gcdo *.gcov *.css *.html *.gcno
	rm -rf report
	rm -rf test

r: clean s21_string.a
