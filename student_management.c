
#include <stdio.h>
#include <stdlib.h>

struct Student
{
    int roll;
    char name[50];
    float marks;
};

void addStudent()
{
    struct Student s, temp;
    FILE *fp;

    printf("Enter Roll Number: ");
    scanf("%d", &s.roll);

    fp = fopen("students.dat", "ab+");

    if(fp == NULL)
    {
        printf("File error!\n");
        return;
    }

    rewind(fp);

    while(fread(&temp, sizeof(temp), 1, fp) == 1)
    {
        if(temp.roll == s.roll)
        {
            printf("Roll number already exists!\n");
            fclose(fp);
            return;
        }
    }

    printf("Enter Name: ");
    scanf(" %49[^\n]", s.name);

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(s), 1, fp);

    fclose(fp);

    printf("Student added successfully!\n");
}

void displayStudents()
{
    struct Student s;
    FILE *fp;

    fp = fopen("students.dat", "rb");

    if(fp == NULL)
    {
        printf("No student records found!\n");
        return;
    }

    printf("\n--- Student Records ---\n");

    while(fread(&s, sizeof(s), 1, fp) == 1)
    {
        printf("\nRoll Number: %d\n", s.roll);
        printf("Name: %s\n", s.name);
        printf("Marks: %.2f\n", s.marks);
    }

    fclose(fp);
}

void searchStudent()
{
    struct Student s;
    int roll, found = 0;
    FILE *fp;

    printf("Enter Roll Number to search: ");
    scanf("%d", &roll);

    fp = fopen("students.dat", "rb");

    if(fp == NULL)
    {
        printf("No records found!\n");
        return;
    }

    while(fread(&s, sizeof(s), 1, fp) == 1)
    {
        if(s.roll == roll)
        {
            printf("\nStudent Found!\n");
            printf("Roll: %d\n", s.roll);
            printf("Name: %s\n", s.name);
            printf("Marks: %.2f\n", s.marks);
            found = 1;
            break;
        }
    }

    if(!found)
        printf("Student not found!\n");

    fclose(fp);
}

void updateStudent()
{
    struct Student s;
    int roll, found = 0;
    FILE *fp;
    long position;

    printf("Enter Roll Number to update: ");
    scanf("%d", &roll);

    fp = fopen("students.dat", "rb+");

    if(fp == NULL)
    {
        printf("No records found!\n");
        return;
    }

    while(1)
    {
        position = ftell(fp);

        if(fread(&s, sizeof(s), 1, fp) != 1)
            break;

        if(s.roll == roll)
        {
            printf("Enter New Name: ");
            scanf(" %49[^\n]", s.name);

            printf("Enter New Marks: ");
            scanf("%f", &s.marks);

            fseek(fp, position, SEEK_SET);
            fwrite(&s, sizeof(s), 1, fp);

            printf("Student updated successfully!\n");
            found = 1;
            break;
        }
    }

    if(!found)
        printf("Student not found!\n");

    fclose(fp);
}

void deleteStudent()
{
    struct Student s;
    int roll, found = 0;
    FILE *fp, *temp;

    printf("Enter Roll Number to delete: ");
    scanf("%d", &roll);

    fp = fopen("students.dat", "rb");

    if(fp == NULL)
    {
        printf("No records found!\n");
        return;
    }

    temp = fopen("temp.dat", "wb");

    if(temp == NULL)
    {
        printf("File error!\n");
        fclose(fp);
        return;
    }

    while(fread(&s, sizeof(s), 1, fp) == 1)
    {
        if(s.roll == roll)
        {
            found = 1;
        }
        else
        {
            fwrite(&s, sizeof(s), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    if(found)
    {
        remove("students.dat");
        rename("temp.dat", "students.dat");
        printf("Student deleted successfully!\n");
    }
    else
    {
        remove("temp.dat");
        printf("Student not found!\n");
    }
}

int main()
{
    int choice;

    do
    {
        printf("\n===== STUDENT MANAGEMENT SYSTEM =====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                printf("Exiting program...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while(choice != 6);

    return 0;
}
