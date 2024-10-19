"""
File path: ./scripts/plot_data.py
This script to plot the simulation statistics from a CSV file.
"""

import pandas as pd
import matplotlib.pyplot as plt

def plot_simulation_data(sim_id):
    """
    Plot the simulation statistics for a given simulation ID.
    
    Param sim_id The unique ID of the simulation whose data is to be plotted.
    """
    input_file = f"../data/simulation_stats_{sim_id}.csv"
    
    try:
        data = pd.read_csv(input_file)
    except FileNotFoundError:
        print(f"Error: The file '{input_file}' was not found.")
        return

    min_servers = data['ServersActive'].min()
    lower_bound = 15 * min_servers
    upper_bound = 30 * min_servers

    fig, ax1 = plt.subplots(figsize=(10, 6))

    ax1.set_xlabel('Cycle')
    ax1.set_ylabel('Queue Size', color='blue')
    queue_line, = ax1.plot(data['Cycle'], data['QueueSize'], label='Queue Size', color='blue')
    ax1.tick_params(axis='y', labelcolor='blue')

    stable_region = (data['QueueSize'] >= lower_bound) & (data['QueueSize'] <= upper_bound)
    ax1.fill_between(data['Cycle'], lower_bound, upper_bound, where=stable_region, color='orange', alpha=0.3, label='Stable Queue Region')

    ax1.text(data['Cycle'].mean(), (lower_bound + upper_bound) / 2, 'Stable Queue Region',
             color='orange', fontsize=12, ha='center', va='center', backgroundcolor='white')

    ax2 = ax1.twinx()
    ax2.set_ylabel('Servers Active', color='green')
    server_line, = ax2.plot(data['Cycle'], data['ServersActive'], label='Servers Active', color='green')
    ax2.tick_params(axis='y', labelcolor='green')

    plt.title('Simulation Stats: Queue Size and Servers Active Over Time')

    lines = [queue_line, server_line]
    labels = [line.get_label() for line in lines]
    ax1.legend(lines, labels, loc='upper left')

    output_file = f"../plots/simulation_plot_{sim_id}.png"
    plt.savefig(output_file)

    fig.tight_layout()
    plt.grid(True)
    plt.show()

if __name__ == "__main__":
    sim_id = input("Enter the simulation ID: ")
    plot_simulation_data(sim_id)
