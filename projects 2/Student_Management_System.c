#include<stdio.h>
#include<string.h>

#define MAX 100

//structure definition

struct student {
    int roll;
    char name[20];
    float marks;
};

struct  student students[MAX];
int count = 0;

//Function declaration

void addstudent();
void viewstudent();
void searchstudent();
void updatestudent();
void deletestudent();
void sortstudent();


int main() {
    int choice;

    do{
        printf("\n===== STUDENT MANAGEMENT SYSTEM =====\n");
        printf("1. Add Student\n");
        printf("2. View All Student\n");
        printf("3. Search By Roll Number\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Sort Student By Marks \n");
        printf("7. Exit\n");

        printf("Enter your choice : ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1: addstudent(); break;
        case 2: viewstudent(); break;
        case 3: searchstudent(); break;
        case 4: updatestudent(); break;
        case 5: deletestudent(); break;
        case 6: sortstudent(); break;
        case 7: printf("Exiting...\n"); break;
        default: printf("Invalid choice!\n");
        }
    } while(choice != 7);
    return 0;
}

// Add student 

void addstudent(){
    if(count >= MAX){
        printf("Student list is full\n");
        return;
    }

    printf("Enter Roll Number : ");
    scanf("%d", &students[count].roll);

    printf("Enter Name : ");
    scanf(" %[^\n]", students[count].name);

    printf("Enter Marks : ");
    scanf("%f", &students[count].marks);

    count++;
    printf("Student added successfully!\n");

}

// view student

void viewstudent(){
    if(count == 0){
        printf("No record found!\n");
        return;
    }

    printf("\n=== STUDENT RECORDS ===\n");
    for(int i = 0; i < count; i++){
        printf("Roll : %d | Name : %s | Marks : %.2f\n", students[i].roll, students[i].name, students[i].marks);
    }
}

//search student 

void searchstudent(){
    int roll, found = 0;
    printf("Enter Roll Number to Search : ");
    scanf("%d", &roll);

    for(int i = 0; i < count; i++){
        if(students[i].roll == roll){
            printf("Found : Roll: %d | Name: %s | Marks: %.2f\n",students[i].roll, students[i].name, students[i].marks );
            found = 1;
            break;
        }
    }
    if(!found)
        printf("Student not found! \n");
    
}

//update student 

void updatestudent(){
    int roll, found = 0;
    printf("Enter Roll Number to Update : ");
    scanf("%d", &roll);

    for(int i = 0; i < count; i++){
        if(students[i].roll == roll){
            printf("Enter New Name : ");
            scanf(" %[^\n]", students[i].name);

            printf("Enter New Marks: ");
            scanf("%f", &students[i].marks);

            printf("Record updated Successfully!\n");
            found = 1;
            break;
        }
    }

    if(!found){
        printf("student not found\n");
    }
}

//delete student

void deletestudent(){
    int roll, found = 0;
    printf("Enter Roll Number to delete : ");
    scanf("%d", &roll);

    for(int i = 0; i < count; i++){
        if(students[i].roll == roll){
            for(int j = i; j < count -1; j++){
                students[j] = students[j + 1];
            }

            count--;
            printf("Record Deleted successfully!\n");
            found = 1;
            break;
        }

    }
    if (!found){
        printf("Student not found!\n");
    }
}

//sort student by marks 

void sortstudent(){
    if(count == 0){
        printf("No records to sort!\n");
        return;
    }

    for(int i = 0; i < count - 1; i++){
        for(int j = 0; j < count - i - 1; j++){
            if(students[j].marks < students[j + 1].marks){
                struct student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
                
            }
        }
    }
    printf("Student sorted by marks. \n");
}