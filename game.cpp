#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <time.h> 

int main()
{
    struct termios oldSettings, newSettings;

    tcgetattr( fileno( stdin ), &oldSettings );
    newSettings = oldSettings;
    newSettings.c_lflag &= (~ICANON & ~ECHO);
    tcsetattr( fileno( stdin ), TCSANOW, &newSettings );    
    int line[10][10];
    int pontos = 0;
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            line[i][j] = 0;
            if(i == 5){
                if(j == 5){
                    line[i][j] = 1;
                }
            }
            if(j == 0 || j == 9) {
                line[i][j] = 9;
            }
        }
    }

    srand (time(NULL));
    int val[8] = {2,3,4,5,6,7,8};
    int x = rand() % 7;
    int y = rand() % 7;
    line[val[x]][val[y]] = 7;

    while ( 1 )
    {
        fd_set set;
        struct timeval tv;

        tv.tv_sec = 10;
        tv.tv_usec = 0;

        FD_ZERO( &set );
        FD_SET( fileno( stdin ), &set );

        int res = select( fileno( stdin )+1, &set, NULL, NULL, &tv );

        if( res > 0 )
        {
            char c;
            system("clear");
            printf("Pontos: %i", pontos);
            printf( "\n##########\n" );
            //printf( "tecla: %i", c);
            read( fileno( stdin ), &c, 1 );
            if(c == 100){
                //PRA DIREITA
                for(int i = 0; i < 10; i++){
                    for(int j = 0; j < 10; j++){
                        if(line[i][j] == 1) {
                            if(j < 8){
                                line[i][j] = 0;
                                if(line[i][j + 1] == 7){
                                    int x = rand() % 7;
                                    int y = rand() % 7;
                                    line[val[x]][val[y]] = 7;
                                    pontos++;
                                }
                                line[i][j + 1] = 1;
                                break;
                            }
                        }
                    }
                }
            }else if (c == 97){
                //PRA ESQUERDA
                for(int i = 0; i < 10; i++){
                    for(int j = 0; j < 10; j++){
                        if(line[i][j] == 1) {
                            if(j > 1){
                                line[i][j] = 0;
                                if(line[i][j - 1] == 7){
                                    int x = rand() % 7;
                                    int y = rand() % 7;
                                    line[val[x]][val[y]] = 7;
                                    pontos++;
                                }
                                line[i][j - 1] = 1;
                                break;
                            }
                        }
                    }
                }
            }else if (c == 119){
                //PRA CIMA
                for(int i = 0; i < 10; i++){
                    for(int j = 0; j < 10; j++){
                        if(line[i][j] == 1) {
                            if(i > 0){
                                line[i][j] = 0;
                                if(line[i - 1][j] == 7) {
                                    int x = rand() % 7;
                                    int y = rand() % 7;
                                    line[val[x]][val[y]] = 7;
                                    pontos++;
                                }
                                line[i - 1][j] = 1;
                                break;
                            }
                        }
                    }
                }
            }else if (c == 115) {
                for(int i = 0; i < 10; i++) {
                    for(int j = 0; j < 10; j++) {
                        if(line[i][j] == 1) {
                            if(i < 9) {
                                line[i][j] = 0;
                                if(line[i + 1][j] == 7) {
                                    int x = rand() % 7;
                                    int y = rand() % 7;
                                    line[val[x]][val[y]] = 7;
                                    pontos++;
                                }
                                line[i + 1][j] = 1;
                                i = 10;
                                j = 10;
                            }
                        }
                    }
                }
            }

            //print
            for(int i = 0; i < 10; i++){
                for(int j = 0; j < 10; j++) {
                    if(line[i][j] == 0) {
                        printf(" ");
                    } else {
                        if(line[i][j] == 1){
                            printf("o");
                        }else{
                            if(line[i][j] == 9){
                                printf("#");
                            }else{
                                if(line[i][j] == 7){
                                    printf("*");
                                }
                            }
                        }
                    }
                }
                printf("\n");
            }
            printf( "##########\n" );
        }
        else if( res < 0 )
        {
            perror( "select error" );
            break;
        }
        else
        {
            printf( "Select timeout\n" );
        }
    }

    tcsetattr( fileno( stdin ), TCSANOW, &oldSettings );
    return 0;
}