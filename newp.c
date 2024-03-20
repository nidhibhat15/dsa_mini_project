#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 1000

struct Student {
    int rollNumber;
    char name[50];
    float sgpa[8];
    float cgpa;
    struct Student *next;
};

struct Student *head = NULL;
int studentCount = 0;

void insertStudent() {
    if (studentCount < MAX_STUDENTS) {
        struct Student *newStudent = (struct Student*)malloc(sizeof(struct Student));
        if (newStudent == NULL) {
            printf("Memory allocation failed!\n");
            return;
        }

        printf("Enter Roll Number: ");
        scanf("%d", &newStudent->rollNumber);

        struct Student *temp = head;
        while (temp != NULL) {
            if (temp->rollNumber == newStudent->rollNumber) {
                printf("Student with Roll Number %d already exists. Cannot add duplicate entry.\n", newStudent->rollNumber);
                free(newStudent);
                return;
            }
            temp = temp->next;
        }

        printf("Enter Name: ");
        scanf("%s", newStudent->name);

        printf("Enter SGPA for each semester:\n");
        for (int i = 0; i < 8; i++) {
            printf("Enter SGPA for Semester %d: ", i + 1);
            scanf("%f", &newStudent->sgpa[i]);
        }

        newStudent->cgpa = 0.0;
        for (int i = 0; i < 8; i++) {
            newStudent->cgpa += newStudent->sgpa[i];
        }
        newStudent->cgpa /= 8;

        newStudent->next = head;
        head = newStudent;

        studentCount++; // Increment studentCount after successful insertion
        printf("Student entry added successfully!\n");
    } else {
        printf("Maximum number of students reached!\n");
    }
}

void deleteStudent(int rollNumber) {
    struct Student *prev = NULL;
    struct Student *current = head;

    while (current != NULL && current->rollNumber != rollNumber) {
        prev = current;
        current = current->next;
    }

    if (current != NULL) {
        if (prev == NULL) {
            head = current->next;
        } else {
            prev->next = current->next;
        }
        free(current);
        studentCount--;
        printf("Student with Roll Number %d deleted successfully!\n", rollNumber);
    } else {
        printf("Student not found!\n");
    }
}

void displayAllStudents() {
    printf("\nAll Students:\n");
    struct Student *current = head;
    while (current != NULL) {
        printf("Roll Number: %d, Name: %s, CGPA: %.2f\n", current->rollNumber, current->name, current->cgpa);
        current = current->next;
    }
}

void searchByRollNumber(int rollNumber) {
    struct Student *current = head;
    while (current != NULL) {
        if (current->rollNumber == rollNumber) {
            printf("Roll Number: %d, Name: %s, CGPA: %.2f\n", current->rollNumber, current->name, current->cgpa);
            return;
        }
        current = current->next;
    }
    printf("Student with Roll Number %d is not found\n", rollNumber);
}

void updateStudent(int rollNumber) {
    struct Student *current = head;
    while (current != NULL && current->rollNumber != rollNumber) {
        current = current->next;
    }

    if (current != NULL) {
        printf("Choose what to update:\n");
        printf("1. Name\n");
        printf("2. SGPA\n");

        int updateChoice;
        scanf("%d", &updateChoice);

        switch (updateChoice) {
            case 1:
                printf("Enter new name: ");
                scanf("%s", current->name);
                printf("Student name updated\n");
                break;
            case 2:
                printf("Enter new SGPA values (8 semesters): ");
                for (int i = 0; i < 8; i++) {
                    scanf("%f", &current->sgpa[i]);
                }

                current->cgpa = 0.0;
                for (int i = 0; i < 8; i++) {
                    current->cgpa += current->sgpa[i];
                }
                current->cgpa /= 8;
                printf("Student CGPA updated\n");
                break;
            default:
                printf("Invalid choice for update.\n");
                return;
        }

        printf("Student with Roll Number %d updated successfully!\n", rollNumber);
    } else {
        printf("Student not found!\n");
    }
}

int compareCGPA(const void *a, const void *b) {
    float cgpaA = ((struct Student*)a)->cgpa;
    float cgpaB = ((struct Student*)b)->cgpa;
    if (cgpaA > cgpaB)
        return -1;
    else if (cgpaA < cgpaB)
        return 1;
    else
        return 0;
}

void sortStudentsByCGPA(struct Student *studentsArray[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (studentsArray[j]->cgpa < studentsArray[j + 1]->cgpa) {
                struct Student *temp = studentsArray[j];
                studentsArray[j] = studentsArray[j + 1];
                studentsArray[j + 1] = temp;
            }
        }
    }
}

void displayTop() {
    struct Student *studentsArray[MAX_STUDENTS];
    struct Student *current = head;
    int i = 0;
    while (current != NULL) {
        studentsArray[i++] = current;
        current = current->next;
    }

    sortStudentsByCGPA(studentsArray, studentCount);

    printf("\nTop Students based on CGPA:\n");
    int topCount = studentCount > 5 ? 5 : studentCount;
    for (int i = 0; i < topCount; i++) {
        printf("Rank %d\nName: %s\nRoll Number: %d\nCGPA: %.2f\n", i + 1, studentsArray[i]->name, studentsArray[i]->rollNumber, studentsArray[i]->cgpa);
    }
}

int main() {
    int choice;
    int rollNumber;

    do {
        printf("\nMenu:\n");
        printf("1. Insert new Student data:\n");
        printf("2. Delete Student\n");
        printf("3. Update Student details\n");
        printf("4. Display top Students\n");
        printf("5. Search by roll number\n");
        printf("6. Display all Students\n");
        printf("7. Get the number of students\n");
        printf("8. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                insertStudent();
                break;
            case 2:
                printf("Enter Roll Number to delete: ");
                scanf("%d", &rollNumber);
                deleteStudent(rollNumber);
                break;
            case 3:
                printf("Enter Roll Number to update: ");
                scanf("%d", &rollNumber);
                updateStudent(rollNumber);
                break;
            case 4:
                displayTop();
                break;
            case 5:
                printf("Enter roll number of the student:");
                scanf("%d", &rollNumber);
                searchByRollNumber(rollNumber);
                break;
            case 6:
                displayAllStudents();
                break;
            case 7:
                printf("Total number of students: %d\n", studentCount);
                break;
            case 8:
                printf("Exiting program. Goodbye!\n");
                exit(0);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 8);

    return 0;
}
