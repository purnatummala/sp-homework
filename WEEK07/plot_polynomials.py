import numpy as np
import matplotlib.pyplot as plt

def plot_polynomial_derivatives(filename, output_pdf, title_suffix):
    # Read data from file
    data = np.loadtxt(filename, skiprows=1)
    
    # Create the plot with a larger figure size
    plt.figure(figsize=(15, 10))
    
    # Labels for derivatives
    labels = ['P(x)', "P'(x)", "P''(x)", "P'''(x)", "P''''(x)", "P'''''(x)"]
    colors = ['blue', 'red', 'green', 'purple', 'orange', 'brown']
    
    # Plot each derivative with distinct colors and styles
    x = data[:, 0]
    for i, (label, color) in enumerate(zip(labels, colors)):
        plt.plot(x, data[:, i+1], label=label, color=color, linewidth=2)
    
    # Customize the plot
    plt.grid(True, linestyle='--', alpha=0.7)
    plt.xlabel('x', fontsize=12)
    plt.ylabel('y', fontsize=12)
    plt.title(f'Polynomial and its Derivatives {title_suffix}', fontsize=14)
    plt.legend(fontsize=10)
    
    # Add vertical lines at zeros
    if "1.txt" in filename:
        zeros = [-0.5, 0, 0.5]
    else:
        zeros = [-1, -0.5, 0, 0.5, 1]
    
    for zero in zeros:
        plt.axvline(x=zero, color='gray', linestyle=':', alpha=0.5)
    
    # Add zero line
    plt.axhline(y=0, color='black', linestyle='-', alpha=0.3)
    
    # Add annotation about zeros
    zeros_text = f"Zeros at x = {', '.join(map(str, zeros))}"
    plt.annotate(zeros_text, xy=(0.02, 0.98), xycoords='axes fraction',
                fontsize=10, ha='left', va='top',
                bbox=dict(boxstyle='round', facecolor='white', alpha=0.8))
    
    # Adjust layout to prevent label cutoff
    plt.tight_layout()
    
    # Save the plot with high DPI
    plt.savefig(output_pdf, dpi=300, bbox_inches='tight')
    plt.close()

# Generate plots for both sets of zeros
plot_polynomial_derivatives('polynomial_evaluation1.txt', 'polynomial_plot1.pdf', 
                          '(3rd degree polynomial)')
plot_polynomial_derivatives('polynomial_evaluation2.txt', 'polynomial_plot2.pdf', 
                          '(5th degree polynomial)')