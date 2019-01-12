#include<stdio.h>
char DW[][5]={"ling","yuan","shi","bai","qian","wan","shi","bai","qian","yi","shi","bai","qian"};
char NB[][5]={"ling","yi","er","san","si","wu","liu","qi","ba","jiu"};
void main(int argc, char*argv[]){
	char N[10];

	int i=0;
	int j=0;
	int has_0=0;
	if(argc!=2){
		printf("usage: a.out number\n");
		return;
	}

	while(argv[1][i]!='\0'){

		N[i]=argv[1][i];
		i++;
	}
	while(j<i){

		if(N[j]-'0'){
			if(has_0 && (i-j != 5 || i-j !=9))printf("ling "); 
			printf("%s %s ",NB[N[j]-'0'],DW[i-j]);
			
			has_0=0;
		}else{
			has_0++;
			if(has_0<4 && (i-j == 5 || i-j ==9)){
			printf("%s ",DW[i-j]); 
			has_0=0;
}
		}

		j++;
	}
	printf("\n");

}

