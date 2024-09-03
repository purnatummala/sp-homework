import matplotlib.pyplot as plt
import os

def read_temperature_profile(filename):
    temperatures = []
    with open(filename, 'r') as file:
        for line in file:
            try:
                temperatures.append(float(line.strip()))
            except ValueError as e:
                print(f"Error converting line to float: {line.strip()} - {e}")
                continue
    time_steps = list(range(len(temperatures)))
    return time_steps, temperatures

def plot_temperature(time_steps, temperatures, title, save_path):
    plt.plot(time_steps, temperatures, label='Temperature')
    plt.xlabel('Time Steps')
    plt.ylabel('Temperature')
    plt.title(title)
    plt.legend()
    plt.savefig(save_path)
    plt.show()

if __name__ == "__main__":
    filename = input("Enter the filename of the normalized temperature data: ")
    time_steps, temperatures = read_temperature_profile(filename)
    
    # Define the path to save the image
    save_path = os.path.join('images', 'normalized_temperature.jpg')
    
    # Plot and save the normalized data
    plot_temperature(time_steps, temperatures, 'Normalized Temperature as a Function of Time', save_path)