
import numpy as np
import matplotlib.pyplot as plt

# Load data from files
edge_lengths = np.loadtxt('edge_lengths.txt')
vertex_areas = np.loadtxt('vertex_areas.txt')

# Plot histogram of edge lengths
plt.figure()
plt.hist(edge_lengths, bins=50, alpha=0.75, edgecolor='black')
plt.title('Histogram of Edge Lengths')
plt.xlabel('Edge Length')
plt.ylabel('Frequency')
plt.grid(True)
plt.savefig('images/edge_lengths_histogram.png')
plt.close()

# Plot histogram of vertex areas
plt.figure()
plt.hist(vertex_areas, bins=50, alpha=0.75, edgecolor='black')
plt.title('Histogram of Vertex Areas')
plt.xlabel('Vertex Area')
plt.ylabel('Frequency')
plt.grid(True)
plt.savefig('images/vertex_areas_histogram.png')
plt.close()