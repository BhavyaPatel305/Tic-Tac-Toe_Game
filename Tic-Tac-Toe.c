// Name: Bhavya Patel
// student Id: 110065852
// Lab Section : 53

// For input of X or O , use (capital) X and (capital) O

// If 1 of the 2 players wins the game but both have same scores than in that case the score of the
// winning player increases by 1.
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void InitializeBoard(int m, int n, char board[][n]);
void PrintBoard(int m, int n, char board[][n]);
int IsValidBoard(int m, int n, char board[][n]);
void ListWinningCells(int m, int n, char board[][n], char s);
char WhoIsTheWinner(int m, int n, char board[][n]);
int validEmailAddress(char emailAddress[]);
void ToLowerCase(char *pStr);
int isAlpha(char *pStr);
int playerId = 0;
int totalNumberOfGames = 0;
struct playerAccount
{
    char firstName[25];
    char lastName[25];
    char emailAddress[100];
    int playerId;
    int playerScore;
    int games;
};
struct gameId
{
    int gameid;
    int player1Id;
    int player2Id;
    char player1Role;
    char player2Role;
    char board[3][3];
    char lastMove;
    char status[20];
};

int j = 0;
void createPlayerAccount(struct playerAccount players[], int size);
void leaderBoard(struct playerAccount players[],struct gameId games[], int size,int sizeOfgames);
void printFun(struct playerAccount players[], int size);
int i = 0;
int numberOfPlayers = 0;
void CreateBoard(int m, int n, char board[][n], int, int, struct playerAccount players[], int, int, struct gameId games[], int sizeOfgames);
void createGame(int m, int n, char board[][n], int, int, struct playerAccount players[], struct gameId games[], int sizeOfgames);
int savedGames(struct gameId games[], int sizeOfgames);
void createSavedGame(int m, int n, char board[][n], int player1, int player2, struct playerAccount players[], struct gameId games[], int sizeOfgames);
int main(void)
{
    char board[3][3];
    InitializeBoard(3, 3, board);
    char input;
    int game = 10;
    int totalPlayers = 5;

    struct gameId *hello = (struct gameId*)malloc(game * sizeof(hello));

    struct playerAccount *players = (struct playerAccount*)malloc(totalPlayers * sizeof(struct playerAccount));;


    while(1)
    {
        if (i == (totalPlayers-1))
        {
            int x = (totalPlayers / 2);
            x = x + totalPlayers;
            players = realloc(players,x*sizeof(players));
            if (players == NULL)
            {
                printf("\n There is no enough memory to continue the game further.\n");
            }
        }
        if (j == game)
        {
            int x = (game / 2);
            x = x + game;
            hello = realloc(hello,x*sizeof(hello));
            if (hello == NULL)
            {
                printf("\n There is no enough memory to continue the game further.\n");
            }
        }
        fflush(stdin);
        printf("press 'P' to add new player\n");
        printf("press 'G' to play a new game or load and play a saved game\n");
        printf("press 'L' to display the leader board\n");
        printf("press 'e' to Exit\n");
        scanf("%c",&input);
        if (input == 'e')
        {
            break;
        }
        if (input == 'P')
        {
            numberOfPlayers++;
            createPlayerAccount(players, i);
            i++;
        }
        if (input == 'G')
        {
           char input;
           printf("\nPress 'N' to create a new game.\n");
           printf("Press 'S' to continue playing a saved game.\n");
           fflush(stdin);
           scanf("%c",&input);
           if (input == 'N')
           {
               int player1 = 0;
               int player2 = 0;
               int flg1 = 0;
               int flg2 = 0;
               int x = 0;
               int y = 0;
               printf("Player1 please enter your player ID:");
               scanf("%d",&player1);

               printf("Player2 please enter your player ID:");
               scanf("%d",&player2);

               for (int i = 0; i<numberOfPlayers; i++)
               {
                   if (player1 == players[i].playerId)
                   {
                       flg1 = 1;
                       x = i;
                   }
                   if (player2 == players[i].playerId)
                   {
                       flg2 = 1;
                       y = i;
                   }
               }
               if (flg1 == 1 && flg2 == 1)
               {
                   createGame(3, 3, board, players[x].playerId, players[y].playerId, players, hello, totalPlayers);
               }
               if (flg1 != 1)
               {
                   printf("\nPlayer 1 is not registered. You first need to register to play the game.\n");
               }
               if (flg2 != 1)
               {
                   printf("\nPlayer 2 is not registered. You first need to register to play the game.\n");
               }
           }
           if (input == 'S')
           {
               createSavedGame(3, 3, board, -1, -1, players, hello, totalPlayers);
           }
        }

        if (input == 'L')
        {
            leaderBoard(players,hello, i, totalNumberOfGames);
        }
    }

    return 0;
}
void InitializeBoard(int m, int n, char board[][n])
{
    int c = 1;
    for(int i = 0; i<m ; i++){
        for(int j = 0; j<n; j++){
                board[i][j] = c + '0';
                c++;
        }
    }
}
void PrintBoard(int m, int n, char board[][n])
{
    printf("\n   |   |  \n");
    for(int i = 0; i<m ; i++){
        for(int j = 0; j<n ;j++){
            if (j == n-1)
            {
                printf(" %c ",board[i][j]);
                continue;
            }
            printf(" %c |",board[i][j]);
        }
        printf("\n");
        if (i == 0 || i == 1)
        {
            printf("___|___|___\n");
        }
        printf("   |   |  ");
        printf("\n");
    }
}


