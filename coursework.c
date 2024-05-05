#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUMROWS 9
#define NUMCOLS 9

void random_step(int *row, int *col,int *step);

int main(void) {
    srand(123456);

    char map[NUMROWS][NUMCOLS];
    double pmap[NUMROWS][NUMCOLS];
    double mmap[NUMROWS][NUMCOLS];
    double smap[NUMROWS][NUMCOLS];

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
    for (int i = 0; i < NUMROWS; i++) {
        for (int u = 0; u < NUMCOLS; u++) {
            if(u == 8){
                printf("%c\n", map[i][u]);
            } else {
                printf("%c ", map[i][u]);
            }
        }

    }

    for (int i = 0; i < NUMROWS; i++) {
        for (int u = 0; u < NUMCOLS; u++) {
            int totalstep = 1000;
            int suc = 0;
            int tem = 0;
            double mean = 0;
            double var = 0;
            int lab1 = 0;

            if (map[i][u] == 'W' || map[i][u] == 'D' || map[i][u] == 'V') {
                pmap[i][u] = 0;
                mmap[i][u] = 0;
                smap[i][u] = 0;
                continue;
            }

            if (map[i][u] == 'B') {
                pmap[i][u] = 100;
                mmap[i][u] = 0;
                smap[i][u] = 0;
                continue;
            }

            if (map[i][u] == 'L') {
                while (totalstep > 0) {
                    int step = 0;
                    int row = i;
                    int col = u;
                    lab1++;

                    do {
                        random_step(&row, &col,&step);
                        totalstep--;
                    } while (map[row][col] == 'L' && step < 10 && totalstep > 0);

                    if (map[row][col] == 'B') {
                        suc += step;
                        tem++;
                        var += pow(step - mean, 2);
                    }
                }

                mean = (double) suc / tem;
                mmap[i][u] = mean;
                double pb = (double) tem / lab1;
                pmap[i][u] = pb * 100;
                double stand = (double) sqrt(var / tem);
                smap[i][u] = stand;
            }
        }
    }

    // Output the maps
    for (int i = 0; i < NUMROWS; i++) {
        for (int u = 0; u < NUMCOLS; u++) {
            printf("%.2f%s", pmap[i][u], (u == NUMCOLS - 1) ? "\n" : " ");
        }
    }

    for (int i = 0; i < NUMROWS; i++) {
        for (int u = 0; u < NUMCOLS; u++) {
            printf("%.2f%s", mmap[i][u], (u == NUMCOLS - 1) ? "\n" : " ");
        }
    }

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
            if (*row > 0 && *col < 8) {
                (*row)--;
                (*col)++;
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
            if (*row < 8 && *col < 8) {
                (*row)++;
                (*col)++;
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
            if (*row < 8 && *col > 0) {
                (*row)++;
                (*col)--;
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
            if (*row > 0 && *col > 0) {
                (*row)--;
                (*col)--;
                (*step)++;
            }
            break;
    }
}
