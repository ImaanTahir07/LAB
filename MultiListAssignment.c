#include<stdio.h>
#include<stdlib.h>
struct Course
{
    int cNo;
    struct Student *sStart;
    struct course *next;

};
struct Course *cStart = NULL;

struct Student
{
    int SID;
    struct Student *sNext;
};

Insert_Course(){
    struct Course *temp = (struct Course*)malloc((sizeof(struct Course)));
    printf("Enter Course Number:\n");
    scanf("%d",&temp->cNo);
    temp->next=NULL;
    temp->sStart=NULL;
    if(cStart==NULL){
        
        cStart = temp;
    }
    else{
        struct Course *cCurr = cStart;
        while (cCurr->next != NULL)
        {
           cCurr=cCurr->next;
        }
        cCurr->next=temp;
    }
}
Print_Course(){
    struct Course *curr = cStart;
    if (cStart == NULL)
    {
        printf("You have No Courses to Show\n");

    }
    while (curr != NULL)
    {
        printf("Course Number: %d \n",curr->cNo);
        curr=curr->next;
    }
}
Search_Course(){
    int searchCourseNo;
    printf("\nSearching the Course By its Course Number\n");
    printf("Enter Course Number You Want To Search: \n");
    scanf("%d",&searchCourseNo);
    struct Course *curr = cStart;
    while (curr != NULL)
    {
        if(curr->cNo==searchCourseNo){
            printf("\nCourse Found!!\nCourse No: %d ",curr->cNo);
            return;
        }
        curr=curr->next;
    }
    if (curr==NULL)
    {
       printf("\nCourse Not Found");
    }
    
    
}
Delete_Course(){
    int deleteCourseNo;
    printf("\nDeleting The Course by Its Course Number\n");
    printf("Enter Course Number You Want to Delete:\n");
    scanf("%d",&deleteCourseNo);
    struct Course* curr = cStart;
    if(deleteCourseNo == cStart->cNo){
        cStart = cStart->next;
        free(curr);
    }else
    {
        struct Course *prev=cStart;
        curr = curr->next;
        while(curr!=NULL){
            if (deleteCourseNo == curr->cNo)
            {
                prev->next=curr->next;
                free(curr);
                printf("\nCourse Deleted!");
                return;
            }else{
                prev=prev->next;
                curr=curr->next;
            }
            
        }
        if (curr==NULL)
        {
           printf("\nCourse Not Found");
        }
        
    }
    
}
Insert_Student() {
    int courseNo;
    int studentId;
    printf("\nEnter Course Number to Enroll a student: ");
    scanf("%d", &courseNo);
    printf("\nEnter Student ID to Enroll a student: ");
    scanf("%d", &studentId);

    struct Course* currCourse = cStart;
    while (currCourse != NULL) {
        if (currCourse->cNo == courseNo) {
            struct Student* student = (struct Student*)malloc(sizeof(struct Student));
            student->SID = studentId;
            student->sNext = NULL;

            if (currCourse->sStart == NULL) {
                currCourse->sStart = student;
            } else {
                struct Student* currStudent = currCourse->sStart;
                while (currStudent->sNext != NULL) {
                    currStudent = currStudent->sNext;
                }
                currStudent->sNext = student;
            }

            printf("\nStudent Enrolled Successfully in course Number:%d ", currCourse->cNo);
            return;
        }
        currCourse = currCourse->next;
    }
    printf("\nCourse with course number: %d Not Found!", courseNo);
}


Print_Students_In_Course() {
    int courseNo;
    printf("\nEnter Course No to see its enrollments: ");
    scanf("%d", &courseNo);
    printf("Enrolled students are:\n");
    struct Course* currCourse = cStart;

    while (currCourse != NULL) {
        if (currCourse->cNo == courseNo) {
            struct Student* currStudent = currCourse->sStart;
            while (currStudent != NULL) {
                printf("Student ID: %d\n", currStudent->SID);
                currStudent = currStudent->sNext;
            }
            return;
        }
        currCourse = currCourse->next;
    }
    printf("\nEntered Course Number is Invalid!\n");
}

Delete_Student_From_Course(){
    int courseNo;
    int studentId;
    printf("\nEnter Course Number to delete a student from course: ");
    scanf("%d",&studentId);
    printf("\nEnter Student ID to delete a student from course: ");
    scanf("%d",&studentId);
    struct Course *currCourse = cStart;
    while (currCourse != NULL)
    {
        if(currCourse->cNo == courseNo){
            struct Student *currStudent = currCourse->sStart;
            struct Student *prevStudent = NULL;
            while (currStudent != NULL)
            {
                if(currStudent->SID == studentId){
                    if (prevStudent==NULL)
                    {
                        currCourse->sStart=currStudent->sNext;
                    }else{
                        prevStudent->sNext = currStudent->sNext;
                    }
                    free(currStudent);
                    printf("\nStudent with ID %d is deleted from course no: %d",studentId,courseNo);
                    return;
                }
                prevStudent = currStudent;
                currStudent = currStudent->sNext;
            }
            printf("\nStudent with ID %d not found in course %d", studentId, courseNo);
            return;
            

        }
        currCourse = currCourse->next;
    }
    printf("\nCourse with number %d not found", courseNo);
    
}

Search_Student_In_Courses(){
    int studentId;
    printf("Enter the SID of the student you want to search for : \t\t");
    printf("\nStudent ID : ");
    scanf("%d",&studentId);
    struct Course *currCourse = cStart;
    int flag = 0;
    while (currCourse != NULL)
    {
        struct Student *currStudent = currCourse->sStart;
        while(currStudent != NULL){
            if (currStudent->SID == studentId)
            {
                printf("\nStudent ID %d found in Course %d",studentId,currCourse->cNo);
                flag = 1;
                return;
            }
            currStudent = currStudent->sNext;
            
        }
        currCourse = currCourse->next;
    }
    if(flag == 0){
        printf("\nStudent ID does not exist!");
    }
    

}
DeleteALL(){
    struct Course *currCourse = cStart;
    while (currCourse!=NULL)
    {
       struct Student *currStudent = currCourse->sStart;
       while(currStudent!=NULL){
            struct Student *tempStudent =  currStudent;
            currStudent = currStudent->sNext;
            free(tempStudent);
       }
       struct Course* tempCourse = currCourse;
       currCourse = currCourse->next;
       free(tempCourse);

    }
    
    cStart = NULL;
    printf("\nAll Courses And Students Are Deleted!");
}
void Print_Menu() {
    printf("\nMenu:\n");
    printf("1. Insert Course\n");
    printf("2. Print Courses\n");
    printf("3. Insert Student\n");
    printf("4. Delete Course\n");
    printf("5. Delete Student From Course\n");
    printf("6. Search Course\n");
    printf("7. Search Student in Courses\n");
    printf("8. Print Students in Course\n");
    printf("9. Delete All Courses and Students\n");
    printf("10. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    int choice;

    while (1) {
        Print_Menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                Insert_Course();
                break;
            case 2:
                Print_Course();
                break;
            case 3:
                Insert_Student();
                break;
            case 4:
                Delete_Course();
                break;
            case 5:
                Delete_Student_From_Course();
                break;
            case 6:
                Search_Course();
                break;
            case 7:
                Search_Student_In_Courses();
                break;
            case 8:
                Print_Students_In_Course();
                break;
            case 9:
                DeleteALL();
                break;
            case 10:
                printf("Exiting the program.\n");
                exit(0); // Exit the program
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;

}

