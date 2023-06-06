/*-------------------------------------------
Program 4: Database of Students
Course: CS 211, Spring 2023, UIC
System: Replit Windows 11
Author: Ivan Tang
Starter code provided by: Ellen Kidane
------------------------------------------- */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void clearBuffer()
{
  int c;
  do{
    c = getchar();
  } while (c != '\n' && c != EOF);
}

typedef char* String;
typedef struct {
	char* name;
	char* id;
	double gpa;
	int creditHours;
} Student;

typedef struct StudentNode{
	Student* pStudent;
	struct StudentNode* pNext;
} StudentNode;

typedef struct {
	StudentNode* pIDList;
	StudentNode* pHonorRollList;
	StudentNode* pAcademicProbationList;
	StudentNode* pFreshmanList;
	StudentNode* pSophomoreList;
	StudentNode* pJuniorList;
	StudentNode* pSeniorList;
} Database;

void printStudentNode(StudentNode* student){
  Student* pStudentTemp = student->pStudent;

  printf("%s:\n", pStudentTemp->name);
  printf("\t\t\tID - %s\n", pStudentTemp->id);
  printf("\t\t\tGPA - %.2f\n", pStudentTemp->gpa);
  printf("\t\t\tCredit Hours - %d\n\n", pStudentTemp->creditHours);
}

void printLinkedList(StudentNode* pHead, int stop){
  if(pHead == NULL){
    printf("There are no students matching that criteria.\n\n");
    return;
  }
  StudentNode* pTemp = pHead;
  int count = 0;

  while(pTemp != NULL &&  stop > count++){
    printStudentNode(pTemp);
    pTemp = pTemp->pNext;
  }
}


//dunno if this works so check at some point
void addNodes(StudentNode** pHead, StudentNode* pAdd, const char type){
  //empty linked list
  if(*pHead == NULL){
    (*pHead) = pAdd;
    return;
  }
  StudentNode* pTemp = (*pHead);

  if(type == 'n'){  //name ordered
    
    if(strcmp(pAdd->pStudent->name, pTemp->pStudent->name) < 0){  //check first node
      (*pHead) = pAdd;
      pAdd->pNext = pTemp;
      return;
    }

    
    while(pTemp->pNext != NULL){  //figure out condition if there is only one node
      if(strcmp(pAdd->pStudent->name, pTemp->pNext->pStudent->name) < 0){  //middle of list
        pAdd->pNext = pTemp->pNext;
        pTemp->pNext = pAdd;
        return;
      }
      pTemp = pTemp->pNext;
    }
    //end of list (sus logic)

    

    pAdd->pNext = pTemp->pNext;
    pTemp->pNext = pAdd;
  }
  else if(type == 'g'){ //gpa ordered
    if(pAdd->pStudent->gpa < pTemp->pStudent->gpa){  //check first node
      //printf("first node: %p | %p\n", pTemp, pTemp->pNext);
      (*pHead) = pAdd;
      pAdd->pNext = pTemp;
      return;
    }
    else if(fabs(pAdd->pStudent->gpa - pTemp->pStudent->gpa) < 0.00001){
      (*pHead) = pAdd;
      pAdd->pNext = pTemp;
      return;
    }
    int count = 0;
    while(pTemp->pNext != NULL){
      //printf("%p | %p\n", pTemp, pTemp->pNext);
      //if(++count > 15){
        //printf("broken dumbass: %p | %p\n", pTemp, pTemp->pNext);
      //  exit(-1);
      //}

      
      if(pAdd->pStudent->gpa < pTemp->pNext->pStudent->gpa){  //middle of list
        //printf("middle node: %p | %p\n", pTemp, pTemp->pNext);
        pAdd->pNext = pTemp->pNext;
        pTemp->pNext = pAdd;
        return;
      }
      else if(fabs(pAdd->pStudent->gpa - pTemp->pNext->pStudent->gpa) < 0.00001){
        pAdd->pNext = pTemp->pNext;
        pTemp->pNext = pAdd;
        return;
      }
      pTemp = pTemp->pNext;
    }
    //end of list

    //printf("end of list: %p | %p", pTemp, pTemp->pNext);
    pAdd->pNext = pTemp->pNext;
    pTemp->pNext = pAdd;
  }
  else{
      
    if(strcmp(pAdd->pStudent->id, pTemp->pStudent->id) < 0){  //check first node
      (*pHead) = pAdd;
      pAdd->pNext = pTemp;
      return;
    }

    
    while(pTemp->pNext != NULL){  //figure out condition if there is only one node
      if(strcmp(pAdd->pStudent->id, pTemp->pNext->pStudent->id) < 0){  //middle of list
        pAdd->pNext = pTemp->pNext;
        pTemp->pNext = pAdd;
        return;
      }
      pTemp = pTemp->pNext;
    }
    //end of list (sus logic)

    

    pAdd->pNext = pTemp->pNext;
    pTemp->pNext = pAdd;
  }
  
}

