/*
 Program: student progress services application through list data structure implementation.
 Author: Aleksandar Lim - 991260070
 College: Sheridan College 
 Date: June 2, 2021
 Class: Prog20799
 Semester: Spring/Summer 2021
 Purpose: Assignment 1
 
 
 */
 
#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_COURSES 4
#define MAX_ITEMS 3
#define MAX_CREDIT_LENGTH 1
#define MAX_GRADE_LENGTH 4
#define MAX_CID_LENGTH 9
#define MAX_REC_LENGTH 38

//Define: data relevant to a college course
struct course {
    char courseId[255];
    int credit;
    float grade;
};

//Define: string representation for data per a courses for conversions
struct courseString {
    char courseId[255];
    char credit[255];
    char grade[255];
};

//Define: simulates a string array when many of these are stored in a array
struct stringArray {
    char sub[255];
};

//Define: simulates a integer array when many of these are stored in a array
struct integerArray {
    int credits;
};

//Define: simulates a float array when many of these are stored in a array
struct floatArray {
    float grades;
};


//Define: C sub-string function that takes 4 parameters
void substring(char chunk[], char sub[], int chunkStart, int length) {

    int i;
    int subStart = 0;

    for (i = 0; i < length; i++) {
        sub[subStart] = chunk[chunkStart];
        subStart++;
        chunkStart++;
    }//End F:*

    sub[length] = '\0';

}//End M:*

//Define: using file name and opening it in write mode creates file in same folder as this source file.
int CreateFile(FILE *fptr, char fileName[255]) {

    //Open: open the file in write mode
    fptr = fopen(fileName, "w");

    //Check:
    if (fptr != NULL) {
        printf("File created successfully!\n");
    }//End I:*

        //Alternate:
    else {

        //Notify:
        printf("Failed to create the file.\n");

        // exit status for OS that an error occurred

        //Report:
        return -1;

    }//End E:*

    return 0;

}//End M:*

//Report: takes in 2 numbers and returns biggest one

float WhosBigger(float num1, float num2) {

    //A: Check
    if (num1 > num2) {
        //B:Copy
        return num1;
    }//End I:*

    //C: Copy
    return num2;

}//End M:*


//Define: iterates course array, stores grades in new float array then shuffles it from smallest to largest.
//Define: largest is at end of array.
float MaxGrade(struct course cList[MAX_COURSES]) {
    //A: Compare

    int i, j, k;
    float grades[MAX_COURSES];

    for (i = 0; i < MAX_COURSES; i++) {
        grades[i] = cList[i].grade;
    }//End F:*

    for (i = 0; i < MAX_COURSES; i++) {
      
        for (j = i + 1; j < MAX_COURSES; j++) {
            if(grades[j] < grades[i]){
                float temp = grades[j];
                grades[j] = grades[i];
                grades[i] = temp; 
            }//End I:*
        }//End F:*
    }//End F:*

    //B: Compare
    float result = grades[MAX_COURSES - 1];

    //C: Copy
    return result;

}//End M:*


void DisplayAll(struct course cList[MAX_COURSES]){
    
    int i;
    for(i = 0; i < MAX_COURSES; i++){
        printf("Course Id: ");
        printf("%s", cList[i].courseId);
        printf("\n");
        printf("Credit: ");
        printf("%d", cList[i].credit);
        printf("\n");
        printf("Grade: ");
        printf("%f", cList[i].grade);
        printf("\n");
    }//End F:*

}//End M:*


//Report: Takes in new grade and program name then loops course array to find match and then updates grade.

void ModifyGrade(struct course cList[MAX_COURSES], float grade, char cName[255]) {
    int i;

    for (i = 0; i < MAX_COURSES; i++) {

        int valueCheck = strcmp(cName, cList[i].courseId);

        if (valueCheck == 0) {
            cList[i].grade = grade;
            printf("New Grade = %f", cList[i].grade);
        }//End I:*

    }//End F:*

}//End M:*


//Define: Open file when given name as string and if in write mode will clear data once in it.
int ClearFile(FILE *fptr, char fileName[255]) {

    //Open: open the file in write mode
    fptr = fopen(fileName, "w");

    //D.0: Close:  connection
    fclose(fptr);

    return 0;

}//End M:*


