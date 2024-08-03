#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_VERTICES 200
#define MAX_EDGES 10000

typedef struct {
    int u, v;
} Edge;

typedef struct {
    int vertices[MAX_VERTICES];
    int num_vertices;
    Edge edges[MAX_EDGES];
    int num_edges;
} Graph;

void read_graph(Graph *graph, const char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (!file) {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }

    graph->num_vertices = 0;
    graph->num_edges = 0;
    char line[1000];
    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, "\t");
        int u = atoi(token);
        graph->vertices[graph->num_vertices++] = u;
        while ((token = strtok(NULL, "\t")) != NULL) {
            int v = atoi(token);
            if (u < v) {  // to avoid duplicating edges
                graph->edges[graph->num_edges].u = u;
                graph->edges[graph->num_edges].v = v;
                graph->num_edges++;
            }
        }
    }
    fclose(file);
}

void contract_edge(Graph *graph, int edge_index) {
    int u = graph->edges[edge_index].u;
    int v = graph->edges[edge_index].v;

    // Merge v into u and update edges
    for (int i = 0; i < graph->num_edges; i++) {
        if (graph->edges[i].u == v) graph->edges[i].u = u;
        if (graph->edges[i].v == v) graph->edges[i].v = u;
    }

    // Remove self-loops
    int new_num_edges = 0;
    for (int i = 0; i < graph->num_edges; i++) {
        if (graph->edges[i].u != graph->edges[i].v) {
            graph->edges[new_num_edges++] = graph->edges[i];
        }
    }
    graph->num_edges = new_num_edges;

    // Remove v from vertices
    int new_num_vertices = 0;
    for (int i = 0; i < graph->num_vertices; i++) {
        if (graph->vertices[i] != v) {
            graph->vertices[new_num_vertices++] = graph->vertices[i];
        }
    }
    graph->num_vertices = new_num_vertices;
}

int karger_min_cut(Graph *graph) {
    while (graph->num_vertices > 2) {
        int edge_index = rand() % graph->num_edges;
        contract_edge(graph, edge_index);
    }
    return graph->num_edges;
}

int repeated_karger_min_cut(Graph *graph, int iterations) {
    int min_cut = MAX_EDGES;
    for (int i = 0; i < iterations; i++) {
        Graph temp_graph = *graph;
        int cut_size = karger_min_cut(&temp_graph);
        if (cut_size < min_cut) {
            min_cut = cut_size;
        }
    }
    return min_cut;
}

int main() {
    srand(time(NULL));
    Graph graph;
    read_graph(&graph, "C:\\Users\\aravs\\Downloads\\_f370cd8b4d3482c940e4a57f489a200b_kargerMinCut.txt");
    int iterations = 100; // Number of iterations for better accuracy
    int min_cut = repeated_karger_min_cut(&graph, iterations);
    printf("The minimum cut is: %d\n", min_cut);
    return 0;
}
