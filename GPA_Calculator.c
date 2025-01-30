#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Semester
{
    int numCourses;
    float *courseCredits;
    char **grades;
    float SGPA;
};

float gradeToPoint(char *grade)
{
    if (strcmp(grade, "A+") == 0)
        return 4.3;
    if (strcmp(grade, "A") == 0)
        return 4.0;
    if (strcmp(grade, "A-") == 0)
        return 3.7;
    if (strcmp(grade, "B+") == 0)
        return 3.3;
    if (strcmp(grade, "B") == 0)
        return 3.0;
    if (strcmp(grade, "B-") == 0)
        return 2.7;
    if (strcmp(grade, "C+") == 0)
        return 2.3;
    if (strcmp(grade, "C") == 0)
        return 2.0;
    if (strcmp(grade, "C-") == 0)
        return 1.7;
    if (strcmp(grade, "D+") == 0)
        return 1.3;
    if (strcmp(grade, "D") == 0)
        return 1.0;
    if (strcmp(grade, "D-") == 0)
        return 0.7;
    if (strcmp(grade, "F") == 0)
        return 0.0;
    return -1.0;
}

int main()
{

    char name[100], usn[20];

    printf("Enter your Name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    printf("Enter your USN: ");
    fgets(usn, sizeof(usn), stdin);
    usn[strcspn(usn, "\n")] = 0;

    FILE *file = fopen("grades_summary.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file for writing.\n");
        return 1;
    }

    fprintf(file, "Name: %s\n", name);
    fprintf(file, "USN: %s\n\n", usn);

    printf("A+ = 4.3 grade points \n A = 4 grade points \n A- = 3.7 grade points \n B+ = 3.3 grade points \n B = 3 grade points \n B- = 2.7 grade points \n C+ = 2.3 grade points \n C = 2 grade points \n C- = 1.7 grade points \n D+ = 1.3 grade points \n D = 1 grade point \n D- = 0.7 grade points \n F = 0 grade points \n");

    const int numSemesters = 8;
    struct Semester semesters[numSemesters];

    for (int i = 0; i < numSemesters; i++)
    {
        printf("\nSemester %d\n", i + 1);

        fprintf(file, "Semester %d\n", i + 1);

        printf("Enter the number of courses: ");
        scanf("%d", &semesters[i].numCourses);

        semesters[i].courseCredits = (float *)malloc(semesters[i].numCourses * sizeof(float));
        semesters[i].grades = (char **)malloc(semesters[i].numCourses * sizeof(char *));

        float totalCredits = 0, weightedGradePoints = 0;

        for (int j = 0; j < semesters[i].numCourses; j++)
        {
            semesters[i].grades[j] = (char *)malloc(3 * sizeof(char));

            printf("Enter credits for course %d: ", j + 1);
            scanf("%f", &semesters[i].courseCredits[j]);

            printf("Enter grade for course %d : ", j + 1);
            scanf("%s", semesters[i].grades[j]);

            float gradePoint = gradeToPoint(semesters[i].grades[j]);
            if (gradePoint >= 0)
            {
                totalCredits += semesters[i].courseCredits[j];
                weightedGradePoints += gradePoint * semesters[i].courseCredits[j];
            }
        }

        if (totalCredits > 0)
        {
            semesters[i].SGPA = weightedGradePoints / totalCredits;
        }
        else
        {
            semesters[i].SGPA = 0;
        }

        printf("SGPA for Semester %d: %.2f\n", i + 1, semesters[i].SGPA);
        fprintf(file, "SGPA: %.2f\n\n", semesters[i].SGPA);
    }

    float totalSGPA = 0, totalSemesterCredits = 0;
    for (int i = 0; i < numSemesters; i++)
    {
        float semesterCredits = 0;
        for (int j = 0; j < semesters[i].numCourses; j++)
        {
            semesterCredits += semesters[i].courseCredits[j];
        }

        totalSGPA += semesters[i].SGPA * semesterCredits;
        totalSemesterCredits += semesterCredits;
    }

    float CGPA = totalSemesterCredits > 0 ? totalSGPA / totalSemesterCredits : 0;
    printf("\nOverall CGPA: %.2f\n", CGPA);
    fprintf(file, "Overall CGPA: %.2f\n", CGPA);

    fclose(file);

    for (int i = 0; i < numSemesters; i++)
    {
        for (int j = 0; j < semesters[i].numCourses; j++)
        {
            free(semesters[i].grades[j]);
        }
        free(semesters[i].grades);
        free(semesters[i].courseCredits);
    }

    return 0;
}