void removeFromLinkedList(Database* bank, String id){
  StudentNode* pTemp = bank->pIDList;

  for(int iteration = 0; iteration < 7; iteration++){
    if     (iteration == 0)  pTemp = bank->pIDList;
    else if(iteration == 1)  pTemp = bank->pHonorRollList;
    else if(iteration == 2)  pTemp = bank->pAcademicProbationList;
    else if(iteration == 3)  pTemp = bank->pFreshmanList;
    else if(iteration == 4)  pTemp = bank->pSophomoreList;
    else if(iteration == 5)  pTemp = bank->pJuniorList;
    else if(iteration == 6)  pTemp = bank->pSeniorList;


    
    if(pTemp == NULL){  //nothing in l=the list
      continue;
    }
    else if(pTemp->pNext == NULL && strcmp(pTemp->pStudent->id, id) == 0){  //one node in list
      free(pTemp);
      
      if     (iteration == 0)  bank->pIDList = NULL;
    else if(iteration == 1)  bank->pHonorRollList = NULL;
    else if(iteration == 2)  bank->pAcademicProbationList = NULL;
    else if(iteration == 3)  bank->pFreshmanList = NULL;
    else if(iteration == 4)  bank->pSophomoreList = NULL;
    else if(iteration == 5)  bank->pJuniorList = NULL;
    else if(iteration == 6)  bank->pSeniorList = NULL;
      
      continue;
    }
    else if(strcmp(pTemp->pStudent->id, id) == 0){  //firstonde matches
      StudentNode* pLink = pTemp->pNext;
      free(pTemp);
      
      if     (iteration == 0)  bank->pIDList = pLink;
    else if(iteration == 1)  bank->pHonorRollList = pLink;
    else if(iteration == 2)  bank->pAcademicProbationList = pLink;
    else if(iteration == 3)  bank->pFreshmanList = pLink;
    else if(iteration == 4)  bank->pSophomoreList = pLink;
    else if(iteration == 5)  bank->pJuniorList = pLink;
    else if(iteration == 6)  bank->pSeniorList = pLink;
      
      continue;
      
      break;
    }
   
    while(pTemp->pNext != NULL){
      if(strcmp(pTemp->pNext->pStudent->id, id) == 0){
        StudentNode* pDelete = pTemp->pNext;
        pTemp->pNext = pTemp->pNext->pNext;
        free(pDelete);
        break;
      }
      pTemp = pTemp->pNext;
    }

    
  }
}

//dunno if this works so check at some point
void removeNode(Database* bank, String id){
  StudentNode* pTemp = bank->pIDList;

  for(int iteration = 0; iteration < 7; iteration++){
    if     (iteration == 0)  pTemp = bank->pIDList;
    else if(iteration == 1)  pTemp = bank->pHonorRollList;
    else if(iteration == 2)  pTemp = bank->pAcademicProbationList;
    else if(iteration == 3)  pTemp = bank->pFreshmanList;
    else if(iteration == 4)  pTemp = bank->pSophomoreList;
    else if(iteration == 5)  pTemp = bank->pJuniorList;
    else if(iteration == 6)  pTemp = bank->pSeniorList;

    if(pTemp != NULL && strcmp(pTemp->pStudent->id, id) == 0){  //check the first node
      StudentNode* pDelete = pTemp;
      pTemp = pTemp->pNext;
      free(pDelete);
    }
    while(pTemp != NULL){
      if(pTemp->pNext != NULL && strcmp(pTemp->pStudent->id, id) == 0){
        StudentNode* pDelete = pTemp->pNext;
        pTemp->pNext = pDelete->pNext;
        free(pDelete);
      }
      pTemp = pTemp->pNext;
    }
  }
}

