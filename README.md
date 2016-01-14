#ZPrompt

Informative and radiant prompt for Zsh

##Building

###Bash:

- Build zprompt
```
make
make install
```

- Add to your .bashrc
```
function _pre_ps1() {
	PS1="$($HOME/.zprompt/zprompt)"
}

PROMPT_COMMAND="_pre_ps1; $PROMPT_COMMAND"
```

###Zsh:

- Build zprompt
```
make TARGET_SHELL=zsh
make install
```

- Add to your .zshrc
```
function precmd() {
	export PS1="$($HOME/.config/zprompt)"
}
```
