#include <stdio.h>
#include <stdlib.h>


void print_grid(char**, int, int);
int get_adjacent_star_number(char**, int, int, int, int);
void bubble_sort(int *, int);

int main(int argc, char *argv[] )
{
   if( argc == 1 ) {
      printf("2 file name are expected for input and output\n");
      return -1;
   }
   else if( argc > 3 ) {
      printf("Too many arguments supplied, however we expect only 2 for input and output file\n");
   }
   char *input_file=argv[1], *output_file=argv[2];
   char **grid;
   int grid_row, grid_col, row, col;
   int *star_groups, *final_star_groups;
   int i=0, j=0;
   FILE *input_file_fp, *output_file_fp;
   int total_start_groups = 0;
   int temp;


   // printf("Input File = %s\n", input_file);
   // printf("Output File = %s\n", output_file);

   input_file_fp = fopen(input_file, "r");
   fscanf(input_file_fp, "%d", &grid_row);
   fscanf(input_file_fp, "%d", &grid_col);
   // printf("Row = %d, Col=%d\n", grid_row, grid_col );

   star_groups = (int *) malloc(grid_row * grid_col * sizeof(int));
   grid = (char **) malloc( grid_row * sizeof(char*));

   
   for(i=0;i<grid_row;i++){
     grid[i] = (char *) malloc(sizeof(char) * grid_col);
     for(j=0;j<grid_col;j++)
     {
         grid[i][j] = ' ';
     }
   }

    
    while (1){
        fscanf(input_file_fp, "%d", &row);
        if(row == -1)
           break;
        fscanf(input_file_fp, "%d", &col);
        grid[row][col] = '*';

   }
    fclose(input_file_fp);
    // print_grid(grid, grid_row, grid_col);

    for(i=0;i<grid_row;i++)
        for(j=0;j<grid_col;j++){
            if(grid[i][j] == '*'){
                
                temp = get_adjacent_star_number(grid, grid_row, grid_col, i, j);
                
                star_groups[total_start_groups++] = temp;
            }
        }
    // print_grid(grid, grid_row, grid_col);
    final_star_groups = (int *) malloc(total_start_groups * sizeof(int)); //
    for(i=0;i<total_start_groups;i++)
        final_star_groups[i] = star_groups[i];

    

    
    free(star_groups);

    
    bubble_sort(final_star_groups, total_start_groups);


    
    output_file_fp = fopen(output_file, "w+");

    fprintf(output_file_fp, "%d ", total_start_groups);
    printf("%d ", total_start_groups);

    for(i=0;i<total_start_groups;i++){
        fprintf(output_file_fp, "%d ", final_star_groups[i]);
        printf("%d ", final_star_groups[i]);
    }
    
    fclose(output_file_fp);
    fprintf(output_file_fp, "\n");
    printf("\n");

    


    free(final_star_groups);

    for(i=0;i<row;i++){
        free(grid[i]);
    }
    free(grid);

    return 0;
}
int get_adjacent_star_number(char** grid, int grid_row, int grid_col, int row, int col){
    if(row < 0 || col < 0 || row >=grid_row || col >= grid_col)
        return 0;

    if(grid[row][col] == '*'){
        grid[row][col] = '?';

        return 1 + get_adjacent_star_number(grid, grid_row, grid_col, row, col + 1) +
                    get_adjacent_star_number(grid, grid_row, grid_col, row + 1, col) +
                    get_adjacent_star_number(grid, grid_row, grid_col, row + 1,  col + 1) +
                    get_adjacent_star_number(grid, grid_row, grid_col, row , col - 1) +
                    get_adjacent_star_number(grid, grid_row, grid_col, row - 1, col) +
                    get_adjacent_star_number(grid, grid_row, grid_col, row - 1,  col-1)+
                    get_adjacent_star_number(grid, grid_row, grid_col, row + 1, col -1) +
                    get_adjacent_star_number(grid, grid_row, grid_col, row - 1, col+1);


    }
    return 0;

}



void print_grid(char** grid, int row, int col){
    int i, j, i2;
    printf("Calling print Grid Function\n");
    printf(" |");
    for(i2=0;i2<col;i2++){
        printf("%d|", i2);
    }
    printf("\n");
    for(i=0; i<row;i++){
            printf("%d|", i);
        for(j=0;j<col;j++){
          if(j >=10)
             printf("%c |", grid[i][j]);
          else
            printf("%c|", grid[i][j]);
        }
        printf("\n");
    }

    printf("\n");

}


void bubble_sort(int *final_star_groups, int n)
{
    int i, j, temp;

    for (i = 0; i < n - 1; i++){
        for (j = 0; j < n - i - 1; j++){
            if (final_star_groups[j] > final_star_groups[j + 1]){
                    
                     temp = final_star_groups[j];
                     final_star_groups[j] = final_star_groups[j + 1];
                     final_star_groups[j + 1] = temp;
  
                }
        }
    }
}
