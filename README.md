NOTE:rshell written for the CS100( Software Construction) class  at UCR by Phillip Zachariah during the Fall quarter of 2015.

What is Rshell?


 Rshell is a simple shell. It takes in basic bash commands.
 the commands that i provides are :
     1. "ls"
     2. "echo"
     3. "mkdir"
 Rshell also provides basic command connector functionality:
     ex) (echo "hi" &&  ls) || ls

Install Instructions: 

    $ clone  https://github.com/pzach001/rshell.git
    $ cd rshell
    $ git checkout hw1
    $ make
    $ bin/rshell


Limitation and Bugs: 
    -cannot comment if there are multiple spaces before the command, changes behavior of what being inputed into execvp.
    -ex": "     #lakjkjaklja"
    -currently cannot use cd. 
    -size of command has a limit.
