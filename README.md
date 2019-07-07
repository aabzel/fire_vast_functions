# fire vast functions


Vast functions are a serious problem in C-language projects for microcontrollers among developers.

Disadvantages of long functions:

-) Long functions do not fit on the screen (26 ... 55 lines tall) and it is impossible to analyze the algorithm inside such long functions.

-) Long functions typically contain repetitive code that violates the procedural paradigm of program development.

My C++ console program finds all functions whose length exceeds the predetermined constant and prints it in sorting view from big to short functions.

My C++ console program bot finds the names of long functions, prints its total length and check that length with parameter of utility.


That checker bot utility can be run before the human Code Review (like a Jenkins bot in Gerrit), and thus save precious time on the human made Code Review.
 
