#pragma once

#include <iostream>
#include <cstring>
#include <string>
using std::string;

#include <socket/client_socket.h>
using namespace yazi::socket;

#include <serialize/data_stream.h>
using namespace yazi::serialize;

namespace yazi
{
    namespace rpc
    {
        struct MsgHead {
            uint16_t cmd;
            uint16_t len;
        };

        const uint32_t send_buff_size = 1024;
        const uint32_t recv_buff_size = 1024;

        class Client : public ClientSocket
        {
        public:
            Client() = delete;
            Client(const string & ip, int port);
            ~Client() = default;

            template <typename R, typename ...Args>
            R call(const string & name, const Args&... args);
        };

        template <typename R, typename ...Args>
        R Client::call(const string & name, const Args&... args)
        {
            DataStream in;
            in << name;
            in.write_args(args...);

            MsgHead head;
            head.cmd = 0;
            head.len = in.size();

            char send_buff[send_buff_size] = {0};
            std::memcpy(send_buff, (char *)&head, sizeof(MsgHead));
            std::memcpy(send_buff + sizeof(MsgHead), in.data(), in.size());

            int len = sizeof(MsgHead) + in.size();
            send(send_buff, len);

            char recv_buff[recv_buff_size] = {0};
            int recv_size = recv(recv_buff, recv_buff_size);

            DataStream out;
            out.write(recv_buff, recv_size);

            R v;
            out >> v;
            return v;
        }
    }
}
