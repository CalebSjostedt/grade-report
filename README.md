# grade-report
Takes in a input file and outputs a grade report to console. Input text file is defaulted to input.txt and is provided with a sample dataset.


## File input 
The first integer represents the amount of total test cases and the second integer represents the amount of courses in each test case. The following string is the course name, and the next integer is the number of sections in the course. The next two integers are the number of students and the scores per section respectively.

For each of the student rows, the first integer is the id of the student, the string is the name, and the following scores are the number of assignments based on scores per section.

## Running the program
Compilation with clang using the ```gcc gradereport.c``` command should work properly. The program output will display on cli.
