import pandas as pd
import matplotlib.pyplot as plt

# Load the CSV data for both methods
non_adaptive_data = pd.read_csv('parallel_trapezoidal_results.csv')
adaptive_data = pd.read_csv('adaptive_trapezoidal_results.csv')

# Function to generate plots for Non-Adaptive Integration
def generate_non_adaptive_plots(data):
    if 'n' not in data.columns:
        print("Column 'n' not found in non-adaptive data.")
        return

    # Execution Time vs Number of Threads
    plt.figure(figsize=(10, 6))
    for n in data['n'].unique():
        subset = data[data['n'] == n]
        plt.plot(subset['threads'], subset['execution_time'], label=f'n={n}', marker='o')
    plt.xlabel('Number of Threads')
    plt.ylabel('Execution Time (s)')
    plt.title('Non-Adaptive: Execution Time vs Number of Threads')
    plt.legend()
    plt.grid(True)
    plt.savefig('non_adaptive_execution_time_vs_threads.png')
    plt.close()

    # Mean Function Evaluations vs Number of Threads
    plt.figure(figsize=(10, 6))
    for n in data['n'].unique():
        subset = data[data['n'] == n]
        plt.plot(subset['threads'], subset['mean_eval'], label=f'n={n}', marker='o')
    plt.xlabel('Number of Threads')
    plt.ylabel('Mean Function Evaluations')
    plt.title('Non-Adaptive: Mean Function Evaluations vs Number of Threads')
    plt.legend()
    plt.grid(True)
    plt.savefig('non_adaptive_mean_eval_vs_threads.png')
    plt.close()

    # Std Dev of Function Evaluations vs Number of Threads
    plt.figure(figsize=(10, 6))
    for n in data['n'].unique():
        subset = data[data['n'] == n]
        plt.plot(subset['threads'], subset['std_eval'], label=f'n={n}', marker='o')
    plt.xlabel('Number of Threads')
    plt.ylabel('Standard Deviation of Function Evaluations')
    if (subset['std_eval'] > 0).any():
        plt.yscale('log')
    plt.title('Non-Adaptive: Std Dev of Function Evaluations vs Number of Threads')
    plt.legend()
    plt.grid(True)
    plt.savefig('non_adaptive_std_eval_vs_threads.png')
    plt.close()

# Function to generate plots for Adaptive Integration
def generate_adaptive_plots(data):
    if 'tolerance' not in data.columns:
        print("Column 'tolerance' not found in adaptive data.")
        return

    # Execution Time vs Number of Threads
    plt.figure(figsize=(10, 6))
    for tolerance in data['tolerance'].unique():
        subset = data[data['tolerance'] == tolerance]
        plt.plot(subset['threads'], subset['execution_time'], label=f'Tolerance={tolerance}', marker='o')
    plt.xlabel('Number of Threads')
    plt.ylabel('Execution Time (s)')
    plt.title('Adaptive: Execution Time vs Number of Threads')
    plt.legend()
    plt.grid(True)
    plt.savefig('adaptive_execution_time_vs_threads.png')
    plt.close()

    # Mean Function Evaluations vs Number of Threads
    plt.figure(figsize=(10, 6))
    for tolerance in data['tolerance'].unique():
        subset = data[data['tolerance'] == tolerance]
        plt.plot(subset['threads'], subset['mean_evaluations'], label=f'Tolerance={tolerance}', marker='o')
    plt.xlabel('Number of Threads')
    plt.ylabel('Mean Function Evaluations')
    plt.title('Adaptive: Mean Function Evaluations vs Number of Threads')
    plt.legend()
    plt.grid(True)
    plt.savefig('adaptive_mean_eval_vs_threads.png')
    plt.close()

    # Std Dev of Function Evaluations vs Number of Threads
    plt.figure(figsize=(10, 6))
    for tolerance in data['tolerance'].unique():
        subset = data[data['tolerance'] == tolerance]
        plt.plot(subset['threads'], subset['stddev_evaluations'], label=f'Tolerance={tolerance}', marker='o')
    plt.xlabel('Number of Threads')
    plt.ylabel('Standard Deviation of Function Evaluations')
    if (subset['stddev_evaluations'] > 0).any():
        plt.yscale('log')
    plt.title('Adaptive: Std Dev of Function Evaluations vs Number of Threads')
    plt.legend()
    plt.grid(True)
    plt.savefig('adaptive_std_eval_vs_threads.png')
    plt.close()

    # Thread Execution Times
    plt.figure(figsize=(10, 6))
    for tolerance in data['tolerance'].unique():
        subset = data[data['tolerance'] == tolerance]
        plt.errorbar(subset['threads'], subset['mean_time'], yerr=subset['stddev_time'], label=f'Tolerance={tolerance}', marker='o')
    plt.xlabel('Number of Threads')
    plt.ylabel('Thread Execution Time (s)')
    plt.title('Adaptive: Thread Execution Time vs Number of Threads')
    plt.legend()
    plt.grid(True)
    plt.savefig('adaptive_thread_times.png')
    plt.close()

# Generate plots for Non-Adaptive Method
generate_non_adaptive_plots(non_adaptive_data)

# Generate plots for Adaptive Method
generate_adaptive_plots(adaptive_data)