#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NUMROWS 9    // map size
#define NUMCOLS 9    // map size
int main(void) {
  srand(01234567);
  int suc = 0;
  int tem = 0;
  double mean = 0;
  int ts = 0;
  int lab=0;
  double var = 0;
  double stand = 0;
    // Load the map
    char map[NUMROWS][NUMCOLS];
    double pmap[NUMROWS][NUMCOLS];
    double mmap[NUMROWS][NUMCOLS];
    double sub[100000];
    double smap[NUMROWS][NUMCOLS];
    FILE *fptr;
    fptr = fopen("island_map.txt", "r");
    if (fptr == NULL) {
        printf("Error. Not able to open the file.");
        return 1;
    }
    // Read in the map from file
    for (int i = 0; i < NUMROWS; i++) {
        for (int u = 0; u < NUMCOLS; u++) {
            do {
                fscanf(fptr, "%c", &map[i][u]);
            } while (map[i][u] == '\n' || map[i][u] == ' '); // Skip newline and space characters
        }
    }
    fclose(fptr);
    // Output the map as a 9x9 array
    printf("Map: \n");
    for (int i = 0; i < NUMROWS; i++) {
        for (int u = 0; u < NUMCOLS; u++) {
            printf("%c ", map[i][u]);
        }
        printf("\n");
    }


   
  for (int i = 0; i < NUMROWS; i++) {
    for (int u = 0; u < NUMCOLS; u++) {//finds the starting point
      int totalstep = 1000;
      suc = 0;
      tem = 0;
      lab = 0;
      //check if it is W,D,V
      if(map[i][u]=='W' || map[i][u]== 'D' || map[i][u]==  'V')
      {
          pmap[i][u]= 0;
          mmap[i][u]= 0;
          smap[i][u]= 0;
      }


      //check if it is B
      if(map[i][u]=='B')
      {
           pmap[i][u]= 100;
           mmap[i][u]= 0;
           smap[i][u]= 0;
      }
      if(map[i][u] == 'L'){//checks if the starting point is a L
        int row = i;
        int col = u;
      while (totalstep>0){//loops until the total step is 0
        int step = 0;
        int row = i;//sets the row and col to the starting point
        int col = u;

       do{ //loops until the step is 0
        int move = rand() % 8;

         

        switch (move) {
            case 0: // North
              if(row>0){

                row--;
              }
                break;
            case 1: // Northeast
              if(row>0){
                row--;
              }
              if(col<8){
                col++;
              }
                break;
            case 2: // East
              if(col<8){
                col++;
              }
                break;
            case 3: // Southeast
              if(row<8){
                row++;
              }

              if(col<8){
                col++;
              }
                break;
            case 4: // South
              if(row<8){
                row++;
              }

                break;
            case 5: // Southwest
              if(row<8){
                row++;
              }
              if(col>0){
                col--;
              }

                break;
            case 6: // West
              if(col>0){

                col--;
              }

                break;
            case 7: // Northwest
              if(row>0){
                row--;
              }
              if(col>0){
                col--;
              }
                break;
        }
          totalstep=totalstep-1;
          step++;
         }
         while(map[row][col] == 'L' && step<=10 && totalstep>0);//checks if the step is a L and if the total step is less than or equal to 10

        if(map[row][col] == 'B'){//checks if the step is a B
          suc = suc+step;
          tem = tem+1;
          
          sub[lab]=step;//xi
          lab++;
        }


        step = 0;


      }

        mean =(double)suc/(double)tem;
        mmap[i][u] = mean;
        double pb = (double)suc/1000.0;
        pmap[i][u] = pb*100;
        for (int lab = 0; lab <= tem; lab++){
          
        var+=pow(sub[lab]-mean,2);
          
      }
        
        double stand = (double)sqrt(var/tem);
        smap[i][u] = stand;
        var = 0;
      }

    }

  }
  printf("\n");
  printf("Probability of escape:  \n");
  for (int i = 0; i < NUMROWS; i++) {
      for (int u = 0; u < NUMCOLS; u++) {
          printf("%.2lf ", pmap[i][u]);

      }
      printf("\n");
  }

    printf("\n");
    printf("Mean path length: \n");
   for (int i = 0; i < NUMROWS; i++) {
       for (int u = 0; u < NUMCOLS; u++) {
           printf("%.2lf ", mmap[i][u]);

       }
       printf("\n");
   }
    printf("\n");
    printf("Standard deviation of path length: \n");
     for (int i = 0; i < NUMROWS; i++) {
         for (int u = 0; u < NUMCOLS; u++) {
             printf("%.2lf ", smap[i][u]);

         }
         printf("\n");
     }






  

    return 0;
}
