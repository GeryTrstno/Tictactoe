#include<stdio.h>

void tempat(char koor[3][3])
{
    int  i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf("%c  ", koor[i][j]);
        }
        printf("\n");
    }
}

int check(char koor[3][3])
{
    int c=0;
    for (int i=0;i<3;i++)
    {
        if ( (koor[i][0] == koor[i][1]) && (koor[i][1] == koor[i][2]) && (koor[i][0] != '-') ) {
            if (koor[i][0] == 'x')
                return -1;
            else
                return 1;
        }
        if ( (koor[0][i] == koor[1][i]) && (koor[1][i] == koor[2][i]) && (koor[0][i] != '-') ) {
            if (koor[0][i] == 'x')
                return -1;
            else
                return 1;
        }
    }
    if ( ((koor[0][0] == koor[1][1]) && (koor[1][1] == koor[2][2]) && (koor[0][0] != '-')) || ((koor[0][2] == koor[1][1]) && (koor[1][1] == koor[2][0]) && (koor[1][1] != '-')) )
    {
        if (koor[1][1] == 'x')
            return -1;
        else
            return 1;
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (koor[i][j] != '-') {
                c++;
            }
        }
    }
    if(c == 9)
        return 78;
    else
        return 0;
}

void game()
{
    char koor[3][3]= {{'-', '-', '-'}, {'-', '-', '-'}, {'-', '-', '-'}};
    int a, b, sensor = 1, pl = 1, i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf("%c  ", koor[i][j]);
        }
        printf("\n");
    }

    while (-1) {
        pl = pl % 2;
        if (pl % 2 == 1) {
            pl = 1;
        } else if (pl % 2 == 0) {
            pl = 2;
        }
        printf("Player %d Move : ", pl);
        scanf("%d %d", &a, &b);

        if (koor[a][b] == 'x' || koor[a][b] == 'o') {
            koor[a][b] = koor[a][b];
            pl--;
        } else if (pl == 1) {
            koor[a][b] = 'x';
        } else if (pl == 2) {
            koor[a][b] = 'o';
        }
        tempat(koor);
        if (check(koor) == 1 || check(koor) == -1) {
            printf("Player %d Win", pl);
            break;
        } else if (check(koor) == 78) {
            printf("Draw");
            break;
        }
        pl++;
    }
}

int minimax(char koor[3][3],int ismax)
{
    int score, i, j, pt;
    score = check(koor);
    if (score != 0)
    {
        return score;
    }
    //maximizer
    if (ismax) {
        int bpt = -1;
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                if (koor[i][j] == '-') {
                    koor[i][j] = 'o';
                    pt = minimax(koor,0);
                    koor[i][j] = '-';
                    if (pt > bpt) {
                        bpt = pt;
                    }
                }
            }
        }
        return bpt;
    }
    //minimizer
    else {
        int bpt = 1;
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                if (koor[i][j] == '-') {
                    koor[i][j] = 'x';
                    pt = minimax(koor,1);
                    koor[i][j] = '-';
                    if (pt < bpt) {
                        bpt = pt;
                    }
                }
            }
        }
        return bpt;
    }
}

void botturn(char koor[3][3])
{
    int i, j, pt, bpt=-20, index_x, index_y;
    for (i = 0;i < 3; i++) {
        for (j = 0;j < 3; j++) {
            if (koor[i][j] == '-') {
                koor[i][j]='o';
                pt = minimax(koor, 0);
                koor[i][j]='-';
                if(pt > bpt) {
                    bpt = pt;
                    index_x = i;
                    index_y = j;
                }
            }
        }
    }
    koor[index_x][index_y]='o';
}

void botgame()
{
    int a, b, i, j, pl = 1, sensor = 0, tanda = 0;
    char koor[3][3]= {{'-', '-', '-'}, {'-', '-', '-'}, {'-', '-', '-'}};

    while (-1) {
        tempat(koor);

        if (pl == 1) {
            printf("Player Move : ");
            scanf("%d %d", &a, &b);
            if (koor[a][b] == 'x' || koor[a][b] == 'o') {
                koor[a][b] = koor[a][b];
            } else {
                koor[a][b] = 'x';
                pl++;
            }
        } else if (pl % 2 == 0) {
            pl--;
            printf("Bot Turn");
            printf("\n");
            botturn(koor);
        }

        if (check(koor) == 1 || check(koor) == -1) {
            tempat(koor);
            printf("Player %d Win\n", pl);
            break;
        } else if (check(koor) == 78) {
            tempat(koor);
            printf("Draw");
            break;
        }
    }
}

int main()
{
    printf("TIC TAC TOE\n");
    printf("1 Player (press 1) or 2 Player (press 2) ?\n");

    char ch;
    ch =-1;
    while (ch!=27)
    {
        if (kbhit()) {
            ch= getch();
        }
        if (ch == 50) {
            system("cls");
            game();
            break;
        } else if (ch == 49) {
            system("cls");
            botgame();
            break;
        }
    }
}
