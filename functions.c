#include "functions.h"

void open_input_file(FILE **f) {
    *f = fopen("d.in", "r");
    if (*f == NULL) {
        printf("Fisierul nu a putut fi deschis \n");
        exit(1);
    }
}

void open_output_file(FILE **f) {
    *f = fopen("r.out", "w");
    if (*f == NULL) {
        printf("Fisierul nu a putut fi deschis \n");
        exit(1);
    }
}

void deleteList (struct Team **head){
    struct Team *headcopy;
    while (*head != NULL){
        headcopy = (*head) -> next ;
        free (*head);
        *head = headcopy;
    }
    *head = NULL ;
}

void deleteMin(struct Team** head, float min) {
    struct Team* current = *head;
    struct Team* prev = NULL;
    int found = 0;
    while (current != NULL) {
        if (current->team_points == min) {
            found = 1;
            break;
        }
        prev = current;
        current = current->next;
    }
    if (found == 1) {
        if (prev == NULL) {
            *head = (*head)->next;
        } else {
            prev->next = current->next;
        }
        free(current);
    }
}

int isEmptyCozi(struct Queue_Games *q){
	return (q->front==NULL);
}

struct Queue_Games *createQueue(){
    struct Queue_Games *q;
    q = (struct Queue_Games*) malloc (sizeof(struct Queue_Games));
    if(q == NULL) return NULL;
    q->front = q->rear = NULL;
    return q;
}

void enQueue(struct Queue_Games *q, struct Team *v){
	struct Team* newNode = (struct Team*) malloc (sizeof(struct Team));
	newNode->name = v->name;
	newNode->next = NULL;
	if (q->rear == NULL) q->rear = newNode;
	else{
		(q->rear)->next = newNode;
		(q->rear) = newNode;
	}
	if (q->front == NULL) q->front = q->rear;
}

char* deQueue(struct Queue_Games *q) {
	struct Team *aux; char *d;
	if (isEmptyCozi(q)) return 0;
	aux = q->front;
	d = aux->name;
	q->front = (q->front)->next;
	free(aux);
	return d;
}

void deleteQueue(struct Queue_Games *q){
	struct Team *aux;
	while (!isEmptyCozi(q)){
		aux = q->front;
		q->front = q->front->next;
		free(aux);
	}
	free(q);
}

int isEmptyStive(struct Stack_Match *top){
	return top == NULL;
}

char* top(struct Stack_Match *top){
	if (isEmptyStive(top)) return 0;
	return top->team->name;
}

void push(struct Stack_Match **top, struct Team *v) {
	struct Stack_Match *newNode = (struct Stack_Match*) malloc (sizeof(struct Stack_Match));
        newNode->team = NULL;
        newNode->team->name = v->name;
        newNode->team->team_points = v->team_points;
	newNode->next = *top;
	*top = newNode;
}

struct Team* pop(struct Stack_Match **top) {
	if (isEmptyStive(*top)) return 0;
	struct Stack_Match *temp=(*top);
	struct Team* aux = temp->team;
	*top = (*top)->next;
	free(temp);
	return aux;
}

void deleteStack(struct Stack_Match **top){
	struct Stack_Match *temp;
	while (!isEmptyStive(*top)){
		temp = *top;
		*top = (*top)->next;
		free(temp);
	}
}

