// Defines symmetric matrix data structure -- 2d square array but assumes value
// at [i][j] should be equal to value at [j][i], and only stores one copy of
// each such duplicate value.

/* Example:
array [0 1 1 1,
       1 1 0 0,
       1 0 0 0,
       1 0 0 1]
becomes symmatrix matrix: [0 1 1 1 / 1 0 0 / 0 0 / 1]
Rows start at indices 0, 4, 7, 9 (+num_rows=4, +3, +2)
So, index [i][i] in matrix with diagonal becomes:
	array[num + (num-1) + ... + (num+1-i)]
	= array[i * (num - (i-1)/2)]
So, for index [i][j] in matrix with diagonal, rename so i<=j, then
find index [i][i], then add (j-i), which is nonnegative.
Note the /2 can leave half, which will be changed back to whole number by i*,
so rather use array[i*num - (i*(i-1))/2].

Ignoring diagonal, this matrix becomes [1 1 1 / 0 0 / 0].
Then, can think of rows as starting at indices -1, 2, 4.
Diagonal indices start at -1, then add num-1, then add num-2,
until value 2 reached.
So, index [i][i] in matrix without diagonal becomes:
    array[-1 + (num-1) + (num-2) + ... + (num-i)]
	= array[i*num - i(i+1)/2 - 1]
*/

#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <assert.h>

struct symmatrix {
	int num_rows;
	bool include_diagonal;
	size_t elem_size;
	void *start;
};

int cells_in_symmatrix(int num_rows, bool include_diagonal) {
	// with diagonals, it's 1 + 2 + ... + num_rows
	// without diagonals, it's 1 + 2 + ... + (num rows - 1)
	if (include_diagonal)
		return (num_rows * (num_rows + 1)) / 2;
	else
		return (num_rows * (num_rows - 1)) / 2;
}

struct symmatrix make_symmatrix(int num_rows, bool include_diagonal, size_t elem_size) {
	void *start = calloc(cells_in_symmatrix(num_rows, include_diagonal), elem_size);
	return ((struct symmatrix) {num_rows, include_diagonal, elem_size, start});
}

int symmatrix_index(struct symmatrix arr, int i, int j) {
	int min = (i < j) ? i : j;
	int max = (i < j) ? j : i;
	if (arr.include_diagonal) {
		return min*arr.num_rows - (min * (min - 1))/2 + (max - min);
	} else {
		return min*arr.num_rows - (min * (min + 1))/2 - 1 + (max - min);
	}
}

void *get_symmatrix_loc(struct symmatrix arr, int i, int j) {
	if (!arr.include_diagonal)
		assert(i != j);
	return arr.start + (arr.elem_size) * symmatrix_index(arr, i, j);
}

void print_symmatrix(struct symmatrix arr, void (*print)(void *)) {
	for (int i = 0; i < arr.num_rows; i++) {
		for (int j = 0; j < arr.num_rows; j++) {
			if ((i == j) && !arr.include_diagonal) {
				printf("*");
			} else {
				(*print)(get_symmatrix_loc(arr, i, j));
			}
			if (j != arr.num_rows - 1)
				printf(" ");
		}
		printf("\n");
	}
}

/* Tests:

int main() {
	struct symmatrix arr = make_symmatrix(3, false, sizeof(int));
	*(int*)get_symmatrix_loc(arr, 1, 0) = 10;
	*(int*)get_symmatrix_loc(arr, 2, 1) = 21;
	printf("val at 0 1: %d\n", *(int*)get_symmatrix_loc(arr, 0, 1));
	printf("val at 2 1: %d\n", *(int*)get_symmatrix_loc(arr, 2, 1));

	struct symmatrix arr2 = make_symmatrix(3, true, sizeof(int));
	*(int*)get_symmatrix_loc(arr2, 1, 0) = 10;
	*(int*)get_symmatrix_loc(arr2, 2, 1) = 21;
	*(int*)get_symmatrix_loc(arr2, 1, 1) = 11;
	printf("val at 0 1: %d\n", *(int*)get_symmatrix_loc(arr2, 0, 1));
	printf("val at 2 1: %d\n", *(int*)get_symmatrix_loc(arr2, 2, 1));
	printf("val at 1 1: %d\n", *(int*)get_symmatrix_loc(arr2, 1, 1));
} */