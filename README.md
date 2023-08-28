# minishell_42
Reproducing the behavior of the Bourne Again Shell (BASH) in C.

## Aim of the Project
The goal of this project is deceptively simple - code and recreate a shell environment just like the ones we use every day as coders. I'm going to first break down what I learned in the project and give a quick overview of the code, then walk you through downloading and compiling the shell. The project can be broken down into four parts: 

- Parsing
- Pipes / Child Processes
- Builtin functions
- Signals / Exit Status

## Parsing

The most difficult part of this project was receiving user input and parsing it in a coherent way for the subsequent functions to work with. Basically, I needed to take the user's input and split it into 'words' based on a few special characters, like ```>```, ```<``` or ```|```.

For example, the following command: ```"cat <infile.txt | grep "str" >outfile.txt```

Would come out as an array looking like this:

```c
cat
<
infile.txt
|
grep
str
>
outfile.txt
```

This enabled the next functions to easily identify special characters and place the commands, files, pipes, and redirections correctly. 

## Pipes / Child Processes

Once the input is correctly parsed, it's time to sort it into categories. For example, the redirection characters ```<``` and ```>```give a command its input and output, respectively. In the command above, the redirection characters tell the shell that the input is ```infile.txt``` and the output should go to ```outfile.txt```. 

The pipe, ```|```, tells the shell that, instead of printing to the terminal, it should write into a pipe for another process to then work with. 

Our new shell command would then become a shorter array, excluding the input and output files. It now looks like this: 

```c
cat
|
grep
str
```

Now, the shell will open a new process for each command. First, it will find and execute the binary for ```cat``` and then it will find and execute the binary for ```grep``` with the input ```str```. These binaries are located using the $PATH variable in the computer's environment, which is typically automatically set to point to the locations of system binaries. 

Once all the processes are completed, the shell returns control to the user and repeats the whole process over again. We've got a working shell!

## Builtin functions

Although the builtin functions were handled by my partner, we tested them together and I contributed to a few bug fixes here and there. These functions are meant to replicate the builtins in bash, and I will list a few of the most interesting ones: 

- env - This prints a list of all variables in the environment. Our shell received an environemnt from the computer at the program's start and my partner filled up our environemnt array with all the variables. 

- export - This allows the user to set environment variables. The syntax for this is "export FOO=bar", which would create an environment variable "FOO" with value "bar". These can then be accessed through the parser with the "$" character, for example by running a command like: "echo my variable is $FOO", which would output "my variable is bar". 

- unset - Allows the user to unset environment variables. One interesting idea is to unset the PATH variable, which makes it impossible for the shell to access system binaries. In this case, a command like "ls" no longer works because the shell cannot find it, but giving a full path like "/bin/ls" would still work. 

- cd - Changes the directory and updates environment variables. The cd command checks if the first input value is a valid directory. If so, it will move the user into that directory using the "chdir" function. Then, it updates the environment variable PWD to reflect the current directory and the variable OLDPWD to reflect the directory we just came from. 

## Signals

In addition, we had to implement the interrupt (ctrl-D) and quit (ctrl-D) signals. The quit signal was straightforward - it just needed to exit the shell when applied to an empty prompt and do nothing otherwise. The interrupt signal was more interesting. 

Basically, we reformatted the interrupt signal to interrupt the child processes of the shell instead of the shell itself. Then, we were able to see when the processes were interrupted and change our exit status to the correct value.

## Downloading and Compiling

First, clone the repository onto your computer. Then try to compile with the Makefile with ```make all```. 

If that doesn't work: the readline library we were using for this project sometimes doesn't contain all of the correct functions. Running the included 'fix.sh' script by one of the other 42 students downloads the correct readline library into a temporary folder on your computer. 

If it still doesn't work after that, shoot me a message and I'll see what I can figure out. I've only tried the project on Mac, so I'm not sure what will happen on various Linux or Windows systems.

## Bonus features / fun stuff to try: 

- Our shell works for unclosed quotes! Try something like the command: ```echo "hello```

- Check out our heredoc implementation! Type ```cat << abc``` and the shell will take lines of input until one is equal to ```abc```. This even works with multiple heredocs! Try out ```cat << a > out | cat << b > out2 | cat << c > out3```. You can delimit the first heredoc with "a", the second with "b" and the third with "c", and each heredoc will appear in the correct file! 

- Start the minishell program within itself and check out the SHLVL variable: ```echo $SHLVL```

- Stop some commands with interrupt signals, like ```sleep 5```. You should get a new prompt and exit status should be 130. Test exit codes like this: ```echo $?```