void initBank(Database* bank){
  bank->pIDList = NULL;
  bank->pHonorRollList = NULL;
  bank->pAcademicProbationList = NULL;
  bank->pFreshmanList = NULL;
  bank->pSophomoreList = NULL;
  bank->pJuniorList = NULL;
  bank->pSeniorList = NULL;
}

void displayStart(){
  printf("CS 211, Spring 2023\n");
	printf("Program 4: Database of Students\n\n");
  printf("Enter E to start with an empty database, \n");
  printf("or F to start with a database that has information on students from a file.\n");
  printf("Your choice --> ");
}

void menuOne(){
  printf("\nEnter: \tC to create a new student and add them to the database,\n");
	printf("\tR to read from the database,\n");
	printf("\tD to delete a student from the database, or\n");
	printf("\tX to exit the program.\n");
	printf("Your choice --> ");
}

void menuTwo(){
  printf("Select one of the following: \n");
	printf("\t1) Display the head (first 10 rows) of the database\n");
	printf("\t2) Display students on the honor roll, in order of their GPA\n");
	printf("\t3) Display students on academic probation, in order of their GPA\n");
	printf("\t4) Display freshmen students, in order of their name\n");
	printf("\t5) Display sophomore students, in order of their name\n");
	printf("\t6) Display junior students, in order of their name\n");
	printf("\t7) Display senior students, in order of their name\n");
	printf("\t8) Display the information of a particular student\n");
	printf("Your choice --> ");
}

void choiceR(Database* bank){
  int validInput = -1;
  
  menuTwo();
  scanf(" %d", &validInput);
  
  while(validInput < 1 || validInput > 8){
	  printf("Sorry, that input was invalid. Please try again.\n");
    printf("Your choice --> ");
    scanf(" %d", &validInput);
  }

  switch(validInput){
    case 1:
      printLinkedList(bank->pIDList, 10);
      break;
    case 2:
      printLinkedList(bank->pHonorRollList, 100000);
      break;
    case 3:
      printLinkedList(bank->pAcademicProbationList, 100000);
      break;
    case 4:
      printLinkedList(bank->pFreshmanList, 100000);
      break;
    case 5:
      printLinkedList(bank->pSophomoreList, 100000);
      break;
    case 6:
      printLinkedList(bank->pJuniorList, 100000);
      break;
    case 7:
      printLinkedList(bank->pSeniorList, 100000);
      break;
    case 8:
      //display particular info
      
      
      printf("Enter the id of the student to find: ");
      String userInput = (String)malloc(100 * sizeof(char));
      clearBuffer();
      fgets(userInput, 30, stdin);
      userInput[strlen(userInput)-1] = '\0';
      //clearBuffer();
      
      StudentNode* pTemp = bank->pIDList;

      while(pTemp != NULL){
    
        if(strcmp(pTemp->pStudent->id, userInput) == 0){
          printStudentNode(pTemp);
          free(userInput);
          return;
        }
        pTemp = pTemp->pNext;
      }
      printf("Sorry, there is no student in the database with the id %s.", userInput);
      free(userInput);
      break;
    default:
      break;
  }
}


void choiceD(Database* bank){
  String userInput = malloc(100 * sizeof(char));
  printf("Enter the id of the student to be removed: ");
  clearBuffer();
  scanf(" %s", userInput);
  //printf("%s", userInput);
  //exit(-1);
  //userInput[strlen(userInput)-1] = '\0';

  //in the database
  char inDatabase = '\0';

  StudentNode* pTemp = bank->pIDList;
  while(pTemp != NULL){
    if(strcmp(userInput, pTemp->pStudent->id) == 0){
      //printf("%s | %s", pTemp->pStudent->id, userInput);
      inDatabase = 'F';
      break;
    }
    pTemp = pTemp->pNext;
  }
  
  if(inDatabase != '\0'){  //check IDList, if not in there, dont check everything else
    //printf("Found in database");
    //exit(-1);
    //removeNode(bank, userInput);
    removeFromLinkedList(bank, userInput);
    //removeNode(bank, userInput);
  }
  else{
    printf("Sorry, there is no student in the database with the id %s.\n", userInput);
  }
  
  free(userInput);
}

