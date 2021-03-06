# ZPrompt

Informative and radiant prompt for ZSH and Bash

Requires Powerline Fonts

## Screenshot

![zprompt01](https://cloud.githubusercontent.com/assets/1478966/20607964/a588403a-b285-11e6-94c5-de8d6357455a.png)

## Installation

### Bash:

- Build ZPrompt
	```
	make install
	```

- Add the following lines to your .bashrc
	```
	function _pre_ps1() {
		PS1="$($HOME/.bash/zprompt)"
	}

	PROMPT_COMMAND="_pre_ps1; $PROMPT_COMMAND"
	```

### Zsh

- Build ZPrompt
	```
	make install TARGET_SHELL=zsh
	```

- Add the following lines to your .zshrc
	```
	function precmd() {
		export PS1="$($HOME/.zsh/zprompt)"
	}
	```
