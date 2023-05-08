#ifndef OHQUEUE_H
#define OHQUEUE_H

#include "my_string.h"
#include <stddef.h>

#define UNUSED_PARAM(x) ((void) x) 
#define UNUSED_FUNC(x) ((void) x)  

#define MAX_NAME_LENGTH  30
#define MAX_QUEUE_LENGTH  30

#define SUCCESS 1
#define FAILURE 0

enum subject{Assembly, LC3, C, Other};
enum status{Completed, InProgress};

struct Topic{
    enum subject topicName;
    float questionNumber;
};

struct StudentData{
    char name[30];
    struct Topic topic;
};

struct Student {
    int customID[30];
    int queue_number;
    struct StudentData studentData;
};

struct OfficeHoursStats{
    int no_of_people_in_queue;
    int no_of_people_visited;
    char *currentStatus;
};

struct public_key {
    int n;
    int e;
};

struct Queue {
    struct OfficeHoursStats stats;
    struct Student students[MAX_QUEUE_LENGTH];
};

int push(const char *studentName, const enum subject topicName, const float questionNumber, struct public_key pub_key);
int pop(void);
int group_by_topic(struct Topic topic, struct Student *grouped[]);
int power_and_mod(int b, int e, int n);
void hash(int *ciphertext, char *plaintext, struct public_key pub_key);
int update_student(struct Topic newTopic, int customID[]);
int remove_student_by_name(char *name);
int remove_student_by_topic(struct Topic topic);
void OfficeHoursStatus(struct OfficeHoursStats* resultStats );

#endif