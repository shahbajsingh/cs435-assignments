# import networkx as nx
# import numpy as np

# def gen_rand_graph(nodes, edges, type='directed'):
#     if type == 'directed':
#         G = nx.gnp_random_graph(nodes, edges / (nodes * (nodes-1)), directed=True)
#     else:
#         G = nx.gnp_random_graph(nodes, edges / (nodes * (nodes-1)), directed=False)

#         for (u, v) in G.edges():
#             G[u][v]['weight'] = np.random.randint(1, 10)

#     return G

import random
import numpy as np

class Graph:
    def __init__(self):
        self.nodes = set()
        self.edges = {}
    
    def add_node(self, node):
        self.nodes.add(node)
    
    def add_edge(self, u, v, weight):
        if u not in self.edges:
            self.edges[u] = {}
        self.edges[u][v] = weight
    
    def generate_random_graph(self, num_nodes, num_edges):
        self.nodes = set(range(num_nodes))
        while len([v for u in self.edges for v in self.edges[u]]) < num_edges:
            u = random.randint(0, num_nodes - 1)
            v = random.randint(0, num_nodes - 1)
            if u != v:
                weight = random.randint(1, 10)
                self.add_edge(u, v, weight)


def bellman_ford(graph, source):
    dist = {node: float('inf') for node in graph.nodes}
    dist[source] = 0

    for _ in range(len(graph.nodes) - 1): # relax edges repeatedly
        for u in graph.edges:
            for v in graph.edges[u]:
                if dist[u] + graph.edges[u][v] < dist[v]:
                    dist[v] = dist[u] + graph.edges[u][v]

    # Check for negative-weight cycles
    for u in graph.edges:
        for v in graph.edges[u]:
            if dist[u] + graph.edges[u][v] < dist[v]:
                raise ValueError("Graph contains a negative weight cycle")

    return dist


import heapq # for priority queue in Dijkstra's algorithm (which node to visit next)

def dijkstra(graph, source):
    dist = {node: float('inf') for node in graph.nodes} # shortest distance from source to node
    dist[source] = 0 # distance from source to source is 0
    pq = [(0, source)] # priority queue of (distance, node) pairs

    while pq: # while the priority queue is not empty
        curr_dist, u = heapq.heappop(pq) # get the node with smallest distance
        if curr_dist > dist[u]: # if a better path to u already found, skip
            continue

        for v in graph.edges.get(u, {}): # for each neighbour of u
            dist_via_u = curr_dist + graph.edges[u][v] # distance to v via u
            if dist_via_u < dist[v]: # if a better path to v found
                dist[v] = dist_via_u # update the distance to v
                heapq.heappush(pq, (dist_via_u, v)) # add v to the priority queue

    return dist

def floyd_warshall(graph): 
    nodes = list(graph.nodes) # list of nodes
    dist = {u: {v: float('inf') for v in nodes} for u in nodes} # dist[u][v] is the shortest distance from u to v
    for node in nodes: # distance from a node to itself is 0
        dist[node][node] = 0 

    for u in graph.edges: # distance from u to v is the weight of the edge (u, v)
        for v in graph.edges[u]: 
            dist[u][v] = graph.edges[u][v] 

    for k in nodes: # for each intermediate node k
        for i in nodes: # for each pair of nodes i, j
            for j in nodes: 
                if dist[i][j] > dist[i][k] + dist[k][j]: # if better path from i to j via k found
                    dist[i][j] = dist[i][k] + dist[k][j] # update distance from i to j

    return dist

def time_function(f, *args): # time a function
    import time
    start = time.time()
    f(*args)
    return (time.time() - start) * 1000 # in ms

def main():
    print("Graph of 5 nodes and 10 edges")
    graph = Graph()
    graph.generate_random_graph(5, 10)
    # print(graph.edges)

    # print("Times")
    print("Bellman-Ford:", time_function(bellman_ford, graph, 0))
    print("Dijkstra:", time_function(dijkstra, graph, 0))
    print("Floyd-Warshall:", time_function(floyd_warshall, graph))

    print()

    print("Graph of 10 nodes and 20 edges")
    graph = Graph()
    graph.generate_random_graph(10, 20)
    # print(graph.edges)

    # print("Times")
    print("Bellman-Ford:", time_function(bellman_ford, graph, 0))
    print("Dijkstra:", time_function(dijkstra, graph, 0))
    print("Floyd-Warshall:", time_function(floyd_warshall, graph))

    print()

    print("Graph of 100 nodes and 200 edges")
    graph = Graph()
    graph.generate_random_graph(100, 200)
    # print(graph.edges)

    # print("Times")
    print("Bellman-Ford:", time_function(bellman_ford, graph, 0))
    print("Dijkstra:", time_function(dijkstra, graph, 0))
    print("Floyd-Warshall:", time_function(floyd_warshall, graph))

    print()

    print("Graph of 1000 nodes and 2000 edges")
    graph = Graph()
    graph.generate_random_graph(1000, 2000)
    # print(graph.edges)

    # print("Times")
    print("Bellman-Ford:", time_function(bellman_ford, graph, 0))
    print("Dijkstra:", time_function(dijkstra, graph, 0))
    print("Floyd-Warshall:", time_function(floyd_warshall, graph))

    print()

    print("Graph of 10K nodes and 20K edges")
    graph = Graph()
    graph.generate_random_graph(10000, 20000)
    # print(graph.edges)

    # print("Times")
    print("Bellman-Ford:", time_function(bellman_ford, graph, 0))
    print("Dijkstra:", time_function(dijkstra, graph, 0))
    print("Floyd-Warshall:", time_function(floyd_warshall, graph))

    # print()

    # print("Graph of 100K nodes and 200K edges")
    # graph = Graph()
    # graph.generate_random_graph(100000, 200000)
    # # print(graph.edges)

    # # print("Times")
    # print("Bellman-Ford:", time_function(bellman_ford, graph, 0))
    # print("Dijkstra:", time_function(dijkstra, graph, 0))
    # print("Floyd-Warshall:", time_function(floyd_warshall, graph))

    # print()

    # print("Graph of 1M nodes and 2M edges")
    # graph = Graph()
    # graph.generate_random_graph(1000000, 2000000)
    # # print(graph.edges)

    # # print("Times")
    # print("Bellman-Ford:", time_function(bellman_ford, graph, 0))    
    # print("Dijkstra:", time_function(dijkstra, graph, 0))
    # print("Floyd-Warshall:", time_function(floyd_warshall, graph))

if __name__ == "__main__":
    main()
