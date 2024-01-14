#include <rpc/server.h>
using namespace yazi::rpc;

#include <frame/server.h>

void Server::start()
{
    try
    {
        Singleton<yazi::frame::Server>::instance()->start();
    }
    catch (std::exception & e)
    {
        std::cout << e.what() << std::endl;
    }
}
