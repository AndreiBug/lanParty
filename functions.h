#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#define table_size 67
#define winner_size 41

struct Player {
    char *firstName;
    char *secondName;
    float points;
    struct Player *next;
};

struct Team {
    float team_points;
    int player_nr;
    int teams_nr;
    char *name;
    struct Player *player;
    struct Player *head_player;
    struct Team *next;
};

struct Queue_Games {     // coada // front = head; rear = sfarsitul
    struct Team *front ,*rear;
};

struct Stack_Match {     // stiva // top == head de la lista doar ca e ultimul element
    struct Team *team;
    struct Stack_Match *next;  
};

void open_input_file(FILE **f);

void open_output_file(FILE **f);

void addAtBeginning (struct Team **head , char* name, int player_nr, int teams_nr, char* firstName, char* secondName, float points);

void deleteList(struct Team **head);

void delete_min(struct Team** head, float value);

int isEmptyCozi(struct Queue_Games *q);

struct Queue_Games *createQueue();

void enQueue(struct Queue_Games *q, struct Team *v);

char *deQueue(struct Queue_Games *q);

void deleteQueue(struct Queue_Games *q);

int isEmptyStive(struct Stack_Match *top);

char *top(struct Stack_Match *top);

void push(struct Stack_Match **top, struct Team *v);

struct Team *pop(struct Stack_Match **top);

void deleteStack(struct Stack_Match **top);