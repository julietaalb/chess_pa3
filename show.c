#include"chess.h"
void handleShow(int w, int b, int r) {
    int i, j;
    if (r == 0)
    {
        if(b){
            printf("%s\n" , secondPlayerName);
        }
        printf("board\t");

        for (i = 0; i < 8; i++)//file labels...
            printf("%c%c", 'a' + i, i == 7 ? '\n' : '\t');
        for (i = 0; i < 8; i++)//table itself
            for (j = 0; j < 9; j++)
                printf("%d%c", j == 0 ? 8 - i : board[i][j - 1], j == 8 ? '\n' : '\t'); //rotate board do backwards reverse
                
        
        if(w){
            printf("%s\n" , firstPlayerName);
        }

    } else{
        if(w){
            printf("%s\n" , firstPlayerName);
        }

        printf("board\t");

        for (i = 0; i < 8; i++)//file labels...
            printf("%c%c", 'h' - i, i == 7 ? '\n' : '\t');

        for(i = 7; i >= 0; i--){
            for(j = 9; j > 0; j--){
            printf("%d%c", j == 9 ? 8 - i : board[i][j - 1], j == 1 ? '\n' : '\t'); 
            }
        }
        if(b){
            printf("%s\n" , secondPlayerName);
        }

    }
   
}
