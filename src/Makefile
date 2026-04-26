CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11

GCOV_FLAGS = -fprofile-arcs -ftest-coverage

# Цвета
GREEN  = \033[0;32m
YELLOW = \033[1;33m
BLUE   = \033[0;34m
RESET  = \033[0m


TARGET = s21_decimal.a
TEST = test
REPORT_NAME = report


# вычисляем тип ОС и проверяем установлен ли pkg-config
OS := $(shell uname)
CONFIG := $(shell which pkg-config 2>/dev/null)

# если pkg-config установлен, используем его для автоматической подстановки флагов
ifneq ($(CONFIG),)
    CHECK_FLAGS := $(shell pkg-config --cflags check 2>/dev/null)
    CHECK_LIBS := $(shell pkg-config --libs check 2>/dev/null)
else
# если не установлен, проставляем флаги вручную
    CHECK_FLAGS = -pthread
    CHECK_LIBS = -lcheck -lm -lrt -lpthread

# если у нас Linux, добавляем специфический флаг
    ifeq ($(OS), Linux)
        CHECK_LIBS += -lsubunit
    endif
endif


# формируем список си-файлов
LIB_SRCS := $(filter-out tests/%, $(wildcard */*.c))
TEST_SRCS := $(wildcard tests/*.c)


# формируем список объектных файлов с разбивкой по директориям на основе си-файлов 
LIB_OBJS = $(patsubst %.c, _LIB_OBJS_DIR/%.o, $(notdir $(LIB_SRCS)))
TEST_OBJS = $(patsubst tests/%.c, tests/TEST_OBJS_DIR/%.o, $(TEST_SRCS))


all: $(TARGET)


# цель для локальной компиляции и отладки функций, удалим когда проект будет заверешен
run: run.c $(TARGET)
	$(CC) $(CFLAGS) run.c $(TARGET) -o LIB_OBJS_DIR/run.o
	./LIB_OBJS_DIR/run.o


# создаем директории для объектных файлов, с разбивкой по типам
_LIB_OBJS_DIR:
	mkdir -p $@

tests/TEST_OBJS_DIR:
	mkdir -p $@

# сборка основной библиотеки
$(TARGET): $(LIB_OBJS)
	echo "$(GREEN)Building library: $@$(RESET)"
	ar rcs $@ $^

# правила компиляции объектных файлов
_LIB_OBJS_DIR/%.o: */%.c | _LIB_OBJS_DIR
	echo "$(BLUE)Compiling:$<$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

tests/TEST_OBJS_DIR/%.o: tests/%.c | tests/TEST_OBJS_DIR
	echo "$(BLUE)Compiling:$<$(RESET)"
	$(CC) $(CFLAGS) $(CHECK_FLAGS) -c $< -o $@

# линковка и запуск тестов
test: $(TARGET) $(TEST_OBJS)
	echo "$(YELLOW)Building tests...$(RESET)"
	$(CC) $(CFLAGS) $(TEST_OBJS) $(TARGET) $(CHECK_LIBS) -o $(TEST)
	echo "$(GREEN)Running tests...$(RESET)"
	./$(TEST)

# генерация отчета о покрытии тестами
gcov_report:
	echo "$(BLUE)Building with coverage...$(RESET)"
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(CHECK_FLAGS) $(LIB_SRCS) $(TEST_SRCS) $(CHECK_LIBS) -o $(TEST)
	echo "$(YELLOW)Running tests...$(RESET)"
	-./$(TEST) || true
	echo "$(BLUE)Generating report...$(RESET)"
	lcov -t "$(TEST)" -o $(TEST).info --no-external -c -d .

	mkdir -p $(REPORT_NAME)
	genhtml -o $(REPORT_NAME) $(TEST).info

clean:
	rm -rf _LIB_OBJS_DIR tests/TEST_OBJS_DIR $(TEST) $(TARGET) *.o *.gcda *.gcno *.info $(REPORT_NAME) .clang-format

format:
	cp ../materials/linters/.clang-format .
	clang-format -i */*.c */*.h
	clang-format -i tests/*.c tests/*.h
	clang-format -n */*.c */*.h
	clang-format -n tests/*.c tests/*.h

docker_build:
	docker build -t test_env .

docker_run:
	docker run -it --rm --name test_container -v $(pwd)/..:/project test_env /bin/bash

docker_stop:
	docker stop test_container

docker_kill:
	docker kill test_container


.PHONY: all run gcov_report clean format docker_build docker_run docker_stop docker_kill
.SILENT: