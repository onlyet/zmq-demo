// 
// 以下程序演示了如何在请求-应答模式中使用套接字标识。
// 需要注意的是s_开头的函数是由zhelpers.h提供的。
// 我们没有必要重复编写那些代码。
//
#include "zhelpers.h"

int main(void)
{
    void *context = zmq_init(1);

    void *sink = zmq_socket(context, ZMQ_ROUTER);
    zmq_bind(sink, "inproc://example");

    // 第一个套接字由0MQ自动设置标识
    void *anonymous = zmq_socket(context, ZMQ_REQ);
    zmq_connect(anonymous, "inproc://example");
    s_send(anonymous, "ROUTER uses a generated UUID");
    s_dump(sink);

    // 第二个由自己设置
    void *identified = zmq_socket(context, ZMQ_REQ);
    zmq_setsockopt(identified, ZMQ_IDENTITY, "Hello", 5);
    zmq_connect(identified, "inproc://example");
    s_send(identified, "ROUTER socket uses REQ's socket identity");
    s_dump(sink);

    zmq_close(sink);
    zmq_close(anonymous);
    zmq_close(identified);
    zmq_term(context);
    system("pause");
    return 0;
}