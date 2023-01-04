#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//three global variables used for the option to transfer the Lab Exam grade to the Final Exam grade
float labGrade;
float finalExamGrade;
char transfer;


//      FUNCTIONS FOR DIFFERENT GRADE GROUPS        //  

float labGrades();
float assignmentGrades();
float quizzes();
float labExam();
char transferLabExam(char);
float finalExam();


int main(){


    printf("\nThere are 5 different assessments you have to input grades for.\nLabs(20%%), Assignments(20%%), Quizzes(20%%), Lab Exam(10%%), Final Exam(30%%)\n");
    printf("\nThere are 5 Labs each worth 4%%.\n3 Assignments. Assignment 1 worth 5%%, Assignment 2 worth 7%%, and Assignment 3 worth 8%%.\n");
    printf("There are 4 quizzes each worth 5%%. One Lab Exam, and one Final Exam. \n\nYou have the choice to transfer the 10%% from your Lab Exam to the Final Exam if need be.\n");
    printf("In order to pass the class, the student must get at least 50%% in the Quizzes and Final Exam combined.\n");
    printf("However, if the student decides to transfer their Lab Exam mark to their Final Exam, 30 marks from the Final Exam section would be considered instead of 40 marks.\n");
    printf("\nThere is a plagiarism checker called SOSS, for each assignment that is flagged by SOSS, that assignment gets a 0.\n");
    printf("If all 3 assignments gets flagged by SOSS, the student receives an automatic 0 in the course\n\n");

    float totalStudentAverage = 0;//keeps track of the total student average depending on how many students there are
    char anotherStudent; // variable used to ask the user if they want to enter grades for another student
    int studentNum = 0; //counter that increments every time a student is added

    do { //do-while loop that repeats until the user doesn't want to add any more students

        studentNum++;
        float totalGrade = 0;//the total grade for that student gets reset to 0
        char courseGrade;// variable used to determine the letter grade depending on the percentage of the student's mark
        printf("\nStudent #%d\n\n",studentNum);

        //      LAB GRADES      //

        float labGrade,labAverage; //variable for function call, and the average of the lab grades
        labGrade = labGrades(); 
        totalGrade = totalGrade + labGrade; //adding towards the student's final grade
        labAverage = labGrade/0.20; //the lab grades take up 20% of the final grade so to get the average just divide by 20
        printf("\nOverall lab grade (20) = %.2f / 20\n",labGrade);
        printf("Overall lab average = %.2f%%\n",labAverage);


        //      ASSIGNMENT GRADES       //


        printf("\n");
        float assignmentGrade, assignmentAverage; //variable for function call, and the average of the assignment grades
        assignmentGrade = assignmentGrades();
        if (assignmentGrade == 0){
            totalGrade = 0;
        }
        totalGrade = totalGrade + assignmentGrade; //adding towards the student's final grade
        assignmentAverage = assignmentGrade/0.20; //the assignment grades take up 20% of the final grade so to get the average just divide by 20
        printf("\nOverall assignment grade (20) = %.2f / 20\n",assignmentGrade);
        printf("Overall assignment average = %.2f%%\n\n",assignmentAverage);


        //     QUIZ GRADES      //


        float quizGrade, quizAverage; //variable for function call, and the average of the quiz grades
        quizGrade = quizzes();
        totalGrade = totalGrade + quizGrade; //adding towards the student's final grade
        quizAverage = quizGrade/0.20;
        printf("Overall quiz grade (20) = %.2f / 20\n",quizGrade);
        printf("Overall quiz average = %.2f%%\n",quizAverage);


        //      LAB EXAM        //


        float finalLabGrade;
        finalLabGrade = labExam();
        totalGrade = totalGrade + finalLabGrade; //adding towards the student's final grade
        printf("\nOverall lab grade (10) = %.2f / 10\n\n",finalLabGrade);


        //      TRANSFER LAB EXAM GRADE     //


        do { //do-while loop that repeats until the user has entered either 'y' or 'n'

            printf("Would you like to transfer the weight of the lab exam to your final exam?\nThis will make your final exam worth 40%% (y/n): ");
            getchar();
            scanf(" %c",&transfer);

            if (transfer == 'y'){//if the user wants to transfer the grades, the Lab Exam grade gets subtracted from the students current grade
                totalGrade = totalGrade - finalLabGrade;
                break;
            }
            else if (transfer == 'n'){
                break;
            }

            else {//if (transfer != 'y' && transfer != 'n'){
                printf("You did not select a valid option\n\n");
            }

        }while(transfer != 'y' && transfer != 'n');

        transferLabExam(transfer);//function call depending on the user's input


        //      FINAL EXAM      // 


        float finalExamMark;
        float finalExamAverage;
        finalExamMark = finalExam();
        totalGrade = totalGrade + finalExamMark;//adding towards the student's final grade

        if (transferLabExam(transfer) == 'y'){//if the student transferred the Lab Exam to the Final Exam, the final exam should be calculated out of 40
            finalExamAverage = finalExamMark / 0.40; 
            printf("Overall Final Exam grade (40) = %.2f / 40\n",finalExamMark);
            printf("Average Final Exam grade = %.2f\n\n",finalExamAverage);
            
        }

        else {
            finalExamAverage = finalExamMark / 0.30;
            printf("Overall final exam grade (30) = %.2f / 30\n",finalExamMark);
            printf("Average Final Exam grade = %.2f%%\n\n",finalExamAverage);
            
        }

        //      DETERMINING THE LETTER GRADE        //

        switch ((int)totalGrade/10)
        {
            //if the average is an 80 or above the student gets an A
            case 10:
            case 9:
            case 8:
                courseGrade = 'A';
                break;
            //if the average is between the range of 70-79 the student gets a B
            case 7: 
                courseGrade = 'B';
                break;
            //if the average is between the range of 60-69 the student gets a C
            case 6:
                courseGrade = 'C';
                break;
            //if the average is between the range of 50-59 the student gets a D
            case 5:
                courseGrade = 'D';
                break;
            //if the average is lower than a 50, the student gets an F
            default:
                courseGrade = 'F';
                break;
        }


        //      PRINTING GRADES     //  


        if (transfer == 'n'){
            if ((quizGrade + finalExamMark) < 25){
                printf("Quizzes + Final Exam = %.2f + %.2f = %.2f (< 25)\n\n",quizGrade,finalExamMark,quizGrade + finalExamMark);
            }
            else {
                printf("Quizzes + Final Exam = %.2f + %.2f = %.2f (>= 25)\n\n",quizGrade,finalExamMark,quizGrade + finalExamMark);
            }

            printf("Overall Course Marks (%%)\n");

            for (int i = 0; i < 25;i++) printf("*");
            printf("\nLabs = %.2f\n",labGrade);
            printf("Assignments = %.2f\n",assignmentGrade);
            printf("Quizzes = %.2f\n",quizGrade);
            printf("Lab Exam = %.2f\n",finalLabGrade);
            printf("Final Exam = %.2f\n",finalExamMark);
            for (int i = 0; i < 25;i++) printf("*");


            if (assignmentGrade == 0){
                totalGrade = 0;
                printf("\nAll 3 assignments have been flagged for plagiarism.\n\n");
                printf("Your overall course grade = %.2f%%\n",totalGrade); 
                printf("Overall Grade = F\n"); 
            }

            printf("\n\nYour overall course grade = %.2f%%\n",totalGrade);
            printf("Overall Grade = %c\n",courseGrade); 

        }
        else { //even though the Final Exam grade was transferred to 40%, the 30% of the final exam part in the quiz + final exam check is still
               //considered preferred to the 40%. So it is taking 4/3 of the 40% final exam mark to calculate the quiz + final exam mark.
            if ((quizGrade + (finalExamMark / 1.333)) < 25){
                printf("Quizzes + Final Exam = %.2f + %.2f = %.2f (< 25)\n\n",quizGrade,finalExamMark / 1.333, quizGrade + finalExamMark / 1.333);
            }
            else {
                printf("Quizzes + Final Exam = %.2f + %.2f = %.2f (>= 25)\n\n",quizGrade,finalExamMark / 1.333, quizGrade + finalExamMark / 1.333);
            }

            printf("Overall Course Marks (%%)\n");

            //      PRINTS THE MARK % IN EACH ASSESSMENT        //


            for (int i = 0; i < 25;i++) printf("*");//for loop to print stars
            printf("\nLabs = %.2f\n",labGrade);
            printf("Assignments = %.2f\n",assignmentGrade);
            printf("Quizzes = %.2f\n",quizGrade);
            printf("Final Exam = %.2f\n",finalExamMark);
            for (int i = 0; i < 25;i++) printf("*");

            if (assignmentGrade == 0){
                totalGrade = 0;
                printf("\nAll 3 assignments have been flagged for plagiarism.\n\n");
                printf("Your overall course grade = %.2f%%\n",totalGrade); 
                printf("Overall Grade = F\n"); 
            }

            else{
                printf("\n\nYour overall course grade = %.2f%%\n",totalGrade); 
                printf("Overall Grade = %c\n",courseGrade); 
            }

        }
        //totalGrade gets added to totalStudentAverage so that it keeps a track of all the students' total mark. Then gets divided by the 
        //number of students to get the average
        totalStudentAverage = totalStudentAverage + totalGrade;
        totalStudentAverage = totalStudentAverage/studentNum;

        

        //prompt that asks the user whether they want to continue or not
        printf("\nWould you like to continue (y/n)? ");
        getchar();
        scanf("%c",&anotherStudent);

    }while(anotherStudent == 'y');

    //prints the average course mark of how ever many students
    printf("\nAverage course mark of %d students = %.2f%%\n",studentNum,totalStudentAverage);


    return 0;
}



