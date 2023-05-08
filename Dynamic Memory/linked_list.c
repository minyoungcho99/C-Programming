#include "list.h"

static User *create_user(char *name, UserType type, UserUnion data);
static int create_student(int num_classes, double *grades, Student *dataOut); 
static int create_instructor(double salary, Instructor *dataOut); 
static Node *create_node(char *name, UserType type, UserUnion data);
static int user_equal(const User *user1, const User *user2);

/** create_user
 * @param the fields of the User struct
 * @return a User, return NULL if malloc fails
 */
static User *create_user(char *name, UserType type, UserUnion data)
{
   User *user = malloc(sizeof(User));
    if (user == NULL) {
        return NULL;
    }

    if (name == NULL) {
        user->name = '\0';
    } else {
        user->name = malloc(strlen(name) + 1);
        if (user->name == NULL) {
            free(user);
            return NULL;
        }
        strcpy(user->name, name);
    }
    
    user->type = type;
    if (user->type == STUDENT) {
        Student student;
        if (create_student(data.student.num_classes, data.student.grades, &student)) {
            free(user->name);
            free(user);
            return NULL;
        }
        user->data.student = student;
    } else {
        Instructor instructor;
        if (create_instructor(data.instructor.salary, &instructor)) {
            free(user->name);
            free(user);
            return NULL;
        }
        user->data.instructor = instructor;
    }

    return user;
}

/** create_student
 * @param the fields of the Student struct, and an existing pointer to a student
 * @return 1 if malloc fails, 0 otherwise.
 */
static int create_student(int num_classes, double *grades, Student *dataOut)
{
    dataOut->num_classes = num_classes;
    dataOut->grades = NULL;
    if (grades != NULL) {
        if (!(dataOut->grades = (double *) malloc(sizeof(double)*num_classes))) return 1;
        memcpy(dataOut->grades, grades, sizeof(double)*num_classes);
    }
    return 0;
}

/** create_instructor
 * @param the fields of the Instructor struct, and an existing pointer to an instructor
 * @return 1 if malloc fails, 0 otherwise. (this function should always return 0 since
 * you won't need to malloc anything)
 */
static int create_instructor(double salary, Instructor *dataOut)
{
    /***do not edit anything in this function***/
    dataOut->salary = salary; //yes that's all this function does
    return 0;
}

/** create_node
  * @param the fields of the User struct
  * @return a Node
  */
static Node* create_node(char *name, UserType type, UserUnion data)
{
   Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }

    User *user = create_user(name, type, data);
    if (user == NULL) {
        free(node);
        return NULL;
    }

    node->data = user;
    node->next = NULL;
    return node;
}

/** student_equal
 * @param the two Student structs to be compared
 * @return 1 if equal, 0 otherwise
 */
static int student_equal(const Student *student1, const Student *student2)
{
    if (student1->num_classes != student2->num_classes) {
        return 0;
    } 

    if (student1->grades != student2->grades) {
        if (student1->grades == NULL || student2->grades == NULL) {
            return 0;
        }
        if (memcmp(student1->grades, student2->grades, student1->num_classes * sizeof(double)))
        {
            return 0;
        }
    }
    return 1;
}

/** user_equal
 * @param the two User structs to be compared
 * @return 1 if equal, 0 otherwise
 */
static int user_equal(const User *user1, const User *user2)
{
    if (user1 == NULL && user2 == NULL) {
        return 0;
    }

    if (user1->type != user2->type) {
        return 0;
    }

    if (user1->name == NULL && user2->name == NULL) {
        return 1;
    } else if (user1->name == NULL || user2->name == NULL || strcmp(user1->name, user2->name) != 0) {
        return 0;
    }


    if (user1->type == STUDENT && user2->type == STUDENT) {
        if (student_equal(&(user1->data.student), &(user2->data.student))) {
            return 1;
        } else { return 0; }
    } else {
        if (user1->data.instructor.salary == user2->data.instructor.salary) {
            return 1;
        } else { return 0; }
    }
    return 0;
}

/** create_list
 * @return a pointer to a new struct list or NULL on failure
 */
