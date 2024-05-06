#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUMROWS 9
#define NUMCOLS 9

void random_step(int *row, int *col,int *step);

int main(void) {
    srand(123456);
    double step_array[10000];//the array which contains the number of step if success
    char map[NUMROWS][NUMCOLS];//array of Map
    double pmap[NUMROWS][NUMCOLS];//array of Probability
    double mmap[NUMROWS][NUMCOLS];//array of Mean path length
    double smap[NUMROWS][NUMCOLS];//array of Standard deviation of path length
    
    // Check if the file pointer is NULL, indicating failure to open the file.
    FILE *fptr = fopen("island_map.txt", "r");//Open the file in read-only mode
    if (fptr == NULL) {
        printf("Error. Not able to open the file.");
        return 1;
    }
    
    // Loop through each row of the map.
    for (int i = 0; i < NUMROWS; i++) {
        // Loop through each column of the map.
        for (int u = 0; u < NUMCOLS; u++) {
            do {
                fscanf(fptr, "%c", &map[i][u]);// Read a character from the file and store it in map[i][u]
            } while (map[i][u] == '\n' || map[i][u] == ' ');// Continue reading if the character is a newline or space.
        }
    }
    fclose(fptr);

    // Output the map as a 9x9 array
    printf("Map:\n");
    // Loop through each row of the map.
    for (int i = 0; i < NUMROWS; i++) {
        // Loop through each row of the map.
        for (int u = 0; u < NUMCOLS; u++) {
            if(u == 8){
                printf("%c\n", map[i][u]);// If it's the last column, print the character followed by a newline.
            } else {
                printf("%c ", map[i][u]);// If it's not the last column, print the character followed by a space.
            }
        }

    }
    printf("\n");
    // Loop through each row of the map.
    for (int i = 0; i < NUMROWS; i++) {
        // Loop through each row of the map.
        for (int u = 0; u < NUMCOLS; u++) {
            //After looping a thousand times, set all variables to 0.
            int suc = 0;//Initialize the number of step if success
            int tem = 0;//Initialize the number of success
            double mean = 0;//Initialize the mean
            double var = 0;//var+=pow(step_array[a]-mean,2)
            int try = 0;//Number of try
            int a=0;//a is for caluating standard deviation
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
                        random_step(&row, &col,&step);// Perform a random movement
                    } while (map[row][col] == 'L' && step < 10);// Continue looping if the current cell is land and the step count is less than 10

                    if (map[row][col] == 'B') {
                        suc += step;//the number of step if success
                        tem++;//the number of success
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

    // Output the map
    printf("Probability of escape:\n");
    for (int i = 0; i < NUMROWS; i++) {
        for (int u = 0; u < NUMCOLS; u++) {
            printf("%.2f%s", pmap[i][u], (u == NUMCOLS - 1) ? "\n" : " ");
        }
    }
    printf("\n");
    
    // Output the mean
    printf("Mean path length:\n");
    for (int i = 0; i < NUMROWS; i++) {
        for (int u = 0; u < NUMCOLS; u++) {
            printf("%.2f%s", mmap[i][u], (u == NUMCOLS - 1) ? "\n" : " ");
        }
    }
    printf("\n");
    
    // Output the Standard deviation
    printf("Standard deviation of path length:\n");
    for (int i = 0; i < NUMROWS; i++) {
        for (int u = 0; u < NUMCOLS; u++) {
            printf("%.2f%s", smap[i][u], (u == NUMCOLS - 1) ? "\n" : " ");
        }
    }

    return 0;
}

//movement
void random_step(int *row, int *col, int *step) {
    int move = rand() % 8;// Generate a random number between 0 and 7
    // Determine the direction based on the random number
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

