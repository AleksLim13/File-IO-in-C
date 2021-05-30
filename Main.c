
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

struct course {
    char courseId[255];
    int credit;
    float grade;
};

struct courseString {
    char courseId[255];
    char credit[255];
    char grade[255];
};

struct stringArray {
    char sub[255];
};

struct integerArray {
    int credits;
};

struct floatArray {
    float grades;
};

//Define: C sub-string function definition. Fully functional - 1:04 am May 22, 2021. [X]

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


//Report: this is fully working - 5:23pm May 20, 2021. [X]

float WhosBigger(float num1, float num2) {

    //A: Check
    if (num1 > num2) {
        //B:Copy
        return num1;
    }//End I:*

    //C: Copy
    return num2;

}//End M:*

//Report: this is fully working - 5:23pm May 20, 2021. [X]

int DisplayMenu() {
    //A: Declare
    int userChoice;

    //B: Notify
    printf("Welcome to student progress services \n"
            "Each menu option is indicated by a certain number as input\n"
            "1: Max Grade, 2: Modify Grade, 3: Compute GPA, 4: Save All\n");

    //C: Read
    scanf("%d", &userChoice);

    //D: Copy
    return userChoice;

}//End M:*


//Report: this is fully working - 5:23pm May 20, 2021. [X]

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


//Report: this is fully working - 5:41pm May 20, 2021. [X]

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


//Report: this is fully working - 5:23pm May 20, 2021. [X]

void ComputeGPA(struct course cList[MAX_COURSES]) {
    
    //A: Declare:
    int i;
    float sum = 0.0;
    
    //B: Add:
    for(i = 0; i < MAX_COURSES; i++){
        sum +=  cList[i].grade;
    }//End F:*
    
    //C: Divide.
    float result = sum / MAX_COURSES;

    //D: Notify.
    printf("GPA or Average = %f", result);

}//End M:*

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

int ClearFile(FILE *fptr, char fileName[255]) {

    //Open: open the file in write mode
    fptr = fopen(fileName, "w");

    //D.0: Close:  connection
    fclose(fptr);

    return 0;

}//End M:*

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


//Report: Fully Functional [X]
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

void growStrArray(struct stringArray sTarg[12]) {

}//End M:*

void growIntArray(struct stringArray iTarg[12]) {

}//End M:*

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

 char* FormatBeforeSaving(struct course cList[MAX_COURSES], int row) {

    char resulty[255];
    //Notice: don't add square brackets
    char *finalist;
    char grade[255];
    char credit[255];
            
   //notice: 255 is bytes and matches the var we set aside above. 
    strncpy(resulty, "credit:", 255);

    //Convert: float and integer to string.
    sprintf(credit, "%d", cList[row].credit);
    sprintf(grade, "%f", cList[row].grade);
  
    credit[1] = '\0';
    grade[4] = '\0';
    cList[row].courseId[9] = '\0';
    
    strlcat(resulty, credit, 255);
    
    strlcat(resulty, ",", 255);
    
    strlcat(resulty, "grade:", 255);
    strlcat(resulty, grade, 255);
    strlcat(resulty, ",", 255);
    strlcat(resulty, "courseid:", 255);
    strlcat(resulty, cList[row].courseId, 255);
    strlcat(resulty, ",", 255);

    resulty[39] = '\0';
 
    finalist = resulty;
    
    return finalist;
}//End M:*

//Define: concatenate all records to one line then write to output file. Fully Functional - 7:48pm - May 23, 2021. [X]

int AppendFile(FILE *fptr, char fileName[255], struct course cList[MAX_COURSES]) {

    char *record;
   
    int i;
    
    //Open: open the file in write mode
    fptr = fopen(fileName, "a");
     
    char resulty[255];
    
    for(i = 0; i < MAX_COURSES; i++){
        record = FormatBeforeSaving(cList, i);
        strncpy(resulty, record, 255);
        fprintf(fptr, "%s", resulty);
        fprintf(fptr, "\n");
    }//End F:*
       
    //D.0: Close:  connection
    fclose(fptr);

    return 0;

}//End M:*

//Notice: Program starts in this function.

int main() {

    struct course cList[MAX_COURSES];

    FILE *fptr;

    struct stringArray* pRecords;
    
    pRecords = ReadFile(fptr, "newstudent.txt", MAX_COURSES);
    
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
  
  
    bool flag = true;
    int uChoice;
    float uChoiceFloat;
    char courseToApply[255];
    
    
      while (flag) {

        printf("\n");
        printf("1: Max Grade, 2: Modify Grade, 3: GPA Calculator, 4: Save All, 5: Quit\n");
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

            ClearFile(fptr, "newstudent.txt");
            AppendFile(fptr, "newstudent.txt", cList);
            printf("\n");
        }//End I:*

        else if (uChoice == 5) {
            flag = false;
        }//End I:*

        else {
            printf("Options range from 1-5 as integer values");
        }//End E:*

    }//End W:*
   
    return 0;

}//End M:*

