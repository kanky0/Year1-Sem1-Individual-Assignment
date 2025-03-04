# Student Grading System

## Description
This program is a **Student Grading System** that allows a **lecturer** to register students, record their marks, and view summaries. Students can also log in to view their individual marks.

## Features
### Lecturer Functions:
1. Register a student – Add a new student to the system.
2. Record marks – Enter marks for assignments, midterms, and projects.
3. View all marks – Display all students' marks and grades.
4. Summary record – Show the total number of students, average marks, and pass/fail percentages.

### Student Functions:
1. View marks – Students can check their individual marks and grade.

## Usage Instructions
1. Run the program.
2. Choose between:
   - Lecturer (Enter Lecturer ID to access the menu)
   - Student (Enter Student ID to check marks)
   - Exit to quit the program.
3. If logged in as a lecturer, follow the menu options to register students, enter marks, or view reports.
4. If logged in as a student, enter a valid Student ID to view recorded marks.

## Input Constraints
- Lecturer ID must be "2223045".
- Student IDs are case-insensitive.
- Marks must be within valid ranges:
  - Assignment: 0 - 25
  - Midterm: 0 - 25
  - Project: 0 - 50

## Grading System
| Total Marks (out of 100) | Grade |
|--------------------------|-------|
| 85 - 100                 | A     |
| 80 - 84                  | A-    |
| 75 - 79                  | B+    |
| 70 - 74                  | B     |
| 65 - 69                  | B-    |
| 60 - 64                  | C+    |
| 55 - 59                  | C     |
| 50 - 54                  | C-    |
| 45 - 49                  | D+    |
| 40 - 44                  | D     |
| 0 - 39                   | F     |

## Error Handling
- Invalid input prompts an error message and re-requests input.
- If no students are registered, the system prevents mark entry.
- If no marks are recorded, the system prevents viewing summary data.

## Notes
- The system supports up to 100 students.
- Student IDs are automatically converted to lowercase for consistency.

## Future Enhancements
- Implement file storage for persistence.
- Add authentication for students.
- Improve UI with a graphical interface.

## Author
Developed by Louis Chua Khai Yi, Toh Bin Bin, Tan Jing Hong, and Lieng Yu Hao

