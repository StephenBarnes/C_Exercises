// Takes in an edge list for a graph.
// Outputs double-degrees of nodes, i.e. for each node outputs the sum of the
// node's neighbors' degrees.

// This version is implemented using symmetric-matrix structure.

#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include "symmetric_matrix.c"


void read_incidence_matrix(int num_edges, int num_nodes, struct symmatrix incidence) {
	for (int i = 0; i < num_edges; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		*(bool *)get_symmatrix_loc(incidence, a-1, b-1) = true;
	}
}

int degree_of(int node, int num_nodes, struct symmatrix incidence) {
	int degree = 0;
	for (int i = 1; i <= num_nodes; i++) {
		if (i == node) continue;
		if (*(bool *) get_symmatrix_loc(incidence, node-1, i-1))
			degree++;
	}
	return degree;
}

int double_degree_of(int node, int num_nodes, struct symmatrix incidence) {
	int double_degree = 0;
	for (int i = 1; i <= num_nodes; i++) {
		if (i == node) continue;
		if (*(bool *) get_symmatrix_loc(incidence, node-1, i-1))
			double_degree += degree_of(i, num_nodes, incidence);
	}
	return double_degree;
}

void print_bool(bool *val) {
	printf("%d", *val);
}

int main() {
	int num_nodes, num_edges;
	scanf("%d %d", &num_nodes, &num_edges);
	struct symmatrix incidence = make_symmatrix(num_nodes, false, sizeof(bool));

	read_incidence_matrix(num_edges, num_nodes, incidence);
	printf("\nIncidence matrix:\n");
	print_symmatrix(incidence, print_bool);

	printf("\nDegrees:\n");
	for (int i = 1; i <= num_nodes; i++) {
		printf("Node %d: degree %d\n", i, degree_of(i, num_nodes, incidence));
	}

	printf("\nDouble-degrees:\n");
	for (int i = 1; i <= num_nodes; i++) {
		printf("Node %d: double-degree %d\n", i, double_degree_of(i, num_nodes, incidence));
	}
}
