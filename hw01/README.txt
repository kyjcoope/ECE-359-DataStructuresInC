At the bottom of each output file is the execution time
and the total number of primes found. Everytime the program is run
an output.txt with all primes, plus execution time and total number of primes,
is either created or overridden.

The time complexity for my program is,

n for making the list, sqrt(n)*n for finding the primes, and n for saving the list.
Which ends up as n + sqrt(n)*n + n = O(sqrt(n)*n)

Program must be run in visual studio unless you remove, #include "stdafx.h"