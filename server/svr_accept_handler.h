/// @file       svr_accept_handler.h
/// @date       2013/12/09 9:37
///
/// @author
///
/// @brief      ��������
///

#ifndef SVR_ACCEPT_HANDLER_H_
#define SVR_ACCEPT_HANDLER_H_

#include <map>
#include "comm_event_handler.h"
#include "comm_socket.h"

class SvrAcceptHandler : public CommEventHandler
{

public:
    SvrAcceptHandler();
    ~SvrAcceptHandler();

    int start_service(const char *ip, unsigned short port);

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
    CommSocket socket_;
};

#endif // SVR_ACCEPT_HANDLER_H_
