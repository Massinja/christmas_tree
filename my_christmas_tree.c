#include <stdlib.h> 
#include <stdio.h> 
#include <unistd.h>

#define COLOR_GREEN   "\x1b[32m"
#define COLOR_RESET   "\x1b[37m"

// tree ornaments for the future use :)
#define COLOR_RED     "\x1b[31m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"



int row_width(int tier_num, int row_width, int adding){
    int i = 1;
    while (i<tier_num) {
        if(i%2 == 0){
            adding+=2;
        }
        row_width += adding;
        i++;
    }

    return row_width;
}

int tier_top_width(int tier_num){
    int num = tier_num;
    int top = 1;
    int adding = 4;
    int tier_start = row_width(num, top, adding);
    
    return tier_start;
}

int tier_base_width(int tier_num){
    int num = tier_num;
    int base = 7;
    int adding = 6;
    int tier_base = row_width(num, base, adding);
    
    return tier_base; 
}

void space_builder(int offset){
    int i = 0;
    while(i<offset){
        printf(" ");
        i++;
    }
}

void trunk_builder(int *tree_size_ptr){
    int i = 0;
    while(i<*tree_size_ptr){
        printf("|");
        i++;
    } 
}

void branch_row_builder(int width){
    int i = 0;
    while(i<width){
        printf(COLOR_GREEN "*");
        printf("*");
        i++;
    } 
}

void bottom_builder(int *tree_size_ptr, int *trunk_offset){
    int k = 0;
    while(k<*tree_size_ptr){

        space_builder(*trunk_offset);
        trunk_builder(tree_size_ptr);          
        printf("\n");
        k++;
    }
}    

void crown_builder(int *tree_size_ptr, int *crown_tip_offset){
    int crown_offset = *crown_tip_offset;
     
    int i = 1;  
    while(i<*tree_size_ptr+1){
        int top_width = tier_top_width(i);
        int bottom_width = tier_base_width(i);
        int offset = crown_offset - (top_width+1)/2 +1;
        while(top_width < bottom_width+2){
           
            space_builder(offset);
            branch_row_builder(top_width);
            printf(COLOR_RESET"\n");
            printf("\n");
            top_width+=2;
            offset--;
        }
        
        i++;
    }   
}



int main(int ac, char **av){
   if(ac != 2)
    {
        return 0;
    }
   
    int tree_size = atoi(av[1]);

    if(tree_size < 1){
        return 0;
    }

    //limit oversized trees :)
    if(tree_size>15){
        tree_size = 15;
    }
  

    int *tree_size_ptr = malloc(32);
    *tree_size_ptr = tree_size;

    int max_base = tier_base_width(tree_size);

    int *trunk_offset = malloc(32);
    *trunk_offset = (max_base - tree_size) / 2 + (tree_size % 2 == 0);
    
    int *crown_tip_offset = malloc(32);
    *crown_tip_offset = (max_base - 1) / 2;

    crown_builder(tree_size_ptr, crown_tip_offset);
    bottom_builder(tree_size_ptr, trunk_offset);

    free(tree_size_ptr);
    free(trunk_offset);
    free(crown_tip_offset);
    
   
    return 0;
}
