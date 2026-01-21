import random
import networkx as nx
import matplotlib.pyplot as plt

# Função que calcula a centralidade (betweenness) de cada vértice do grafo
# utilizando o algoritmo de Dijkstra
def calcular_betweenness(graph):
    betweenness = nx.betweenness_centrality(graph, weight='weight')
    return betweenness

# Cria um grafo aleatório, "sorteando" o número de vértices entre 25 e 75,
# e sorteando a densidade de arestas entre 0.35 e 1.0.
def criar_grafo_aleatorio():
    num_vertices = random.randint(25, 75)
    densidade = random.uniform(0.35, 1)
    
    grafo = nx.Graph()
    grafo.add_nodes_from(range(num_vertices))

    # Para cada par de vértices no grafo, sorteia um número de arestas,
    # um peso para cada aresta (de 1 a 10), e adiciona essa aresta a esse par.
    for i in range(num_vertices):
        for j in range(i+1, num_vertices):
            if random.random() < densidade:
                peso = random.randint(1, 10)
                grafo.add_edge(i, j, peso=peso)

    # Tratamento de erro para caso o grafo criado esteja desconexo.
    # Cria arestas entre o novo vértice e um vértice aleatório,
    # sorteando o peso da aresta entre 1 e 10.
    if not nx.is_connected(grafo):
        componentes = list(nx.connected_components(grafo))
        vertice_aleatorio = random.choice(list(componentes[0]))
        for componente in componentes[1:]:
            novo_vertice = random.choice(list(componente))
            peso = random.randint(1, 10)
            grafo.add_edge(vertice_aleatorio, novo_vertice, peso=peso)
    
    return grafo

# Função para colorir os vértices na representação, dependendo do índice de centralidade.
# No caso, vértices com centralidade maior se aproximam mais do roxo e
# os com centralidade menor se aproximam do azul claro.
def colorir_vertices_por_betweenness(graph, betweenness):
    max_betweenness = max(betweenness.values())
    cores_vertices = [betweenness[node] / max_betweenness for node in graph.nodes()]
    return cores_vertices

# Cria 5 grafos baseados em listas de adjacência e associa eles a diferentes variáveis.
grafos = []
for i in range(5):
    grafo = criar_grafo_aleatorio()
    grafos.append(grafo)
    print("Grafo criado")

# Calcula a centralidade para cada vértice do grafo.
for i, grafo in enumerate(grafos):
    betweenness = calcular_betweenness(grafo)
    print(f"Betweenness para o Grafo {i+1}:")
    for node, value in betweenness.items():
        print(f"Vértice {node}: {value}")
    print()
    
    # Colore os vértices com base nos índices de centralidade.
    cores_vertices = colorir_vertices_por_betweenness(grafo, betweenness)
    
    # Cria uma representação gráfica dos grafos.
    plt.figure(i+1)
    nx.draw(grafo, with_labels=True, font_weight='bold', node_color=cores_vertices, cmap='cool')
    plt.title(f"Grafo {i+1}")

# Mostra os grafos e salva as imagens dos grafos.
for i in range(5):
    plt.figure(i+1)
    plt.savefig(f"grafo_{i+1}.png")