LinkedList *create_list(void)
{
    LinkedList *list = (LinkedList *) malloc(sizeof(LinkedList));
    if (list == NULL) {
        return NULL;
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

/** push_front
 * @param list a pointer to the LinkedList structure.
 * @param      the fields of the User struct
 * @return 1 if the LinkedList is NULL or if allocating the new node fails, 0 if
 * successful.
 */
int push_front(LinkedList *list, char *name, UserType type, UserUnion data)
{
    if (list == NULL) {
    	return 1;
    }
    Node *node = create_node(name, type, data);

    if (node == NULL) {
    	return 1;
    }

    if (list->size == 0) {
        list->head = node;      
    } else {
        node->next = list->head;
        list->head = node;
    }
    list->size++;
    return 0;         
}

/** push_back
 * @param list a pointer to the LinkedList structure.
 * @param      the fields of the User struct
 * @return 1 if the LinkedList is NULL or if allocating the new node fails, 0 if
 * successful.
 */
int push_back(LinkedList *list, char *name, UserType type, UserUnion data)
{    
    if (list == NULL) {
        return 1;
    }

    if (list->size == 0) {
        return push_front(list, name, type, data);
    }

    Node *temp = list->head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    Node *newNode = create_node(name, type, data);

    if (newNode == NULL) {
        return 1;
    }
    temp->next = newNode;
    list->size++;

    return 0;
}

/** add_at_index
 * @param list a pointer to the LinkedList structure
 * @param index 0-based, starting from the head in the inclusive range
 *              [0,size]
 * @param the fields of the User struct
 * @return 1 if the index is out of bounds or the LinkedList is NULL or malloc fails
 *         (do not add the data in this case)
 *         otherwise (on success) return 0
 */
int add_at_index(LinkedList *list, int index, char *name, UserType type, UserUnion data)
{
   if (list == NULL) {
        return 1;
    }
    if (index < 0 || index > list->size) {
        return 1;
    }

    if (index == 0) {
        return push_front(list, name, type, data);
    } else if (index == list->size) {
        return push_back(list, name, type, data);
    } else {
        Node *temp = list->head;
        for (int i = 0; i < index - 1; i++) {
            temp = temp->next;
        }
        Node *newNode = create_node(name, type, data);

        if (newNode == NULL) {
            return 1;
        }
        newNode->next = temp->next;
        temp->next = newNode;
        list->size++;
    }
    
    return 0;
}

/** get
 * @param list a pointer to the LinkedList structure
 * @param index 0-based, starting from the head.
 * @param dataOut A pointer to a pointer used to return the data from the
 *        specified index in the LinkedList or NULL on failure.
 * @return 1 if dataOut is NULL or index is out of range of the LinkedList or
 *         the LinkedList is NULL, 0 (on success) otherwise
 */
int get(LinkedList *list, int index, User **dataOut)
{
   if (list == NULL || dataOut == NULL) {
        return 1;
    }


    if (index < 0 || index >= list->size) {
        return 1;
    }

    Node *temp = list->head;
    for (int i = 0; i < index; i++) {
        temp = temp->next;
    }

    *dataOut = temp->data;
    return 0;
}

/** contains
  * @param list a pointer to the LinkedList structure
  * @param data The data, to see if it exists in the LinkedList
  * @param dataOut A pointer to a pointer used to return the data contained in
  *                the LinkedList or NULL on failure
  * @return int    0 if dataOut is NULL, the list is NULL, or the list
  *                does not contain data, else 1
  */
int contains(LinkedList *list, User *data, User **dataOut)
{
    if (dataOut == NULL || list == NULL) {
        if (dataOut != NULL) {
            *dataOut = NULL;
        }
        return 0;
    }

    for (Node *temp = list->head; temp != NULL; temp = temp->next) {
        if (user_equal(temp->data, data)) {
            *dataOut = temp->data;
            return 1;
        }
    }

    *dataOut = NULL;
    return 0;
}

/** pop_front
  * @param list a pointer to the LinkedList.
  * @param dataOut A pointer to a pointer used to return the data in the first
  *                Node or NULL if the LinkedList is NULL or empty
  * @return 1 if dataOut is NULL (the LinkedList is NULL or empty), else (on success) 0
  */
int pop_front(LinkedList *list, User **dataOut)
{
   if (dataOut == NULL || list == NULL || list->size == 0) {
        return 1;
    }

    *dataOut = list->head->data;
    Node *removedNode = list->head;
    list->head = list->head->next;
 
    free(removedNode);
    list->size--;
    return 0;
}

/** pop_back
  * @param list a pointer to the LinkedList.
  * @param dataOut A pointer to a pointer used to return the data in the last
  *                Node or NULL if the LinkedList is NULL or empty
  * @return 1 if dataOut is NULL (the LinkedList is NULL or empty), else (on success) 0
  */
int pop_back(LinkedList *list, User **dataOut)
{
    if (dataOut == NULL || list == NULL || list->size == 0) {
        return 1;
    }

    Node *temp = list->head;

    if (list->size == 1) {
        return pop_front(list, dataOut);
    }

    while (temp->next->next != NULL) {
        temp = temp->next;
        
    }

    Node *removedNode = temp->next;
    *dataOut = removedNode->data;
    temp->next = NULL;

    free(removedNode);
    list->size--;

    return 0;
}


/** remove_at_index
 * @param list a pointer to the LinkedList structure
 * @param dataOut A pointer to a pointer used to return the data in the last
 *                Node or NULL if the LinkedList is NULL or empty
 * @param index 0-based, starting from the head in the inclusive range
 *              [0,size-1]
 * @return 1 if the index is out of bounds, the LinkedList is NULL or
 *         the dataOut is NULL
 *         otherwise return 0
 */
int remove_at_index(LinkedList *list, User **dataOut, int index)
{
    if (list == NULL || dataOut == NULL) {
        return 1;
    }
    
    if (index < 0 || index >= list->size) {
        return 1;
    }

    if (index == 0) {
        return pop_front(list, dataOut);
    } else if (index == list->size - 1) {
        return pop_back(list, dataOut);
    } else {
        Node *temp = list->head;
        for (int i = 0; i < index - 1; i++) {
            temp = temp->next;
        }

        Node *removedNode = temp->next;
        *dataOut = removedNode->data;
        temp->next = temp->next->next;
        list->size--;

        free(removedNode);
        return 0;
    }
}

/** empty_list
 * @param list a pointer to the LinkedList structure
 */
void empty_list(LinkedList *list)
{
    if (list == NULL || list->size == 0) {
        return;
    }
    if (list->size == 1) {
        free(list->head->data->name);
        if (list->head->data->type == STUDENT) {
            free(list->head->data->data.student.grades);
        }
        free(list->head->data);
        free(list->head);
        list->head = NULL;
        list->size = 0;
        return;
    }

    User *user;
    while (list->size > 0) {
        pop_front(list, &user);
        free(user->name);
        if (user->type == STUDENT) {
            free(user->data.student.grades);
        }
        free(user);
    }
}

/** num_passing_all_classes
 * @param list a pointer to the LinkedList structure
 * @param dataOut A pointer to int used to return the count of students passing all
 *                of their classes
 *                or -1 if the LinkedList is NULL or empty
 * @return 1 if the LinkedList is NULL or empty, else (on success) 0
 */
int num_passing_all_classes(LinkedList *list, int *dataOut)
{
    if (list == NULL || list->size == 0) {
        if (dataOut != NULL) {
            *dataOut = -1;
        }
        return 1;
    }

    int count = 0;
    Node *temp = list->head;

    while (temp != NULL) {
        if (temp->data != NULL && temp->data->type == STUDENT) {
            Student *student = &(temp->data->data.student);
            int passed = 1;

            if (student->num_classes > 0) {
                for (int i = 0; i < student->num_classes; i++) {
                    if (student->grades[i] < 60) {
                        passed = 0;
                        break;
                    }
                }
            } else {
                passed = 0;
            }

            if (passed == 1) {
                count++;
            }
        }

        temp = temp->next;
    }

    if (dataOut != NULL) {
        *dataOut = count;
    }
    return 0;
}

/** get_average_salary
 * @param list a pointer to the LinkedList structure
 * @param dataOut A pointer to double used to return the average salary of the instructors
 *                or -1 if the LinkedList is NULL or empty
 * @return 1 if the LinkedList is NULL or empty, else (on success) 0
 */
int get_average_salary(LinkedList *list, double *dataOut)
{
    if (list == NULL || list->size <= 0) {
        if (dataOut != NULL) {
            *dataOut = -1;
        }
        return 1;
    }

    double total = 0;
    int count = 0;
    Node *temp = list->head;

    while (temp != NULL) {
        if (temp->data != NULL && temp->data->type == INSTRUCTOR) {
            Instructor *instructor = &(temp->data->data.instructor);
            total += instructor->salary;
            count++;
        }
        temp = temp->next;
    }

    double avg;
    if (count > 0) {
        avg = total / count;
    } else {
        avg = 0;
    }
    *dataOut = avg;

    return 0;
}