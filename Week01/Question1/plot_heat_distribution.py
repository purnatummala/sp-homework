import matplotlib.pyplot as plt
import os

def read_data(file_path):
    x = []
    T = []
    with open(file_path, 'r') as file:
        for line in file:
            data = line.split()
            if len(data) != 2:
                print(f"Skipping malformed line: {line.strip()}")
                continue
            try:
                x.append(float(data[0]))
                T.append(float(data[1]))
            except ValueError as e:
                print(f"Error converting line to float: {line.strip()} - {e}")
                continue
    return x, T

def plot_temperature_profile(x, T, save_path):
    plt.figure(figsize=(10, 6))
    plt.plot(x, T, marker='o', linestyle='-', color='b')
    plt.title('1D Heat Distribution')
    plt.xlabel('x')
    plt.ylabel('Temperature (T)')
    plt.grid(True)
    plt.savefig(save_path)
    plt.show()

if __name__ == "__main__":
    file_path = 'final_output.txt'  # Ensure this matches the actual output file name
    x, T = read_data(file_path)
    
    # Define the path to save the image
    save_path = os.path.join('images', 'heat_distribution.png')
    
    # Plot and save the temperature profile
    plot_temperature_profile(x, T, save_path)