float labGrades(){
    float grades[5];//an array with 5 elements to store each of the grades
    float totalLabGrade = 0;//variable to hold the total lab grade out of 20
    printf("Enter 5 lab grades, each separated by a space: ");
    for (int i = 0; i < 5;i++){
        scanf("%f",&grades[i]);
        totalLabGrade = totalLabGrade + grades[i];
    }
    totalLabGrade = ((totalLabGrade/5)*0.20);
    return totalLabGrade;

}


float assignmentGrades(){
    float a1,a2,a3; //3 variables used to hold the grade for each assignment
    int s1,s2,s3;
    float totalAssignmentGrade = 0;


    printf("Enter the grades for the 3 assignments followed by a space: ");
    scanf("%f%f%f",&a1,&a2,&a3);
    printf("Enter the SOSS result for assignment 1: ");
    scanf("%d",&s1);
    printf("Enter the SOSS result for assignment 2: ");
    scanf("%d",&s2);
    printf("Enter the SOSS result for assignment 3: ");
    scanf("%d",&s3);


    //SOSS checker, if it was flagged, that assignment gets an automatic 0
    if (s1 == 0){
        a1 = 0;
    }
    if (s2 == 0){
        a2 = 0;
    }
    if (s3 == 0){
        a3 = 0;
    }

    if (s1 == 0 && s2 == 0 && s3 == 0){
        totalAssignmentGrade = 0;
    }

    totalAssignmentGrade = ((a1*0.05)+(a2*0.07)+(a3*0.08));

    //if all 3 assignments get flagged for plagiarism, the student automatically fails the course
    if (s1 == 0 && s2 == 0 && s3 == 0){
        totalAssignmentGrade = 0;
    }
    return totalAssignmentGrade;
}


float quizzes(){
    float quiz[4];
    float totalQuizMarks = 0;

    printf("Enter 4 Quiz marks each separated by a space: ");
    for (int i = 0; i < 4;i++){
        scanf("%f",&quiz[i]);
        totalQuizMarks = totalQuizMarks + quiz[i]*0.05;
    }
    return totalQuizMarks;

}


float labExam(){
    printf("\nEnter the mark for the Lab Exam: ");
    scanf("%f",&labGrade);

    return labGrade * 0.10;
}


char transferLabExam(char transfer){
    if (transfer == 'y'){
        labGrade = 0;
        printf("\nYour Lab Exam is now worth 0 and the Final Exam is worth 40%%\n");
        return 'y';
    }
    else {
        printf("\nYour Lab Exam is worth 10%% and the Final Exam is worth 30%%\n");
        return 'n';
    }

}


float finalExam(){
    printf("Enter the Final Exam grade: ");
    scanf("%f",&finalExamGrade);

    if (transferLabExam(transfer) == 'y'){
        finalExamGrade = finalExamGrade*0.40;
        return finalExamGrade;
    }
    else{
        finalExamGrade = finalExamGrade * 0.30;
        return finalExamGrade;
    }
}
