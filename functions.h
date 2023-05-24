#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#define table_size 69
#define winner_size 37

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

struct Queue_Games {
    struct Team *front ,*rear;
};

struct Stack_Match {
    struct Team *team;
    struct Stack_Match *next;  
};

void delete_endlines_spaces(char*name);

void deleteList(struct Team **head);

void deleteMin(struct Team** head, float value);

int isEmptyCozi(struct Queue_Games *q);

struct Queue_Games *createQueue();

void enQueue(struct Queue_Games *q, struct Team *v, struct Player* head_player);

struct Team* deQueue(struct Queue_Games *q, struct Player* head_player);

void deleteQueue(struct Queue_Games *q);

int isEmptyStive(struct Stack_Match *top);

struct Team* top(struct Stack_Match *top);

void push(struct Stack_Match **top, struct Team *v, struct Team* head_player);

struct Team* pop(struct Stack_Match **top, struct Player* head_player);

void deleteStack(struct Stack_Match **top);