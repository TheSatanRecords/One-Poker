#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define DECK_SIZE 52

const char suits[] = {03, 04, 05, 06};
const char *ranks[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

typedef struct {
    char c1; char c2; unsigned char w;
} Player;

char random_card(char e1, char e2, char e3) {
    if (e1 == 0) e1 = -1;
    if (e2 == 0) e2 = -1;
    if (e3 == 0) e3 = -1;
    char card;
    do {
        card = rand() % DECK_SIZE;
    } while (card == e1 || card == e2 || card == e3);
    return card;
}

char duel(char c1, char c2) {
    char rank1 = c1 % 13;
    char rank2 = c2 % 13;

    if (rank1 == 0) rank1 = 13;
    if (rank2 == 0) rank2 = 13;

    if (rank1 == 13 && rank2 == 1) return 2;
    if (rank2 == 13 && rank1 == 1) return 1;

    if (rank1 > rank2) return 1;
    else if (rank1 < rank2) return 2;
    else return 0;
}

void hand(const Player *p) {
    char rank1 = p->c1 % 13;
    char rank2 = p->c2 % 13;

    bool is_up1 = (rank1 >= 7 || rank1 == 0);
    bool is_up2 = (rank2 >= 7 || rank2 == 0);

    if (is_up1 && is_up2) {
        printf("UP/UP\n");
    } else if (!is_up1 && !is_up2) {
        printf("DOWN/DOWN\n");
    } else {
        printf("UP/DOWN\n");
    }
}

char* selectc(char card) {
    char suit = card / 13;
    char rank = card % 13;

    char* card_str = (char*)malloc(4 * sizeof(char));
snprintf(card_str, sizeof(card_str), "%s%c", ranks[rank], suits[suit]);
    return card_str;
}

int main() {
    srand(time(NULL));
    
    char player_card = 1;
    Player p1 = {0, 0, 0};
    Player p2 = {0, 0, 0};
    char c1, c2;
    printf("# ONE POKER #\n");
    while (player_card == 1 || player_card == 2) {
char select = 0;
if (p1.c1 == 0) p1.c1 = random_card(p1.c2, p2.c1, p2.c2);
        if (p1.c2 == 0) p1.c2 = random_card(p1.c1, p2.c1, p2.c2);
        if (p2.c1 == 0) p2.c1 = random_card(p1.c1, p1.c2, p2.c2);
        if (p2.c2 == 0) p2.c2 = random_card(p1.c1, p1.c2, p2.c1);

printf("Your hand: ");
printf("%s %s\n", selectc(p1.c1), selectc(p1.c2));
printf("Player 2 : ");
hand(&p2);
printf("\n");
    printf("Enter your card (1 or 2): ");
    scanf("%d", &player_card);

        c1 = (player_card == 1) ? p1.c1 : p1.c2;
        c2 = rand() % 2 ? p2.c1 : p2.c2;

printf("Player plays card %s\n", selectc(c1));
printf("Player 2 plays %s\n", selectc(c2));

        char result = duel(c1, c2);
        if (result == 1) {p1.w++; printf("Player 1 wins!");}
        else if (result == 2) {p2.w++; printf("Player 2 wins!");}
        else printf("It's a tie!");
        printf(" [%d/%d]\n\n",p1.w,p2.w);

        if (player_card == 1 || player_card == 2) {
            if (player_card == 1) p1.c1 = 0; else p1.c2 = 0;
            if (c2 == p2.c1) p2.c1 = 0; else p2.c2 = 0;
        }
    }

    return 0;
}
