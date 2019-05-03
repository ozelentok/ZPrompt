CXXFLAGS = -O2 -Werror -Wall -pie -fPIE -fno-stack-protector -fomit-frame-pointer -ffunction-sections -fdata-sections
LDFLAGS = -Wl,--gc-sections -s
SRC_CXX_FILES = $(wildcard *.cpp)

ifeq ($(TARGET_SHELL), zsh)
	INSTALL_DIR_PATH = $(HOME)/.zsh
	CPPFLAGS += -D ZSH
else
	INSTALL_DIR_PATH = $(HOME)/.bash
endif

all: zprompt
zprompt: $(SRC_CXX_FILES)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) $^ -o $@

install: zprompt
	mkdir -p $(INSTALL_DIR_PATH)
	cp ./$^ $(INSTALL_DIR_PATH)/$^

clean:
	rm -f zprompt
