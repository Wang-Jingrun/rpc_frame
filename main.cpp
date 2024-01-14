#include <iostream>
#include <serialize/data_stream.h>
using namespace yazi::serialize;

#include <rpc/function.h>
using namespace yazi::rpc;

string bar(int x)
{
	return "bar: " + std::to_string(x);
}

int main()
{
	// 服务启动时候先绑定函数
	Function server;
	server.bind("bar", bar);

	// 客户端需要将函数名称和参数进行序列化
	DataStream args;
	args << "bar" << 1;    // function="bar", x=1

	// 客户端向网络端发送发送，略

	// 服务端反序列化
	string func;
	args >> func;    // function="foo"

	// 服务端调用函数
	DataStream ret;
	server.call(func, args, ret);

	// 处理返回值
	string output;
	ret >> output;
	std::cout << output << std::endl;
	return 0;
}
