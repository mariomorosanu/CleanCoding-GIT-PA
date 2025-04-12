#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node* next;
} NODE;

typedef struct Graph
{
    int vertices;
    int* visited;
    NODE** adjacency_lists;
} GPH;

// === UTILITARE ===
NODE* create_node(int v)
{
    NODE* new_node = malloc(sizeof(NODE));
    new_node->data = v;
    new_node->next = NULL;
    return new_node;
}

GPH* create_graph(int vertices)
{
    GPH* graph = malloc(sizeof(GPH));
    graph->vertices = vertices;
    graph->adjacency_lists = malloc(vertices * sizeof(NODE*));
    graph->visited = malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++)
    {
        graph->adjacency_lists[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

void add_edge(GPH* graph, int src, int dest)
{
    NODE* new_node = create_node(dest);
    new_node->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = new_node;

    new_node = create_node(src);
    new_node->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = new_node;
}

void insert_edges(int nr_of_vertices, int nr_of_edges, GPH* graph)
{
    int src, dest;
    printf("Adauga %d muchii (noduri de la 0 la %d):\n", nr_of_edges, nr_of_vertices - 1);

    for (int i = 0; i < nr_of_edges; i++)
    {
        scanf_s("%d %d", &src, &dest);
        if (src >= 0 && dest >= 0 && src < nr_of_vertices && dest < nr_of_vertices)
        {
            add_edge(graph, src, dest);
        }
        else
        {
            printf("Muchie invalida: %d - %d\n", src, dest);
            i--; // repetam introducerea
        }
    }
}

// === COADA pentru BFS ===
int is_empty(NODE* queue)
{
    return queue == NULL;
}

void enqueue(NODE** queue, int data)
{
    NODE* new_node = create_node(data);

    if (is_empty(*queue))
    {
        *queue = new_node;
    }
    else
    {
        NODE* temp = *queue;
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

int dequeue(NODE** queue)
{
    int data = (*queue)->data;
    NODE* temp = *queue;
    *queue = (*queue)->next;
    free(temp);
    return data;
}

void print_graph(GPH* graph)
{
    printf("Graful este:\n");
    for (int i = 0; i < graph->vertices; i++)
    {
        NODE* temp = graph->adjacency_lists[i];
        printf("%d: ", i);
        while (temp)
        {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

void wipe_visited_list(GPH* graph)
{
    for (int i = 0; i < graph->vertices; i++)
    {
        graph->visited[i] = 0;
    }
}

// === PARCURGERI ===
void DFS(GPH* graph, int vertex)
{
    NODE* adj_list = graph->adjacency_lists[vertex];
    NODE* temp = adj_list;

    graph->visited[vertex] = 1;
    printf("%d ", vertex);

    while (temp != NULL)
    {
        int connected_vertex = temp->data;

        if (graph->visited[connected_vertex] == 0)
        {
            DFS(graph, connected_vertex);
        }

        temp = temp->next;
    }
}

void BFS(GPH* graph, int start)
{
    NODE* queue = NULL;

    graph->visited[start] = 1;
    enqueue(&queue, start);

    while (!is_empty(queue))
    {
        int current = dequeue(&queue);
        printf("%d ", current);

        NODE* temp = graph->adjacency_lists[current];

        while (temp)
        {
            int adj_vertex = temp->data;

            if (graph->visited[adj_vertex] == 0)
            {
                graph->visited[adj_vertex] = 1;
                enqueue(&queue, adj_vertex);
            }

            temp = temp->next;
        }
    }
}

// === MAIN ===
int main()
{
    int nr_of_vertices;
    int nr_of_edges;
    int starting_vertex;

    printf("Cate noduri are graful? ");
    scanf_s("%d", &nr_of_vertices);

    printf("Cate muchii are graful? ");
    scanf_s("%d", &nr_of_edges);

    GPH* graph = create_graph(nr_of_vertices);

    insert_edges(nr_of_vertices, nr_of_edges, graph);
    print_graph(graph);

    printf("De unde plecam in DFS? ");
    scanf_s("%d", &starting_vertex);

    printf("Parcurgere cu DFS: ");
    DFS(graph, starting_vertex);
    printf("\n");

    wipe_visited_list(graph);

    printf("De unde plecam in BFS? ");
    scanf_s("%d", &starting_vertex);

    printf("Parcurgere cu BFS: ");
    BFS(graph, starting_vertex);
    printf("\n");

    return 0;
}
