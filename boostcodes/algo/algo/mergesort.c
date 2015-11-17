#include "algo.h"

typedef struct CELL *LIST;
struct CELL {
	int element;
	LIST next;
};

LIST merge(LIST list1, LIST list2);
LIST split(LIST list);
LIST MergeSort(LIST list);
LIST MakeList(void);
void PrintList(LIST list);

int main()
{
	LIST list = MakeList();
	PrintList(MergeSort(list));
	return 0;
}

LIST MakeList()
{
	int x;
	if (scanf("%d", &x) == EOF) return NULL;

	LIST list = (LIST) malloc(sizeof(struct CELL));
	list->element = x;
	list->next = MakeList();
	return list;
}

void PrintList(LIST list)
{
	while (list != NULL) {
		printf("%d ", list->element);
		list = list->next;
	}
	putchar('\n');
}

LIST merge(LIST list1, LIST list2)
{
	if (list1 == NULL) return list2;
	if (list2 == NULL) return list1;

	if (list1->element <= list2->element) {
		list1->next = merge(list1->next, list2);
		return list1;
	}
	else {
		list2->next = merge(list2->next, list1);
		return list2;
	}
}

LIST split(LIST list)
{
	if (list == NULL || list->next == NULL) return NULL;

	LIST splitoutlist = list->next;
	list->next = splitoutlist->next;

	splitoutlist->next = split(splitoutlist->next);
	return splitoutlist;
}

LIST MergeSort(LIST list)
{
	if (list == NULL || list->next == NULL) return list;
	LIST right = split(list);
	return merge(MergeSort(list), MergeSort(right));
}

