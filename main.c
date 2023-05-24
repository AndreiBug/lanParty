#include "functions.c"

int main( int argc, char *argv[] ) { 
    FILE* input_file = fopen(argv[2], "r");
    FILE* output_file = fopen(argv[3], "w");
    FILE* tasks = fopen(argv[1], "r");
    struct Team* team = (struct Team*)malloc(sizeof(struct Team)); ////////////////////////////task1////////////////////////////
    struct Team* head_team = team;
    struct Team* aux = NULL;
    struct Player* head_player = NULL;
    struct Player* aux_previous = NULL;
    fscanf(input_file, "%d", &team->teams_nr);
    int number_of_teams = team->teams_nr;
    int number_of_players;
    int cerinte[5];
    for (int i = 0; i < 5; i++){
        fscanf(tasks, "%d", &(cerinte[i]));
    }
    
    team->next = NULL;
    for (int i = 0; i < number_of_teams; i++) {
        aux_previous = NULL;
        fscanf(input_file, "%d", &team->player_nr);
        
        number_of_players = team->player_nr;
        
        team->name = (char*)malloc(sizeof(char) * 50);
        fgets(team->name, 50, input_file);
        delete_endlines_spaces(team->name);
        int x = 0;
        for (int j = 0; j < number_of_players; j++) {
            team->player = malloc(sizeof(struct Player));

            team->player->firstName = (char*)malloc(sizeof(char) * 50);
            fscanf(input_file, "%s", team->player->firstName);

            team->player->secondName = (char*)malloc(sizeof(char) * 50);
            fscanf(input_file, "%s", team->player->secondName);

            fscanf(input_file, "%f", &team->player->points);
            if (x == 0) {
                head_player = team->player;
                x = 1;
                aux_previous = team->player;
            } else {
                aux_previous->next = team->player;
                aux_previous = team->player;
            }
            team->player->next = NULL;
            team->player = team->player->next;
        }
        head_team = team;
        aux = (struct Team*)malloc(sizeof(struct Team));
        team->head_player = head_player;
        aux->next = team;
        team = aux;
    }
    team = head_team;

    if (cerinte[1] == 1){ ////////////////////////////task2////////////////////////////
    int n = 1;
    while (n <= number_of_teams) {
        n = n * 2;
    }
    n = n / 2;

    float min;
    while (number_of_teams != n) {
        struct Team* current = head_team;
        min = INT_MAX;
        while (current != NULL) {
            struct Player* player = current->head_player;
            current->team_points = 0;
            
            while(player != NULL) {
                current->team_points = current->team_points + player->points;
                player = player->next;
            }
            current->team_points = current->team_points / number_of_players;
            if (min > current->team_points) {
                min = current->team_points;
            }
            current = current->next;
        }
        deleteMin(&head_team, min);
        number_of_teams--;
    }
    }

    team = head_team;
    for (int i = 0; i < number_of_teams; i++) {
    fputs(team->name, output_file);
    fprintf(output_file, "\n");
    team = team->next;
    }

    if (cerinte[2] == 1) { ////////////////////////////task3////////////////////////////
    fprintf(output_file, "\n");
    struct Queue_Games* games = createQueue();  // coada
    team = head_team;
    for (int i = 0; i < number_of_teams; i++) {
        enQueue(games, team, head_player);
        team = team->next;
    }
    struct Stack_Match* winners = NULL;  // stive
    struct Stack_Match* losers = NULL;
    int round_nr = 1;
    //while (number_of_teams != 8) {
    show_games(output_file, number_of_teams, round_nr, head_player, games, &winners, &losers);
    deleteStack(&losers);
    deleteQueue(games);
    games = createQueue();
    struct Player* head_aux = head_player;
    //show_winners(output_file, number_of_teams, round_nr, head_aux, games,&winners, &losers);
    round_nr++;
    //number_of_teams = number_of_teams / 2;
    //}
    }
    fclose(input_file);
    fclose(output_file);

}