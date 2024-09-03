import matplotlib.pyplot as plt
import csv

def read_temperature_profile(filename):
    temperatures = []
    with open(filename, 'r') as csvfile:
        reader = csv.reader(csvfile)
        for row in reader:
            temperatures.extend([float(temp) for temp in row])
    return temperatures

def plot_temperature(temperatures):
    plt.plot(temperatures, label='Temperature')
    plt.xlabel('Time Steps')
    plt.ylabel('Temperature')
    plt.title('Temperature as a Function of Time')
    plt.legend()
    plt.show()

if __name__ == "__main__":
    filename = input("Enter the filename of the temperature data: ")
    temperatures = read_temperature_profile(filename)
    plot_temperature(temperatures)