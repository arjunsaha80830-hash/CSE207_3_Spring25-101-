#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 10
#define STACK_SIZE 10

//  Doctor BST 
struct Doctor
{
    int id;
    char name[100];
    char time[50];
    struct Doctor *left, *right;
};

struct Doctor *newDoctor(int id, char name[], char time[])
{
    struct Doctor *d = (struct Doctor *)malloc(sizeof(struct Doctor));
    d->id = id;
    strcpy(d->name, name);
    strcpy(d->time, time);
    d->left = d->right = NULL;
    return d;
}

struct Doctor *insertDoctor(struct Doctor *root, int id, char name[], char time[])
{
    if (root == NULL)
    {
        printf("Doctor added successfully: %s (ID: %d)\n", name, id);
        return newDoctor(id, name, time);
    }
    if (id < root->id)
        root->left = insertDoctor(root->left, id, name, time);
    else if (id > root->id)
        root->right = insertDoctor(root->right, id, name, time);
    return root;
}

struct Doctor *searchDoctor(struct Doctor *root, int id)
{
    if (root == NULL || root->id == id)
        return root;
    if (id < root->id)
        return searchDoctor(root->left, id);
    return searchDoctor(root->right, id);
}

struct Doctor *findMin(struct Doctor *root)
{
    while (root && root->left != NULL)
        root = root->left;
    return root;
}

struct Doctor *deleteDoctor(struct Doctor *root, int id)
{
    if (root == NULL)
        return root;
    if (id < root->id)
        root->left = deleteDoctor(root->left, id);
    else if (id > root->id)
        root->right = deleteDoctor(root->right, id);
    else
    {
        if (root->left == NULL)
        {
            struct Doctor *temp = root->right;
            printf("Doctor deleted successfully: %s (ID: %d)\n", root->name, root->id);
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct Doctor *temp = root->left;
            printf("Doctor deleted successfully: %s (ID: %d)\n", root->name, root->id);
            free(root);
            return temp;
        }
        struct Doctor *temp = findMin(root->right);
        root->id = temp->id;
        strcpy(root->name, temp->name);
        strcpy(root->time, temp->time);
        root->right = deleteDoctor(root->right, temp->id);
    }
    return root;
}

void inorderDoctor(struct Doctor *root)
{
    if (root == NULL)
        return;
    inorderDoctor(root->left);
    printf("Doctor: %s (ID: %d, Time: %s)\n", root->name, root->id, root->time);
    inorderDoctor(root->right);
}

// Patient Linked List
struct Patient
{
    char name[100];
    int id;
    int age;
    char gender[50];
    char disease[100];
    char appTime[50];
    struct Patient *next;
};

struct Patient *head = NULL;

void addPatient(char name[], int id, int age, char gender[], char disease[], char appTime[])
{
    struct Patient *p = (struct Patient *)malloc(sizeof(struct Patient));
    strcpy(p->name, name);
    p->id = id;
    p->age = age;
    strcpy(p->gender, gender);
    strcpy(p->disease, disease);
    strcpy(p->appTime, appTime);
    p->next = head;
    head = p;
    printf("Patient %s added successfully with appointment at %s\n", name, appTime);
}

void displayPatients()
{
    if (head == NULL)
    {
        printf("No patients found.\n");
        return;
    }
    struct Patient *temp = head;
    while (temp != NULL)
    {
        printf("Patient: %s | ID: %d | Age: %d | Gender: %s | Disease: %s | Appointment: %s\n",
               temp->name, temp->id, temp->age, temp->gender, temp->disease, temp->appTime);
        temp = temp->next;
    }
}

