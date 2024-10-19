/**
 * @file main.cpp
 * @brief Load balancer simulation for handling web server requests.
 *
 * This simulates a load balancer distributing network requests across multiple web servers.
 * It dynamically manages the servers, adjusting their count based on the current load in the queue.
 * You'll see logs for things like assigning requests, adding servers, or removing them when necessary.
 */

#include "Request.h"
#include "WebServer.h"
#include "LoadBalancer.h"

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <functional>
#include <fstream>

using namespace std;

/**
 * @brief Number of web servers in the simulation.
 */

int kNumWebServers = 10;

/**
 * @brief Number of requests initially generated in the simulation.
 */
int kNumRequests = kNumWebServers * 100;

/**
 * @brief Total duration of the simulation, measured in cycles.
 */
int kSimDuration = 10000;

/**
 * @brief Generates a unique simulation ID using the current time.
 *
 * @return A string representing the unique simulation ID.
 */
string SimulationID()
{
    time_t now = time(0);
    stringstream ss;
    ss << now;
    hash<string> hash_function;
    size_t unique_hash = hash_function(ss.str());
    return to_string(unique_hash);
}

/**
 * @brief Outputs a message to both the terminal and the log file.
 *
 * @param logFile The file where the message will be logged.
 * @param message The message to display and log.
 */
void print(ofstream &logFile, const string &message)
{
    cout << message;
    logFile << message;
}

/**
 * @brief Creates a random request.
 *
 * Generates a `Request` object with random source and destination IPs, processing time,
 * and job type ('P' for primary, 'S' for secondary) and a unique hashed ID.
 *
 * @return A randomly generated `Request` object.
 */
Request CreateRandomRequest()
{
    stringstream ips, ipd;
    Request request;
    ips << (rand() % 256) << "." << (rand() % 256) << "." << (rand() % 256) << "." << (rand() % 256);
    ipd << (rand() % 256) << "." << (rand() % 256) << "." << (rand() % 256) << "." << (rand() % 256);
    request.ip_in = ips.str();
    request.ip_out = ipd.str();
    request.time = rand() % 100;
    request.job_type = (rand() % 2 == 0) ? 'P' : 'S';
    hash<string> hash_function;
    request.id = hash_function(request.ip_in + request.ip_out + to_string(request.time) + request.job_type);
    return request;
}

/**
 * @brief Main function to run the load balancer simulation.
 *
 * Initializes the load balancer, generates requests, manages servers, and processes them
 * throughout the simulation. Adjusts the server count based on queue load and logs key events
 * like adding/removing servers and handling requests.
 *
 * @return 0 when the simulation completes successfully.
 */
int main()
{
    cout << "Enter the number of servers: ";
    cin >> kNumWebServers;
    cout << "Enter the simulation duration (in cycles): ";
    cin >> kSimDuration;

    kNumRequests = kNumWebServers * 100;

    srand(time(0));
    LoadBalancer load_balancer;

    string unique_id = SimulationID();

    ofstream logFile("./logs/simulation_log_" + unique_id + ".txt");
    ofstream statsFile("./data/simulation_stats_" + unique_id + ".csv");

    statsFile << "Cycle,QueueSize,ServersActive\n";

    print(logFile, "[INFO] Starting simulation with " + to_string(kNumWebServers) + " servers and a queue of " + to_string(kNumRequests) + " requests.\n");

    // Generate and add the initial batch of requests
    print(logFile, "[INFO] Adding initial batch of requests. Total requests added: " + to_string(kNumRequests) + "\n");
    for (int i = 0; i < kNumRequests; i++)
    {
        Request r = CreateRandomRequest();
        load_balancer.AddRequest(r);
        if (i == 0)
            print(logFile, "[ADD-REQUESTS] IDs = " + to_string(r.id) + ", ");
        else
            print(logFile, to_string(r.id) + ", ");
    }
    print(logFile, "\n");

    // Add the initial batch of servers
    print(logFile, "[INFO] Adding initial batch of servers. Total servers added: " + to_string(kNumWebServers) + "\n");
    vector<WebServer> web_servers;
    for (int i = 0; i < kNumWebServers; i++)
    {
        WebServer web_server(i + 65);
        web_servers.push_back(web_server);
        web_servers[i].AddRequest(load_balancer.GetRequest(), load_balancer.GetSystemTime());
        if (i == 0)
            print(logFile, "[ADD-SERVERS] ID = " + to_string(web_servers[i].GetId()) + ", ");
        else
            print(logFile, to_string(web_servers[i].GetId()) + ", ");
    }
    print(logFile, "\n");

    // Simulation loop
    load_balancer.IncrementTime();
    int prev_q_size = load_balancer.GetQueueSize();
    int prev_server_count = kNumWebServers;

    while (load_balancer.GetSystemTime() < kSimDuration)
    {
        int curr_time = load_balancer.GetSystemTime();
        int curr_q_size = load_balancer.GetQueueSize();

        if (curr_q_size != prev_q_size || prev_server_count != kNumWebServers)
        {
            print(logFile, "[INFO] Cycle " + to_string(curr_time) + ": Queue size = " + to_string(curr_q_size) + ", Servers active = " + to_string(kNumWebServers) + "\n");
            prev_q_size = curr_q_size;
            prev_server_count = kNumWebServers;
        }

        // Process servers and requests
        for (int i = 0; i < kNumWebServers; i++)
        {
            if (web_servers[i].IsRequestDone(curr_time))
            {
                if (load_balancer.GetQueueSize() / 15 < kNumWebServers)
                {
                    print(logFile, "[REMOVE-SERVER] ID = " + to_string(web_servers[kNumWebServers - 1].GetId()) + "\n");
                    web_servers.pop_back();
                    kNumWebServers--;
                }
                else
                {
                    Request r = web_servers[i].GetRequest();
                    print(logFile, "[PROCESSED] Server " + to_string(web_servers[i].GetId()) + " completed request ID = " + to_string(r.id) + " from " + r.ip_in + " to " + r.ip_out + " in " + to_string(r.time) + " cycles.\n");
                    web_servers[i].AddRequest(load_balancer.GetRequest(), curr_time);
                }
            }
        }

        // Add servers dynamically based on queue size
        if (load_balancer.GetQueueSize() / 30 > kNumWebServers)
        {
            int servers_to_add = 2;
            for (int i = 0; i < servers_to_add; i++)
            {
                WebServer web_server(kNumWebServers++);
                web_servers.push_back(web_server);
                web_servers[kNumWebServers - 1].AddRequest(load_balancer.GetRequest(), load_balancer.GetSystemTime());
                print(logFile, "[ADD-SERVER] ID = " + to_string(web_servers[kNumWebServers - 1].GetId()) + "\n");
            }
        }

        // Randomly add requests during the simulation
        if (rand() % 5 == 0)
        {
            Request r = CreateRandomRequest();
            load_balancer.AddRequest(r);
            print(logFile, "[ADD-REQUEST] ID = " + to_string(r.id) + "\n");
        }

        statsFile << curr_time << "," << curr_q_size << "," << kNumWebServers << "\n";
        load_balancer.IncrementTime();
    }

    print(logFile, "[INFO] Simulation ended after " + to_string(kSimDuration) + " cycles.\n");

    statsFile.close();
    logFile.close();
    return 0;
}
