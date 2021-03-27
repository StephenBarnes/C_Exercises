#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <string.h>

struct circbuf {
	void *next_read;
	void *next_write;
	void *buffer_start;
	size_t buffer_size;
};

struct circbuf make_circbuf(int buffer_size) {
	char *buffer_start = malloc(buffer_size * sizeof(char));
	struct circbuf c = {
		NULL, // next_read
		buffer_start, // next_write
		buffer_start,
		buffer_size
	};
	return c;
}

char *circbuf_end(struct circbuf c) {
	return c.buffer_start + c.buffer_size;
}

size_t circbuf_free_space(struct circbuf c) {
	if (c.next_read > c.next_write) {
		return (size_t) (c.next_read - c.next_write);
	} else if (c.next_read < c.next_write) {
		return (size_t) ((circbuf_end(c) - (char*)c.next_write) + (c.next_read - c.buffer_start));
	} else {
		return (size_t) 0;
	}
}

size_t circbuf_occupied_space(struct circbuf c) {
	return c.buffer_size - circbuf_free_space(c);
}

int store_in_circbuf(struct circbuf *c, void *data_ptr, size_t size) {
	// size is size of data at data_ptr, in chars.
	// Returns 0 on success, -1 on error

	if (size == 0)
		return 0;
	if (c->next_read == NULL) {
		if (c->buffer_size < size)
			return -1;
		c->next_read = c->buffer_start;
	} else if (circbuf_free_space(*c) < size)
		return -1;

	if (c->next_write < c->next_read) {
		memcpy(c->next_write, data_ptr, size);
		c->next_write += size;
		return 0;
	} else {
		int size_right = circbuf_end(*c) - (char*) c->next_write;
		if (size_right > size) {
			memcpy(c->next_write, data_ptr, size);
			c->next_write += size;
			return 0;
		} else {
			memcpy(c->next_write, data_ptr, size_right);
			memcpy(c->buffer_start, data_ptr + size_right, size - size_right);
			c->next_write = c->buffer_start + size - size_right;
			return 0;
		}
	}
}

int read_circbuf(struct circbuf *c, void *dest, size_t size) {
	if (size == 0)
		return 0;
	if (c->next_read == NULL)
		return -1;
	if (circbuf_occupied_space(*c) < size)
		return -1;

	if (c->next_write > c->next_read) {
		memcpy(dest, c->next_read, size);
		c->next_read += size;
		return 0;
	} else {
		int size_right = circbuf_end(*c) - (char*) c->next_read;
		if (size_right > size) {
			memcpy(dest, c->next_read, size);
			c->next_read += size;
			return 0;
		} else {
			memcpy(dest, c->next_read, size_right);
			memcpy(dest + size_right, c->buffer_start, size - size_right);
			c->next_read = c->buffer_start + size - size_right;
			return 0;
		}
	}
}

void show_circbuf(struct circbuf c) {
	printf("buffer state:\n");
	for (char *loc = c.buffer_start; loc - (char *)c.buffer_start < c.buffer_size; loc++) {
		printf("%c ", *loc == '\0' ? '_' : *loc);
	}
	printf("\n");
	for (char *loc = c.buffer_start; loc - (char *)c.buffer_start < c.buffer_size; loc++) {
		if (loc == c.next_write) {
			if (c.next_read == c.next_write) printf("rw");
			else printf("w ");
		}
		else if (loc == c.next_read) printf("r ");
		else printf(". ");
	}
	printf("\n\n");
}

int main() {
	struct circbuf c = make_circbuf(8);
	char write1[] = "abc";
	char write2[] = "defg";
	char write3[] = "hijk";
	show_circbuf(c);
	store_in_circbuf(&c, write1, 3);
	show_circbuf(c);
	store_in_circbuf(&c, write2, 4);
	show_circbuf(c);
	char read1[6];
	read_circbuf(&c, read1, 5);
	read1[5] = '\0';
	printf("read: %s\n", read1);
	show_circbuf(c);
	store_in_circbuf(&c, write3, 4);
	show_circbuf(c);
	char read2[7];
	read_circbuf(&c, read2, 6);
	read2[6] = '\0';
	printf("read: %s\n", read2);
	show_circbuf(c);
}
