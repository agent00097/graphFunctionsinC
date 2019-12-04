
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

//HELPER FUNCTIONS USED

//check_it finds a path between two vertices
int check_it(Graph *graph, int try, int destination, int index);

//check_if_visited is used to check whether vertex is already visited
int check_if_visited(Graph *graph, int what_to_check);

//check_max_vertex checks for the maximum vertex in the graph
int check_max_vertex(Graph *graph);

//clear_the_graph initiales all the value of matrix before loading a new file
void clear_the_graph(Graph *graph);


//GRAPH INITIALIZATION FUNCTION

Graph *graph_initialize()
{
    Graph *whatever = malloc(sizeof(Graph));
    //return null if memory was not allocated
    if (whatever == NULL)
    {
        return NULL;
    }
    else
    {
        //Initializing all the values before returning a pointer to it
        whatever->max_vertex = MAX_VERTICES;
        for (int i = 0; i < MAX_VERTICES; i++)
        {
            for (int j = 0; j < MAX_VERTICES; j++)
            {
                whatever->adj_matrix[i][j] = -1;
            }
        }
        for (int i = 0; i < MAX_VERTICES; i++)
        {
            whatever->visited[i] = -1;
        }

        return whatever;
    }
}

//GRAPH CLEAR FUNCTION

void clear_the_graph(Graph *graph)
{
    for (int i = 0; i < MAX_VERTICES; i++)
    {
        for (int j = 0; j < MAX_VERTICES; j++)
        {
            //setting all the values in the matrix to -1
            graph->adj_matrix[i][j] = -1;
        }
    }
}

//VERTEX ADDING FUNCTION

int graph_add_vertex(Graph *graph, int v1)
{
    //If provided vertex is incorrect or if the graph doesn't exist return -1
    if (v1 < 0 || v1 >= MAX_VERTICES || graph == NULL)
    {
        return -1;
    }
    else
    //adding vertex and returning 0
    {
        graph->adj_matrix[v1][v1] = 0;
        return 0;
    }
}

//FUNCTION TO CHECK WHETHER GRAPH CONTAINS VERTEX

