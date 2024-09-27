import matplotlib.pyplot as plt
import pandas as pd

# Read the iteration data from CSV files
newton_data = pd.read_csv('newton_iterations.csv', header=None, names=['Iteration', 'Root'])
secant_data = pd.read_csv('secant_iterations.csv', header=None, names=['Iteration', 'Root'])

# Plot the data
plt.figure(figsize=(10, 6))
plt.plot(newton_data['Iteration'], newton_data['Root'], label='Newton-Raphson', marker='o')
plt.plot(secant_data['Iteration'], secant_data['Root'], label='Secant', marker='x')

# Add labels and title
plt.xlabel('Iteration')
plt.ylabel('Computed Root')
plt.title('Computed Root vs. Number of Iterations')
plt.legend()
plt.grid(True)

# Save the plot as a PNG file
plt.savefig('root_vs_iterations.png')

# Show the plot
plt.show()