CC = g++
FLAGS = -Wall -Wextra -Wconversion -Wsign-conversion -Wformat-security -pie -fPIE -Wl,-z,relro,-z,now -Werror -O2 -std=c++11
CPP_FILES = $(wildcard *.cpp)

all: zprompt
zprompt: $(CPP_FILES)
	$(CC) $(FLAGS) $^ -o $@
	strip $@
clean:
	rm -f zprompt
