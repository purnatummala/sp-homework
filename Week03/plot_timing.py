import matplotlib.pyplot as plt

# Read the timing results from the file
sizes = []
times = []
with open("timing_results.txt", "r") as infile:
    for line in infile:
        size, time = map(float, line.split())
        sizes.append(size)
        times.append(time)

# Plot the results
plt.figure()
plt.plot(sizes, times, marker='o')
plt.xlabel('Grid Size (n)')
plt.ylabel('Time (seconds)')
plt.title('Execution Time of Grid Summation')
plt.grid(True)
plt.savefig('timing_plot.png')
plt.show()