void CreateBoard(int m, int n, char board[][n], int Player1, int Player2, struct playerAccount players[], int saved, int ID, struct gameId helo[], int sizeOfgames)
{
    int turn = 0;
    int counter = 0;
    int exception1 = 0;
    if (saved == 0)
    {
        players[Player1].games++;
        players[Player2].games++;
        helo[j].gameid = j;
        strcpy(helo[j].status,"Ongoing");
    }
    if (saved == 1)
    {
        strcpy(helo[ID].status,"Ongoing");
        if (helo[j].player2Role == 'X')
        {
            switch(helo[ID].lastMove)
            {
                case 'O':
                    turn = Player1;
                    printf("\n Player 1's turn\n");
                    counter++;
                    break;
                case 'X':
                    turn = Player2;
                    printf("\n Player 2's turn\n");
                    break;
            }
        }
        if (helo[j].player1Role = 'X')
        {
            switch(helo[ID].lastMove)
            {
                case 'O':
                    turn = Player2;
                    printf("\n Player 2's turn\n");
                    counter++;
                    break;
                case 'X':
                    turn = Player1;
                    printf("\n Player 1's turn\n");
                    break;
            }
        }

    }
    if (saved == 0)
    {
       helo[j].player1Id = Player1;
       helo[j].player2Id = Player2;
    }

    int number;

    char symbol;
    char num;
    PrintBoard(3, 3, board);

    if (saved == 0)
    {
        if (players[Player1 - 1].playerScore == players[Player2 - 1].playerScore)
        {
            printf("\nPlayer 1 is now player X.\n");
            printf("\nPlayer 2 is now player O.\n");
            turn = Player1;
            helo[j].player1Role = 'X';
            helo[j].player2Role = 'O';
        }
        if (players[Player1 - 1].playerScore < players[Player2 - 1].playerScore)
        {
            printf("\nPlayer 1 is now player X.\n");
            printf("\nPlayer 2 is now player O.\n");
            turn = Player1;
            helo[j].player1Role = 'X';
            helo[j].player2Role = 'O';
        }
        if (players[Player1 - 1].playerScore > players[Player2 - 1].playerScore)
        {
            exception1 = 1;
            printf("\nPlayer 2 is now player X.\n");
            printf("\nPlayer 1 is now player O.\n");
            printf("\n Player 2's turn\n");
            turn = Player2;
            counter++;
            helo[j].player2Role = 'X';
            helo[j].player1Role = 'O';
        }
    }
    if (saved == 0 && turn == Player1)
    {
        printf("\n Player 1's turn\n");
    }

    if (saved == 0)
    {
        helo[j].lastMove = 'X';
    }

    char s;
    while(1)
    {
        fflush(stdin);
        printf("Enter the number of the cell where you want to insert X or 0 or enter -1 to pause and save the game or enter -2 to know the winning moves.\n");
        scanf("%d",&number);
        if (number == -1)
        {
            break;
        }
        if (number == -2)
        {
            if (turn == Player1)
            {
                players[Player1 - 1].playerScore--;
                s = 'X';
                ListWinningCells(3, 3, board, s);
            }
            if (turn == Player2)
            {
                players[Player2 - 1].playerScore--;
                s = 'O';
                ListWinningCells(3, 3, board, s);
            }
        }

        if (number < 1 || number > 9)
        {
            PrintBoard(3, 3, board);
            continue;
        }
        num = number + '0';
        for(int i = 0; i<m ; i++){
            for(int j = 0; j<n; j++){
                if (board[i][j] == num)
                {
                    fflush(stdin);
                    printf("Type X or O\n");
                    scanf("%c",&symbol);
                    if (symbol != 'X' && symbol != 'O')
                    {
                        continue;
                    }

                    if (symbol == 'X')
                    {
                        if (exception1 == 0)
                        {
                            if (turn == Player2)
                            {
                                printf("\nYou are player O you cannot enter X as input.\n");
                                while (symbol != 'O')
                                {
                                    printf("Type O\n");
                                    fflush(stdin);
                                    scanf("%c",&symbol);
                                    board[i][j] = symbol;
                                }
                            }
                            else
                            {
                                board[i][j] = 'X';
                            }
                        }
                        if (exception1 == 1)
                        {
                            board[i][j] = symbol;
                        }
                    }
                    if (symbol == 'O')
                    {
                        if (exception1 == 0)
                        {
                            if (turn == Player1)
                            {
                                printf("\nYou are player X you cannot enter O as input.\n");
                                while (symbol != 'X')
                                {
                                    printf("Type X\n");
                                    fflush(stdin);
                                    scanf("%c",&symbol);
                                    board[i][j] = symbol;
                                }
                            }
                            else
                            {
                                board[i][j] = 'O';
                            }
                        }
                        if (exception1 == 1)
                        {
                            board[i][j] = symbol;
                        }
                    }

                    if (counter % 2 == 0)
                    {
                        if (saved == 0)
                        {
                            helo[j].lastMove = 'O';

                        }
                        if (saved == 1)
                        {
                            helo[ID].lastMove = 'O';
                        }

                        turn = Player2;
                        counter++;
                    }
                    else if (counter % 2 != 0)
                    {
                        if (saved == 0)
                        {
                            helo[j].lastMove = 'X';

                        }
                        if (saved == 1)
                        {
                            helo[ID].lastMove = 'X';
                        }

                        turn = Player1;
                        counter++;
                    }

                }
            }
        }
        if (saved == 0)
        {
                for(int i = 0; i<m ; i++){
                for(int k = 0; k<n ;k++){
                    helo[j].board[i][k] = board[i][k];
                }
            }
        }
        if (saved == 1)
        {
            for(int i = 0; i<m ; i++){
                for(int k = 0; k<n ;k++){
                    helo[ID].board[i][k] = board[i][k];
                }
            }
        }

        PrintBoard(3, 3, board);


        char y = WhoIsTheWinner(3, 3, board);
        if (y == 'X')
        {
            printf("\nPlayer X is the winner.\n\n");
            if (saved == 0)
            {
                strcpy(helo[j].status,"X won");
            }
            if (saved == 1)
            {
                strcpy(helo[ID].status,"X won");
            }

            if (players[Player1 - 1].playerScore >= players[Player2 - 1].playerScore)
            {
                players[Player1 - 1].playerScore++;
            }
            if (players[Player1 - 1].playerScore < players[Player2 - 1].playerScore)
            {
                players[Player1 - 1].playerScore += 3;
                players[Player2 - 1].playerScore -= 2;

            }
            printf("\n");
            leaderBoard(players,helo, i, totalNumberOfGames);

            return;
        }
        if (y == 'O')
        {
            printf("\nPlayer O is the winner.\n\n");
            if (saved == 0)
            {
                strcpy(helo[j].status,"O won");
            }
            if (saved == 1)
            {
                strcpy(helo[ID].status,"O won");
            }

            if (players[Player2 - 1].playerScore >= players[Player1 - 1].playerScore)
            {
                players[Player2 - 1].playerScore++;
            }
            if (players[Player2 - 1].playerScore < players[Player1 - 1].playerScore)
            {
                players[Player2 - 1].playerScore += 3;
                players[Player1 - 1].playerScore -= 2;
            }
            printf("\n");
            leaderBoard(players,helo, i, totalNumberOfGames);
            return;
        }
        if (y == 'D')
        {
            int flg = 0;
            for(int i = 0; i<m ; i++){
                for(int k = 0; k<n; k++){
                       if (board[i][k] != 'X' && board[i][k] != 'O')
                       {
                           if (saved == 0)
                           {
                               strcpy(helo[j].status,"Ongoing");
                           }
                           if (saved == 1)
                           {
                               strcpy(helo[ID].status,"Ongoing");
                           }

                           flg = 1;
                           break;
                       }
                    }
            }
            if (flg == 0)
            {
                if (saved == 0)
                {
                    strcpy(helo[j].status,"Draw");
                }
                if (saved == 1)
                {
                    strcpy(helo[ID].status,"Draw");
                }

                printf("\nGame is Draw.\n");
                printf("\n");
                leaderBoard(players,helo, i, totalNumberOfGames);
                break;
            }
            printf("\n");
            leaderBoard(players,helo, i, totalNumberOfGames);
        }

        if (turn == Player1)
        {
            printf("\n Player 1's turn\n");
        }
        if (turn == Player2)
        {
            printf("\n Player 2's turn\n");

        }

    }
    if (saved == 0)
    {
       j++;
    }

}

