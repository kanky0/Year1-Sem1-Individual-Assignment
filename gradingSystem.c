#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define LECTURER_ID "2223045"
#define MAX_STUDENTS 100

// function prototypes
int lecturer_menu();
int student_menu(char studentID[]);
void verify_lecturer();
void verify_student();
void register_new_student();
void record_student_marks();
void register_student(char id[]);
void record_marks(char id[], float assignment, float midterm, float project);
void view_all_marks();
void summary_record();
void view_mark(char id[]);
int check_student_exist(char id[]);
int find_student_position(char id[]);
int enter_mark(char type[], char id[]);
void grading_system(char id[]);
float calculate_individual_total_marks(char id[]);
void to_uppercase(char string[]);
int has_marks_recorded();

// global variables
char studentsID_list[MAX_STUDENTS][20], student_grades_list[MAX_STUDENTS][3];
float students_assignment[MAX_STUDENTS], students_midterm[MAX_STUDENTS], students_project[MAX_STUDENTS];
int studentCount = 0, passCount = 0, failCount = 0;

// main function
int main() {
    char input[10];
    int choice;

    while (1) {
        printf("\n-------Main Menu-------\n");
        printf("1. Lecturer\n");
        printf("2. Student\n");
        printf("3. Exit\n");
        printf("> ");
        
        // this is to check and get valid input from user
        if (!fgets(input, sizeof(input), stdin)) {
            printf("Error reading input, try again\n");
            continue;
        }
        input[strcspn(input, "\n")] = '\0';
        if (sscanf(input, "%d", &choice) != 1) {
            printf("Invalid input, enter a number\n");
            continue;
        }

        switch (choice) {
            case 1: verify_lecturer(); break;
            case 2: verify_student(); break;
            case 3: printf("\nGoodbye\n"); return 0;
            default: printf("Invalid choice, try again\n"); break;
        }
    }
    return 0;
}

// function to verify lecturer ID
void verify_lecturer() {
    char lecturerID[20];
    printf("\nEnter Lecturer ID: ");
    fgets(lecturerID, sizeof(lecturerID), stdin);
    lecturerID[strcspn(lecturerID, "\n")] = '\0';

    if (strcmp(lecturerID, LECTURER_ID) == 0) {
        lecturer_menu();
    } else {
        printf("Invalid Lecturer ID\n");
    }
}


// function to verify student ID
void verify_student() {
    char studentID[20];
    if (studentCount == 0) {
        printf("\nNo student registered yet\n");
        return;
    }
    
    printf("\nEnter Student ID: ");
    fgets(studentID, sizeof(studentID), stdin);
    studentID[strcspn(studentID, "\n")] = '\0';

    if (check_student_exist(studentID)) {
        student_menu(studentID);
    } else {
        printf("Student not registered\n");
    }
}


// function to check if marks has been recorded
int has_marks_recorded() {
    int count = 0;
    for (int i=0; i < studentCount; i++) {
        if (students_assignment[i] > 0 || students_midterm[i] > 0 || students_project[i] > 0) {
            count = 1;
            break;
        }
    }
    return count;
}

// lecturer menu
int lecturer_menu() {
    char input[10];
    int choice;

    while (1) {
        printf("\n-------Lecturer Menu-------\n");
        printf("1. Register Student\n");
        printf("2. Record Marks\n");
        printf("3. View all marks\n");
        printf("4. Summary record\n");
        printf("5. Back\n");
        printf("> ");
        
        if (!fgets(input, sizeof(input), stdin)) {
            printf("Error reading input, try again\n");
            continue;
        }
        input[strcspn(input, "\n")] = '\0';
        if (sscanf(input, "%d", &choice) != 1) {
            printf("Invalid input, enter a number\n");
            continue;
        }

        switch (choice) {
            case 1: register_new_student(); break;
            case 2: record_student_marks(); break;
            case 3: view_all_marks(); break;
            case 4: summary_record(); break;
            case 5: return 1;
            default: printf("Invalid choice, try again\n");
        }
    }
    return 0;
}

