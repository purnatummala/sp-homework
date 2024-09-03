import matplotlib.pyplot as plt

def read_data(file_path):
    x = []
    T = []
    with open(file_path, 'r') as file:
        for line in file:
            data = line.split()
            x.append(float(data[0]))
            T.append(float(data[1]))
    return x, T

def plot_temperature_profile(x, T):
    plt.figure(figsize=(10, 6))
    plt.plot(x, T, marker='o', linestyle='-', color='b')
    plt.title('1D Heat Distribution')
    plt.xlabel('x')
    plt.ylabel('Temperature (T)')
    plt.grid(True)
    plt.show()

if __name__ == "__main__":
    file_path = 'output.txt'  # Replace with the actual output file path
    x, T = read_data(file_path)
    plot_temperature_profile(x, T)