void choiceC(Database* bank){
  StudentNode* addNode = malloc(sizeof(StudentNode));
  addNode->pNext = NULL;
  clearBuffer();

  Student* addStudent = malloc(sizeof(Student));

  String name = malloc(100 * sizeof(char));
  String id = malloc(100 * sizeof(char));
  double gpa = 0.0;
  int CHT = 0;

  printf("Enter the name of the new student: ");
  fgets(name, 50, stdin);  //get user input
  name[strlen(name)-1] = '\0';
  addStudent->name = name;

  
	printf("Enter the ID of the new student: ");
  fgets(id, 50, stdin);  //get user string
  addStudent->id = id;
  id[strlen(id)-1] = '\0';
  
	printf("Enter the GPA of the new student: ");
  scanf(" %lf", &gpa);
  addStudent->gpa = gpa;

  
	printf("Enter the credit hours of the new student: ");
  scanf(" %d", &CHT);
  addStudent->creditHours = CHT;
 
  
	printf("Successfully added the following student to the database!\n");
  addNode->pStudent = addStudent;
  printStudentNode(addNode);
  
  StudentNode* addedNode = malloc(sizeof(StudentNode));
    addedNode->pStudent = addStudent;
    addedNode->pNext = NULL;
    addNodes(&(bank->pIDList), addedNode, 'l');

    if(gpa > 3.5 || fabs(gpa - 3.5) < 0.00001){  //honor
      StudentNode* addedNode = malloc(sizeof(StudentNode));
      addedNode->pStudent = addStudent;
      addedNode->pNext = NULL;
      addNodes(&(bank->pHonorRollList), addedNode, 'g');
    }
    else if(gpa < 2){  //probation
      StudentNode* addedNode = malloc(sizeof(StudentNode));
      addedNode->pStudent = addStudent;
      addedNode->pNext = NULL;
      addNodes(&(bank->pAcademicProbationList), 
      addedNode, 'g');
    }
    
    if(CHT < 30 && CHT >= 0){  //freshman
      StudentNode* addedNode = malloc(sizeof(StudentNode));
      addedNode->pStudent = addStudent;
      addedNode->pNext = NULL;
      addNodes(&(bank->pFreshmanList), addedNode, 'n');
    }
    else if(CHT < 60 && CHT >= 30){  //sophomore
      StudentNode* addedNode = malloc(sizeof(StudentNode));
      addedNode->pStudent = addStudent;
      addedNode->pNext = NULL;  
      addNodes(&(bank->pSophomoreList), addedNode, 'n');
    }
    else if(CHT < 90 && CHT >= 60){  //junior
      StudentNode* addedNode = malloc(sizeof(StudentNode));
      addedNode->pStudent = addStudent;
      addedNode->pNext = NULL;
      addNodes(&(bank->pJuniorList), addedNode, 'n');  
    }
    else{  //senior
      StudentNode* addedNode = malloc(sizeof(StudentNode));
      addedNode->pStudent = addStudent;
      addedNode->pNext = NULL;
      addNodes(&(bank->pSeniorList), addedNode, 'n');
    }
  clearBuffer();
}

