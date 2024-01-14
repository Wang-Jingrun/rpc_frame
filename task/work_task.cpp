#include <task/work_task.h>
using namespace yazi::task;

#include <socket/socket_handler.h>
using namespace yazi::socket;

#include <rpc/server.h>
using namespace yazi::rpc;

WorkTask::WorkTask(int sockfd) : Task(), m_sockfd(sockfd)
{
}

WorkTask::~WorkTask()
{
}

void WorkTask::run()
{
    log_debug("work task run");

    struct MsgHead msg_head;
    std::memset(&msg_head, 0, sizeof(msg_head));

    Socket socket(m_sockfd);
    int len = socket.recv((char *)(&msg_head), sizeof(msg_head));
    if (len < 0)
    {
        if (errno == EAGAIN || errno == EWOULDBLOCK)
        {
            log_debug("socket recv would block: conn=%d errno=%d errmsg=%s", m_sockfd, errno, strerror(errno));
            return;
        }
        else if (errno == EINTR)
        {
            log_debug("socket recv interrupted: conn=%d errno=%d errmsg=%s", m_sockfd, errno, strerror(errno));
            return;
        }
        log_error("socket connection abort: conn=%d errno=%d errmsg=%s", m_sockfd, errno, strerror(errno));
        m_closed = true;
        return;
    }
    else if (len == 0)
    {
        log_debug("socket closed by peer: conn=%d", m_sockfd);
        m_closed = true;
        return;
    }
    if (len != sizeof(msg_head))
    {
        log_error("msg head length error: %d", len);
        m_closed = true;
        return;
    }
    log_info("msg head: cmd=%d len=%d", msg_head.cmd, msg_head.len);
    if (msg_head.len >= uint16_t(recv_buff_size))
    {
        log_error("msg body too large: len=%d", msg_head.len);
        m_closed = true;
        return;
    }

    // 开始接收数据
    char buf[recv_buff_size] = {0};
    len = socket.recv(buf, msg_head.len);
    if (len != (int)(msg_head.len))
    {
        log_error("msg body length error: len=%d", len);
        m_closed = true;
        return;
    }

    log_info("msg body: len=%d, data=%s", len, buf);

    DataStream in;
    in.write(buf, len);

    string func;
    in >> func;

    DataStream out;
    auto server = Singleton<Server>::instance();
    server->call(func, in, out);
    socket.send(out.data(), out.size());
}

void WorkTask::destroy()
{
    log_debug("work task destroy");
    if (m_closed)
    {
        ::close(m_sockfd);
    }
    else
    {
        Singleton<SocketHandler>::instance()->attach(m_sockfd);
    }
    delete this;
}
