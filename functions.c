#include "functions.h"

void delete_endlines_spaces(char *name){
    int length = strlen(name);
    if (name[length - 1] == '\n' || name[length - 1] == ' ')
        strcpy(name + (length - 1), name + length);

    length = strlen(name);
    if (name[length - 1] == ' ') {
        while (length > 0 && name[length - 1] == ' ') {
            strcpy(name + (length - 1), name + length);
            }
        }
    length = strlen(name);
    if(name[0] == ' '){
            for (int i = 0; i < length - 1; i++){
            name[i] = name[i + 1];
            }
            name[length - 1] = '\0';
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

void enQueue(struct Queue_Games *q, struct Team *v, struct Player* head_player){
	struct Team* newNode = (struct Team*) malloc (sizeof(struct Team));
        newNode->name = (char *)malloc(sizeof(char) * 50);
        strcpy(newNode->name, v->name);
	newNode->team_points = v->team_points;
    v->player = head_player;
    while (v->player != NULL) {
        newNode->player = v->player;
        newNode->player->points = v->player->points;
        newNode->player = newNode->player->next;
        v->player = v->player->next;
    }
	newNode->next = NULL;
	if (q->rear == NULL) q->rear = newNode;
	else{
		(q->rear)->next = newNode;
		(q->rear) = newNode;
	}
	if (q->front == NULL) q->front = q->rear;
}

struct Team* deQueue(struct Queue_Games *q, struct Player* head_player) {
	struct Team *aux;
    struct Team *d = malloc(sizeof(struct Team));
	if (isEmptyCozi(q)) return 0;
	aux = q->front;
	d->name = (char*) malloc (sizeof(char) * 50);
    strcpy(d->name,aux->name);
	d->team_points = aux->team_points;
    aux->player = head_player;
    while (aux->player != NULL) {
        d->player = aux->player;
        d->player->points = aux->player->points;
        aux->player = aux->player->next;
        d->player = d->player->next;
    }
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

struct Team* top(struct Stack_Match *top){
	if (isEmptyStive(top)) return 0;
	return top->team;
}

void push(struct Stack_Match **top, struct Team *v, struct Team* head_player) {
        struct Stack_Match *newNode =
            (struct Stack_Match *)malloc(sizeof(struct Stack_Match));
        newNode->team = (struct Team *)malloc(sizeof(struct Team));
        newNode->team->name = (char *)malloc(sizeof(char) * 50);
        strcpy(newNode->team->name, v->name);
        newNode->team->team_points = v->team_points;
        v->player = head_player;
        while (v->player != NULL) {
                newNode->team->player = v->player;
                newNode->team->player->points = v->player->points;
                newNode->team->player = newNode->team->player->next;
                v->player = v->player->next;
    }
    newNode->next = *top;
    *top = newNode;
}


struct Team* pop(struct Stack_Match **top, struct Player* head_player) {
    if (isEmptyStive(*top)) return NULL;
    struct Stack_Match *temp = *top;
    struct Team* aux = temp->team;
    aux->name = strdup(temp->team->name);
    temp->team->player = head_player;
    while (temp->team->player != NULL) {
        aux->player = temp->team->player;
        aux->player->points = temp->team->player->points;
        aux->player = aux->player->next;
        temp->team->player = temp->team->player->next;
    }
    aux->team_points = temp->team->team_points;
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

void task1(FILE* tasks, FILE*input_file, int cerinte[], struct Team** team, int number_of_teams, struct Player* aux_previous, int number_of_players, struct Player* head_player, struct Team** head_team, struct Team* aux){
    for (int i = 0; i < 5; i++){
        fscanf(tasks, "%d", &(cerinte[i]));
    }
    
    (*team)->next = NULL;
    for (int i = 0; i < number_of_teams; i++) {
        aux_previous = NULL;
        fscanf(input_file, "%d", &(*team)->player_nr);
        
        number_of_players = (*team)->player_nr;
        
        (*team)->name = (char*)malloc(sizeof(char) * 50);
        fgets((*team)->name, 50, input_file);
        delete_endlines_spaces((*team)->name);
        int x = 0;
        for (int j = 0; j < number_of_players; j++) {
            (*team)->player = malloc(sizeof(struct Player));

            (*team)->player->firstName = (char*)malloc(sizeof(char) * 50);
            fscanf(input_file, "%s", (*team)->player->firstName);

            (*team)->player->secondName = (char*)malloc(sizeof(char) * 50);
            fscanf(input_file, "%s", (*team)->player->secondName);

            fscanf(input_file, "%f", &(*team)->player->points);
            if (x == 0) {
                head_player = (*team)->player;
                x = 1;
                aux_previous = (*team)->player;
            } else {
                aux_previous->next = (*team)->player;
                aux_previous = (*team)->player;
            }
            (*team)->player->next = NULL;
            (*team)->player = (*team)->player->next;
        }
        (*head_team) = (*team);
        aux = (struct Team*)malloc(sizeof(struct Team));
        (*team)->head_player = head_player;
        aux->next = (*team);
        (*team) = aux;
    }
    (*team) = (*head_team);
}

void show_games(FILE *output_file, int number_of_teams, int round_nr, struct Player* head_player, struct Queue_Games* games, struct Stack_Match** winners, struct Stack_Match** losers) {
        struct Team *team_aux1 = NULL;
        struct Team *team_aux2 = NULL;
        fprintf(output_file, "--- ROUND NO:%d", round_nr);
        for (int i = 0; i < number_of_teams / 2; i++) {
                struct Team *team_aux1 = (struct Team *)malloc(sizeof(struct Team));
                struct Player *player_aux1 = head_player;
                team_aux1 = deQueue(games, player_aux1);
                char *table_line = (char *)malloc(sizeof(char) * (table_size));
            for (int j = 0; j < table_size; j++) {
                table_line[j] = ' '; 
            }
        fprintf(output_file, "\n");
        table_line[33] = '-';
        int k = 0;
        while (team_aux1->name[k + 1] != '\0') {
            table_line[k] = team_aux1->name[k]; 
            k++;
        }
        struct Team* team_aux2 = (struct Team*)malloc(sizeof(struct Team));
        struct Player* player_aux2 = head_player;
        team_aux2 = deQueue(games, player_aux2);
        int length = strlen(team_aux2->name), length_in_table = 0;
        k = 0;
        while (length_in_table != length + 1) {
            table_line[table_size - k - 1] = team_aux2->name[length - k];
            length_in_table++;
            k++;
        }
        fputs(table_line, output_file);
        free(table_line);
        if (team_aux1->team_points >= team_aux2->team_points) {
            team_aux1->player = head_player;
            while (team_aux1->player != NULL) {
                team_aux1->player->points++;
                team_aux1->player = team_aux1->player->next;
                }
                team_aux1->team_points++;
            push(winners, team_aux1, head_player);
            push(losers, team_aux2, head_player);
            } else if (team_aux1->team_points < team_aux2->team_points) {
            team_aux2->player = head_player;
            while (team_aux2->player != NULL) {
                team_aux2->player->points++;
                team_aux2->player = team_aux2->player->next;
            }
                team_aux2->team_points++;
            push(winners, team_aux2, head_player);
            push(losers, team_aux1, head_player);
            }
            team_aux1 = team_aux1->next;
            team_aux2 = team_aux2->next;
    }
}

/*void show_winners(FILE *output_file, int number_of_teams, int round_nr, struct Player* head_player, struct Queue_Games* games, struct Stack_Match** winners, struct Stack_Match** losers){
    fprintf(output_file, "\n\nWINNERS OF ROUND NO:%d", round_nr);
    for (int i = 0; i < number_of_teams / 2; i++) {
        char* winner_line = (char*) malloc (sizeof(char) * winner_size+1);
        games->front = pop(winners, head_player);
        for (int j = 0; j < winner_size; j++) {
            winner_line[j] = ' ';
        }
        winner_line[34] = '-';
        int k = 0;
        while (games->front->name[k + 1] != '\0') {
            winner_line[k] = games->front->name[k]; 
            k++;
        }

        fprintf(output_file,"\n");
        fputs(winner_line, output_file);
        fprintf(output_file, "%.2f", games->front->team_points);
    }
}*/