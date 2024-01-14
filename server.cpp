#include <iostream>
#include <algorithm>
#include <rpc/server.h>
using namespace yazi::rpc;

string hello(const string & name)
{
    return "hello, " + name;
}

int sum(int a, int b)
{
    return a + b;
}

class Request : public Serializable
{
public:
    Request() {}
    Request(const string & name) : m_name(name) {}
    ~Request() {}

    const string & name() const
    {
        return m_name;
    }

    SERIALIZE(m_name)

private:
    string m_name;
};

class Response : public Serializable
{
public:
    Response() {}
    Response(const string & name) : m_name(name) {}
    ~Response() {}

    const string & name() const
    {
        return m_name;
    }

    SERIALIZE(m_name)

private:
    string m_name;
};

Response upper(const Request & req)
{
    string name = req.name();
    transform(name.begin(), name.end(), name.begin(), ::toupper);
    return Response(name);
}

int main()
{
    auto server = Singleton<Server>::instance();
    server->bind("hello", hello);
    server->bind("sum", sum);
    server->bind("upper", upper);
    server->start();

    return 0;
}
