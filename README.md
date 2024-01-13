# 42-philosophers
Philosophers project at 42 School

This project is a resolution to the dining philosophers that is written entirely in C, from the common core of 42 School.
Each philosopher is a thread, there are as many philosophers as forks, and each philosophers needs two forks to eat.
Forks are protected by mutexes, philosophers die event is checked by the main function.
Only some functions were authorized, you can find them in the subject :
[Full subject](https://cdn.intra.42.fr/pdf/pdf/115742/en.subject.pdf)

Organization of files, readability of code and/or the names of functions and variables can seem awful, because of the [42 Norm](https://raw.githubusercontent.com/42School/norminette/master/pdf/en.norm.pdf) that limits the length of a line to 80, number of functions in a file to 5, and number of lines in a function to 25.

