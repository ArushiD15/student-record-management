// PROGRAM 1: STUDENT RECORD MANAGEMENT SYSTEM
#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 50
#define NAME_LEN 50

//Structure Definition
struct Student {
    int rollNumber;
    char name[NAME_LEN];
    float marks[3];
    float total;
    float average;
};

//Function Prototypes
void addStudent(struct Student students[], int *count);
void displayAll(const struct Student students[], int count);
int searchByRoll(const struct Student students[], int count, int roll);
void searchStudent(const struct Student students[], int count);
void updateMarks(struct Student students[], int count);
void deleteStudent(struct Student students[], int *count);
void sortByTotal(struct Student students[], int count);
void displayTopper(const struct Student students[], int count);
void calculateTotalAverage(struct Student *s);
int isDuplicateRoll(const struct Student students[], int count, int roll);
void printStudent(const struct Student *s);
int getMenuChoice(void);
int readInt(const char *prompt);
float readFloat(const char *prompt);

//Main Function
int main(void) {
    struct Student students[MAX_STUDENTS];
    int count = 0;   // current number of stored students
    int choice;
    printf("      STUDENT RECORD MANAGEMENT SYSTEM\n");

    do {
        choice = getMenuChoice();

        switch (choice) {
            case 1:
                addStudent(students, &count);
                break;
            case 2:
                displayAll(students, count);
                break;
            case 3:
                searchStudent(students, count);
                break;
            case 4:
                updateMarks(students, count);
                break;
            case 5:
                deleteStudent(students, &count);
                break;
            case 6:
                sortByTotal(students, count);
                break;
            case 7:
                displayTopper(students, count);
                break;
            case 8:
                printf("\nExiting program. Goodbye!\n");
                break;
            default:
                printf("\nInvalid choice! Please enter a number between 1 and 8.\n");
        }

    } while (choice != 8);

    return 0;
}

/* ---------- Menu Display ---------- */
int getMenuChoice(void) {
    printf("\n----------------- MENU -----------------\n");
    printf("1. Add a new student record\n");
    printf("2. Display all student records\n");
    printf("3. Search for a student (by roll number)\n");
    printf("4. Update a student's marks\n");
    printf("5. Delete a student record\n");
    printf("6. Sort students by total marks\n");
    printf("7. Display student with highest marks\n");
    printf("8. Exit\n");
    printf("-----------------------------------------\n");

    return readInt("Enter your choice (1-8): ");
}

/* ---------- Safe Integer Input ---------- */
int readInt(const char *prompt) {
    int value;
    int result;

    printf("%s", prompt);
    result = scanf("%d", &value);

    /* clear leftover input in case of invalid entry */
    while (getchar() != '\n');

    if (result != 1) {
        return -1; /* invalid, will be caught by menu default case */
    }
    return value;
}

/* ---------- Safe Float Input ---------- */
float readFloat(const char *prompt) {
    float value;
    int result;

    printf("%s", prompt);
    result = scanf("%f", &value);
    while (getchar() != '\n');

    if (result != 1) {
        printf("Invalid input, defaulting to 0.\n");
        return 0.0f;
    }
    return value;
}

/* ---------- Check for Duplicate Roll Number ---------- */
int isDuplicateRoll(const struct Student students[], int count, int roll) {
    int i;
    for (i = 0; i < count; i++) {
        if (students[i].rollNumber == roll) {
            return 1; /* duplicate found */
        }
    }
    return 0;
}

/* ---------- Calculate Total & Average (uses pointer) ---------- */
void calculateTotalAverage(struct Student *s) {
    s->total = s->marks[0] + s->marks[1] + s->marks[2];
    s->average = s->total / 3.0f;
}

