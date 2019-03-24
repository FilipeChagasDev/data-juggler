# data-juggler
This is a set of portable C++ codes that perform optimized data organization features such as item collections (lists and trees), strings, among other things.
This library is under development and does not have enough descriptive documents. Look at the source code itself to better understand its operation.

## Documentation
The documentation can be accessed through this link: 
https://filipechagasdev.github.io/data-juggler/index.html

## How to include this in my code
To use this library in your C ++ program, you must include the datajuggler.hpp header in your code. When compiling your program, you should give all .o files from the obj directory or all .cpp files from the src directory to the compiler to compile the datajuggler together with your program.

## Source code files
all code files are in the src directory. The .cpp files can each be compiled into an .o file, and then linked to an executable. The .cxx files do not require individual compilation, since their contents are already included in the main code. .Cpp files have implementations of normal classes, and .cxx files have implementations of template classes.
