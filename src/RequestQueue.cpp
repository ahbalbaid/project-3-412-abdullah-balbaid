#include "RequestQueue.h"

bool RequestQueue::IsEmpty() const
{
    return request_queue_.empty();
}

Request RequestQueue::pop()
{
    if (!IsEmpty())
    {
        Request front_request = request_queue_.front();
        request_queue_.pop();
        return front_request;
    }
    return {};
}

void RequestQueue::push(const Request &request)
{
    request_queue_.push(request);
}

int RequestQueue::size() const
{
    return request_queue_.size();
}
