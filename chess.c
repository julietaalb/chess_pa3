#include "chess.h"
square board[8][8];
int turn;
static void resetBoard()
{
    turn = WHITE; //WHITE moves first
    int i, j;
    for (i = 2; i < 6; i++)
        for (j = 0; j < 8; j++)
            board[i][j] = EMPTY;
    for (j = 0; j < 8; j++)
    {
        board[1][j] = BLACK * PAWN;
        board[6][j] = WHITE * PAWN;
    }
    board[0][0] = board[0][7] = BLACK * ROOK;
    board[7][0] = board[7][7] = WHITE * ROOK;
    board[0][1] = board[0][6] = BLACK * KNIGHT;
    board[7][1] = board[7][6] = WHITE * KNIGHT;
    board[0][2] = board[0][5] = BLACK * BISHOP;
    board[7][2] = board[7][5] = WHITE * BISHOP;
    board[0][3] = BLACK * QUEEN;
    board[7][3] = WHITE * QUEEN;
    board[0][4] = BLACK * KING;
    board[7][4] = WHITE * KING;
}
char getCommandWord(char command[], int maxLength)
{
    char lastCharacter; //either space or new line
    int i;
    for (i = 0; (lastCharacter = getchar()) == ' '; i++)
        ; //skip leading white spaces
    if (lastCharacter == '\n')
    {
        command[0] = '\0';
        return lastCharacter;
    }
    command[0] = lastCharacter;
    for (i = 1; i < maxLength - 1 && (command[i] = getchar()) != ' ' && command[i] != '\n'; i++)
        ;
    lastCharacter = command[i];
    command[i] = '\0';
    return lastCharacter;
}

main(int argc, char **argv){ //char** argv holds command (argv[1])
    resetBoard();
    int w = 0;
    int b = 0;
    int r = 0;
    int import = 0 ;

    char sourceBlock[MAX_COMMAND_TOKEN_LENGTH];
    char targetBlock[MAX_COMMAND_TOKEN_LENGTH];

    int x = 1;
    char importGame[5000];
    char *temp[5000];

    while (argv[x] != NULL){
        if (strcmp(argv[x], "-i") == 0){ 
            import = 1;
            strcpy(temp, argv[x + 1]);
            char *token = strtok(temp, ",");

            while (token != NULL){// moves stored in token
                int length = strlen(token); //get length of token

                if(length == 5 && strchr(token, 'x') == NULL){ //remove upper letter
                    token++; //increment to next postion
                }
                if (strchr(token, 'x') == NULL){ //move
                    strncpy(sourceBlock, &token[0], 2); //copy first two into sourceBlock
                    sourceBlock[2] = '\0'; //end of file at 2
                    strncpy(targetBlock, &token[2], 2);//copy first two into targetBlock
                    targetBlock[2] = '\0';
                    handleMove(import, sourceBlock, targetBlock); 
                    
                }
                else { //capture
                    strncpy(sourceBlock, &token[0], 2);
                    sourceBlock[2] = '\0';
                    strncpy(targetBlock, &token[3], 2);
                    targetBlock[2] = '\0';
                    handleCapture(import, sourceBlock, targetBlock);
                }
                
                token = strtok(NULL, ",");
            }
        }
        else if (strcmp(argv[x], "-w") == 0) {
            w = 1;
            strcpy(firstPlayerName, argv[x + 1]);
        }
        else if (strcmp(argv[x], "-b") == 0) {
            b = 1;
            strcpy(secondPlayerName, argv[x + 1]);
        }
        else if (strcmp(argv[x], "-r") == 0) {
            r = 1;
        }
        x++;
    }
    /*
    * You can access all the command-line arguments here
    * argv[1], argv[2], ...
    * Example of import option: -i d2d4,d7d5,e2e4,d5xe4,Ng1h3,Ke8d7,Qd1d3
    * which is equivalent to a new game started this way:
    * mv d2 d4
    * mv d7 d5
    * mv e2 e4
    * cp d5 e4
    * mv g1 h3
    * mv e8 d7
    * mv d1 d3
    * 
    */
    import = 0;
    char command[MAX_COMMAND_TOKEN_LENGTH];
    char lastCharacter;
    printf("\nStart the game using a mv command! Valid commands are quit, show, mv and cp.\n");
    while (1)
    { //infinite while loop...
        printf(">>");
        lastCharacter = getCommandWord(command, MAX_COMMAND_TOKEN_LENGTH);
        if (strcmp(command, "quit") == 0) //if command === "quit"
            break;
        else if (!strcmp(command, "mv")) //if command == "mv"
        {
            if (lastCharacter == '\n') //mv\n
                printf("Too few arguments for mv command! It must be in the form of mv ai bj.\n");
            else
                handleMove(import, sourceBlock, targetBlock);
        }
        else if (!strcmp(command, "cp")) //if command == "cp"
        {
            if (lastCharacter == '\n') //cp\n
                printf("Too few arguments for cp command! It must be in the form of cp ai bj.\n");
            else
                handleCapture(import, sourceBlock, targetBlock);
        }
        else if (!strcmp(command, "show")) //if command == "show"
        {
            if (lastCharacter != '\n')
            { //show x\n
                printf("Too many arguments for show command! It must be in the form of show.\n");
                while (getCommandWord(command, MAX_COMMAND_TOKEN_LENGTH) != '\n')
                    ; //skip the ramainder of the invalid show command...
            }
            else
                handleShow(w, b, r);
        }
        else
        {
            printf("invalid command! Your command must start either with quit, show, mv or cp.\n");
            while (lastCharacter != '\n') //skip the remainder of my invalid command...
                lastCharacter = getCommandWord(command, MAX_COMMAND_TOKEN_LENGTH);
        }
    }
}


