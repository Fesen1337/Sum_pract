import pandas as pd
import networkx as nx
import matplotlib.pyplot as plt

G = nx.Graph()
label = 'label'

with open("output.txt", "r") as f:
    for line in f:
        q = line.split()
        if q[2] == '1':
            col = 'black'
        else:
            col = 'red'
        G.add_edge(q[0], q[1], color=col)
        label = q[3]



plt.gcf().canvas.set_window_title(label)
edges = G.edges()
colors = [G[u][v]['color'] for u,v in edges]

nx.draw(G, edges=edges, edge_color=colors)

plt.show() 
