CC = g++
FLAGS = -Wall -Wextra -Wconversion -Wsign-conversion -Wformat-security -pie -fPIE -Wl,-z,relro,-z,now -Werror -O2 -std=c++11
CPP_FILES = $(wildcard *.cpp)

all: zprompt
zprompt: $(CPP_FILES)
ifeq ($(TARGET_SHELL), zsh)
	$(CC) $(FLAGS) -D ZSH $^ -o $@
else
	$(CC) $(FLAGS) $^ -o $@
endif
	strip $@

install: zprompt
ifeq ($(TARGET_SHELL), zsh)
	mkdir -p $(HOME)/.zsh
	cp ./zprompt $(HOME)/.zsh/zprompt
else
	mkdir -p $(HOME)/.bash
	cp ./zprompt $(HOME)/.bash/zprompt
endif


clean:
	rm -f zprompt