void loadDatabase(Database* bank, String userInput){
  FILE* filePtr = NULL;
  filePtr = fopen(userInput, "r");
  
  if(filePtr == NULL) {                       // Check that the file was able to be opened       
		printf("Error: could not open file for reading\n");
		exit(-1);
	}

  String inputString = malloc(100 * sizeof(char));    
  fgets(inputString, 100, filePtr);  
  
  while(fgets(inputString, 100, filePtr) != NULL) {  
    Student* addStudent = malloc(sizeof(Student));
    
    String name = malloc(100 * sizeof(char));
    strcpy(name, strtok(inputString, ","));
    String id = malloc(100 * sizeof(char));
    strcpy(id, strtok(NULL, ","));
    double gpa = 0;
    sscanf(strtok(NULL, ","), "%lf", &gpa);
    int CHT = atoi(strtok(NULL, ","));

    addStudent->name = name;
    addStudent->id = id;
    addStudent->gpa = gpa;
    addStudent->creditHours = CHT;
    
    //ID list
    StudentNode* addNode = malloc(sizeof(StudentNode));
    addNode->pStudent = addStudent;
    addNode->pNext = NULL;
    addNodes(&(bank->pIDList), addNode, 'l');

    if(gpa > 3.5 || fabs(gpa - 3.5) < 0.00001){  //honor
      StudentNode* addNode = malloc(sizeof(StudentNode));
      addNode->pStudent = addStudent;
      addNode->pNext = NULL;
      addNodes(&(bank->pHonorRollList), addNode, 'g');
    }
    else if(gpa < 2){  //probation
      StudentNode* addNode = malloc(sizeof(StudentNode));
      addNode->pStudent = addStudent;
      addNode->pNext = NULL;
      addNodes(&(bank->pAcademicProbationList), 
      addNode, 'g');
    }
    
    if(CHT < 30 && CHT >= 0){  //freshman
      StudentNode* addNode = malloc(sizeof(StudentNode));
      addNode->pStudent = addStudent;
      addNode->pNext = NULL;
      addNodes(&(bank->pFreshmanList), addNode, 'n');
    }
    else if(CHT < 60 && CHT >= 30){  //sophomore
      StudentNode* addNode = malloc(sizeof(StudentNode));
      addNode->pStudent = addStudent;
      addNode->pNext = NULL;  
      addNodes(&(bank->pSophomoreList), addNode, 'n');
    }
    else if(CHT < 90 && CHT >= 60){  //junior
      StudentNode* addNode = malloc(sizeof(StudentNode));
      addNode->pStudent = addStudent;
      addNode->pNext = NULL;
      addNodes(&(bank->pJuniorList), addNode, 'n');  
    }
    else{  //senior
      StudentNode* addNode = malloc(sizeof(StudentNode));
      addNode->pStudent = addStudent;
      addNode->pNext = NULL;
      addNodes(&(bank->pSeniorList), addNode, 'n');
    }
	}
}

int main() {
  Database* bank = malloc(sizeof(Database));
  initBank(bank);
  int count =0;
  String userInput = (String)malloc(100 * sizeof(char));
  memset(userInput, 0, 30 * sizeof(char));
  
  char validInput = '\0';

  
  displayStart();
  scanf(" %c", &validInput);    //uncomment for input
  //validInput = 'F';

  while(validInput != 'E' && validInput != 'F'){
	  printf("Sorry, that input was invalid. Please try again.\nYour choice --> ");
    scanf(" %c", &validInput);
  }
  int terminate = 0;
  if(validInput == 'F'){
    printf("Enter the name of the file you would like to use: ");
  scanf(" %s", userInput);        //uncomment for input
  //userInput = "small-list.csv";
    /*if(strcmp(userInput, "students-100.csv") == 0){
      terminate = 1;
    }
    else{*/
      loadDatabase(bank, userInput);
    //}
  }

  
  
  
  do{
	menuOne();
  scanf(" %c", &validInput);
  
  while(validInput != 'C' && validInput != 'R' && validInput != 'D' && validInput != 'X'){
    menuOne();
	  printf("Invalid option. Try again.\n");
    scanf(" %c", &validInput);
  }
    /*
    if(count++ >20 && terminate == 1){
      printf("\n\nSHEEEESH\n\n");
        return 0;
    }
    */

  switch(validInput){
    case 'C':
      choiceC(bank);
      break;
    case 'R':
      choiceR(bank);
      break;
    case 'D':
      choiceD(bank);
      break;
    case 'X':
      printf("\nThanks for playing!\n");
	    printf("Exiting...\n");
      return 0;
  }
    

	

	
	


	


}while(1);
	printf("Thanks for playing!\n");
	printf("Exiting...\n");
	
	return 0;
}