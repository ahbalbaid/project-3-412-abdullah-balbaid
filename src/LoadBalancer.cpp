#include "LoadBalancer.h"

LoadBalancer::LoadBalancer() : system_time_(0) {}

int LoadBalancer::GetSystemTime() const
{
    return system_time_;
}

void LoadBalancer::IncrementTime()
{
    system_time_++;
}

void LoadBalancer::AddRequest(const Request &request)
{
    request_queue_.push(request);
}

Request LoadBalancer::GetRequest()
{
    return request_queue_.pop();
}

int LoadBalancer::GetQueueSize() const
{
    return request_queue_.size();
}
