# Mastermind-Knuth-Algorithm
Donal Knuth's five guess algorithm for solving the game Mastermind.

In 1977, Donald Knuth demonstrated that the codebreaker can solve the pattern in five moves or fewer, using an algorithm that progressively reduced the number of possible patterns.

The algorithm works as follows:

Create the set S of 1296 possible codes (1111, 1112 ... 6665, 6666).

Start with initial guess 1122 (Knuth gives examples showing that other first guesses such as 1123, 1234 do not win in five tries on every code).

Play the guess to get a response of colored and white pegs.

If the response is four colored pegs, the game is won, the algorithm terminates.

Otherwise, remove from S any code that would not give the same response if the current guess were the code.

For example, if your current guess is 1122 and you get a response of BW;
If the code were 1111 you would get two black pegs (BB) with a guess of 1122, which is not the same as one black peg and one white peg (BW). So, remove 1111 from the list of potential solutions.

F(1122,1112) = BBB≠BW →Remove 1112 from S

F(1122,1113) = BB≠BW →Remove 1113 from S

F(1122,1114) = BB≠BW →Remove 1114 from S

F(1122,1314) = BW=BW →Keep 1314 in S


Apply minimax technique to find a next guess as follows:
For each possible guess, that is, any unused code of the 1296 not just those in S, calculate how many possibilities in S would be eliminated for each possible colored/white peg score. The score of a guess is the minimum number of possibilities it might eliminate from S.

A single loop through S for each unused code of the 1296 will provide a 'hit count' for each of the possible colored/white peg scores; Create a set of guesses with the smallest max score (hence minmax).
From the set of guesses with the minimum (max) score, select one as the next guess, choosing a member of S whenever possible.

Knuth follows the convention of choosing the guess with the least numeric value e.g. 2345 is lower than 3456. Knuth also gives an example showing that in some cases no member of S will be among the highest scoring guesses and thus the guess cannot win on the next turn, yet will be necessary to assure a win in five.

Table of example scoreset counts for two possible next guesses

Scores(B/W)	RRGB	RGBG
(0,0)	25	15
(0,1)	4	84
(0,2)	6	0
(0,3)	0	0
(0,4)	0	0
(1,0)	15	0
(1,1)	10	0
(1,2)	0	0
(1,3)	5	0
(2,0)	5	0
(2,1)	3	0
(2,2)	2	0
(3,0)	24	0
(4,0)	1	1
max	25	84
Repeat from step 3.

For reference https://www.cs.uni.edu/~wallingf/teaching/cs3530/resources/knuth-mastermind.pdf

# Getting Started
Open a new terminal window or cmd if you are on windows

Change the directory to the directory in which you have your source.cpp file. For example, if it is in C:/Users/Dell/Documents, enter your command line −
`$ cd 'C:/Users/Dell/Documents'`

Enter the following command to compile the source file using g++
`$ g++ -o <name-you-want-to-give> source.cpp`

Run it! Now you can run the program using −
`$ ./myprogram`
