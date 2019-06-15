# fire vast functions


Vast functions are a serious problem in C-language projects for microcontrollers among immature so called firmware developers.

Disadvantages of long functions:

-) Long functions do not fit on the screen (26 ... 55 lines tall) and it is impossible to analyze the algorithm inside such long functions.

-) Long functions typically contain repetitive code that violates the procedural paradigm of program development.

My C++ console program finds all functions whose length exceeds the predetermined constant.

My C++ console program bot finds the names of long functions, prints its total length and check that length with parameter of utility.

That checker bot utility can be run before the human CodeReview (like a Jenkins bot in Gerrit), and thus save time on the CodeReview.

 
