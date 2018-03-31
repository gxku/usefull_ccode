#include<stdio.h>

void main(){
    int i=0;
    for(i=0;i<3140;i++){
    printf("%f %f %f\n",i/100.0,0.0,0.0);
    fflush(stdout);
//    sleep(1);
    }
}
