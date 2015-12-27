/// @file       comm_socket.h
/// @date       2013/12/04 19:03
///
/// @author
///
/// @brief      socket������
///

#ifndef COMM_SOCKET_H_
#define COMM_SOCKET_H_

#include "comm_define.h"
//#include "svr_proto.h"

class CommSocket
{
public:
    CommSocket();
    ~CommSocket();

    typedef enum
    {
        TCP = 1,
    } SocketType;

    typedef enum
    {
        SOCKET_EVENT_READ = 1,
        SOCKET_EVENT_WRITE = 2,
        SOCKET_EVENT_ERROR = 4,
    } SocketEvent;

    typedef enum
    {
        ERR_SOCKET_FINISH = 0, // ��д�ɹ����
        ERR_SOCKET_FAIL = 1, // ��дʧ��
        ERR_SOCKET_CONTINUE, // ��Ҫ����������д
        ERR_SOCKET_PACKET_NOT_FINISH,
        ERR_SOCKET_BUFFER_NOT_ENOUGH,
        ERR_SOCKET_INVALID_PARAM,
        ERR_SOCKET_TIMEOUT, // ��ʱ
    } SocketResult;

    // tcp or udp
    int create(SocketType type);

    void set_fd(int fd)
    {
        fd_ = fd;
    }

    int get_fd() const
    {
        return fd_;
    }

    void close();

    // fd�Ƿ���Ч
    bool is_valid() const ;

    // listenǰҪcreate�ɹ���
    int listen(const char *ip, unsigned short port);
    int accept(CommSocket *socket);

    int connect(const char *ip, unsigned short port);

    // ���ð���Ƭ��Ϣ����֧�ִ������İ�
    int set_pkg_info(unsigned int pkg_len_size, unsigned int pkg_len_offset);

    // ���Ѷ����Ļ�������ȡ��һ�������İ����ɹ�����0 ���߷���-1
    int get_pkg(unsigned char **game_pkg, unsigned int *game_pkg_len);

    void get_recv_buffer(unsigned char **buffer, unsigned int *recv_len);

    // �������ݰ���������ܷ��꣬��ŵ��������У� buffer����Ϊ�գ����bufferΪ�յĻ������ͻ������е�����
    // ���������ݷ�������򷵻�ERR_SOCKET_FINISH
    SocketResult send(const unsigned char *buffer, unsigned int buf_len);
    // ��ȡ����������
    SocketResult recv();

    int sendfile(int file_fd, unsigned int offset, size_t *len);

    int wait(bool *read, bool *write, unsigned int wait_mil_sec);

    int get_event()
    {
        return event_;
    }

    void set_event(int event)
    {
        event_ = event;
    }

    int enable_noblock();
    int disable_noblock();
    int get_peer_ip();

    int enable_cork();
    int disable_cork();

    int enbale_quickack();

    int set_recv_buffer_size(unsigned int recv_buffer_size);

    int if_recv_buffer_will_mommove()
    {
        return ((recv_buf_len_ - effective_recv_begin_) <= (1024)) 
            && ((recv_buf_len_ - effective_recv_begin_) > 0);
    }

private:
    static const unsigned int MAX_SEND_BUFFER_LEN = 64 * 1024;
    static const unsigned int MAX_RECV_BUFFER_LEN = 64 * 1024;

    // �������ݻ���
    unsigned char send_buffer_[MAX_SEND_BUFFER_LEN];
    // �������ݻ���
    unsigned char recv_buffer_[MAX_RECV_BUFFER_LEN];

    // ���յ������ݳ���
    unsigned int recv_buf_len_;
    // ��Ч���ݿ�ʼλ��, ֮ǰ�������Ѿ���������
    unsigned int effective_recv_begin_;   

    // ����Ҫ���͵����ݳ���
    unsigned int need_send_buf_len_;
    // ��������ƫ��λ��
    unsigned int effective_send_begin_; 

    int event_;
    int fd_;

    // �����ֶ��ڰ��е�ƫ��λ��
    unsigned int pkg_len_offset_;
    // �����ֶε��ֽ���
    unsigned int pkg_len_size_;
};

#endif // COMM_SOCKET_H_
