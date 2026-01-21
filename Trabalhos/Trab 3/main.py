class Graph:
    def _init_(self, num_vertices):
        self.num_vertices = num_vertices
        self.adj_matrix = [[0] * num_vertices for _ in range(num_vertices)]

    def add_edge(self, v1, v2, weight):
        self.adj_matrix[v1][v2] = weight
        self.adj_matrix[v2][v1] = weight
import heapq

def dijkstra(graph, source):
    num_vertices = graph.num_vertices
    distances = [float('inf')] * num_vertices
    distances[source] = 0

    pq = [(0, source)]

    while pq:
        dist, curr_vertex = heapq.heappop(pq)

        if dist > distances[curr_vertex]:
            continue

        for neighbor in range(num_vertices):
            weight = graph.adj_matrix[curr_vertex][neighbor]

            if weight > 0:
                new_dist = dist + weight

                if new_dist < distances[neighbor]:
                    distances[neighbor] = new_dist
                    heapq.heappush(pq, (new_dist, neighbor))

    return distances
def calculate_betweenness(graph):
    num_vertices = graph.num_vertices
    betweenness = [0] * num_vertices

    for source in range(num_vertices):
        distances = dijkstra(graph, source)
        shortest_paths = [[] for _ in range(num_vertices)]

        for target in range(num_vertices):
            path = []
            current_vertex = target

            while current_vertex != source:
                path.insert(0, current_vertex)
                prev_vertex = current_vertex

                for neighbor in range(num_vertices):
                    if (
                        graph.adj_matrix[neighbor][current_vertex] > 0
                        and distances[neighbor] == distances[current_vertex] - graph.adj_matrix[neighbor][current_vertex]
                    ):
                        current_vertex = neighbor
                        break

                if current_vertex == prev_vertex:
                    break

            path.insert(0, source)
            shortest_paths[target] = path

        num_shortest_paths = [0] * num_vertices

        for i in range(num_vertices):
            for j in range(i + 1, num_vertices):
                if source in shortest_paths[j] and i in shortest_paths[j]:
                    num_shortest_paths[i] += 1
                    num_shortest_paths[j] += 1

        for vertex in range(num_vertices):
            for path in shortest_paths[vertex]:
                if path != source:
                    if num_shortest_paths[path] != 0:
                        betweenness[path] += 1 / num_shortest_paths[path]


    return betweenness
import networkx as nx
import matplotlib.pyplot as plt

def draw_graph(graph, betweenness):
    G = nx.Graph()

    for v1 in range(graph.num_vertices):
        G.add_node(v1)

    for v1 in range(graph.num_vertices):
        for v2 in range(v1 + 1, graph.num_vertices):
            if graph.adj_matrix[v1][v2] > 0:
                G.add_edge(v1, v2, weight=graph.adj_matrix[v1][v2])

    node_colors = ['blue' if b > 0 else 'red' for b in betweenness]

    pos = nx.spring_layout(G)
    nx.draw(G, pos, node_color=node_colors, with_labels=True, node_size=500)
    edge_labels = nx.get_edge_attributes(G, 'weight')
    nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels)

    plt.show()

# Criação do grafo
graph = Graph(4)
graph.add_edge(0, 1, 1)
graph.add_edge(1, 2, 2)
graph.add_edge(2, 3, 3)
graph.add_edge(3, 0, 4)

# Cálculo da centralidade de betweenness
betweenness = calculate_betweenness(graph)
print("Betweenness centrality:", betweenness)

# Desenho do grafo com as cores dos vértices
draw_graph(graph, betweenness)