import networkx as nx
import matplotlib.pyplot as plt

def read_graph_from_file(filename):
    G = nx.Graph()  # Create an undirected graph
    with open(filename, 'r') as f:
        for line in f:
            # Strip any leading/trailing whitespace and split by commas
            nodes = line.strip().split(', ')
            if len(nodes) == 2:
                # Add an edge between two nodes
                G.add_edge(nodes[0], nodes[1])
    return G

def visualize_graph(G):
    # Draw the graph with a spring layout (you can use other layouts like circular, shell, etc.)
    plt.figure(figsize=(12, 12))
    nx.draw(G, with_labels=True, node_size=500, node_color='skyblue', font_size=4, font_weight='bold', edge_color='gray')
    plt.title("Graph Visualization")
    plt.show()

# Replace 'graph.txt' with the path to your graph file
filename = 'edgeList.txt'

# Read the graph from the file and visualize it
G = read_graph_from_file(filename)
visualize_graph(G)