struct Patient *searchPatient(int id)
{
    struct Patient *temp = head;
    while (temp != NULL)
    {
        if (temp->id == id)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

void deletePatient(int id)
{
    if (head == NULL)
    {
        printf("No patients found.\n");
        return;
    }
    struct Patient *temp = head;
    struct Patient *prev = NULL;
    while (temp != NULL)
    {
        if (temp->id == id)
        {
            if (prev == NULL)
                head = temp->next;
            else
                prev->next = temp->next;
            printf("Patient %s (ID: %d) deleted successfully.\n", temp->name, temp->id);
            free(temp);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Patient with ID %d not found.\n", id);
}

// Appointment Queue
struct Patient queue[N];
int front = -1, rear = -1;

void enqueue(struct Patient p)
{
    if (rear == N - 1)
    {
        printf("Queue Overflow\n");
    }
    else if (front == -1 && rear == -1)
    {
        front = rear = 0;
        queue[rear] = p;
        printf("Patient %s added to appointment queue.\n", p.name);
    }
    else
    {
        rear++;
        queue[rear] = p;
        printf("Patient %s added to appointment queue.\n", p.name);
    }
}

void dequeue()
{
    if (front == -1 && rear == -1)
    {
        printf("No patients in the queue.\n");
    }
    else if (front == rear)
    {
        printf("Appointment completed for %s (ID: %d)\n", queue[front].name, queue[front].id);
        front = rear = -1;
    }
    else
    {
        printf("Appointment completed for %s (ID: %d)\n", queue[front].name, queue[front].id);
        front++;
    }
}

void peek()
{
    if (front == -1 && rear == -1)
    {
        printf("No patients in the queue.\n");
    }
    else
    {
        printf("Next Appointment: %s (ID: %d, Time: %s)\n", queue[front].name, queue[front].id, queue[front].appTime);
    }
}

void displayQueue()
{
    if (front == -1 && rear == -1)
    {
        printf("No patients in the queue.\n");
    }
    else
    {
        printf("Remaining Patients in Queue:\n");
        for (int i = front; i <= rear; i++)
        {
            printf("Name: %s | ID: %d | Age: %d | Gender: %s | Disease: %s | Appointment: %s\n",
                   queue[i].name, queue[i].id, queue[i].age, queue[i].gender, queue[i].disease, queue[i].appTime);
        }
    }
}

//  Stack for deleted appointments
struct Patient stack[STACK_SIZE];
int top = -1;

void push(struct Patient p)
{
    if (top == STACK_SIZE - 1)
        printf("Stack Overflow\n");
    else
    {
        top++;
        stack[top] = p;
    }
}

void pop()
{
    if (top == -1)
        printf("Stack Underflow\n");
    else
    {
        struct Patient p = stack[top];
        printf("Undo Appointment Deletion -> %s (ID: %d) restored.\n", p.name, p.id);
        top--;
    }
}

void peekStack()
{
    if (top == -1)
        printf("Stack Empty\n");
    else
    {
        struct Patient p = stack[top];
        printf("Last Deleted Appointment -> %s (ID: %d)\n", p.name, p.id);
    }
}

void displayStack()
{
    if (top == -1)
        printf("Stack Empty\n");
    else
    {
        printf("Deleted Appointments in Stack:\n");
        for (int i = top; i >= 0; i--)
        {
            printf("Name: %s | ID: %d\n", stack[i].name, stack[i].id);
        }
    }
}

//  Main Menu 
int main()
{
    struct Doctor *doctorRoot = NULL;
    int choice;
    char password[20];

    printf("Enter password: ");
    scanf("%s", password);
    if (strcmp(password, "12345") != 0)
    {
        printf("Invalid User\n");
        return 0;
    }

    while (1)
    {
        printf("\n--- MAIN MENU ---\n");
        printf("1. Doctor Management\n");
        printf("2. Patient Management\n");
        printf("3. Appointment Queue\n");
        printf("4. Deleted Appointments Stack\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            int ch, id;
            char name[100], time[50];
            printf("Doctor Menu: 1.Insert 2.Delete 3.Search 4.Display\n");
            scanf("%d", &ch);
            if (ch == 1)
            {
                printf("Enter Doctor ID, Name, Time: ");
                scanf("%d %s %s", &id, name, time);
                doctorRoot = insertDoctor(doctorRoot, id, name, time);
            }
            else if (ch == 2)
            {
                printf("Enter Doctor ID to delete: ");
                scanf("%d", &id);
                doctorRoot = deleteDoctor(doctorRoot, id);
            }
            else if (ch == 3)
            {
                printf("Enter Doctor ID to search: ");
                scanf("%d", &id);
                struct Doctor *d = searchDoctor(doctorRoot, id);
                if (d)
                    printf("Found Doctor: %s (ID: %d, Time: %s)\n", d->name, d->id, d->time);
                else
                    printf("Doctor not found.\n");
            }
            else if (ch == 4)
            {
                if (doctorRoot == NULL)
                    printf("No doctors found.\n");
                else
                    inorderDoctor(doctorRoot);
            }
        }
        else if (choice == 2)
        {
            int ch, id, age;
            char name[100], gender[50], disease[100], appTime[50];
            printf("Patient Menu: 1.Insert 2.Delete 3.Search 4.Display\n");
            scanf("%d", &ch);
            if (ch == 1)
            {
                printf("Enter Patient ID, Name, Age, Gender, Disease, Appointment Time: ");
                scanf("%d %s %d %s %s %s", &id, name, &age, gender, disease, appTime);
                addPatient(name, id, age, gender, disease, appTime);
            }
            else if (ch == 2)
            {
                printf("Enter Patient ID to delete: ");
                scanf("%d", &id);
                struct Patient *p = searchPatient(id);
                if (p != NULL)
                {
                    push(*p); // push deleted patient to stack
                    deletePatient(id);
                }
                else
                    printf("Patient not found.\n");
            }
            else if (ch == 3)
            {
                printf("Enter Patient ID to search: ");
                scanf("%d", &id);
                struct Patient *p = searchPatient(id);
                if (p)
                    printf("Found Patient: %s | ID: %d | Age: %d | Gender: %s | Disease: %s | Appointment: %s\n",
                           p->name, p->id, p->age, p->gender, p->disease, p->appTime);
                else
                    printf("Patient not found.\n");
            }
            else if (ch == 4)
            {
                displayPatients();
            }
        }
        else if (choice == 3)
        {
            int ch;
            printf("Appointment Menu: 1.Enqueue 2.Dequeue 3.Peek 4.Display\n");
            scanf("%d", &ch);
            if (ch == 1)
            {
                if (head == NULL)
                    printf("No patients available to enqueue.\n");
                else
                    enqueue(*head);
            }
            else if (ch == 2)
            {
                dequeue();
            }
            else if (ch == 3)
            {
                peek();
            }
            else if (ch == 4)
            {
                displayQueue();
            }
        }
        else if (choice == 4)
        {
            int ch;
            printf("Stack Menu: 1.Pop 2.Peek 3.Display\n");
            scanf("%d", &ch);
            if (ch == 1)
                pop();
            else if (ch == 2)
                peekStack();
            else if (ch == 3)
                displayStack();
        }
        else if (choice == 5)
            break;
    }
    return 0;
}