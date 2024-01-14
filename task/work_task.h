#pragma once

#include <socket/socket.h>
using namespace yazi::socket;

#include <thread/task.h>
using namespace yazi::thread;

namespace yazi
{
    namespace task
    {
        struct MsgHead {
            uint16_t cmd;
            uint16_t len;
        };

        const uint32_t recv_buff_size = 1024;

        class WorkTask : public Task
        {
        public:
            WorkTask() = delete;
            WorkTask(int sockfd);
            ~WorkTask();

            virtual void run();
            virtual void destroy();

        private:
            int m_sockfd = 0;
            bool m_closed = false;
        };
    }
}
