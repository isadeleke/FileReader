# FileReader


The application was developed using C++ with Visual Studio as a console application.
Requirement Verification
1. File Reading and Display 
Methodology:
- A structured text file (students.txt) was created and passed to the program.
- The application reads student records line by line and stores them in a vector of Student objects.
Results:
The records are successfully displayed in the console upon file load. Example output:
1, John Doe, 20, 85
2, Jane Smith, 22, 78
2. Search Functionality 
Methodology:
- The user is prompted to enter a name to search.
- The program checks all student names using string::find() to allow partial matches.
Results:
When searching for 'Jane', output is:
2, Jane Smith, 22, 78
If the student is not found, the program outputs:
No student found with name containing "X".
3. Sorting Records 
Methodology:
- The user can sort file by either 'age' or 'grade', in 'asc' or 'desc' order.
- Sorting uses std::sort() with lambda functions inside the DataAnalyzer class.
Results:
Sorted records display correctly. Example:
Sorted by grade descending

Console Output
3, Alice Brown, 19, 92
1, John Doe, 20, 85
2, Jane Smith, 22, 78
4. Statistical Analysis 
Methodology:
- Loops through grades to calculate average, highest, lowest, and number of students with grade ≥ 50.( For the highest it compares until it gets to highest and vice versa)
Results:
Console output:
Grade Statistics:
------------------
Average Grade: 85
Highest Grade: 92
Lowest Grade : 78
Students Passed (>= 50): 3
5. Saving the Results 
Methodology:
- The saveResults() function creates results.txt.
- It writes all student records and appends grade statistics at the end.
Results:
results.txt contains:
ID, Name, Age, Grade
1, John Doe, 20, 85
...
Grade Statistics:
Average Grade: 85
...
6. Object-Oriented Design 
Methodology:
- Implemented two classes:
  - Student: encapsulates individual record details.
  - DataAnalyzer: manages all core functionality (file I/O, search, sort, stats, save).
- Used:
  - Encapsulation (private members and getters) I.e as used in the student class
  - Composition (vector of Student in DataAnalyzer)
  - Operator Overloading (< for grade comparison)
  - Clear method separation per responsibility
Conclusion
I have developed an application that was able to meet the requirements stated, The application demonstrate key concepts such as features like file I/O , file searching sorting, saving and shows use of Object-oriented approaches.

