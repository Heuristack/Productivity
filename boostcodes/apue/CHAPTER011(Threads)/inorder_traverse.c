









while ( ptr != NULL || stacktop != NULL){		//(1)
	while (ptr != NULL) {
		q = (stnode *)malloc(sizeof(stnode));
		q->elem = ptr;
		q->link = stacktop;		//(2)
		stacktop = q;
		ptr = ptr->lchild;		//(3)
	}
	q = stacktop;
	stacktop = q->link;			//(4)
	visit(q);
	ptr = ptr->rchild;			//(5)
	free(q);
}
