#include<stdio.h>

#define DEBUG 1
// Input dims : Height H, Width W
#define H 7
#define W 7

// Channels C, common for Input and Kernel
#define C 1

// Filter dims : Height KH, Width KW, 
#define FH 3
#define FW 3

// Not considering these : Padding P, Stride S
#define P 0
#define S 1

// Output dims : Height OH, Width OW - Auto calculated
#define OH ((H + 2*P - FH)/S + 1)
#define OW ((W + 2*P - FW)/S + 1)

// Padded input dims : Height PH, Width PW
#define PH H+(2*P)
#define PW W+(2*P)

int main(){

    int input[C][H][W];
    int padded_input[C][PH][PW];
    int filter[C][FH][FW];
    int output[OH][OW];
    int counter, ir, ic;


    // Init
    counter = 1;
    for(int i=0; i < C; i++)
        for(int j=0; j < H; j++)
            for(int k=0; k < W; k++)
                input[i][j][k] = 1;
    
    counter = 1;
    for(int i=0; i < C; i++)
        for(int j=0; j < FH; j++)
            for(int k=0; k < FW; k++)
                filter[i][j][k] = counter++;


    // Padding

    for(int i=0; i < C; i++)
        for(int j=0; j < PH; j++)
            for(int k=0; k < PW; k++){
                if(j < P || j >= (P+H) || k < P || k >= (P+W))
                    padded_input[i][j][k] = 0;
                else
                    padded_input[i][j][k] = input[i][j-P][k-P];
            }

    if (DEBUG){
        for(int i=0; i < C; i++){
            for(int j=0; j < PH; j++){
                for(int k=0; k< PW; k++){
                    printf(" %d ", padded_input[i][j][k]);
                }
                printf("\n");
            }
            printf("----------------------------\n");
        }
    }

    for(int i=0; i < OH; i++){
        for(int j=0; j < OW; j++){
            
            ir = i*S;
            ic = j*S;
            output[i][j] = 0;

            for(int c=0; c < C; c++){
                for(int a=0; a < FH; a++){
                    for(int b=0; b < FW; b++){
                        
                        output[i][j] += filter[c][a][b] * padded_input[c][ir+a][ic+b];
                    }
                }
            }
        }
    }

    if (DEBUG){
        for(int j=0; j < OH; j++){
            for(int k=0; k< OW; k++){
                printf(" %d ", output[j][k]);
            }
            printf("\n");
        }
    }




    
    return 0;
}