//Define: while loop uses FGETS to read one line a time and stores each in a simulated array that gets returned.
struct stringArray* ReadFile(
        FILE *fptr,
        char fileName[255], 
        int size
        ) {

    struct stringArray records[size];
    struct stringArray *pRecords;
    
    //B.0: Open: open file for reading: all records on same line separated by comma.
    fptr = fopen(fileName, "r");
    int counter = 0;

    while (fgets(records[counter].sub, 255, fptr) != NULL) {
        counter++;
    }//End W:*
    
    pRecords = records;
  
    //D.0: Close: connection
    fclose(fptr);

    return pRecords; 
    
}//End M:*


//Report: gets position of comma and colon two extract data items to a string course STRUCT and then returns it.
struct courseString GetRecord(
        struct stringArray records[MAX_COURSES],
        int row
        ) {

    int i;
    
    int colonCreditPos;
    int commaCreditPos;
    
    int colonGradePos;
    int commaGradePos;
    
    int colonCIdPos;
    int commaCIdPos;
    
    char colon[255] = ":";
    char comma[255] = ",";

    struct courseString singleRecord;
    
    char credita[255];
    char grady[255];
    char cIda[255];
    
    int lenny = strlen(records[row].sub);

    //Get: colon start position as integer
    for (i = 0; i < lenny; i++) {
        if (records[row].sub[i] == colon[0]) {
            colonCreditPos = i;         
            break;
        }//End I:*
    }//End F:*

    //Get: ending comma position as integer
    for (i = 0; i < lenny; i++) {
        if (records[row].sub[i] == comma[0]) {
            commaCreditPos = i;
            break;
        }//End I:*
    }//End F:*
    
   
    //Extract: credit item as sub-string of full line of text
    for (i = colonCreditPos + 1; i < commaCreditPos; i++) {
        credita[0] = records[row].sub[i];
    }//End F:*
    
   
    //Get: starting colon position as integer
    for (i = commaCreditPos + 1; i < lenny; i++) {
        if (records[row].sub[i] == colon[0]) {
            colonGradePos = i;
            break;
        }//End I:*
    }//End F:*

    //Get: ending comma position as integer
    for (i = commaCreditPos + 1; i < lenny; i++) {
        if (records[row].sub[i] == comma[0]) {
            commaGradePos = i;
            break;
        }//End I:*
    }//End F:*
    
    int gradeCount = 0;
    //Extract: grade item as sub-string of full line of text
    for (i = colonGradePos + 1; i < commaGradePos; i++) {
        grady[gradeCount] = records[row].sub[i];
        gradeCount++;
    }//End F:*
    
    //Get: colon position as integer.
    for (i = commaGradePos + 1; i < lenny; i++) {
        if (records[row].sub[i] == colon[0]) {
            colonCIdPos = i;
            break;
        }//End I:*
    }//End F:*

    //Get: Ending comma position as integer
    for (i = commaGradePos + 1; i < lenny; i++) {
        if (records[row].sub[i] == comma[0]) {
            commaCIdPos = i;
            break;
        }//End I:*
    }//End F
    
    int cIdCount = 0;
    //Extract: c id item as sub-string of full line of text
    for (i = colonCIdPos + 1; i < MAX_REC_LENGTH; i++) {
        cIda[cIdCount] = records[row].sub[i];
        cIdCount++;
    }//End F:*
   
    char cleanCred[255];
    char cleanGrade[255];
    char cleanCId[255];
    
    for(i = 0; i < 1; i++){
        cleanCred[i] = credita[i];
    }//End F:*
    
    for(i = 0; i < 4; i++){
        cleanGrade[i] = grady[i];
    }//End F:*
    
    for(i = 0; i < 9; i++){
        cleanCId[i] = cIda[i];
    }//End F:*
    
    cleanCred[1] = '\0';
    cleanGrade[4] = '\0';
    cleanCred[9] = '\0';
    
    strncpy(singleRecord.credit, cleanCred, 255);
    strncpy(singleRecord.grade, cleanGrade, 255);
    strncpy(singleRecord.courseId, cleanCId, 255);
    
    return singleRecord; 

}//End M:*

