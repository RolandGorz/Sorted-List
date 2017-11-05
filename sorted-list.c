/*
 * sorted-list.c
 */
//This program has a runtime of O(n). This is due to the functions where i have to traverse the entire list.

#include	<stdio.h>
#include	<string.h>
#include	"sorted-list.h"

void * SLGetItem(SortedListIteratorPtr iter) {
	if(iter->travel == NULL) { //if the list is empty
		void *ans = NULL;	
		return ans;
	}	
	return iter->travel->value;
}

void * SLNextItem(SortedListIteratorPtr iter) {
	void *ans = NULL;
	if(iter->travel == NULL || iter->travel->next == NULL) { //if the list is empty or at the final node
		iter->travel = NULL;	
		return ans;
	}
	ans = iter->travel->next->value;
	iter->travel->counter--; //moved iterator means one less pointer to the node
	if (iter->travel->counter == 0) {//remove it if nothing is pointing to it
		free(iter->travel);
	}
	iter->travel = iter->travel->next;
	iter->travel->counter++;
	return ans;	
}

void SLDestroyIterator(SortedListIteratorPtr iter){
	iter->travel->counter--;
	if (iter->travel->counter == 0) {
		free(iter->travel);
	}
	free(iter);
}

void SLDestroy(SortedListPtr list) {
	Node* walk = list->head;
	if (walk == NULL) {
		free(walk);
		free(list);
		return;
	}
	while(walk->next != NULL) {
		list->head = list->head->next;
		free(walk);
		walk = list->head;
	}
	free(walk);
	free(list);
}

void PrintListInt(SortedListPtr list) {
	Node* walk = list->head;
	if (walk == NULL) {
		printf("NULL");
		return;
	}
	while(walk != NULL) {
		printf("%d", *(int*)walk->value);
		if (walk->next != NULL) {
			printf(" --> ");
		}
		walk = walk->next;
	}
	printf("\n");
}

void PrintListDouble(SortedListPtr list) {
	Node* walk = list->head;
	if (walk == NULL) {
		printf("NULL");
		return;
	}
	while(walk != NULL) {
		printf("%f", *(double*)walk->value);
		if (walk->next != NULL) {
			printf(" --> ");
		}
		walk = walk->next;
	}
	printf("\n");
}

void PrintListString(SortedListPtr list) {
	Node* walk = list->head;
	if (walk == NULL) {
		printf("NULL");
		return;
	}
	while(walk != NULL) {
		printf("%s", (char*)walk->value);
		if (walk->next != NULL) {
			printf(" --> ");
		}
		walk = walk->next;
	}
	printf("\n");
}



int SLRemove(SortedListPtr list, void *newObj) {//do this one
	Node* walk = list->head;
	Node* behind = list->head;
	if (list->head->value == NULL) {
		return 0;
	}
	while(walk != NULL) {
		if (list->cf(newObj, walk->value) == 0) {
			if (behind == walk) {
				list->head->counter--;
				list->head = list->head->next;
				if (walk->counter == 0) {
					free(walk);
				}
				//PrintListInt(list);//COMMENT THIS OUT
				//PrintListDouble(list);
				//PrintListString(list);
				return 1;
			}
			behind->next = walk->next;
			walk->counter--;
			if (walk->counter == 0) {
				free(walk);
				//PrintListInt(list);//COMMENT THIS OUT
				//PrintListDouble(list);
				//PrintListString(list);
			}
			return 1;
			//PrintListInt(list);//COMMENT THIS OUT
			//PrintListDouble(list);
			//PrintListString(list);
		}
		behind = walk;
		walk = walk->next;
	}
	return 0;
}

int SLInsert(SortedListPtr list, void *newObj) {
	Node* walk = list->head;
	Node* behind = list->head;
	Node* new = malloc(sizeof(Node));
	if (list->head->value == NULL) {
		list->head->value = newObj;
		free(new);
		//PrintListInt(list);//COMMENT THIS OUT
		//PrintListDouble(list);
		//PrintListString(list);
		return 1;	
	}
	while (walk != NULL) {
		if (list->cf(newObj, walk->value) > 0) {//put the newobj first so that you know to put it before or after
			if(behind == walk) {
				new->value = newObj;
				new->next = walk;
				list->head = new;
				new->counter = 1;
				//PrintListInt(list);//COMMENT THIS OUT
				//PrintListDouble(list);
				//PrintListString(list);
				return 1;
			}
			new->value = newObj;
			new->next = walk;
			new->counter = 1;
			behind->next = new;
			//PrintListInt(list);//COMMENT THIS OUT
			//PrintListDouble(list);
			//PrintListString(list);
			return 1;
		}
		if (list->cf(newObj, walk->value) < 0) {
			if (walk->next == NULL) {
				walk->next = new;
				new->value = newObj;
				new->counter = 1;
				new->next = NULL;
				//PrintListInt(list);//COMMENT THIS OUT
				//PrintListDouble(list);
				//PrintListString(list);
				return 1;
			}
			behind = walk;
			walk = walk->next;
		}
		if (list->cf(newObj, walk->value) == 0) {
			if(behind == walk) {
				new->value = newObj;
				new->next = walk;
				list->head = new;
				new->counter = 1;
				//PrintListInt(list);//COMMENT THIS OUT
				//PrintListDouble(list);
				//PrintListString(list);
				return 1;
			}
			new->value = newObj;
			new->counter = 1;
			new->next = walk;
			behind->next = new;
			//PrintListInt(list);//COMMENT THIS OUT
			//PrintListDouble(list);
			//PrintListString(list);
			return 1;
		}
	}
	return 1;
}

SortedListPtr SLCreate(CompareFuncT cf, DestructFuncT df) {
	SortedListPtr ptr = malloc(sizeof(struct SortedList));
	ptr->head = malloc(sizeof(Node));
	ptr->cf = cf;
	ptr->df = df;
	ptr->head->value = NULL;
	ptr->head->counter = 1;
	ptr->head->next = NULL;
	return ptr;
}

SortedListIteratorPtr SLCreateIterator(SortedListPtr list) {
	SortedListIteratorPtr iter = malloc(sizeof(struct SortedListIterator));
	list->head->counter++;
	iter->travel = list->head;
	return iter;
}

