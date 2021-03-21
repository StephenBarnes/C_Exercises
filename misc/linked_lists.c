#include <stdio.h>
#include <malloc.h>

struct list {
	struct node *start;
	int num_nodes;
	struct node *end;
};

struct node {
	struct node *next;
	char content;
};

struct list *make_list() {
	struct list *l = (struct list*)malloc(sizeof(struct list));
	l->start = NULL;
	l->end = NULL;
	l->num_nodes = 0;
	return l;
}

void append_data(struct list *l, char data) {
	struct node *n = (struct node*)malloc(sizeof(struct node));
	n->content = data;
	n->next = NULL;
	l->num_nodes += 1;
	if (l->start == NULL) {
		l->start = l->end = n;
	}
	else {
		struct node *end = l->end;
		end->next = n;
		l->end = n;
	}
}

void show_all_data(struct list *l) {
	struct node *curr = l->start;
	while (curr != NULL) {
		printf("%c\n", curr->content);
		curr = curr->next;
	}
}


int main() {
	struct list *l = make_list();
	append_data(l, 'h');
	append_data(l, 'e');
	append_data(l, 'l');
	append_data(l, 'l');
	append_data(l, 'o');
	show_all_data(l);
}
