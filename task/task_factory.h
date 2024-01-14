#pragma once

#include <socket/socket.h>
using namespace yazi::socket;

#include <thread/task.h>
using namespace yazi::thread;

#include <task/work_task.h>
using namespace yazi::task;

namespace yazi
{
    namespace task
    {
        class TaskFactory
        {
        public:
            static Task * create(int sockfd)
            {
                return new WorkTask(sockfd);
            }
        };
    }
}
