/**
 * @file LoadBalancer.h
 * @brief Defines the LoadBalancer class.
 *
 * Handles distributing requests across multiple web servers. It manages system time,
 * tracks a request queue, and assigns tasks to the available servers.
 */
#ifndef LOAD_BALANCER_H
#define LOAD_BALANCER_H

#include "Request.h"
#include "RequestQueue.h"

/**
 * @class LoadBalancer
 * @brief Manages load balancing for web server requests.
 *
 * This class handles incoming requests, assigning them to web servers,
 * while also managing system time and the request queue.
 */
class LoadBalancer
{
private:
    int system_time_;            ///< Tracks the current system time.
    RequestQueue request_queue_; ///< Holds the queue of pending requests.

public:
    /**
     * @brief Constructs a LoadBalancer.
     */
    LoadBalancer();
    /**
     * @brief Getter for private member current system time.
     * @return The current system time.
     */
    int GetSystemTime() const;
    /**
     * @brief Increments the system time by 1.
     */
    void IncrementTime();
    /**
     * @brief Adds a request to the request queue.
     * @param request The request to be added.
     */
    void AddRequest(const Request &request);

    /**
     * @brief Getter and remover of the next request from the queue.
     * @return The next request.
     */
    Request GetRequest();
    /**
     * @brief Getter for the current size of the request queue.
     * @return The size of the queue.
     */
    int GetQueueSize() const;
};

#endif
