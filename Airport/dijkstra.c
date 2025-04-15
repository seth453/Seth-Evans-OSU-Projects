/*
 * In this file, you'll implement Dijkstra's algorithm to find the least
 * expensive paths in the graph defined in `airports.dat`.  Don't forget to
 * include your name and @oregonstate.edu email address below.
 *
 * Name:
 * Email:
 */

#include <stdio.h>
#include <stdlib.h>

#define DATA_FILE "airports.dat"
#define START_NODE 0
#define INFINITY 99999

/* 
Name: readGraphData
Description: read the graph data from the file the store in matrix 
Parameters: 
Input: 
Output: 
*/ 
void readGraphData(int n_nodes, int n_edges, int graph[][n_nodes], FILE* file) { 
  for (int i = 0; i < n_nodes; ++i) {
    for (int j = 0; j < n_nodes; ++j) {
      graph[i][j] = 0; //initialize all entries to no edges
    }
  } 

  for (int i = 0; i < n_edges; ++i)
  {
    int node_i, node_j, cost; 
    fscanf(file, "%d %d %d", &node_i, &node_j, &cost); 
    graph[node_i][node_j] = cost;
  }
}

/* 
Name: 
Description: 
Parameters: 
Input: 
Output: 
*/ 
int findMinDistance(int dist[], int visited[], int n_nodes) { 
  int min_dist = INFINITY; 
  int min_node = -1;

  for (int i = 0; i < n_nodes; ++i) {
    if (!visited[i] && dist[i] < min_dist) {
      min_dist = dist[i]; 
      min_node = i;
    }
  }

  return min_node;
}

/* 
Name: 
Description: 
Parameters: 
Input: 
Output: 
*/ 
void dijkstra(int n_nodes, int graph[][n_nodes]) { 
  //Array to store min distance from start node
  int dist[n_nodes];
  //Array to keep track of visited nodes
  int visited[n_nodes]; 
  //Array to store previous node on shortest path
  int prev[n_nodes];

  //initialize arrays
  for (int i = 0; i < n_nodes; ++i)
  {
    dist[i] = INFINITY; 
    visited[i] = 0; 
    prev[i] = -1;
  }

  dist[START_NODE] = 0;

  //Dijkstra's algorithm
  for (int count = 0; count < n_nodes; ++count) {
    int u = findMinDistance(dist, visited, n_nodes); 
    visited[u] = 1; 
    for (int v = 0; v < n_nodes; ++v) { 
      if (!visited[v] && graph[u][v] != 0 && dist[u] + graph[u][v] < dist[v]) { 
        dist[v] = dist[u] + graph[u][v]; 
        prev[v] = u; 
      }
    
    }
  }
/*least cost paths*/
  for (int i = 0; i < n_nodes; ++i) {
    if (i != START_NODE) {
      printf("Least cost path from Node %d to Node %d: ", START_NODE, i);
      printf("Total cost: %d, Pathel: ", dist[i]);  
      int path_node = i; 
      while (path_node != -1) { 
        printf("%d", path_node); 
        path_node = prev[path_node];
      }
      printf("\n");
    }
  }
}

int main(int argc, char const *argv[]) {
  /*
   * Open file and read the first two int: num of nodes, num of edges
   */
  int n_nodes, n_edges;
  FILE* file = fopen(DATA_FILE, "r");
  fscanf(file, " %d %d ", &n_nodes, &n_edges);


  int graph[n_nodes][n_nodes];

  //creating graph
  readGraphData(n_nodes, n_edges, graph, file);
  
  //use Dijkstras algorithm
  dijkstra(n_nodes, graph);

   
  return 0;
}