int graph_contains_vertex(Graph *graph, int v1)
{
    //return 0 if graph doesn't exist
    if (graph == NULL || v1 < 0)
    {
        return 0;
    }
    else
    //If vertex is found then return 1 else return 0
    {
        if (graph->adj_matrix[v1][v1] >= 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

//VERTEX REMOVAL FUNCTION

int graph_remove_vertex(Graph *graph, int v1)
{
    //return -1 if graph is not found or if v1 provided was incorrect
    if (graph == NULL || v1 < 0)
    {
        return -1;
    }
    else
    {
        //First remove the vertex by adding -1 there
        graph->adj_matrix[v1][v1] = -1;
        for (int i = 0; i < MAX_VERTICES; i++)
        {
            //removing edges to or from that vertex
            graph->adj_matrix[v1][i] = -1;
            graph->adj_matrix[i][v1] = -1;
        }

        return 0;
    }
}

//EDGE ADDING FUNCTION

int graph_add_edge(Graph *graph, int v1, int v2, int wt)
{
    //returning -1 if graph doesnt exist or if provided v1 and v2 vertex doesn't exist
    if (graph == NULL || graph->adj_matrix[v1][v1] < 0 || graph->adj_matrix[v2][v2] < 0 || wt <= 0)
    {
        return -1;
    }
    else
    //Adding weight to the matrix
    {
        graph->adj_matrix[v1][v2] = wt;
        return 0;
    }
}

//FUNCTION TO CHECK WETHER GRAPH HAS AN EDGE BETWEEN TWO PROVIDED VERTICES

int graph_contains_edge(Graph *graph, int v1, int v2)
{
    //returning 0 if graph doesnt exist or if provided v1 and v2 vertex doesn't exist
    if (graph == NULL || graph->adj_matrix[v1][v1] < 0 || graph->adj_matrix[v2][v2] < 0)
    {
        return 0;
    }
    else
    {
        //If edge exists return 1 else return 0
        if (graph->adj_matrix[v1][v2] >= 1)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

//EDGE REMOVING FUNCTION

int graph_remove_edge(Graph *graph, int v1, int v2)
{
    //returning -1 if graph doesnt exist or if provided v1 and v2 vertex doesn't exist
    if (graph == NULL || graph->adj_matrix[v1][v1] < 0 || graph->adj_matrix[v2][v2] < 0)
    {
        return -1;
    }
    else
    {
        if(v1==v2)
        {
            graph->adj_matrix[v1][v2] = 0;
        }
        else
        {
            graph->adj_matrix[v1][v2] = -1;
        }
        
    }
}

//FUNCTION TO COUNT THE VERTICES IN THE GRAPH

int graph_num_vertices(Graph *graph)
{
    //return -1 if graph doesnt exist
    if (graph == NULL)
    {
        return -1;
    }
    else
    {
        //Settin up a counter to count all the vertices
        int dooku = 0;
        for (int i = 0; i < MAX_VERTICES; i++)
        {
            if (graph->adj_matrix[i][i] >= 0)
            {
                //if found the counter is incremented
                dooku++;
            }
        }
        return dooku;
    }
}

//FUNCTION TO COUNT ALL THE EDGES IN THE GRAPH

int graph_num_edges(Graph *graph)
{
    //If graph doesnt exist return -1
    if (graph == NULL)
    {
        return -1;
    }
    else
    {
        //Initialing a counter to count all the edges if found
        int dooku = 0;
        for (int i = 0; i < MAX_VERTICES; i++)
        {
            for (int j = 0; j < MAX_VERTICES; j++)
            {
                if (graph->adj_matrix[i][j] >= 1)
                {
                    //If the value exits then incrementing counter
                    dooku++;
                }
            }
        }
        return dooku;
    }
}

//FUNCTION TO COUNT THE TOTAL WEIGHT

int graph_total_weight(Graph *graph)
{
    //If graoh doesnt exist then return -1
    if (graph == NULL)
    {
        return -1;
    }
    else
    {
        //Initializing a counter to count the total weight
        int dooku = 0;
        for (int i = 0; i < MAX_VERTICES; i++)
        {
            for (int j = 0; j < MAX_VERTICES; j++)
            {
                if (graph->adj_matrix[i][j] >= 1)
                {
                    //Adding weight to the counter everytime found
                    dooku = dooku + graph->adj_matrix[i][j];
                }
            }
        }

        return dooku;
    }
}

//FUNCTION TO GET THE DEGREE OF THE FUNCTION

int graph_get_degree(Graph *graph, int v1)
{
    //If graph doesnt exist or if v1 doesnt exist then return -1
    if (graph == NULL || graph->adj_matrix[v1][v1] < 0)
    {
        return -1;
    }
    else
    {
        //Initializing a counter to count in-degrees and out-degrees
        int dooku = 0;
        for (int i = 0; i < MAX_VERTICES; i++)
        {
            if (graph_contains_edge(graph, i, v1) == 1)
            {
                //incrementing counter if you get in-degree
                dooku++;
            }
            if (graph_contains_edge(graph, v1, i) == 1)
            {
                //incrementing counter if you get out-degree
                dooku++;
            }
        }
        return dooku;
    }
}

//FUNCTION TO GET VALUE OF THE EDGE

int graph_get_edge_weight(Graph *graph, int v1, int v2)
{
    //returning -1 if graph doesnt exist or if provided v1 and v2 vertex doesn't exist
    if (graph == NULL || graph->adj_matrix[v1][v1] < 0 || graph->adj_matrix[v2][v2] < 0)
    {
        return -1;
    }
    else
    {
        //return -1 if vertex doesnt exist
        if (graph->adj_matrix[v1][v2] <= 0)
        {
            return -1;
        }
        else
        {
            //else return the value of the weight from v1 to v2
            return graph->adj_matrix[v1][v2];
        }
    }
}

//FUNCTION TO CHECK WHETHER TWO VERTICES ARE NEIGHBOR

int graph_is_neighbor(Graph *graph, int v1, int v2)
{
    //returning NULL if graph doesnt exist or if provided v1 and v2 vertex doesn't exist
    if (graph == NULL || graph->adj_matrix[v1][v1] < 0 || graph->adj_matrix[v2][v2] < 0)
    {
        return 0;
    }
    else

    {
        //If there's an edge between v1 to v2 or v2 to v1 then return 1
        if (graph->adj_matrix[v1][v2] >= 1 || graph->adj_matrix[v2][v1] >= 1)
        {
            return 1;
        }
        //return 0 if they are not neighbor
        else
        {
            return 0;
        }
    }
}

//FUNCTION TO GET ALL THE PREDECESSORS OF THE VERTEX

int *graph_get_predecessors(Graph *graph, int v1)
{
    //If graph doesnt exist or if vertex v1 doesnt exist
    if (graph == NULL || graph->adj_matrix[v1][v1] < 0)
    {
        return NULL;
    }
    else
    {
        //Allocating pointer to integer array on heap
        int dooku = 0;
        int *here = malloc(sizeof(int) * MAX_VERTICES + 1);
        for (int i = 0; i < MAX_VERTICES; i++)
        {
            //If vertex is found then assigning it the next available space in heap
            if (graph->adj_matrix[i][v1] >= 1)
            {
                here[dooku] = i;
                dooku++;
            }
            here[dooku] = -1;
        }
        return here;
    }
}

//FUNCTION TO GET SUCCESSORS OF THE VERTEX

int *graph_get_successors(Graph *graph, int v1)
{
    //returning NULL if graph doesnt exist or if provided v1 vertex doesn't exist
    if (graph == NULL || graph->adj_matrix[v1][v1] < 0)
    {
        return NULL;
    }
    else
    {
        //Initialing counter to see the next available space in the array
        int dooku = 0;
        //Creating a new pointer to integer to and initializing all the values to -1
        int *here = malloc(sizeof(int) * MAX_VERTICES + 1);
        for (int i = 0; i < MAX_VERTICES; i++)
        {
            here[i] = -1;
        }
        //Assigning value of the vertex to next available space
        for (int i = 0; i < MAX_VERTICES; i++)
        {
            if (graph->adj_matrix[v1][i] >= 1)
            {
                here[dooku] = i;
                dooku++;
            }
        }
        //Assiging max_vertex value as the counter, it is later used in a loop in the has path function
        graph->max_vertex = dooku;
        return here;
    }
}

//FUNCTION TO CHECK WHETHER THEIR'S A PATH FROM VERTEX V1 TO V2

int graph_has_path(Graph *graph, int v1, int v2)
{
    //returning -1 if graph doesnt exist or if provided v1 and v2 vertex doesn't exist or if the value of v1 and v2 are not correct
    if (graph == NULL || graph->adj_matrix[v1][v1] < 0 || graph->adj_matrix[v2][v2] < 0 || v1 < 0 || v2 < 0)
    {
        return 0;
    }
    else
    {
        //Counter to keep adding vertex in visited
        int dooku = 0;
        int answer = check_it(graph, v1, v2, dooku);
        //After getting the answer, visited vertex is reinitialized and also max_vertex is initialized
        for (int i = 0; i < MAX_VERTICES; i++)
        {
            graph->visited[i] = -1;
        }
        graph->max_vertex = -1;
        return answer;
    }
}

//HELPER FUNCTION FOR HAS PATH

int check_it(Graph *graph, int try, int destination, int index)
{
    //If the path is found then return 1
    if (graph->adj_matrix[try][destination] > 0)
    {
        return 1;
    }
    else
    {
        //Assiging that vertex into the visited
        graph->visited[index] = try;
        //Updating the counter after that
        index++;
        //Getting all the successors of that specific vertex
        int *temp = graph_get_successors(graph, try);
        for (int i = 0; i < graph->max_vertex; i++)
        {
            //Only recurse when that vertex is not in the visited array
            if (check_if_visited(graph, temp[i]) == 0)
            {
                return check_it(graph, temp[i], destination, index);
            }
        }
    }
}

//HELPER FUNCTION TO SEE WHETHER THAT VERTEX IS IN THE VISITED

int check_if_visited(Graph *graph, int what_to_check)
{
    int yeah = 0;
    //For loop until you get -1 in the visited array
    for (int i = 0; graph->visited[i] != -1; i++)
    {
        if (graph->visited[i] == what_to_check)
        {
            yeah = 1;
        }
    }
    return yeah;
}

//GRAPH PRINT FUNCTION

void graph_print(Graph *graph)
{
    int dooku = check_max_vertex(graph);
    for (int i = 0; i < dooku + 1; i++)
    {
        printf("\n");
        for (int j = 0; j < dooku + 1; j++)
        {
            if (graph->adj_matrix[i][j] == -1)
            {
                //printing * wherever there is -1
                printf("*\t");
            }
            else
            {
                //printing the value if found
                printf("%d\t", graph->adj_matrix[i][j]);
            }
        }
    }
}

//HELPER FUNCTION TO CHECK MAXIMUM VERTEX IN THE GRAPH

int check_max_vertex(Graph *graph)
{
    int dooku = 0;
    for (int i = 0; i < MAX_VERTICES; i++)
    {
        if (graph->adj_matrix[i][i] >= 0)
        {
            dooku = i;
        }
    }
    return dooku;
}

//FUNCTION TO PRINT THE GRAPH IN THE DOT FORMAT

void graph_output_dot(Graph *graph, char *filename)
{
    //If graoh or filename are not found then exit
    if (graph == NULL || filename == NULL)
    {
        exit(-1);
    }
    else
    {
        //Initializing a new pointer to file
        FILE *whatever = fopen(filename, "w+");
        //If files not found then exit
        if (whatever == NULL)
        {
            exit(-1);
        }
        else
        {
            //printing the first line which will always be digraph{
            fprintf(whatever, "digraph {\n");
            
            for (int i = 0; i < MAX_VERTICES; i++)
            {
                for (int j = 0; j < MAX_VERTICES; j++)
                {
                    if (i == j)
                    {
                        //If vertex is same and it has no self loop then returning only the vertex in that line
                        if (graph->adj_matrix[i][j] == 0)
                        {
                            fprintf(whatever, "%d;\n", i);
                        }
                        //If there's a self loop then returning vertex,vertex,weight of the self loop
                        if (graph->adj_matrix[i][j] > 0)
                        {
                            fprintf(whatever, "%d -> %d [label = %d];\n", i, i, graph->adj_matrix[i][j]);
                        }
                    }
                    else
                    {
                        //If its not the same vertex than printing out vertex,vertex,weight of the edge if found
                        if (graph->adj_matrix[i][j] > 0)
                        {
                            fprintf(whatever, "%d -> %d [label = %d];\n", i, j, graph->adj_matrix[i][j]);
                        }
                    }
                }
            }

            //last line which will be the closing bracket of digraph
            fprintf(whatever, "}");
            //closing down the file pointer
            fclose(whatever);
        }

    }
}

//FUNCTION TO LOAD MATRIX FROM THE FILE

int graph_load_file(Graph *graph, char *filename)
{

    //If graph or filename are not found then return 0

    if (graph == NULL || filename == NULL)
    {
        return 0;
    }
    else
    {
        //before loading the graph, previous graph is cleared
        clear_the_graph(graph);
        //Assiging File pointer
        FILE *whatever = fopen(filename, "r");
        char *token;
        //If pointer is null then returning 0
        if (whatever == NULL)
        {
            return 0;
        }
        else
        {
            char line[FILE_ENTRY_MAX_LEN];
            while (fgets(line, sizeof(line), whatever) != NULL)
            {
                int if_second_exists = 0;
                int number_count = 1;
                token = strtok(line, ", ");
                //First charachter action
                //converting char into int
                int first_digit = strtol(token,NULL,10);
                //If vertex doesnt exist then add vertex
                if (graph_contains_vertex(graph, first_digit) == 0)
                {
                    int u = graph_add_vertex(graph, first_digit);
                }
                number_count++;
                while (token != NULL)
                {
                    token = strtok(NULL, ", ");
                    if (token != NULL)
                    {
                        if (number_count == 2)
                        {
                            //Second charachter action
                            //converting char into int
                            int digit = strtol(token,NULL,10);
                            if_second_exists = digit;
                            //If vertex doesnt exist then add vertex
                            if (graph_contains_vertex(graph, digit) == 0)
                            {
                                int s = graph_add_vertex(graph, digit);
                            }
                            number_count++;
                        }
                        else
                        {
                            //Third charachter token
                            //converting char into int
                            int digit = strtol(token,NULL,10);
                            int j = graph_add_edge(graph, first_digit, if_second_exists, digit);
                        }
                    }
                }
            }
            fclose(whatever);
        }
        return 1;
    }
}

//FUNCTION TO SAVE FILE

int graph_save_file(Graph *graph, char *filename)
{
    //If graph or filename is incorrect then return 0
    if (graph == NULL || filename == NULL)
    {
        return 0;
    }
    else
    {
        //pointer to the file initialized
        FILE *whatever = fopen(filename, "w+");
        if (whatever == NULL)
        {
            return 0;
        }
        else
        {
            for (int i = 0; i < MAX_VERTICES; i++)
            {
                for (int j = 0; j < MAX_VERTICES; j++)
                {
                    if (i == j)
                    {
                        //If vertex is same and it has no self loop then returning only the vertex in that line
                        if (graph->adj_matrix[i][j] == 0)
                        {
                            fprintf(whatever, "%d\n", i);
                        }
                        //If there's a self loop then returning vertex,vertex,weight of the self loop
                        if (graph->adj_matrix[i][j] > 0)
                        {
                            fprintf(whatever, "%d,%d,%d\n", i, i, graph->adj_matrix[i][j]);
                        }
                    }
                    else
                    {
                        //If its not the same vertex than printing out vertex,vertex,weight of the edge if found
                        if (graph->adj_matrix[i][j] > 0)
                        {
                            fprintf(whatever, "%d,%d,%d\n", i, j, graph->adj_matrix[i][j]);
                        }
                    }
                }
            }

            fclose(whatever);
        }

        return 1;
    }
}
