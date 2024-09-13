import matplotlib.pyplot as plt

def plot_2d_trajectory(file_path):
    times = []
    x_positions = []
    y_positions = []

    with open(file_path, 'r') as file:
        for line in file:
            t, x, y = map(float, line.split())
            times.append(t)
            x_positions.append(x)
            y_positions.append(y)

    plt.figure()
    plt.plot(x_positions, y_positions, label='2D Trajectory')
    plt.xlabel('X Position')
    plt.ylabel('Y Position')
    plt.title('2D Particle Trajectory')
    plt.legend()
    plt.grid(True)
    plt.show()

def plot_3d_trajectory(file_path):
    from mpl_toolkits.mplot3d import Axes3D

    times = []
    x_positions = []
    y_positions = []
    z_positions = []

    with open(file_path, 'r') as file:
        for line in file:
            t, x, y, z = map(float, line.split())
            times.append(t)
            x_positions.append(x)
            y_positions.append(y)
            z_positions.append(z)

    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    ax.plot(x_positions, y_positions, z_positions, label='3D Trajectory')
    ax.set_xlabel('X Position')
    ax.set_ylabel('Y Position')
    ax.set_zlabel('Z Position')
    ax.set_title('3D Particle Trajectory')
    ax.legend()
    plt.show()

if __name__ == "__main__":
    plot_2d_trajectory('traject_2d.txt')
    plot_3d_trajectory('traject_3d.txt')