int IsValidBoard(int m, int n, char board[][n])
{
    int numberOfX = 0;
    int numberOf0 = 0;
    int difference = 0;
    for(int i = 0; i<m ; i++){
        for(int j = 0; j<n; j++){
            if (board[i][j] == 'X')
            {
                numberOfX++;
            }
            if (board[i][j] == 'O')
            {
                numberOf0++;
            }
        }
    }
    difference = abs(numberOfX - numberOf0);
    if (difference == 0)
    {
        return 1;
    }
    if (difference == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void ListWinningCells(int m, int n, char board[][n], char s)
{
    int x = IsValidBoard(3, 3, board);
    if(x == 0)
    {
        printf("\nSince the board is Invalid , winning cells cannot be predicted.\n\n");
        return;
    }
    char winningCellsForX[9];
    int row = 0;
    int col = 0;
    fflush(stdin);
    char winningCellsFor0[9] = "";
    int counterForX = 0;
    int counterFor0 = 0;
    char emptyCell;
    for (int i = 0; i<m; i++)    // For rows
    {
        for (int j = 0; j<n; j++)
        {
            if (board[i][j] == 'X')
            {
                counterForX++;
            }
            if (board[i][j] == 'O')
            {
                counterFor0++;
            }
            if (board[i][j] != 'X' && board[i][j] != 'O')
            {
                emptyCell = board[i][j];
            }
        }
        if (counterForX >= 2)
        {
            winningCellsForX[row] = emptyCell;
            row++;
        }
        if (counterFor0 >= 2)
        {
            winningCellsFor0[col] = emptyCell;
            col++;
        }
        counterForX = 0;
        counterFor0 = 0;
    }

    for (int i = 0; i<m; i++)   // For column 1
    {
        for (int j = 0; j<1; j++)
        {
            if (board[i][j] == 'X')
            {
                counterForX++;
            }
            if (board[i][j] == 'O')
            {
                counterFor0++;
            }
            if (board[i][j] != 'X' && board[i][j] != 'O')
            {
               emptyCell = board[i][j];
            }
        }
    }
    if (counterForX >= 2)
    {
        winningCellsForX[row] = emptyCell;
        row++;
    }
    if (counterFor0 >= 2)
    {
        winningCellsFor0[col] = emptyCell;
        col++;
    }
    counterForX = 0;
    counterFor0 = 0;

    for (int i = 0; i<m; i++)   // For column 2
    {
        for (int j = 1; j<2; j++)
        {
            if (board[i][j] == 'X')
            {
                counterForX++;
            }
            if (board[i][j] == 'O')
            {
                counterFor0++;
            }
            if (board[i][j] != 'X' && board[i][j] != 'O')
            {
                emptyCell = board[i][j];
            }
        }
    }
    if (counterForX >= 2)
    {
        winningCellsForX[row] = emptyCell;
        row++;
    }
    if (counterFor0 >= 2)
    {
        winningCellsFor0[col] = emptyCell;
        col++;
    }
    counterForX = 0;
    counterFor0 = 0;

    for (int i = 0; i<m; i++)   // For column 3
    {
        for (int j = 2; j<3; j++)
        {
            if (board[i][j] == 'X')
            {
                counterForX++;
            }
            if (board[i][j] == 'O')
            {
                counterFor0++;
            }
            if (board[i][j] != 'X' && board[i][j] != 'O')
            {
                emptyCell = board[i][j];
            }
        }
    }
    if (counterForX >= 2)
    {
        winningCellsForX[row] = emptyCell;
        row++;
    }
    if (counterFor0 >= 2)
    {
        winningCellsFor0[col] = emptyCell;
        col++;
    }
    counterForX = 0;
    counterFor0 = 0;

    for (int i = 0; i<m; i++)   // For Diagonal 1
    {
        for (int j = 0; j<n; j++)
        {
            if(i == j)
            {
                if (board[i][i] == 'X')
                {
                    counterForX++;
                }
                if (board[i][i] == 'O')
                {
                    counterFor0++;
                }
                if (board[i][i] != 'X' && board[i][i] != 'O')
                {
                    emptyCell = board[i][j];
                }
            }
        }
    }
    if (counterForX >= 2)
    {
        winningCellsForX[row] = emptyCell;
        row++;
    }
    if (counterFor0 >= 2)
    {
        winningCellsFor0[col] = emptyCell;
        col++;
    }
    counterForX = 0;
    counterFor0 = 0;


    for (int i = 0; i<m; i++)   // For Diagonal 2
    {
        for (int j = 0; j<n; j++)
        {
                if ((i + j) == (n-1))
                {
                    if (board[i][j] == 'X')
                    {
                        counterForX++;
                    }
                    if (board[i][j] == 'O')
                    {
                        counterFor0++;
                    }
                    if (board[i][j] != 'X' && board[i][j] != 'O')
                    {
                        if (counterForX >= 2 || counterFor0 >= 2)
                        {
                            emptyCell = board[i][j];
                        }
                        else
                        {
                            emptyCell = '\0';
                        }

                    }
            }
        }
    }
    if (counterForX >= 2)
    {
        winningCellsForX[row] = emptyCell;
        row++;
    }
    if (counterFor0 >= 2)
    {
        if (emptyCell != '\0')
        {
            winningCellsFor0[col] = emptyCell;
            col++;
        }

    }
    counterForX = 0;
    counterFor0 = 0;
    if (s == 'X')
    {
        if (strlen(winningCellsForX) != 0)
        {
            printf("Winning Cells For Player X : ");
        }
        for (int i = 0; i<9; i++)
        {
            if (winningCellsForX[i] == '1')
            {
                printf(" 1 ");
            }
            if (winningCellsForX[i] == '2')
            {
                printf(" 2 ");
            }
            if (winningCellsForX[i] == '3')
            {
                printf(" 3 ");
            }
            if (winningCellsForX[i] == '4')
            {
                printf(" 4 ");
            }
            if (winningCellsForX[i] == '5')
            {
                printf(" 5 ");
            }
            if (winningCellsForX[i] == '6')
            {
                printf(" 6 ");
            }
            if (winningCellsForX[i] == '7')
            {
                printf(" 7 ");
            }
            if (winningCellsForX[i] == '8')
            {
                printf(" 8 ");
            }
            if (winningCellsForX[i] == '9')
            {
                printf(" 9 ");
            }
        }
        printf("\n");
        if (strlen(winningCellsForX) == 0)
        {
            printf("No winning cells for player X\n\n");
        }
    }
    if (s == 'O')
    {
        if (strlen(winningCellsFor0) != 0)
        {
            printf("Winning Cells For Player O : ");
        }
        for (int i = 0; i<9; i++)
        {
            if (winningCellsFor0[i] == '1')
            {
                printf(" 1 ");
            }
            if (winningCellsFor0[i] == '2')
            {
                printf(" 2 ");
            }
            if (winningCellsFor0[i] == '3')
            {
                printf(" 3 ");
            }
            if (winningCellsFor0[i] == '4')
            {
                printf(" 4 ");
            }
            if (winningCellsFor0[i] == '5')
            {
                printf(" 5 ");
            }
            if (winningCellsFor0[i] == '6')
            {
                printf(" 6 ");
            }
            if (winningCellsFor0[i] == '7')
            {
                printf(" 7 ");
            }
            if (winningCellsFor0[i] == '8')
            {
                printf(" 8 ");
            }
            if (winningCellsFor0[i] == '9')
            {
                printf(" 9 ");
            }
        }
        printf("\n");
        if (strlen(winningCellsFor0) == 0)
        {
            printf("No winning cells for player O\n\n");
        }
    }
}
char WhoIsTheWinner(int m, int n, char board[][n])
{
    int counterForX = 0;
    int counterFor0 = 0;
    for (int i = 0; i<m; i++)    // For rows
    {
        for (int j = 0; j<n; j++)
        {
            if (board[i][j] == 'X')
            {
                counterForX++;
            }
            if (board[i][j] == 'O')
            {
                counterFor0++;
            }
        }
        if (counterForX == 3)
        {
            int x = IsValidBoard(3, 3, board);
            if(x == 0)
            {
                printf("\nBoard is invalid.\n\n");
                return 'D';
            }
            return 'X';
        }
        if (counterFor0 == 3)
        {
            int x = IsValidBoard(3, 3, board);
            if(x == 0)
            {
                printf("\nBoard is invalid.\n\n");
                return 'D';
            }
            return 'O';
        }
        counterForX = 0;
        counterFor0 = 0;
    }
    counterForX = 0;
    counterFor0 = 0;

    for (int i = 0; i<m; i++)   // For column 1
    {
        for (int j = 0; j<1; j++)
        {
            if (board[i][j] == 'X')
            {
                counterForX++;
            }
            if (board[i][j] == 'O')
            {
                counterFor0++;
            }
        }
    }
    if (counterForX == 3)
    {
        int x = IsValidBoard(3, 3, board);
        if(x == 0)
        {
            printf("\nBoard is invalid.\n\n");
            return 'D';
        }
        return 'X';
    }
    if (counterFor0 == 3)
    {
        int x = IsValidBoard(3, 3, board);
        if(x == 0)
        {
            printf("\nBoard is invalid.\n\n");
            return 'D';
        }
        return 'O';
    }
    counterForX = 0;
    counterFor0 = 0;

    for (int i = 0; i<m; i++)   // For column 2
    {
        for (int j = 1; j<2; j++)
        {
            if (board[i][j] == 'X')
            {
                counterForX++;
            }
            if (board[i][j] == 'O')
            {
                counterFor0++;
            }
        }
    }
    if (counterForX == 3)
    {
        int x = IsValidBoard(3, 3, board);
        if(x == 0)
        {
            printf("\nBoard is invalid.\n\n");
            return 'D';
        }
        return 'X';
    }
    if (counterFor0 == 3)
    {
        int x = IsValidBoard(3, 3, board);
        if(x == 0)
        {
            printf("\nBoard is invalid.\n\n");
            return 'D';
        }
        return 'O';
    }
    counterForX = 0;
    counterFor0 = 0;

    for (int i = 0; i<m; i++)   // For column 3
    {
        for (int j = 2; j<3; j++)
        {
            if (board[i][j] == 'X')
            {
                counterForX++;
            }
            if (board[i][j] == 'O')
            {
                counterFor0++;
            }
        }
    }
    if (counterForX == 3)
    {
        int x = IsValidBoard(3, 3, board);
        if(x == 0)
        {
            printf("\nBoard is invalid.\n\n");
            return 'D';
        }
        return 'X';
    }
    if (counterFor0 == 3)
    {
        int x = IsValidBoard(3, 3, board);
        if(x == 0)
        {
            printf("\nBoard is invalid.\n\n");
            return 'D';
        }
        return 'O';
    }
    counterForX = 0;
    counterFor0 = 0;

    for (int i = 0; i<m; i++)   // For Diagonal 1
    {
        for (int j = 0; j<n; j++)
        {
            if(i == j)
            {
                if (board[i][i] == 'X')
                {
                    counterForX++;
                }
                if (board[i][i] == 'O')
                {
                    counterFor0++;
                }
            }
        }
    }
    if (counterForX == 3)
    {
        int x = IsValidBoard(3, 3, board);
        if(x == 0)
        {
            printf("\nBoard is invalid.\n\n");
            return 'D';
        }
        return 'X';
    }
    if (counterFor0 == 3)
    {
        int x = IsValidBoard(3, 3, board);
        if(x == 0)
        {
            printf("\nBoard is invalid.\n\n");
            return 'D';
        }
        return 'O';
    }
    counterForX = 0;
    counterFor0 = 0;

    for (int i = 0; i<m; i++)   // For Diagonal 2
    {
        for (int j = 0; j<n; j++)
        {
                if ((i + j) == (n-1))
                {
                    if (board[i][j] == 'X')
                    {
                        counterForX++;
                    }
                    if (board[i][j] == 'O')
                    {
                        counterFor0++;
                    }
            }
        }
    }
    if (counterForX == 3)
    {
        int x = IsValidBoard(3, 3, board);
        if(x == 0)
        {
            printf("\nBoard is invalid.\n\n");
            return 'D';
        }
        return 'X';
    }
    if (counterFor0 == 3)
    {
        int m = IsValidBoard(3, 3, board);
        if(m == 0)
        {
            printf("\nBoard is invalid.\n\n");
            return 'D';
        }
        return 'O';
    }
    counterForX = 0;
    counterFor0 = 0;
    return 'D';
}
void createPlayerAccount(struct playerAccount player[], int i)
{
    printf("Enter the First name of the player:");
    scanf("%s",player[i].firstName);

    int alpha = isAlpha(player[i].firstName);
    while (alpha == 0)
    {
        printf("\nFirst Name should only have alphabetical characters no digits or spaces !!!\n\n");
        printf("Enter the First name of the player:");
        scanf("%s",player[i].firstName);
        alpha = isAlpha(player[i].firstName);
    }
    ToLowerCase(player[i].firstName);

    printf("Enter the Last name of the player:");
    scanf("%s",player[i].lastName);
    alpha = isAlpha(player[i].lastName);
    while (alpha == 0)
    {
        printf("\nLast Name should only have alphabetical characters no digits or spaces !!!\n\n");
        printf("Enter the Last name of the player:");
        scanf("%s",player[i].lastName);
        alpha = isAlpha(player[i].lastName);
    }
    ToLowerCase(player[i].lastName);

    printf("Enter the email address of the player:");
    scanf("%s",player[i].emailAddress);
    int x = validEmailAddress(player[i].emailAddress);
    while (x == -1)
    {
        printf("\nEnter a valid email address!!!\n");
        printf("Enter the email address of the player:");
        scanf("%s",player[i].emailAddress);
        x = validEmailAddress(player[i].emailAddress);
    }
    player[i].playerId = ++playerId;
    printf("\n Your Player Id is: %d\n",player[i].playerId);
    player[i].playerScore = 100;
    player[i].games = 0;
    puts("");

}

int validEmailAddress(char emailAddress[])
{
    int i = 0;
    int flg1 = 0;
    int flg2 = 0;
    while (emailAddress[i] != '\0')
    {
       if (emailAddress[i] == '@')
       {
           flg1= 1;
       }
       if (emailAddress[i] == '.')
       {
           flg2 = 1;
       }
       i++;
    }
    if (flg1 != 1 || flg2 != 1)
    {
        return -1;
    }
    i = 0;
    int pos1 = 0; // for @
    int pos2 = 0; // for .
    int finalPos1 = 0; // for @
    int finalPos2 = 0; // for .
    while (emailAddress[i]!= '\0')
    {
       if (emailAddress[i] != '@')
       {
           pos1++;
       }
       if (emailAddress[i] != '.')
       {
           pos2++;
       }
       if (emailAddress[i] == '@')
       {
           finalPos1 = pos1;
       }
       if (emailAddress[i] == '.')
       {
           finalPos2 = pos2;
       }
       i++;
    }
    if (finalPos2 <= finalPos1)
    {
        return -1;
    }
    i = i - 1;
    if (emailAddress[i] == '.')
    {
        return -1;
    }
    return 1;
}
void ToLowerCase(char *pStr)
{
    while(*pStr)
    {
        if ((int)*pStr >=65 && (int)*pStr <= 90)
        {
            *pStr = (int)*pStr + 32;

        }
        if ((int)*pStr >=97 && (int)*pStr <= 122)
        {
            *pStr++;
            continue;

        }
        *pStr++;
    }
}
int isAlpha(char *pStr)
{
    int flg = 0;
    while(*pStr)
    {
        if (((int)*pStr >=65 && (int)*pStr <= 90) || ((int)*pStr >=97 && (int)*pStr <= 122))
        {
            flg = 1;
        }
        else
        {
            flg = 0;
            return 0;
        }
        *pStr++;
    }
    return 1;
}
void createGame(int m, int n, char board[][n], int player1, int player2, struct playerAccount players[], struct gameId gameId[], int sizeOfgames)
{
    totalNumberOfGames++;
    InitializeBoard(3, 3, board);
    CreateBoard(3, 3, board, player1, player2, players, 0, -1,gameId,sizeOfgames);
}
void createSavedGame(int m, int n, char board[][n], int player1, int player2, struct playerAccount players[], struct gameId gameId[], int sizeOfgames)
{
    int ma = savedGames(gameId,totalNumberOfGames);
    if (ma == -1)
    {
        return;
    }
    int inp = 0;
    printf("\nEnter the GameId of the game which you want to continue to play : ");
    scanf("%d",&inp);
    int res = -1;
    for (int k = 0; k<totalNumberOfGames; k++)
    {
        if (gameId[k].gameid == inp)
        {
            res = strcmp(gameId[k].status,"X won");
            if (res == 0)
            {
                printf("\nThis game is already over.\n\n");
                return;
            }
            res = strcmp(gameId[k].status,"O won");
            if (res == 0)
            {
                printf("\nThis game is already over.\n\n");
                return;
            }
            res = strcmp(gameId[k].status,"Draw");
            if (res == 0)
            {
                printf("\nThis game is already over.\n\n");
                return;
            }

            player1 = gameId[k].player1Id;
            player2 = gameId[k].player2Id;
            CreateBoard(3, 3, board, player1, player2, players, 1,inp, gameId,sizeOfgames);
        }
    }
}
int savedGames(struct gameId games[], int sizeOfgames)
{
    if (sizeOfgames == 0)
    {
        printf("\nThere are no saved games.\n\n");
        return -1;
    }
    printf("                     Saved Games                 \n");
    printf("GameId        Player1Id        Player2Id        Status \n");
    for (int i = 0;i<sizeOfgames; i++)
    {
        printf("%-5d               %d               %d           %s\n",games[i].gameid,games[i].player1Id,games[i].player2Id,games[i].status);
    }
    return 0;
}

void leaderBoard(struct playerAccount players[],struct gameId games[], int size, int sizeOfgames)
{
    int x = 0;
    struct playerAccount scores[size];
    struct playerAccount temp;
    printf("                       LeaderBoard                                       \n");
    printf("\nPress 1 to print the leaderboard in descending order of player's scores.\n");
    printf("Press 2 to print the leaderboard in ascending order of player's scores.\n");
    printf("Press 3 to print the leaderboard sorted by the player's total number of games.\n");
    printf("Press 4 to print the leaderboard sorted by the total number of losses.\n");
    printf("Press 5 to print the leaderboard sorted by the total number of wins.\n");
    printf("Press 6 to print the leaderboard sorted by the total number of draws.\n");
    scanf("%d",&x);
    for (int i = 0; i<size;i++)
    {
        scores[i] = players[i];
    }
    if (x == 1)
    {
        for (int i = 0;i<size;i++)
        {
            for (int j = i + 1 ;j<size;j++)
            {
                if (scores[i].playerScore < scores[j].playerScore)
                {
                    temp = scores[i];
                    scores[i] = scores[j];
                    scores[j] = temp;
                }
            }

        }
        printFun(scores,size);
    }
    if (x == 2)
    {
        for (int i = 0;i<size;i++)
        {
            for (int j = i + 1 ;j<size;j++)
            {
                if (scores[i].playerScore > scores[j].playerScore)
                {
                    temp = scores[i];
                    scores[i] = scores[j];
                    scores[j] = temp;
                }
            }

        }
        printFun(scores,size);
    }
    if (x == 3)
    {
        for (int i = 0;i<size;i++)
        {
            for (int j = i + 1 ;j<size;j++)
            {
                if (scores[i].games < scores[j].games)
                {
                    temp = scores[i];
                    scores[i] = scores[j];
                    scores[j] = temp;
                }
            }

        }
        printFun(scores,size);
    }
    if (x == 4)
    {
        for (int i = 0;i<size;i++)
        {
            scores[i].games = 0;
        }
        for (int i = 0; i<sizeOfgames;i++)
        {
            if (games[i].status == "X won")
            {
                if (games[i].player1Role == 'X')
                {
                    for (int j = 0;j<size;j++)
                    {
                        if (scores[j].playerId == games[i].player2Id)
                        {
                            scores[j].games++;
                        }
                    }

                }
                if (games[i].player2Role == 'X')
                {
                    for (int j = 0;j<size;j++)
                    {
                        if (scores[j].playerId == games[i].player1Id)
                        {
                            scores[j].games++;
                        }
                    }

                }

            }
            if (games[i].status == "O won")
            {
                if (games[i].player1Role == 'O')
                {
                    for (int j = 0;j<size;j++)
                    {
                        if (scores[j].playerId == games[i].player2Id)
                        {
                            scores[j].games++;
                        }
                    }

                }
                if (games[i].player2Role == 'O')
                {
                    for (int j = 0;j<size;j++)
                    {
                        if (scores[j].playerId == games[i].player1Id)
                        {
                            scores[j].games++;
                        }
                    }

                }

            }
        }
        for (int i = 0;i<size;i++)
        {
            for (int j = i + 1 ;j<size;j++)
            {
                if (scores[i].games < scores[j].games)
                {
                    temp = scores[i];
                    scores[i] = scores[j];
                    scores[j] = temp;
                }
            }
        }
        printFun(scores,size);
    }
    if (x == 5)
    {
        for (int i = 0;i<size;i++)
        {
            scores[i].games = 0;
        }
        for (int i = 0; i<sizeOfgames;i++)
        {
            if (games[i].status == "X won")
            {
                if (games[i].player1Role == 'X')
                {
                    for (int j = 0;j<size;j++)
                    {
                        if (scores[j].playerId == games[i].player1Id)
                        {
                            scores[j].games++;
                        }
                    }

                }
                if (games[i].player2Role == 'X')
                {
                    for (int j = 0;j<size;j++)
                    {
                        if (scores[j].playerId == games[i].player2Id)
                        {
                            scores[j].games++;
                        }
                    }

                }

            }
            if (games[i].status == "O won")
            {
                if (games[i].player1Role == 'O')
                {
                    for (int j = 0;j<size;j++)
                    {
                        if (scores[j].playerId == games[i].player1Id)
                        {
                            scores[j].games++;
                        }
                    }

                }
                if (games[i].player2Role == 'O')
                {
                    for (int j = 0;j<size;j++)
                    {
                        if (scores[j].playerId == games[i].player2Id)
                        {
                            scores[j].games++;
                        }
                    }

                }

            }
        }
        for (int i = 0;i<size;i++)
        {
            for (int j = i + 1 ;j<size;j++)
            {
                if (scores[i].games < scores[j].games)
                {
                    temp = scores[i];
                    scores[i] = scores[j];
                    scores[j] = temp;
                }
            }
        }
        printFun(scores,size);
    }
    if (x == 6)
    {
        for (int i = 0;i<size;i++)
        {
            scores[i].games = 0;
        }
        for (int i = 0; i<sizeOfgames;i++)
        {
            if (games[i].status == "Draw")
            {
                for (int j = 0;j<size;j++)
                {
                    if (scores[j].playerId == games[i].player1Id)
                    {
                        scores[j].games++;
                    }
                }
                for (int j = 0;j<size;j++)
                {
                    if (scores[j].playerId == games[i].player2Id)
                    {
                        scores[j].games++;
                    }
                }
            }
        }
        for (int i = 0;i<size;i++)
        {
            for (int j = i + 1 ;j<size;j++)
            {
                if (scores[i].games < scores[j].games)
                {
                    temp = scores[i];
                    scores[i] = scores[j];
                    scores[j] = temp;
                }
            }
        }
        printFun(scores,size);
    }
}
void printFun(struct playerAccount scores[], int size)
{
    printf("ID                   FirstName                   LastName                    Score\n");
    for (int i = 0;i<size;i++)
    {
        printf("%d                    %-25s   %-25s   %-5d\n",scores[i].playerId,scores[i].firstName,scores[i].lastName,scores[i].playerScore);
    }
}