//Define: under construction. Going to check capacity of array and then multiple it by two to simulate resizing a array.
void growStrArray(struct stringArray sTarg[12]) {

}//End M:*

//Define: under construction. Going to check capacity of array and then multiple it by two to simulate resizing a array.
void growIntArray(struct stringArray iTarg[12]) {

}//End M:*

//Define: Takes in array of records as each line a record and converts and populates proper course array for further data processing.
struct course* FillCourseArray(struct stringArray records[MAX_COURSES]) {
    
   struct course cList[MAX_COURSES];
   struct courseString cListString[MAX_COURSES];
   struct course* resultCList;
   int credits[MAX_COURSES];
   float grades[MAX_COURSES];
   
   int i;
   
   for(i = 0; i < MAX_COURSES; i++){
      cListString[i] = GetRecord(records, i);
   }//End F:*
   
   for(i = 0; i < MAX_COURSES; i++){
       credits[i] = atoi(cListString[i].credit);
       cList[i].credit = credits[i];
   }//End F:*
   
   for(i = 0; i < MAX_COURSES; i++){
       grades[i] = atof(cListString[i].grade);
       cList[i].grade = grades[i]; 
   }//End F:*
  
   //Recall: 3rd parameter in STRNCPY is byte size that matches the var your declared. not length of characters. Lost time here...
   for(i = 0; i < MAX_COURSES; i++){
       strncpy(cList[i].courseId, cListString[i].courseId, 255);
   }//End F:*
   
   resultCList = cList; 
   
   return resultCList; 
   
}//End M:*



//Define: 



float GetGradePoint(float grade){
    float result = 0.0;
    
    if(grade >= 90.0 && grade <= 100.0){
        result = 4.0;
    }//End I:*
    else if(grade >= 85.0 && grade <= 89.0){
        result = 3.8;
    }//End I:*
    else if(grade >= 80.0 && grade <= 84.0){
        result = 3.6;
    }//End I:*
    else if(grade >= 75.0 && grade <= 79.0){
        result = 3.3;
    }//End I:*
    else if(grade >= 70.0 && grade <= 74.0){
        result = 3.0;
    }//End I:*
    else if(grade >= 65.0 && grade <= 69.0){
        result = 2.5;
    }//End I:*
    else if(grade >= 60.0 && grade <= 64.0){
        result = 2.0;
    }//End I:*
    else if(grade >= 50.0 && grade <= 54.0){
        result = 1.0;
    }//End I:*
    else if(grade >= 0.0 && grade <= 49.0){
        result = 0.0;
    }//End I:*
    return result;
}//End F:*

//Report: Iterates course array and adds grades then divides by amount of grades and prints result.

int ComputeGPA(struct course cList[MAX_COURSES]) {
    
    float sumOfPointsByCredits;
    int i;
    float finalist;
    int sumCredits;
    
    for(i = 0; i < MAX_COURSES; i++){
        sumOfPointsByCredits += (GetGradePoint(cList[i].grade) * cList[i].credit);
        sumCredits += cList[i].credit;
    }//End F:*
    
    finalist = sumOfPointsByCredits / sumCredits;
     
    printf("GPA or Average = %f", finalist);

    return 0;
}//End M:*

//Define: overall algorithm of program. Main use cases in here. 


