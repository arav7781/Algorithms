#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

// Structure to represent an edge
typedef struct {
    int u, v;
} Edge;

// Function to read the graph from a file
int read_graph(const char* filename, Edge* edges, int* num_edges, int* num_vertices) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return -1;
    }

    int u, v;
    int max_vertex = 0;
    *num_edges = 0;

    while (fscanf(file, "%d", &u) != EOF) {
        while (fscanf(file, "%d", &v) != EOF) {
            edges[*num_edges].u = u;
            edges[*num_edges].v = v;
            (*num_edges)++;
            if (v > max_vertex) max_vertex = v;
            if (fgetc(file) == '\n') break;
        }
        if (u > max_vertex) max_vertex = u;
    }

    fclose(file);
    *num_vertices = max_vertex;
    return 0;
}

// Function to find the minimum cut using Karger's algorithm
int karger_min_cut(Edge* edges, int num_edges, int num_vertices) {
    int* vertices = (int*)malloc(num_vertices * sizeof(int));
    for (int i = 0; i < num_vertices; i++) {
        vertices[i] = i;
    }

    int remaining_vertices = num_vertices;

    while (remaining_vertices > 2) {
        // Pick a random edge
        int random_edge_index = rand() % num_edges;
        int u = edges[random_edge_index].u;
        int v = edges[random_edge_index].v;

        // Contract the edge (u, v)
        for (int i = 0; i < num_edges; i++) {
            if (edges[i].u == v) edges[i].u = u;
            if (edges[i].v == v) edges[i].v = u;
        }

        // Remove self-loops
        int new_num_edges = 0;
        for (int i = 0; i < num_edges; i++) {
            if (edges[i].u != edges[i].v) {
                edges[new_num_edges++] = edges[i];
            }
        }
        num_edges = new_num_edges;

        remaining_vertices--;
    }

    // Count the number of edges crossing the cut
    int min_cut = 0;
    for (int i = 0; i < num_edges; i++) {
        if (edges[i].u != edges[i].v) {
            min_cut++;
        }
    }

    free(vertices);
    return min_cut;
}

// Function to run Karger's min cut algorithm multiple times
int run_karger_min_cut(const char* filename, int num_trials) {
    Edge* edges = (Edge*)malloc(200 * 200 * sizeof(Edge));
    int num_edges;
    int num_vertices;
    if (read_graph(filename, edges, &num_edges, &num_vertices) != 0) {
        return -1;
    }

    int min_cut = INT_MAX;
    for (int i = 0; i < num_trials; i++) {
        Edge* edges_copy = (Edge*)malloc(num_edges * sizeof(Edge));
        memcpy(edges_copy, edges, num_edges * sizeof(Edge));
        int cut_size = karger_min_cut(edges_copy, num_edges, num_vertices);
        if (cut_size < min_cut) {
            min_cut = cut_size;
        }
        free(edges_copy);
    }

    free(edges);
    return min_cut;
}

int main() {
    srand(time(NULL));

    const char* filename = "C:\\Users\\aravs\\Downloads\\_f370cd8b4d3482c940e4a57f489a200b_kargerMinCut.txt";
    int num_trials = 100;  // You can increase this number for better approximation
    int min_cut = run_karger_min_cut(filename, num_trials);

    if (min_cut != -1) {
        printf("The minimum cut found after %d trials is: %d\n", num_trials, min_cut);
    } else {
        printf("Error reading the graph.\n");
    }

    return 0;
}
