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
    distance = {node: float('inf') for node in graph.nodes}
    distance[source] = 0

    for _ in range(len(graph.nodes) - 1):
        for u in graph.edges:
            for v in graph.edges[u]:
                if distance[u] + graph.edges[u][v] < distance[v]:
                    distance[v] = distance[u] + graph.edges[u][v]

    # Check for negative-weight cycles
    for u in graph.edges:
        for v in graph.edges[u]:
            if distance[u] + graph.edges[u][v] < distance[v]:
                raise ValueError("Graph contains a negative weight cycle")

    return distance


import heapq

def dijkstra(graph, source):
    distance = {node: float('inf') for node in graph.nodes}
    distance[source] = 0
    priority_queue = [(0, source)]

    while priority_queue:
        current_distance, u = heapq.heappop(priority_queue)
        if current_distance > distance[u]:
            continue

        for v in graph.edges.get(u, {}):
            distance_via_u = current_distance + graph.edges[u][v]
            if distance_via_u < distance[v]:
                distance[v] = distance_via_u
                heapq.heappush(priority_queue, (distance_via_u, v))

    return distance

def floyd_warshall(graph):
    nodes = list(graph.nodes)
    dist = {u: {v: float('inf') for v in nodes} for u in nodes}
    for node in nodes:
        dist[node][node] = 0

    for u in graph.edges:
        for v in graph.edges[u]:
            dist[u][v] = graph.edges[u][v]

    for k in nodes:
        for i in nodes:
            for j in nodes:
                if dist[i][j] > dist[i][k] + dist[k][j]:
                    dist[i][j] = dist[i][k] + dist[k][j]

    return dist

def time_function(f, *args):
    import time
    start = time.time()
    f(*args)
    return (time.time() - start) * 1000 # in ms

def main():
    print("Graph of 5 nodes and 10 edges")
    graph = Graph()
    graph.generate_random_graph(5, 10)
    print(graph.edges)

    print("Times")
    print("Bellman-Ford:", time_function(bellman_ford, graph, 0))
    print("Dijkstra:", time_function(dijkstra, graph, 0))
    print("Floyd-Warshall:", time_function(floyd_warshall, graph))

    print("Graph of 10 nodes and 20 edges")
    graph = Graph()
    graph.generate_random_graph(10, 20)
    # print(graph.edges)

    print("Times")
    print("Bellman-Ford:", time_function(bellman_ford, graph, 0))
    print("Dijkstra:", time_function(dijkstra, graph, 0))
    print("Floyd-Warshall:", time_function(floyd_warshall, graph))

    print("Graph of 100 nodes and 200 edges")
    graph = Graph()
    graph.generate_random_graph(100, 200)
    # print(graph.edges)

    print("Times")
    print("Bellman-Ford:", time_function(bellman_ford, graph, 0))
    print("Dijkstra:", time_function(dijkstra, graph, 0))
    print("Floyd-Warshall:", time_function(floyd_warshall, graph))

    print("Graph of 1000 nodes and 2000 edges")
    graph = Graph()
    graph.generate_random_graph(1000, 2000)
    # print(graph.edges)

    print("Times")
    print("Bellman-Ford:", time_function(bellman_ford, graph, 0))
    print("Dijkstra:", time_function(dijkstra, graph, 0))
    print("Floyd-Warshall:", time_function(floyd_warshall, graph))

    print("Graph of 10K nodes and 20K edges")
    graph = Graph()
    graph.generate_random_graph(10000, 20000)
    # print(graph.edges)

    print("Times")
    print("Bellman-Ford:", time_function(bellman_ford, graph, 0))
    print("Dijkstra:", time_function(dijkstra, graph, 0))
    print("Floyd-Warshall:", time_function(floyd_warshall, graph))

    print("Graph of 100K nodes and 200K edges")
    graph = Graph()
    graph.generate_random_graph(100000, 200000)
    # print(graph.edges)

    print("Times")
    print("Bellman-Ford:", time_function(bellman_ford, graph, 0))
    print("Dijkstra:", time_function(dijkstra, graph, 0))
    print("Floyd-Warshall:", time_function(floyd_warshall, graph))

    print("Graph of 1M nodes and 2M edges")
    graph = Graph()
    graph.generate_random_graph(1000000, 2000000)
    # print(graph.edges)

    print("Times")
    print("Bellman-Ford:", time_function(bellman_ford, graph, 0))    
    print("Dijkstra:", time_function(dijkstra, graph, 0))
    print("Floyd-Warshall:", time_function(floyd_warshall, graph))

if __name__ == "__main__":
    main()
    