char* FloatToString(float target){
    
    //Declare: pointer and char equivalent 
    char* pResult;
    char result[255];
    
    //Convert: to truncate the remainder.
    int conv = (int)target;
    
    //Get: the remainder and save it.
    float remain = target - conv;
    
    //Format: move the digit we want before decimal
    float pushDecimal = remain * 10;
    
    //Convert: so we get the digit by itself. 
    int finalRemain = (int)pushDecimal;
    
    //Declare: a holder for our swaps.
    int numAr[4];
    
    //Extract: each digit and store each in a array
    int i;
    for(i = 0; i < 2; i++){
         int stripper = conv % 10;
         numAr[i] = stripper;
         conv = conv / 10;
    }//End F:*
    
    //Reverse: their backward so swap with a temp var
    int tempest = numAr[0];
    numAr[0] = numAr[1];
    numAr[1] = tempest;
    
    //Evaluate: check with 0-9 range then assign appropriate string version.
    for(i = 0; i < 2; i++){
      if(numAr[i] == 0){
          result[i] = '0';
      }//End I:*  
      else if(numAr[i] == 1){
          result[i] = '1';
      }//End I:*  
       else if(numAr[i] == 2){
          result[i] = '2';
      }//End I:*  
       else if(numAr[i] == 3){
          result[i] = '3';
      }//End I:*  
       else if(numAr[i] == 4){
          result[i] = '4';
      }//End I:*  
       else if(numAr[i] == 5){
          result[i] = '5';
          
      }//End I:*  
       else if(numAr[i] == 6){
          result[i] = '6';
      }//End I:*  
      
       else if(numAr[i] == 7){
          result[i] = '7';
      }//End I:*  
       else if(numAr[i] == 8){
          result[i] = '8';
      }//End I:*  
       else if(numAr[i] == 9){
          result[i] = '9';
      }//End I:*  
      
    }//End F:*
    
    //Insert: The decimal back in the right position 
    result[2] = '.';
    
    //Check: the remainder against a range of base 10 numbers that make up all numbers.
     if(finalRemain == 0){
          result[3] = '0';
      }//End I:*  
     else if(finalRemain == 1){
          result[3] = '1';
      }//End I:*  
     else if(finalRemain == 2){
          result[3] = '2';
      }//End I:*  
       else if(finalRemain == 3){
          result[3] = '3';
      }//End I:*  
       else if(finalRemain == 4){
          result[3] = '4';
      }//End I:*  
       else if(finalRemain == 5){
          result[3] = '5';      
      }//End I:*  
       else if(finalRemain == 6){
          result[3] = '6';
      }//End I:*  
       else if(finalRemain == 7){
          result[3] = '7';
      }//End I:*  
       else if(finalRemain == 8){
          result[3] = '8';
      }//End I:*  
       else if(finalRemain == 9){
          result[3] = '9';
      }//End I:*  
    
    //Assign: the char result as conversion to a pointer so we can return it. 
    pResult = result;
    
    //Copy: bring it back now.
    return pResult; 
}//End M:*

char* IntToString(int target){
    
    char* pResult;
    
    
      if(target == 0){
          pResult = "0";     
      }//End I:*  
    
      else if(target == 1){
          pResult = "1";
      }//End I:*
    
       else if(target == 2){
          pResult = "2";
         
      }//End I:*
    
       else if(target == 3){
           
          pResult = "3";
         
      }//End I:*  
    
       else if(target == 4){
          pResult = "4";
       
      }//End I:*  
    
       else if(target == 5){
          pResult = "5";
        
      }//End I:*  
    
       else if(target == 6){
          pResult = "6";
       
      }//End I:*  
    
       else if(target == 7){
          pResult = "7";
       
      }//End I:*  
    
       else if(target == 8){
          pResult = "8";
          
      }//End I:*  
    
       else if(target == 9){
          pResult = "9";
         
      }//End I:*  
      
    return pResult;
    
}//End M:*

char* CustomConcat(char* appendedTo, char* theAppended){
    
    //Declare holder and pointer for result.
     char* pResult;
     char result[255];
     
    int lenny1 = strlen(appendedTo);
    int lenny2 = strlen(theAppended);
    int fullL = lenny1 + lenny2;
     
    int i;
    
    for(i = 0; i < lenny1; i++){
        result[i] = appendedTo[i];
    }//End F:*
    
    for(i = 0; i < lenny2; i++){
        result[lenny1] = theAppended[i];
        lenny1++;
    }//End F:*
    
    result[fullL] = '\0';
    
    pResult = result;
     
    return pResult;
  
}//End M:*


