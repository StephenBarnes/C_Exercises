// Takes in an edge list for a graph.
// Outputs double-degrees of nodes, i.e. for each node outputs the sum of the
// node's neighbors' degrees.

// This version is implemented by creating an incidence matrix.

#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>


void read_degree_matrix(int num_edges, int num_nodes, bool *incidence) {
	for (int i = 0; i < num_edges; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		incidence[(a - 1) * num_nodes + b - 1] = 1;
		incidence[(b - 1) * num_nodes + a - 1] = 1;
	}
}

void print_bool_matrix(int side_len, bool *matrix) {
	for (int i = 0; i < side_len; i++) {
		for (int j = 0; j < side_len; j++) {
			printf("%d ", matrix[i * side_len + j]);
		}
		printf("\n");
	}
}

int degree_of(int node, int num_nodes, bool *incidence) {
	int degree = 0;
	for (int i = 1; i <= num_nodes; i++) {
		if (incidence[(node-1) * num_nodes + i - 1]) {
			degree++;
		}
	}
	return degree;
}

int double_degree_of(int node, int num_nodes, bool *incidence) {
	int double_degree = 0;
	for (int i = 1; i <= num_nodes; i++) {
		if (incidence[(node-1) * num_nodes + i - 1]) {
			double_degree += degree_of(i, num_nodes, incidence);
		}
	}
	return double_degree;
}


int main() {
	int num_nodes, num_edges;
	scanf("%d %d", &num_nodes, &num_edges);
	bool *incidence = calloc(num_nodes * num_nodes, sizeof(bool));
	read_degree_matrix(num_edges, num_nodes, incidence);
	printf("\nIncidence matrix:\n");
	print_bool_matrix(num_nodes, incidence);
	printf("\nDegrees:\n");
	for (int i = 1; i <= num_nodes; i++) {
		printf("Node %d: degree %d\n", i, degree_of(i, num_nodes, incidence));
	}
	printf("\nDouble-degrees:\n");
	for (int i = 1; i <= num_nodes; i++) {
		printf("Node %d: double-degree %d\n", i, double_degree_of(i, num_nodes, incidence));
	}
}
