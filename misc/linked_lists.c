#include <stdio.h>
#include <malloc.h>

struct list {
	struct node *start;
	struct node *end;
	int num_nodes;
};

struct node {
	struct node *next;
	void *data;
};

struct list *make_list() {
	struct list *l = (struct list*)malloc(sizeof(struct list));
	l->start = NULL;
	l->end = NULL;
	l->num_nodes = 0;
	return l;
}

void append_data(struct list *l, void *data) {
	struct node *n = (struct node*)malloc(sizeof(struct node));
	n->data = data;
	n->next = NULL;
	l->num_nodes++;
	if (l->start == NULL) {
		l->start = l->end = n;
	}
	else {
		struct node *end = l->end;
		end->next = n;
		l->end = n;
	}
}

void print_char_list(struct list l) {
	struct node *curr = l.start;
	while (curr != NULL) {
		printf("%c\n", *((char*)(curr->data)));
		curr = curr->next;
	}
}

void print_int_list(struct list l) {
	struct node *curr = l.start;
	while (curr != NULL) {
		printf("%d\n", *((int*)(curr->data)));
		curr = curr->next;
	}
}

char *make_char(char c) {
	char *ptr = malloc(sizeof(char));
	*ptr = c;
	return ptr;
}

char *make_int(int x) {
	char *ptr = malloc(sizeof(int));
	*ptr = x;
	return ptr;
}


int main() {
	struct list char_list = *make_list();
	append_data(&char_list, make_char('t'));
	append_data(&char_list, make_char('e'));
	append_data(&char_list, make_char('s'));
	append_data(&char_list, make_char('t'));
	append_data(&char_list, make_char('1'));
	print_char_list(char_list);

	struct list int_list = *make_list();
	append_data(&int_list, make_int(1));
	append_data(&int_list, make_int(2));
	append_data(&int_list, make_int(4));
	append_data(&int_list, make_int(8));
	print_int_list(int_list);
}
