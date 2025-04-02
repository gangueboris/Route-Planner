# Compilation et exécution
`make` `./main`

# Ma logique de raisonnement
- Ma comprehension du fonctionnement des graphes
- Explication de mon approche
- Incertitude sur le choix des poids

 De ce que j'ai compris du fonctionnement de l'algorithme de recherche du chemin le plus court, elle prend en paramêtre une adjacencyList (manière de représenter les relations entre les waypoints) et les waypoints de départ et d'arrivé. Mon adjacencyList représente le graph de waypoints sous forme de 'directed graph', en prenant pour 'poids' la distance minimal entre deux waypoints. Mais le problème avec cette approche, c'est que lorsque l'algorithme oppère sur l'adjacencyList, elle me return [depart, arrivee] comme chemin le plus court (A noter que ceci est le comportement d'un 'indirected graph') et lorsque le chemin d'existe pas, elle ne retourne rien. Je me demande, d'ailleurs si ce cas existe dans notre projet ? Le cas où l'utilisateur entre une ville de départ et d'arrivée qui sont dans la base de données mais qu'il n'existe pas de chemins.

Je me dit que mon problème doit probablement venir de la définition de mes 'poids'. Si c'est le cas, je n'ai pas d'idée de comment le faire.


En resumé la 'methode' où il y'a un soucis est: createWeightedAdjacencyList() : Comment choisir les poids et créé mon adjacencyList.

Le fichier 'closestMapOutput.txt' contient une représentation visuelle de mon adjacency list avec 'methods' de tests différents.


# Test éffectué sur cette partie de la liste d'adjacence:
```
Brest : [(Guipavas Aéroport, 9429.68); ]

Marans : [(La Rochelle, 24351.6); ]
```
*Test1*
graph.getShortestPath("Brest", "Guipavas Aéroport");
Output : 
9429
Brest
Guipavas Aéroport

"Test2"
graph.getShortestPath("Brest", "Marans");
output: -2147483648


## Code Python pour générer la ralation visuelle du graph
```py
import networkx as nx
import matplotlib.pyplot as plt

# Read edges from a text file
filename = "closestMapOutput.txt"

G = nx.Graph()
edges = []
with open(filename, "r") as file:
    for line in file:
        node1, node2 = map(str.strip, line.split(","))
        edges.append((node1, node2))

# Define edges based on input

# Create a graph
G = nx.Graph()
G.add_edges_from(edges)

# Draw the graph
plt.figure(figsize=(12, 9))
nx.draw(G, with_labels=True, node_color="lightblue", edge_color="black", node_size=80, font_size=0)
plt.show()
```