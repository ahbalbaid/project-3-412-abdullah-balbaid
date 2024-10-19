/**
 * @file WebServer.h
 * @brief Defines the WebServer class responsible for processing requests.
 *
 * The WebServer class is responsible for processing requests assigned to it.
 * It keeps track of the current request, start time of the request, and
 * the server's ID.
 */

#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "Request.h"

/**
 * @class WebServer
 * @brief Represents a web server that processes requests.
 *
 * The WebServer class is responsible for handling requests assigned to it. It
 * tracks the request start time and determines if the request is complete. The class
 * also provides functions to assign requests to the server and retrieve the request details.
 */
class WebServer
{
private:
    Request r_;              ///< The current request being processed by the server.
    int request_start_time_; ///< The time at which the current request started.
    int id;                  ///< Unique ID of the server.

public:
    /**
     * @brief Default constructor for WebServer.
     *
     * Constructs a WebServer with default values.
     */
    WebServer();

    /**
     * @brief Constructs a WebServer with a specific ID.
     *
     * @param id The unique ID of the server.
     */
    explicit WebServer(int id);

    /**
     * @brief Assigns a request to the server for processing.
     *
     * @param req The request to be processed.
     * @param curr_time The current system time when the request was assigned.
     */
    void AddRequest(const Request &req, int curr_time);

    /**
     * @brief Retrieves the current request being processed by the server.
     * @return The current request.
     */
    Request GetRequest() const;

    /**
     * @brief Returns the unique ID of the server.
     * @return The server's ID.
     */
    int GetId() const;

    /**
     * @brief Checks if the current request is complete based on the system time.
     *
     * The request is considered complete if the current system time exceeds
     * the start time of the request plus the time required to process it.
     *
     * @param curr_time The current system time.
     * @return True if the request is complete, false otherwise.
     */
    bool IsRequestDone(int curr_time) const;
};

#endif
