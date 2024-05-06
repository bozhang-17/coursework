#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUMROWS 9
#define NUMCOLS 9

void random_step(int *row, int *col,int *step);
int calculate_status(int suc, int tem, double mean, double var, int lab1);

int main(void) {
    srand(123456);
    double step_array[10000];
    char map[NUMROWS][NUMCOLS];
    double pmap[NUMROWS][NUMCOLS];//array of Probability
    double mmap[NUMROWS][NUMCOLS];//array of Mean path length
    double smap[NUMROWS][NUMCOLS];//array of Standard deviation of path length

    FILE *fptr = fopen("island_map.txt", "r");
    if (fptr == NULL) {
        printf("Error. Not able to open the file.");
        return 1;
    }

    for (int i = 0; i < NUMROWS; i++) {
        for (int u = 0; u < NUMCOLS; u++) {
            do {
                fscanf(fptr, "%c", &map[i][u]);
            } while (map[i][u] == '\n' || map[i][u] == ' ');
        }
    }
    fclose(fptr);
    // Output the map as a 9x9 array
    printf("Map:\n");
    for (int i = 0; i < NUMROWS; i++) {
        for (int u = 0; u < NUMCOLS; u++) {
            if(u == 8){
                printf("%c\n", map[i][u]);
            } else {
                printf("%c ", map[i][u]);
            }
        }

    }
    printf("\n");

    for (int i = 0; i < NUMROWS; i++) {
        for (int u = 0; u < NUMCOLS; u++) {
            int suc = 0;
            int tem = 0;
            double mean = 0;
            double var = 0;
            int try = 0;//Number of try
            int a=0;
            int step_array[10000] = {0};//Initialize the array
            

            //if it starts from W,D,V,the Probability,Mean path length and Standard deviation are 0.
            if (map[i][u] == 'W' || map[i][u] == 'D' || map[i][u] == 'V') {
                pmap[i][u] = 0;
                mmap[i][u] = 0;
                smap[i][u] = 0;
                continue;
            }
            
            //if it starts from B,the Probability is 100,Mean path length and Standard deviation are 0.
            if (map[i][u] == 'B') {
                pmap[i][u] = 100;
                mmap[i][u] = 0;
                smap[i][u] = 0;
                continue;
            }
            
            //if it starts from L.then let it move randomly and check its location at the meantime.
            if (map[i][u] == 'L') {
                while (try < 1000) {
                    int step = 0;//step
                    int row = i;
                    int col = u;
                    try++;//Number of try plus one

                    do {
                        random_step(&row, &col,&step);
                    } while (map[row][col] == 'L' && step < 10);

                    if (map[row][col] == 'B') {
                        suc += step;//the number of step if success
                        tem++;//the time of success
                        step_array[a]=step;//for caluating standard deviation
                        a++;//for step_array[a]
                    }
                }
                
                //caluate Probability
                double pb = (double) tem / try;
                pmap[i][u] = pb * 100;

                //caluate mean
                mean = (double) suc / tem;
                mmap[i][u] = mean;


                //caluate standard deviation
                for(a=0;a<tem;a++){
                  var+=pow(step_array[a]-mean,2);
                }
                double stand = (double) sqrt(var / tem);
                smap[i][u] = stand;


            }
        }
    }

    // Output the maps
    printf("Probability of escape:\n");
    for (int i = 0; i < NUMROWS; i++) {
        for (int u = 0; u < NUMCOLS; u++) {
            printf("%.2f%s", pmap[i][u], (u == NUMCOLS - 1) ? "\n" : " ");
        }
    }
    printf("\n");

    printf("Mean path length:\n");
    for (int i = 0; i < NUMROWS; i++) {
        for (int u = 0; u < NUMCOLS; u++) {
            printf("%.2f%s", mmap[i][u], (u == NUMCOLS - 1) ? "\n" : " ");
        }
    }
    printf("\n");

    printf("Standard deviation of path length:\n");
    for (int i = 0; i < NUMROWS; i++) {
        for (int u = 0; u < NUMCOLS; u++) {
            printf("%.2f%s", smap[i][u], (u == NUMCOLS - 1) ? "\n" : " ");
        }
    }

    return 0;
}

void random_step(int *row, int *col, int *step) {
    int move = rand() % 8;
    switch (move) {
        case 0: // North
            if (*row > 0) {
                (*row)--;
                (*step)++;
              
                
            }
            break;
        case 1: // Northeast
        if (*row > 0)
        {
                (*row)--;
        }
        if (*col < 8)
        {
                (*col)++;
        }
            
            if (*row > 0 && *col < 8) {
                (*step)++;
               
            }
            break;
        case 2: // East
            if (*col < 8) {
                (*col)++;
                (*step)++;
            }
            break;
        case 3: // Southeast
                if (*row < 8)
        {
                (*row)++;
        }
        if (*col < 8)
        {
                (*col)++;
        }
            if (*row < 8 || *col < 8) {
                (*step)++;
            }
            break;
        case 4: // South
            if (*row < 8) {
                (*row)++;
                (*step)++;
            }
            break;
        case 5: // Southwest
                        if (*row < 8)
        {
                (*row)++;
        }
        if (*col > 0)
        {
                (*col)--;
        }
            if (*row < 8 || *col > 0) {
                (*step)++;
            }
            break;
        case 6: // West
            if (*col > 0) {
                (*col)--;
                (*step)++;
            }
            break;
        case 7: // Northwest
         if (*row > 0)
        {
                (*row)--;
        }
        if (*col > 0)
        {
                (*col)--;
        }
            if (*row > 0 || *col > 0) {
                (*step)++;
            }
            break;
    }
}

