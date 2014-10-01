The Elvish races of Middle Earth believed that certain numbers were more significant than
others. When using a particular quantity n of metal to forge a particular sword, they believed that
sword would be most powerful if the thickness k were chosen according to the following rule:

Given a nonnegative integer n, what is the smallest k such that the decimal representations of
the integers in the sequence:

n, 2n, 3n, 4n, 5n, . . . , kn

contain all ten digits (0 through 9) at least once?

Lord Elrond of Rivendell has commissioned you with the task to develop an algorithm to find
the optimal thickness (k) for any given quantity of metal (n).

Input
================

Input will consist of a single integer n per line. The end of input will be signaled by end of file.
The input integer will be between 1 and 200,000,000, inclusive.

Output
==================

The output will consist of a single integer per line, indicating the value of k needed such that every
digit from 0 through 9 is seen at least once.

Sample Input
=

1

10

123456789

3141592

Sample Output
=

10

9

3

5
