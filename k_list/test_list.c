#include <stdio.h>
#include <stdlib.h>
#include "list.h"


struct node{
	struct list_head list;
	int value;
}*my_node;

void main(){
	int i = 0;
	LIST_HEAD(test_list);
	while(i<1500){
		my_node = malloc(sizeof(struct node));
		my_node->value = i;
		list_add(&(my_node->list),&test_list);
		i++; 
	}


	while(!list_empty(&test_list)){
		struct node *node = list_entry(test_list.next,struct node,list);
		printf("value = %d\n",node->value);
		list_del(&(node->list));
		free(node);

	}
	return ;
}
