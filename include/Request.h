/**
 * @file Request.h
 * @brief Defines the Request struct.
 *
 * Represents a request with details like request ID, source and destination IPs,
 * processing time, and job type.
 */

#ifndef REQUEST_H
#define REQUEST_H

#include <string>

/**
 * @struct Request
 * @brief Represents a request for the system to process.
 *
 * Holds info about an incoming request like its unique ID, source and destination IPs,
 * processing time, and job type.
 */
struct Request
{
    size_t id;          ///< Unique ID for the request.
    std::string ip_in;  ///< Source IP of the request.
    std::string ip_out; ///< Destination IP of the request.
    int time;           ///< Processing time for the request.
    char job_type;      ///< Job type ('P' for primary, 'S' for secondary).
};

#endif
