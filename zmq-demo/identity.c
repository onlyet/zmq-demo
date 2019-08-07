// 
// ���³�����ʾ�����������-Ӧ��ģʽ��ʹ���׽��ֱ�ʶ��
// ��Ҫע�����s_��ͷ�ĺ�������zhelpers.h�ṩ�ġ�
// ����û�б�Ҫ�ظ���д��Щ���롣
//
#include "zhelpers.h"

int main(void)
{
    void *context = zmq_init(1);

    void *sink = zmq_socket(context, ZMQ_ROUTER);
    zmq_bind(sink, "inproc://example");

    // ��һ���׽�����0MQ�Զ����ñ�ʶ
    void *anonymous = zmq_socket(context, ZMQ_REQ);
    zmq_connect(anonymous, "inproc://example");
    s_send(anonymous, "ROUTER uses a generated UUID");
    s_dump(sink);

    // �ڶ������Լ�����
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