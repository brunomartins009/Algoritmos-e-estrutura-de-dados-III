import random
import networkx as nx
import matplotlib.pyplot as plt

# Função que calcula a centralidade(betweenness) de cada vertice do grafo
# utiliza do algoritmo de dijkstra
def calculate_betweenness(graph):
    betweenness = nx.betweenness_centrality(graph, weight='weight')
    return betweenness

# Cria um grafo aleatorio, "sorteando" o número de vértices entre 25 e 75, e sorteando a densidade de arestas entre 0.2 e 0.8. 
def create_random_graph():
    num_vertices = random.randint(25,75)
    density = random.uniform(0.2, 0.8)
    
    graph = nx.Graph()
    graph.add_nodes_from(range(num_vertices))

  #Para cada par de vértices no grafo sorteia um numero de arestas, um peso para cada aresta(de 1 a 10), e adiciona essa aresta a esse par.
    for i in range(num_vertices):
        for j in range(i+1, num_vertices):
            if random.random() < density:
                weight = random.randint(1, 10)
                graph.add_edge(i, j, weight=weight)

  #Tratamento de erro para caso o grafo criado esteja desconexo, cria arestas entre o novo vertice e um vertice aleatorio, sorteando o peso da aresta entre 1 e 10.
    if not nx.is_connected(graph):
        components = list(nx.connected_components(graph))
        random_vertex = random.choice(list(components[0]))
        for component in components[1:]:
            new_vertex = random.choice(list(component))
            weight = random.randint(1, 10)
            graph.add_edge(random_vertex, new_vertex, weight=weight)
    
    return graph

# Função para colorir os vértices na representação dependendo do indice de centralidade.
# No caso vertices com centralidade maior se aproximam mais do roxo e os com centralidade menor, do azul claro.
def color_nodes_by_betweenness(graph, betweenness):
    max_betweenness = max(betweenness.values())
    node_colors = [betweenness[node] / max_betweenness for node in graph.nodes()]
    return node_colors

# Cria 5 grafos baseados em listas de adjacência e associa eles a diferentes vetores.
graphs = []
for i in range(5):
    graph = create_random_graph()
    graphs.append(graph)
    print("Graph created")

# Calcula acentralidade para cada vertice do grafo.
for i, graph in enumerate(graphs):
    betweenness = calculate_betweenness(graph)
    print(f"Betweenness for Graph {i+1}:")
    for node, value in betweenness.items():
        print(f"Node {node}: {value}")
    print()
    
    # Colore vertices baseados nos indices.
    node_colors = color_nodes_by_betweenness(graph, betweenness)
    
    # Cria uma repgesentação gráfica dos grafos em questão.
    plt.figure(i+1)
    nx.draw(graph, with_labels=True, font_weight='bold', node_color=node_colors, cmap='cool')
    plt.title(f"Grafo {i+1}")

# Mostra os grafos
# Salva as imagens dos grafos
for i in range(5):
    plt.figure(i+1)
    plt.savefig(f"graph_{i+1}.png")