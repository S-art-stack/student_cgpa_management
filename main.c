#include <stdio.h>
#include <stdlib.h>

// store student information
typedef struct
{
    int roll;
    char name[50];
    float cgpa;
    int bonus;
} Student;

// convert a string into number
int toNum(char *s)
{
    // taking first number and converting it into a number and appending it into n
    int n = 0, i = 0;
    while (s[i] != '\0')
    {
        n = (n * 10) + (s[i] - 48); // '0' = 48, '9' = 57
        i++;
    }
    return n;
}

// check if a input is valid number or not
int isNum(char *s)
{
    int status = 1;
    int i = 0;
    while (s[i] != '\0')
    {
        if (s[i] < '0' || s[i] > '9')
        {
            status = 0;
            break;
        }
        i++;
    }
    return status;
}

void swap(Student *a, Student *b)
{
    Student temp = *a;
    *a = *b;
    *b = temp;
}

int main()
{
    char *in = (char *)malloc(10);

    // taking number of students
    printf("Enter the number of students: ");

    // this loop will check if the inputed number is valid or not
    while (1)
    {
        scanf("%s", in);
        if (isNum(in)) // isNum() -> 1 if the number only contain numeric values
            break;
        else // tell user to reenter the number
            printf("Please enter a valid number: ");
    }
    // number of students
    int n = toNum(in);

    // taking bonus point
    printf("Enter bonus point: ");
    while (1)
    {
        scanf("%s", in);
        if (isNum(in))
            break;
        else
            printf("Please enter a valid point(number): ");
    }
    int bonus_point = toNum(in);

    Student students[n];

    FILE *inputFile, *highCgpaFile, *lowCgpaFile;
    inputFile = fopen("student_data.txt", "w");
    highCgpaFile = fopen("high_cgpa_students.txt", "w");
    lowCgpaFile = fopen("low_cgpa_students.txt", "w");

    // checking if the file opened or not
    if (highCgpaFile == NULL || lowCgpaFile == NULL || inputFile == NULL)
    {
        perror("File opening failed");
        return 0;
    }

    // taking data from user
    for (int i = 0; i < n; i++)
    {
        printf("Enter details for Student %d:\n", i + 1);
        printf("Name: ");
        scanf(" %[^\n]s", students[i].name);
        printf("Roll: ");
        scanf("%d", &students[i].roll);
        printf("CGPA: ");
        scanf("%f", &students[i].cgpa);
    }

    // sorting the inputed data (students) with 
    for (int i = 0; i < n; i++)
    {
        for (int j = 1; j < n - i; j++)
        {
            if (students[j].cgpa > students[j - 1].cgpa)
            {
                swap(&students[j], &students[j - 1]);
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        fprintf(inputFile, "%d %s %.2f\n", students[i].roll, students[i].name, students[i].cgpa);
        if (students[i].cgpa > 3.8)
        {
            students[i].bonus = bonus_point;
            fprintf(highCgpaFile, "%s %d %.2f %d\n", students[i].name, students[i].roll, students[i].cgpa, students[i].bonus);
        }
        else
        {
            students[i].bonus = 0;
            fprintf(lowCgpaFile, "%s %d %.2f %d\n", students[i].name, students[i].roll, students[i].cgpa, students[i].bonus);
        }
    }

    fclose(highCgpaFile);
    fclose(lowCgpaFile);
    fclose(inputFile);
    return 0;
}