// function to register new student
void register_new_student() {
    char studentID[20];
    int is_blank;

    while (1) {
        printf("\nEnter student ID to register: ");
        fgets(studentID, sizeof(studentID), stdin);
        studentID[strcspn(studentID, "\n")] = '\0';

        is_blank = 1;
        for (int i=0; studentID[i] != '\0'; i++) {
            if (!isspace((unsigned char)studentID[i])) {
                is_blank = 0;
                break;
            }
        }

        if (is_blank) {
            printf("Student ID cannot be empty, try again\n");
            continue;
        }
        
        if (check_student_exist(studentID)) {
            printf("Student already registered\n");
            return;
        } else {
            register_student(studentID);
            studentCount++;
            printf("Student successfully registered\n");
            break;
        }
    }
}

// record the marks of students
void record_student_marks() {
    char studentID[20];

    if (studentCount == 0) {
        printf("\nNo students registered yet\n");
        return;
    }

    printf("\nEnter registered Student ID to record marks: ");
    fgets(studentID, sizeof(studentID), stdin);
    studentID[strcspn(studentID, "\n")] = '\0';

    if (!check_student_exist(studentID)) {
        printf("Student not registered\n");
        return;
    }

    enter_mark("assignment", studentID);
    enter_mark("midterm", studentID);
    enter_mark("project", studentID);
    grading_system(studentID);
    printf("Marks recorded successfully\n");
}

// student menu
int student_menu(char studentID[]) {
    char input[10];
    int choice;

    while (1) {
        printf("\n-------Student Menu-------\n");
        printf("1. View marks\n");
        printf("2. Back\n");
        printf("> ");

        if (!fgets(input, sizeof(input), stdin)) {
            printf("Error reading input, try again\n");
            continue;
        }
        input[strcspn(input, "\n")] = '\0';

        if (sscanf(input, "%d", &choice) != 1) {
            printf("Invalid input, enter a number\n");
            continue;
        }

        if (choice == 1) {
            int position = find_student_position(studentID);
            if (students_assignment[position] == 0 && students_midterm[position] == 0 && students_project[position] == 0) {
                printf("\nMarks not recorded yet\n");
            } else {
                view_mark(studentID);
            }
        } else if (choice == 2) {
            return 1;
        } else {
            printf("Invalid choice, try again\n");
        }
    }
    return 0;
}

// function to uppercase IDs
void to_uppercase(char string[]) {
    for (int i = 0; string[i] != '\0'; i++) {
        string[i] = toupper((unsigned char)string[i]);
    }
}

// function to check if student exists
int check_student_exist(char id[20]) {
    for (int i = 0; i < studentCount; i++) {
        if (strcasecmp(id, studentsID_list[i]) == 0) {
            return 1;
        }
    }
    return 0;    
}

// function to return the position of a student in StudentID_list
int find_student_position(char id[20]) {
    for (int i = 0; i < studentCount; i++) {
        if (strcasecmp(id, studentsID_list[i]) == 0) {
            return i;
        }
    }
    return -1;
}

// function to handle mark input
int enter_mark(char type[], char id[]) {
    char input[10];
    float mark = 0;
    int max_mark;

    if (strcmp(type, "assignment") == 0 || strcmp(type, "midterm") == 0) {
        max_mark = 25;
    } else if (strcmp(type, "project") == 0) {
        max_mark = 50;
    }

    while (1) {
        printf("Enter %s mark (0/%d): ", type, max_mark);
        if (!fgets(input, sizeof(input), stdin)) {
            printf("Error reading input, try again\n");
            continue;
        }
        input[strcspn(input, "\n")] = '\0';
        if (sscanf(input, "%f", &mark) != 1) {
            printf("Invalid input. Please enter a number\n");
            continue;
        }

        if (mark < 0 || mark > max_mark) {
            printf("Invalid mark, try again\n");
            continue; 
        }

        if (strcmp(type, "assignment") == 0) record_marks(id, mark, -1, -1);
        else if (strcmp(type, "midterm") == 0) record_marks(id, -1, mark, -1);
        else if (strcmp(type, "project") == 0) record_marks(id, -1, -1, mark);

        break;
    }
    return 0;
}

// function to update students marks' lists
void record_marks(char id[], float assignment, float midterm, float project) {
    int position = find_student_position(id);
    if (position == -1) {
        printf("Student not found\n");
        return;
    }

    if (assignment != -1) students_assignment[position] = assignment;
    if (midterm != -1) students_midterm[position] = midterm;
    if (project != -1) students_project[position] = project;
}

