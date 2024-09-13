import matplotlib.pyplot as plt

# Function to read data from a file
def read_data(filename):
    time = []
    x = []
    y = []
    z = []
    with open(filename, 'r') as file:
        for line in file:
            values = line.split()
            time.append(float(values[0]))
            x.append(float(values[1]))
            y.append(float(values[2]))
            if len(values) > 3:
                z.append(float(values[3]))
    return time, x, y, z

# Read 2D trajectory data
time_2d, x_2d, y_2d, _ = read_data('traject_2d.txt')

# Read 3D trajectory data
time_3d, x_3d, y_3d, z_3d = read_data('traject_3d.txt')

# Plot 2D trajectory
plt.figure()
plt.plot(x_2d, y_2d, marker='o')
plt.title('2D Trajectory')
plt.xlabel('X Position')
plt.ylabel('Y Position')
plt.grid(True)
plt.savefig('trajectory_2d.png')
plt.show()

# Plot 3D trajectory
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot(x_3d, y_3d, z_3d, marker='o')
ax.set_title('3D Trajectory')
ax.set_xlabel('X Position')
ax.set_ylabel('Y Position')
ax.set_zlabel('Z Position')
plt.grid(True)
plt.savefig('trajectory_3d.png')
plt.show()