//Define: Before saving, we need labels for each data item and colon and comma for when the file is read later on in next app run.
 char* FormatBeforeSaving(struct course cList[MAX_COURSES], int row) {

    //Notice: don't add square brackets
    char* finalist = "credit:";
 
    //Convert: float and integer to string.
    
    char* creditConv = IntToString(cList[row].credit);
    
    //char* pCredConv = &creditConv; Remember this piece. 
    
    char* gradeConv = FloatToString(cList[row].grade);
         
    cList[row].courseId[9] = '\0';
    
    finalist = CustomConcat(finalist, creditConv);
    
    finalist = CustomConcat(finalist, ",");
     
    finalist = CustomConcat(finalist, "grade:");
    
    finalist = CustomConcat(finalist, gradeConv);
    
    finalist = CustomConcat(finalist, ",");
  
    finalist = CustomConcat(finalist, "courseid:");
    
    finalist = CustomConcat(finalist, cList[row].courseId);
    
    finalist = CustomConcat(finalist, ",");
    
    return finalist;
    
}//End M:*

 //Define: this calls format before method then appends each line as record as string to desired file.
int AppendFile(FILE *fptr, char fileName[255], struct course cList[MAX_COURSES]) {

    char *singleRecord;
    char resulty[255];
   
    int i;
    
    //Open: open the file in write mode
    fptr = fopen(fileName, "a");
         
    for(i = 0; i < MAX_COURSES; i++){
        singleRecord = FormatBeforeSaving(cList, i);
        strncpy(resulty, singleRecord, 255);
        fprintf(fptr, "%s", resulty);
        fprintf(fptr, "\n");
    }//End F:*
       
    //D.0: Close:  connection
    fclose(fptr);

    return 0;

}//End M:*

//Define: displays menus items as matched two integers and returns user choice
int DisplayMenu(struct course cList[MAX_COURSES], FILE *fptr) {
    //A: Declare
   
    bool flag = true;
    int uChoice;
    float uChoiceFloat;
    char courseToApply[255];
    
      while (flag) {

        printf("\n");
        printf("1: Max Grade, 2: Modify Grade, 3: GPA Calculator, 4: Display All, 5: Save All, 6: Quit\n");
        scanf("%d", &uChoice);

        if (uChoice == 1) {
            printf("Max Grade = %f", MaxGrade(cList));
            printf("\n");
        }//End I:*

        else if (uChoice == 2) {
            printf("\n");
            printf("What grade do you want to replace the old one with?\n");
            scanf("%f", &uChoiceFloat);
            printf("\n");
            printf("What is the course that you want to apply the new grade to?\n");
            scanf("%s", courseToApply);

            ModifyGrade(cList, uChoiceFloat, courseToApply);
            printf("\n");

        }//End EI:*

        else if (uChoice == 3) {
            ComputeGPA(cList);
            printf("\n");
        }//End EI:*

        else if (uChoice == 4) {
            DisplayAll(cList);
        }//End I:*
        
        else if (uChoice == 5) {

            ClearFile(fptr, "grades.txt");
            AppendFile(fptr, "grades.txt", cList);
            printf("\n");
        }//End I:*

        else if (uChoice == 6) {
            flag = false;
        }//End I:*

        else {
            printf("Options range from 1-6 as integer values");
        }//End E:*

    }//End W:*

}//End M:*

int main() {

    struct course cList[MAX_COURSES];

    FILE *fptr;

    struct stringArray* pRecords;
    
    pRecords = ReadFile(fptr, "grades.txt", MAX_COURSES);
    
    struct stringArray records[MAX_COURSES];
    
    int i;
    for(i = 0; i < MAX_COURSES; i++){
        strncpy(records[i].sub, pRecords->sub, MAX_REC_LENGTH);
        pRecords++;
    }//End F:*
    
  struct course* cListPointer;    

   cListPointer = FillCourseArray(records);  
  
    for(i = 0; i < MAX_COURSES; i++){
        cList[i].credit = cListPointer->credit;
        cList[i].grade = cListPointer->grade;
        strncpy(cList[i].courseId, cListPointer->courseId, 255);
        cList[i].courseId[9] = '\0';
        cListPointer++;
    }//End F:*
  
   
    DisplayMenu(cList, fptr);
    
  
    return 0;

}//End M:*

