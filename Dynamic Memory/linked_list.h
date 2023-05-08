#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <string.h>

#define UNUSED(x) ((void)(x))

typedef struct student
{
    int num_classes; 
    double *grades; 
} Student;

typedef struct instructor
{
    double salary;
} Instructor;

typedef enum user_type {
    STUDENT,
    INSTRUCTOR
} UserType;

typedef union {
  Student student;
  Instructor instructor;
} UserUnion;

typedef struct user
{
    char *name;
    UserType type;
    UserUnion data;
} User;


typedef struct node
{
    struct node *next;  
    User *data;        
} Node;


typedef struct linked_list
{
    Node *head; 
    int size;  
} LinkedList;

LinkedList *create_list(void);

/* Adding */
int push_front(LinkedList *list, char *name, UserType type, UserUnion data);
int push_back(LinkedList *list, char *name, UserType type, UserUnion data);
int add_at_index(LinkedList *list, int index, char *name, UserType type, UserUnion data);

/* Querying */
int get(LinkedList *list, int index, User **dataOut);
int contains(LinkedList *list, User *data, User **dataOut);

/* Removing */
int pop_front(LinkedList *list, User **dataOut);
int pop_back(LinkedList *list, User **dataOut);
int remove_at_index(LinkedList *list, User **dataOut, int index);
void empty_list(LinkedList *list);

/* Analysis */
int num_passing_all_classes(LinkedList *list, int *dataOut);
int get_average_salary(LinkedList *list, double *dataOut);

#endif
