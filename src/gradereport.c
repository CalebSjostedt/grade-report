/* Caleb Sjostedt
Student grade report
COP3502C */

#include <stdio.h>
#include <stdlib.h>

typedef struct student{
    int id;
    char *lname;
    float *scores;
    float stdAvg;
}student;

typedef struct course{
    char *courseName;
    int numSections;
    student **sections;
    int *numStudents;
    int *numScores;
}course;

//prototypes
course *readCourses(FILE *fp, int *numCourses);
student **readSections(FILE *fp, int numStudents[], int numScores[], int numSections);
void processCourses(course *courses, int numCourses);
void releaseCourses(course *courses, int numCourses);


void main(){
    
    int testCases, numCourses;

    //initialize opening of input file
    FILE *fp = fopen("input.txt", "r");

    if(fp == NULL){
        printf("Error! No file found!\n");
    } else {
        
        course *courses;

        fscanf(fp, "%d", &testCases); //inputs Number of testcases

        for(int i=0; i<testCases; i++){
            
            
            fscanf(fp, "%d", &numCourses); //number of courses 

            printf("test case %d\n", i+1);

            courses = readCourses(fp, &numCourses);
            processCourses(courses, numCourses);
            releaseCourses(courses, numCourses);
         

        }

    }
    fclose(fp);
}

course *readCourses(FILE *fp, int *numCourses){
  
    course *courses = malloc(sizeof(course) * (*numCourses));
    
    //loops through amount of courses in each test case
    for(int i=0; i < *numCourses; i++){
        
        //allocates mem for Course Name
        courses[i].courseName = malloc(sizeof(char) * 20);
        
        //scans course name and number of sections
        fscanf(fp, "%s", courses[i].courseName); //inputs course name 
        fscanf(fp, "%d", &courses[i].numSections); //inputs number of sections in the course

        //allocates mem for number of students/scores
        courses[i].numStudents = malloc(sizeof(int) * courses[i].numSections);
        courses[i].numScores = malloc(sizeof(int) * courses[i].numSections);
        
        //calls to readSections for use in main
        courses[i].sections = readSections(fp, courses[i].numStudents, courses[i].numScores, courses[i].numSections);

    }
    //returns struct
    return courses;
} 

student **readSections(FILE *fp, int numStudents[], int numScores[], int numSections){

    //creation of temp double pointer struct with malloc'd struct
    student **sections = malloc(sizeof(student*) * (numSections));

    //loops through sections
    for(int i=0; i < numSections; i++){
        
            //scans in number of students/scores
            fscanf(fp, "%d %d", &numStudents[i], &numScores[i]); //inputs numbers of students/scores per course section

            //allocates mem for the array inside the structs
            sections[i] = malloc(sizeof(student) * numStudents[i]);

        //loops through students
        for(int j=0; j < numStudents[i]; j++){

                //scans in student's id
                fscanf(fp, "%d", &sections[i][j].id); //int id

                //allocates memory and scans in student's name
                sections[i][j].lname = malloc(20 * sizeof(char));
                fscanf(fp, "%s", sections[i][j].lname); //inputs student's name
                
            
                //allocates mem for scores array
                sections[i][j].scores = malloc(sizeof(float) * numScores[i]);

                float sum = 0;
                
                //loops through scores
                for(int k=0; k < numScores[i]; k++){

                    fscanf(fp, "%f", &sections[i][j].scores[k]); //scans in the amount of scores per student per section
                    
                    sum += sections[i][j].scores[k]; //add all the scores for the student
                       
                }
           
            //calculates student average
            sections[i][j].stdAvg = sum / (float) numScores[i]; //averages the students course score

        }
    }
    //returns struct
    return sections;
}

void processCourses(course *courses, int numCourses){

    for(int i=0; i < numCourses; i++){
        
        //sets bestStudent to a null value to prevent seg fault
        student bestStudent = courses[i].sections[0][0];

        int passCount = 0;
        //allocates mem for sectionAvg array
        float *sectionAvg = malloc(sizeof(float) * courses[i].numSections);

        for(int j=0; j < courses[i].numSections; j++){

            float sum = 0;
            
            for(int k=0; k < courses[i].numStudents[j]; k++){
                
                //increments passCount based on students passing each section
                if(courses[i].sections[j][k].stdAvg >= 70){
                    passCount++;
                }
                
                //determines best student per course and changes data accordingly
                if(courses[i].sections[j][k].stdAvg > bestStudent.stdAvg){
                    bestStudent = courses[i].sections[j][k];
                }
                //adds section average
                sum += courses[i].sections[j][k].stdAvg;
                             
            }
            //inserts avg into array
            sectionAvg[j] = sum / (float)courses[i].numStudents[j];

        }  
        //outputs to console
        printf("%s %d ", courses[i].courseName, passCount);
        for(int l=0; l < courses[i].numSections; l++){
            printf("%.2f ", sectionAvg[l]);
        }
        free(sectionAvg);
        printf("%d %s %.2f\n", bestStudent.id, bestStudent.lname, bestStudent.stdAvg);    
    } 
}

void releaseCourses(course *courses, int numCourses){
    //loops through courses
    for(int i = 0; i < numCourses; i++){
        //loops through sections
        for(int j = 0; j < courses[i].numSections; j++){
            //loops through students
            for(int k = 0; k < courses[i].numStudents[j]; k++){
                free(courses[i].sections[j][k].scores);    
                free(courses[i].sections[j][k].lname);      
            }
            free(courses[i].sections[j]);        
        }
        free(courses[i].numScores);    
        free(courses[i].numStudents);    
        free(courses[i].courseName);   
        free(courses[i].sections);   
    }
    free(courses);   
}  