#include "functions.c"

int main() {
    FILE* input_file = NULL;
    FILE* output_file = NULL;
    open_input_file(&input_file);
    open_output_file(&output_file);
    struct Team* team = (struct Team*)malloc(sizeof(struct Team));
    struct Team* head_team = team;
    struct Team* aux = NULL;
    struct Player* head_player = NULL;
    struct Player* aux_previous = NULL;
    fscanf(input_file, "%d", &team->teams_nr);
    int number_of_teams = team->teams_nr;
    int number_of_players;

    for (int i = 0; i < number_of_teams; i++) {
        aux_previous = NULL;
        team->next = NULL;
        fscanf(input_file, "%d ", &team->player_nr);

        number_of_players = team->player_nr;

        team->name = (char*)malloc(sizeof(char) * 30);
        fgets(team->name, 30, input_file);
        int length = strlen(team->name);
        if (team->name[length - 1] == '\n')
            strcpy(team->name + (length - 1), team->name + length);

        length = strlen(team->name);
        if (team->name[length - 1] == ' ') {  // CE NU MERGE
            while (length > 0 && team->name[length - 1] == ' ') {
                length = length - 1;
            }
            team->name[length] = '\n';
            team->name[length + 1] = '\0';
        }

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
        aux = (struct Team*)malloc(sizeof(struct Team));
        team->next = aux;
        team->head_player = head_player;
        team = team->next;
    }
    team = head_team;

    int n = 1;
    while (n <= number_of_teams) {
        n = n * 2;
    }
    n = n / 2;

    float min;
    while (number_of_teams != n) {
        min = INT_MAX;
        struct Team* current = head_team;

        while (current != NULL) {
            struct Player* player = current->head_player;
            current->team_points = 0;
            for (int j = 0; j < number_of_players; j++) {
                current->team_points = current->team_points + player->points;
                player = player->next;
            }

            current->team_points = current->team_points / number_of_players;

            if (min > current->team_points) {
                min = current->team_points;
            }
            current = current->next;
        }
        // seg fault
        deleteMin(&head_team, min);
        number_of_teams--;
    }

    team = head_team;
    for (int i = 0; i < number_of_teams; i++) {
        fputs(team->name, output_file);
        fprintf(output_file, "\n");
        team = team->next;
    }
    fprintf(output_file, "\n");

    struct Queue_Games* games = createQueue();  // coada
    for (int i = 0; i < number_of_teams; i++) {
        enQueue(games, team);
    }
    struct Stack_Match* winners = NULL;  // stive
    struct Stack_Match* losers = NULL;

    team = head_team;
    int round_nr = 1;
    while (number_of_teams != 8) {
        fprintf(output_file, "--- ROUND NO:%d \n", round_nr);
        for (int i = 0; i < number_of_teams / 2; i++) {
            char* table_line = (char*)malloc(sizeof(char) * (table_size + 1));
            for (int j = 0; j < table_size; j++) {
                table_line[j] = ' ';
            }
            table_line[33] = '-';
            int k = 0;
            while (team->name[k] != '\0') {
                table_line[k] = team->name[k];
                k++;
            }

            team = team->next;
            int length = strlen(team->name), length_in_table = 0;
            k = 0;
            while (length_in_table != length + 1) {
                table_line[table_size - k] = team->name[length - k];
                length_in_table++;
                k++;
            }
            team = team->next;
            fprintf(output_file, "%s", table_line);
            fprintf(output_file, "\n");
        }

        team = head_team;
        while (team != NULL) {
            if (team->team_points >= team->next->team_points) {
                push(&winners, team);
                push(&losers, team->next);
                for (int i = 0; i < number_of_players; i++) {
                    team->player->points = team->player->points + 1;
                }
                team->team_points = team->team_points + 1;
            } else {
                push(&losers, team);
                push(&winners, team->next);
                for (int i = 0; i < number_of_players; i++) {
                    team->next->player->points = team->next->player->points + 1;
                }
                team->next->team_points = team->next->team_points + 1;
            }
            team = team->next->next;
        }
        deleteStack(&losers);
        fprintf(output_file, "\n");
        fprintf(output_file, "WINNERS OF ROUND NO:%d", round_nr);
        char* winner_line = (char*)malloc(sizeof(char) * (winner_size + 1));
        for (int i = 0; i < number_of_teams / 2; i++) {
            for (int j = 0; j < winner_size; j++) {
                winner_line[j] = ' ';
            }   
            winner_line[34] = '-';
            //print winners
            for (int i = 0; i < number_of_teams / 2; i++) {
                struct Team* aux = pop(&winners);
                int k = 0;
                while (aux->name[k] != '\0') {
                  winner_line[k] = aux->name[k];
                  k++;
                }
                char* points = (char*)malloc(sizeof(char) * 8);
                sprintf(points, "%f", aux->team_points);
                int length = strlen(points), length_in_table = 0;
                k = 0;
                while (length_in_table != length + 1) {
                    winner_line[winner_size - k] = points[length - k];
                    length_in_table++;
                    k++;
                }
            }
        fprintf(output_file, "%s", winner_line);
        fprintf(output_file, "\n");
        number_of_teams = number_of_teams / 2;
        round_nr++;
        }
    }
    fclose(input_file);
    fclose(output_file);
}   
