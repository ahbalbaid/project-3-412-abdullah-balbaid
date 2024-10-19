# Load Balancer Simulation

## Overview

This project simulates a load balancer that distributes requests to web servers. The system handles requests by assigning them to available servers, each of which processes the request and tracks its status. The simulation allows for the dynamic addition and removal of servers based on the request load.

The main components of the simulation include:

- **Request**: Represents a request with metadata such as source and destination IPs, processing time, and job type.
- **RequestQueue**: Manages a queue of requests to be processed by the load balancer.
- **WebServer**: Represents a server that processes assigned requests.
- **LoadBalancer**: Manages the distribution of requests to web servers.

## Project Structure

```

/loadbalancer_project
├── /bin            # Compiled binary files
├── /data           # Generated CSV data files
├── /docs           # Doxygen documentation
├── /include        # Header files
├── /logs           # Log files from the simulation
├── /plots          # Generated plots from Python scripts
├── /scripts        # Python scripts for data visualization
│   └── plot_data.py # Script for generating plots from CSV files
├── /src            # Source files
│   ├── main.cpp    # Main simulation file
│   ├── LoadBalancer.cpp
│   ├── Request.cpp
│   └── WebServer.cpp
├── Doxyfile        # Doxygen configuration file
├── Makefile        # Makefile for building and generating documentation
└── README.md       # Project overview and instructions
```

## Installation

1. **Clone the repository**:
   ```bash
   git clone https://github.com/ahbalbaid/project-3-420-abdullah-balbaid.git
   ```
````

2. **Install dependencies**:
   - You need a C++ compiler (e.g., `g++`) and Doxygen to generate the documentation.
   - For Python plotting, install the required libraries:
     ```bash
     pip install pandas matplotlib
     ```

## Building and Running

1. **Build the project**:

   ```bash
   make
   ```

2. **Run the simulation**:

   - **Interactive run** (input servers and cycles manually):
     ```bash
     make run
     ```
   - **Default run** (10 servers, 10000 cycles):
     ```bash
     make start
     ```

3. **Generate documentation**:
   ```bash
   make docs
   ```

## Python Plotting Script

The Python script `plot_data.py` is used to plot the simulation statistics.

- **Run the script**:

  ```bash
  python3 scripts/plot_data.py
  ```

- The script will prompt for a simulation ID and generate a plot of the simulation's queue size and active servers over time.

## Documentation

The documentation for the project is generated using Doxygen. After generating the documentation, you can open it by navigating to the `docs/html/index.html` file in your web browser.

```bash
make docs
```

For detailed documentation, see the [Project Documentation](./docs/html/index.html).
````
