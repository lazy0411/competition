/// @file       svr_tcp_client_handler.h
/// @date       2013/12/05 9:56
///
/// @author
///
/// @brief      tcp�ͻ����߼�����
///

#ifndef SVR_TCP_CLIENT_HANDLER_H_
#define SVR_TCP_CLIENT_HANDLER_H_

#include "comm_event_handler.h"
#include "comm_socket.h"
#include "svr_proto.h"

class SvrTcpClientHandler : public CommEventHandler
{
public:
    SvrTcpClientHandler();
    SvrTcpClientHandler(int fd);

    int init(int fd);

    /*!
    @brief      ȡ�ض�Ӧ��ZEN_SOCKET ���
    @return     ZEN_SOCKET CommEventHandler ��Ӧ��ZEN_SOCKET ���
    */
    virtual int get_handle(void) const;

    /*!
    @brief      ��ȡ�¼��������ú��������ڶ�ȡ���ݣ�accept�ɹ�����connectʧ�ܣ�����
    @return     int ����0��ʾ�������������return -1�󣬷�Ӧ��������handle_close�������������
    */
    virtual int handle_input();

    /*!
    @brief      д���¼��������ú���������д���ݣ�connect�ɹ���
    @return     int int ����0��ʾ�������������return -1�󣬷�Ӧ��������handle_close�������������
    */
    virtual int handle_output();

    /*!
    @brief      �����쳣��return -1��ʾ����handle_close
    @return     int
    */
    virtual int handle_exception();

    /*!
    @brief      ����رմ����������ຯ��������remove
    @return     int
    */
    virtual int handle_close();

private:

    // �������а�
    int handle_recv_pkg(const svr_proto::SvrPkg &pkg);
    int handle_player_login(const svr_proto::PlayerLogin &pkg_body);
    int handle_player_get_axis(const svr_proto::PlayerGetAxis &pkg_body);

    int send_pkg(const svr_proto::SvrPkg &send_pkg);
private:
    // �ͻ������Ӷ���
    CommSocket socket_;
    // ������
    static const unsigned int MAX_PKG_LEN = 64*1024;
    char recv_buffer_[MAX_PKG_LEN];
    char send_buffer_[MAX_PKG_LEN];

    svr_proto::SvrPkg recv_pkg_;
    svr_proto::SvrPkg send_pkg_;

};

#endif // SVR_TCP_CLIENT_HANDLER_H_
