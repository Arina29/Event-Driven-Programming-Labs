# Programming style guideline 
The programming style used in laboratory works will coincide with 
[this one](https://users.physics.ox.ac.uk/~Steane/cpp_help/mycppstyle.htm) ,but with some little changes.
 * The code is written in CamelCase, using Hungarian notation.
 * Variable and function names should be meaningfull
 * variable and function names uses camelCase starting with a lowercase letter
 * #define's uses SNAKE_CASE and all letters caps
 
 ### Identations:
 * Tabs of size 4 
 * In case of if with one statement don't use braces
```c++
if(condition)
    \\code
```
 * Use braces for all switch cases
 ```c++
 switch(msg)
 {
     case 1:
     {
     \\code
     }
 }
```
 * Use 'Allman' indentation and braces style:
 ```c++
 if(condition)
 {
     \\code
 }
 ```

