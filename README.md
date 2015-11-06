rshell

This is bash command shell. It was created with c++, using fork,wait, and execvp.

Intro

this rshell currently has some characteristics of a full real terminal. It can do many commands due to execvp, but relies on it, therefore leaivng out commands that aren't run by execvp.

Install Instructions

$ clone  https://github.com/pzach001/rshell.git
$ cd rshell
$ git checkout hw1
$ make
$ bin/rshell


limitation and bugs
currently cannot use cd
size of command has a limit
