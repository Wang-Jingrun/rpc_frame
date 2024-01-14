#pragma once

#include <string>
using std::string;

#include <utility/singleton.h>
using namespace yazi::utility;

#include <rpc/function.h>

namespace yazi
{
    namespace rpc
    {
        class Server
        {
            SINGLETON(Server);
        public:
            void start();

            template <typename F>
            void bind(const string & name, F func)
            {
                m_func.bind(name, func);
            }

            void call(const string & name, DataStream & in, DataStream & out)
            {
                m_func.call(name, in, out);
            }

        private:
            Function m_func;
        };
    }
}
