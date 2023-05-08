#include <stdio.h>
#include "oh_queue.h"

struct Queue oh_queue;

/** push
 * Creates a new student and push him onto the OH queue.
 */
int push(const char *studentName, const enum subject topicName, const float questionNumber, struct public_key pub_key){
    if (studentName == NULL || questionNumber == -1 || oh_queue.stats.no_of_people_in_queue >= MAX_QUEUE_LENGTH) {
        return FAILURE;
    }

    struct Student student;
    int customID[30] = {0};
    char plaintext[MAX_NAME_LENGTH] = {0};
    int length = 0;

    while (studentName[length] != '\0' && length < MAX_NAME_LENGTH - 1) {
        plaintext[length] = studentName[length];
        length++;
    }

    plaintext[length] = '\0';
    int counter = 0;
    while (counter < length) {
        student.customID[counter] = customID[counter];
        counter++;
    }

    hash(student.customID, plaintext, pub_key);
    length = pub_key.e;
    student.queue_number = oh_queue.stats.no_of_people_visited + oh_queue.stats.no_of_people_in_queue;
    int i = 0;

    while (studentName[i] != '\0' && i < MAX_NAME_LENGTH - 1) {
        student.studentData.name[i] = studentName[i];
        i++;
    }

    student.studentData.name[i] = '\0';
    student.studentData.topic.topicName = topicName;
    student.studentData.topic.questionNumber = questionNumber;
    oh_queue.students[oh_queue.stats.no_of_people_in_queue] = student;
    oh_queue.stats.no_of_people_in_queue++;

    OfficeHoursStatus(&oh_queue.stats);
    return SUCCESS;
    }

/** pop 
 * Pops a student out the OH queue.
 */
int pop(void) {
    if (oh_queue.stats.no_of_people_in_queue <= 0) {
        return FAILURE;
    }

    int i = 0;
    while (i < oh_queue.stats.no_of_people_in_queue - 1) {
        oh_queue.students[i] = oh_queue.students[i+1];
        i++;
    }

    oh_queue.stats.no_of_people_in_queue--;

    if (oh_queue.stats.no_of_people_in_queue == 0) {
        oh_queue.stats.currentStatus = "Completed";
    } else {
        oh_queue.stats.currentStatus = "InProgress";
    }

    oh_queue.stats.no_of_people_visited++;

    return SUCCESS;  
}

/** group_by_topic
 * Pushes pointers to students, who match the given topic, to the given array "grouped".
 */
int group_by_topic(struct Topic topic, struct Student *grouped[]) { 
    int i = 0;
    int numStudents = 0;
    while (i < oh_queue.stats.no_of_people_in_queue) {
        if (oh_queue.students[i].studentData.topic.topicName == topic.topicName && oh_queue.students[i].studentData.topic.questionNumber == topic.questionNumber) {
            grouped[numStudents] = &oh_queue.students[i];
            numStudents++;
        }
        i++;
    }

    return numStudents;
}

/** hash
 * Creates a hash based on pub_key provided.
 */
void hash(int *ciphertext, char *plaintext, struct public_key pub_key) {
    int i = 0;
    int a = -1;
    do {
        a = 1;
        for (int j = 0; j < pub_key.e; j++) {
            a = (a * plaintext[i]) % pub_key.n;
        }
        ciphertext[i] = a;
        i++;
    } while (plaintext[i - 1] != '\0');
}

/** update_student
 * Finds the student with the given ID and update his topic.
 */
int update_student(struct Topic newTopic, int *customID) {
    int i = 0;
    int found = 0;

    while (i < oh_queue.stats.no_of_people_in_queue && !found) {
        int j = 0;
        int statusChecker = 1;

        while (j < MAX_NAME_LENGTH) {
            if (customID[j] != oh_queue.students[i].customID[j]) {
                statusChecker = 0;
                break;
            }
            if (oh_queue.students[i].customID[j] == 0) {
                break;
            }
            j++;
        }

        if (statusChecker) {
            oh_queue.students[i].studentData.topic = newTopic;
            return SUCCESS;
        }

        i++;
    }

    return FAILURE;
}

/** remove_student_by_name
 * Removes first instance of a student with the given name.
 */
int remove_student_by_name(char *name) {
    int nameLength = my_strlen(name);
    int statusChecker = 0;
    int i = 0;

    while (i < oh_queue.stats.no_of_people_in_queue) {
        if (my_strncmp(oh_queue.students[i].studentData.name, name, nameLength) == 0) {
            for (int j = i; j < oh_queue.stats.no_of_people_in_queue; j++) {
                oh_queue.students[j] = oh_queue.students[j + 1];
            }
            oh_queue.stats.no_of_people_visited++;
            oh_queue.stats.no_of_people_in_queue--;
            statusChecker = 1;
            break;
        }
        else {
            i++;
        }
    }
    
    if (statusChecker == 1) {
        OfficeHoursStatus(&oh_queue.stats);
        return SUCCESS;
    } else {
        return FAILURE;
    }
}

/** remove_student_by_topic
 * Removes all instances of students with the given topic.
 */
int remove_student_by_topic(struct Topic topic) {
    int statusChecker = 0;

    for (int i = oh_queue.stats.no_of_people_in_queue - 1; i >= 0; i--) {
        if (oh_queue.students[i].studentData.topic.topicName == topic.topicName && oh_queue.students[i].studentData.topic.questionNumber == topic.questionNumber) {
            for (int j = i; j < oh_queue.stats.no_of_people_in_queue - 1; j++) {
                oh_queue.students[j] = oh_queue.students[j + 1];
            }
            oh_queue.stats.no_of_people_visited++;
            oh_queue.stats.no_of_people_in_queue--;
            statusChecker = 1;
        }
    }

    if (statusChecker == 1) {
        OfficeHoursStatus(&oh_queue.stats);
        return SUCCESS;
    } else {
        return FAILURE;
    }
}

/** OfficeHoursStatus
 * Updates the "currentStatus" field based on whether or not all students in the queue have been help.
 */
void OfficeHoursStatus(struct OfficeHoursStats* resultStats ){
    if (resultStats->no_of_people_visited == MAX_QUEUE_LENGTH) {
        resultStats->currentStatus = "Completed";
    } else {
        resultStats->currentStatus = "InProgress";
    }
}

/*
 * Calculates (b^e)%n without overflow.
 */
int power_and_mod(int b, int e, int n) {
    long int currNum = 1;
    for (int i = 0; i < e; i++) {
        currNum *= b;
        if (currNum >= n) {
            currNum %= n;
        }
    }
    return (int) (currNum % n);
}
