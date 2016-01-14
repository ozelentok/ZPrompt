#ZPrompt

Informative and radiant prompt for Zsh

##Installing

###Bash:

- Build ZPrompt
```
make
make install
```

- Add the following lines to your .bashrc
```
function _pre_ps1() {
	PS1="$($HOME/.config/zprompt)"
}

PROMPT_COMMAND="_pre_ps1; $PROMPT_COMMAND"
```

###Zsh:

- Build ZPrompt
```
make TARGET_SHELL=zsh
make install
```

- Add the following lines to your .zshrc
```
function precmd() {
	export PS1="$($HOME/.config/zprompt)"
}
```