// function to update student_grades_list[]
void grading_system(char id[]) {
    int position = find_student_position(id);
    float total_marks = students_assignment[position] + students_midterm[position] + students_project[position];
    char grade[3];

    if (total_marks >= 85) strcpy(grade, "A ");
    else if (total_marks >= 80) strcpy(grade, "A-");
    else if (total_marks >= 75) strcpy(grade, "B+"); 
    else if (total_marks >= 70) strcpy(grade, "B ");
    else if (total_marks >= 65) strcpy(grade, "B-");
    else if (total_marks >= 60) strcpy(grade, "C+");
    else if (total_marks >= 55) strcpy(grade, "C "); 
    else if (total_marks >= 50) strcpy(grade, "C-"); 
    else if (total_marks >= 45) strcpy(grade, "D+");
    else if (total_marks >= 40) strcpy(grade, "D ");
    else strcpy(grade, "F ");

    strcpy(student_grades_list[position], grade);

    if (total_marks >= 50) passCount++;
    else failCount++;
}

// function to return student's total marks
float calculate_individual_total_marks(char id[]) {
    int position = find_student_position(id);
    return students_assignment[position] + students_midterm[position] + students_project[position];
}

// function to update studentID_list[]
void register_student(char id[]) {
    if (studentCount >= MAX_STUDENTS) {
        printf("Maximum number of students reached\n");
        return;
    }
    for (int i = 0; id[i] != '\0'; i++) {
        studentsID_list[studentCount][i] = tolower(id[i]);
    }
    studentsID_list[studentCount][strlen(id)] = '\0';
    students_assignment[studentCount] = 0;
    students_midterm[studentCount] = 0;
    students_project[studentCount] = 0;
}

// function to give summary of the recorded marks
void summary_record() {
    if (studentCount == 0) {
        printf("\nNo student registered yet\n");
        return;
    }

    int count = has_marks_recorded();
    if (!count) {
        printf("\nNo marks recorded yet\n");
        return;
    }

    float total_marks = 0.0;
    float average_marks = 0.0;

    for (int i = 0;i < studentCount; i++) {
        total_marks += calculate_individual_total_marks(studentsID_list[i]);
    }

    if (studentCount > 0) {
        average_marks = total_marks / studentCount;
    }

    printf("\n----------Summary----------\n");
    printf("Total students\t: %d\n", studentCount);
    printf("Total average\t: %.1f\n", average_marks);
    printf("Passes\t\t: %.1f% %\n", (float)passCount / studentCount * 100);
    printf("Fails\t\t: %.1f% %\n", (float)failCount / studentCount * 100);
    printf("---------------------------\n");
}

// function to view all marks
void view_all_marks() {
    if (studentCount == 0) {
        printf("\nNo students registered yet\n");
        return;
    }
    
    int count = has_marks_recorded();
    if (!count) {
        printf("\nNo marks recorded yet\n");
        return;
    }

    printf("\n%-13s %13s %15s %16s %15s %15s\n", "Student ID", "Assignment", "Midterm", "Project", "Total", "Grade");
    printf("-------------------------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < studentCount; i++) {
        char uppercase_id[20];
        strcpy(uppercase_id, studentsID_list[i]);
        to_uppercase(uppercase_id);
        float total = calculate_individual_total_marks(studentsID_list[i]);

        printf("%-10s %11.1f/25 %14.1f/25 %13.1f/50 %13.1f/100 %12s\n", uppercase_id, students_assignment[i], students_midterm[i], students_project[i], total, student_grades_list[i]);
    }

    printf("-------------------------------------------------------------------------------------------------\n");
}

// function to view student's individual marks
void view_mark(char id[]) {
    int position = find_student_position(id);
    float total = calculate_individual_total_marks(id);
    char uppercase_id[20];
    strcpy(uppercase_id, id);
    to_uppercase(uppercase_id);

    printf("\nStudent ID\t: %s\n", uppercase_id);
    printf("Assignment\t: %.1f/25\n", students_assignment[position]);
    printf("Midterm\t\t: %.1f/25\n", students_midterm[position]);
    printf("Project\t\t: %.1f/50\n", students_project[position]);
    printf("Total Mark\t: %.1f/100\n", total);
    printf("Grade\t\t: %s\n", student_grades_list[position]);

}
