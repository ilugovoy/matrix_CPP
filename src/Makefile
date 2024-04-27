# #------------> опции компилятора
CC = g++
CCFLAGS = -Wall -Werror -Wextra -g -std=c++17 -lm
GCOV = -lgcov --coverage -fprofile-arcs -ftest-coverage

# коллекции флагов в зависимости от системы
ifeq ($(shell uname), Linux)
	TESTFLAGS=-lgtest -lgtest_main -lrt -lstdc++ -pthread
	LEAK_TEST_TOOL = valgrind
else
	TESTFLAGS=-lgtest -lgtest_main -lpthread -lstdc++
	LEAK_TEST_TOOL = leak
endif

# указывает флаги для сборки на маке с камнем M1
ifeq ($(shell uname -m), arm64)
CCFLAGS += -arch arm64
endif

SRCS = matrix_constructors.cpp matrix_methods.cpp matrix_operators.cpp tests.cpp
OBJS = $(SRCS:.cpp=.o)

# #---> основные цели
all: check style s21_matrix_oop.a test gcov_report open_report dvi cpp leak_test 

s21_matrix_oop.a:
	$(CC) $(CCFLAGS) -c $(SRCS)
	@ar -src lib_s21_matrix_oop.a $(OBJS)

test: clean_gcov $(OBJS)
	$(CC) $(CCFLAGS) $(SRCS) -o test $(TESTFLAGS) $(GCOV)
	@./test

gcov_report: test
	@lcov -t "gcov_report" -o report.info --no-external -c -d .
	@genhtml -o report report.info

open_report:
	@open report/index.html

dvi:
	doxygen dvi_sources/Doxyfile > /dev/null 2>&1
	@open dvi_sources/dvi_report/index.html > /dev/null 2>&1


# #---> дополнительные проверки
leak_test:
	@make $(LEAK_TEST_TOOL)

valgrind:
	@valgrind  --leak-check=full --track-origins=yes ./test

leak:
	@CK_FORK=no leaks --atExit -- ./test 

cpp:
	@cppcheck --enable=all --suppress=missingIncludeSystem --check-config --language=c++ *.cpp *.h

style:
	@cd scripts && bash ./style_test.sh || (echo "Style tests failed")

check:    
	@cd scripts && bash ./install_brew.sh || (echo "install_brew.sh failed")
	@cd scripts && bash ./check_dependencies.sh || (echo "check_dependencies.sh failed")


# #---> очистка
clean: 
	rm -rf *.o *.a test report *.info *.gcda *.gcno *.gcov *.gch *.out *.txt test.dSYM dvi_sources/dvi_report

clean_gcov:
	rm -f *.gcda *.gcno


# #--->  исключения для аналогичных имён файлов 
.PHONY: make clean cppcheck style memcheck test gcov_report open_report cpp valgrind dvi install uninstall build rebuild leak



# Заметки по флагам

# -lgcov --coverage -fprofile-arcs -ftest-coverage:
# Эти флаги необходимы для генерации отчетов о покрытии кода и выполнения тестов для оценки покрытия кода. 
# Они обеспечивают информацию о том, какие части кода были протестированы, а какие нет.

# -lgtest -lgtest_main -lrt -lstdc++ -pthread:
# Данные флаги используются для подключения библиотеки Google Test, стандартных библиотек и обеспечения поддержки многопоточности. 
# Google Test позволяет создавать и запускать тесты для проверки корректности функционирования кода.

# -lpthread -lstdc++:
# Эти флаги необходимы для подключения библиотек POSIX Threads и стандартной библиотеки C++. 
# POSIX Threads обеспечивают многопоточность для приложения, а -lstdc++ содержит функции и классы для работы с C++.

# --no-external -c -d:
# В контексте lcov, эти опции позволяют подсчитывать покрытие кода только внутренних элементов без учета внешних зависимостей. 
# Таким образом, отчет о покрытии будет фокусироваться исключительно на самом коде проекта.

# --leak-check=full --track-origins=yes:
# Флаги Valgrind позволяют провести полную проверку утечек памяти и отследить происхождение этих утечек. 
# Это важно для обнаружения и устранения потенциальных проблем с управлением памятью.

# no leaks --atExit:
# Эти опции используются при выполнении тестирования на утечки памяти для обнаружения любых утечек, 
# которые могут возникнуть при завершении выполнения программы.

# --enable=all --suppress=missingIncludeSystem --check-config --language=c++:
# Эти опции для cppcheck позволяют провести полный статический анализ кода, включая все доступные проверки, 
# подавление определенных предупреждений, проверку конфигурации и указание используемого языка (C++).
