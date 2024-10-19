/**
 * @file RequestQueue.h
 * @brief Defines the RequestQueue class that manages a queue of requests.
 *
 * This class handles the management of a queue of requests. It provides functions
 * to add requests, retrieve and remove requests, check if the queue is empty, and
 * get the size of the queue.
 */

#ifndef REQUEST_QUEUE_H
#define REQUEST_QUEUE_H

#include "Request.h"
#include <queue>

/**
 * @class RequestQueue
 * @brief Handles a queue of requests.
 *
 * Provides an interface to manage a queue of requests, including adding new requests,
 * and removing them, checking if the queue is empty, and getting its size.
 */
class RequestQueue
{
private:
    std::queue<Request> request_queue_; ///< Holds the internal queue of requests.

public:
    /**
     * @brief Checks if the request queue is empty.
     * @return True if empty, false otherwise.
     */
    bool IsEmpty() const;

    /**
     * @brief Retrieves and removes the front request in the queue.
     * @return The front request.
     */
    Request pop();

    /**
     * @brief Adds a request to the queue.
     * @param request The request to add to the queue.
     */
    void push(const Request &request);

    /**
     * @brief Returns the size of the request queue.
     * @return The number of requests in the queue.
     */
    int size() const;
};

#endif
