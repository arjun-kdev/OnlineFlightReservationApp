#include"myutil.h"
#include<stdio.h>
void clear_input_buffer(void){
    while(getchar() != '\n');
}