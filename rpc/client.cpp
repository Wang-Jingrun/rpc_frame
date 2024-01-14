#include <rpc/client.h>
using namespace yazi::rpc;

#include <utility/system.h>
using namespace yazi::utility;

Client::Client(const string & ip, int port) : ClientSocket(ip, port)
{
    auto sys = Singleton<System>::instance();
    sys->init();

    string root_path = sys->get_root_path();

    auto logger = Singleton<Logger>::instance();
    logger->open(root_path + "/log/client.log");
}