/* ---------- 1. Add Student ---------- */
void addStudent(struct Student students[], int *count) {
    struct Student newStudent;
    int roll;

    if (*count >= MAX_STUDENTS) {
        printf("\nCannot add more students. Maximum limit (%d) reached.\n", MAX_STUDENTS);
        return;
    }

    printf("\n--- Add New Student ---\n");

    roll = readInt("Enter roll number: ");
    if (roll < 0) {
        printf("Invalid roll number entered.\n");
        return;
    }

    if (isDuplicateRoll(students, *count, roll)) {
        printf("Error: A student with roll number %d already exists!\n", roll);
        return;
    }

    newStudent.rollNumber = roll;

    printf("Enter name: ");
    fgets(newStudent.name, NAME_LEN, stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = '\0'; /* strip newline */

    newStudent.marks[0] = readFloat("Enter marks in Subject 1: ");
    newStudent.marks[1] = readFloat("Enter marks in Subject 2: ");
    newStudent.marks[2] = readFloat("Enter marks in Subject 3: ");

    calculateTotalAverage(&newStudent);

    students[*count] = newStudent;
    (*count)++;

    printf("\nStudent record added successfully!\n");
}

/* ---------- Print a Single Student (uses pointer) ---------- */
void printStudent(const struct Student *s) {
    printf("%-10d %-20s %-8.2f %-8.2f %-8.2f %-10.2f %-10.2f\n",
           s->rollNumber, s->name,
           s->marks[0], s->marks[1], s->marks[2],
           s->total, s->average);
}

/* ---------- 2. Display All Students ---------- */
void displayAll(const struct Student students[], int count) {
    int i;

    if (count == 0) {
        printf("\nNo student records available.\n");
        return;
    }

    printf("\n--- All Student Records (%d total) ---\n", count);
    printf("%-10s %-20s %-8s %-8s %-8s %-10s %-10s\n",
           "Roll", "Name", "Sub1", "Sub2", "Sub3", "Total", "Average");
    printf("--------------------------------------------------------------------\n");

    for (i = 0; i < count; i++) {
        printStudent(&students[i]);
    }
}

/* ---------- Helper: Search by Roll Number, Returns Index ---------- */
int searchByRoll(const struct Student students[], int count, int roll) {
    int i;
    for (i = 0; i < count; i++) {
        if (students[i].rollNumber == roll) {
            return i;
        }
    }
    return -1; /* not found */
}

/* ---------- 3. Search Student (menu wrapper) ---------- */
void searchStudent(const struct Student students[], int count) {
    int roll, index;

    if (count == 0) {
        printf("\nNo student records available to search.\n");
        return;
    }

    roll = readInt("\nEnter roll number to search: ");
    index = searchByRoll(students, count, roll);

    if (index == -1) {
        printf("Student with roll number %d not found.\n", roll);
    } else {
        printf("\nStudent found:\n");
        printf("%-10s %-20s %-8s %-8s %-8s %-10s %-10s\n",
               "Roll", "Name", "Sub1", "Sub2", "Sub3", "Total", "Average");
        printStudent(&students[index]);
    }
}

/* ---------- 4. Update Marks ---------- */
void updateMarks(struct Student students[], int count) {
    int roll, index;

    if (count == 0) {
        printf("\nNo student records available to update.\n");
        return;
    }

    roll = readInt("\nEnter roll number of student to update: ");
    index = searchByRoll(students, count, roll);

    if (index == -1) {
        printf("Student with roll number %d not found.\n", roll);
        return;
    }

    /* using a pointer to directly modify the array element */
    struct Student *s = &students[index];

    printf("Updating marks for %s (Roll No: %d)\n", s->name, s->rollNumber);
    s->marks[0] = readFloat("Enter new marks for Subject 1: ");
    s->marks[1] = readFloat("Enter new marks for Subject 2: ");
    s->marks[2] = readFloat("Enter new marks for Subject 3: ");

    calculateTotalAverage(s);

    printf("Marks updated successfully!\n");
}

/* ---------- 5. Delete Student ---------- */
void deleteStudent(struct Student students[], int *count) {
    int roll, index, i;

    if (*count == 0) {
        printf("\nNo student records available to delete.\n");
        return;
    }

    roll = readInt("\nEnter roll number of student to delete: ");
    index = searchByRoll(students, *count, roll);

    if (index == -1) {
        printf("Student with roll number %d not found.\n", roll);
        return;
    }

    /* shift all subsequent records one position left */
    for (i = index; i < *count - 1; i++) {
        students[i] = students[i + 1];
    }

    (*count)--;
    printf("Student record deleted successfully!\n");
}

/* ---------- 6. Sort by Total Marks (descending, bubble sort) ---------- */
void sortByTotal(struct Student students[], int count) {
    int i, j;
    struct Student temp;

    if (count == 0) {
        printf("\nNo student records available to sort.\n");
        return;
    }

    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - i - 1; j++) {
            if (students[j].total < students[j + 1].total) {
                temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    printf("\nStudents sorted by total marks (highest to lowest):\n");
    displayAll(students, count);
}

/* ---------- 7. Display Topper ---------- */
void displayTopper(const struct Student students[], int count) {
    int i, topIndex = 0;

    if (count == 0) {
        printf("\nNo student records available.\n");
        return;
    }

    for (i = 1; i < count; i++) {
        if (students[i].total > students[topIndex].total) {
            topIndex = i;
        }
    }

    printf("\n--- Student with Highest Marks ---\n");
    printf("%-10s %-20s %-8s %-8s %-8s %-10s %-10s\n",
           "Roll", "Name", "Sub1", "Sub2", "Sub3", "Total", "Average");
    printStudent(&students[topIndex]);
}

