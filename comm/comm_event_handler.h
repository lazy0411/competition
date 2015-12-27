/// @file       comm_event_handler.h
/// @date       2013/12/04 21:03
///
/// @author
///
/// @brief      �¼�������
///
#ifndef COMM_EVENT_HANDLER_H_
#define COMM_EVENT_HANDLER_H_

#include "comm_define.h"

class CommRefactor;
class CommEventHandler
{
public:

    ///IO�����¼�
    enum EVENT_MASK
    {
        NULL_MASK    = 0,
        ///��ȡ�¼����������Ϊ�ɶ��ǣ�����handle_input
        READ_MASK    = (1 << 1),
        ///д�¼����������Ϊ��д�ǣ�handle_output
        WRITE_MASK   = (1 << 2),
        ///�쳣�¼������������handle_exception
        EXCEPT_MASK  = (1 << 3),
        ///�첽CONNECT�ɹ��󣬵���handle_output���첽CONNECTʧ�ܺ󣬵���handle_input��
        CONNECT_MASK = (1 << 4),
        ///ACCEPT�¼�����һ��ACCEPT�˿ڿ������Ӻ󣬵���handle_input��
        ACCEPT_MASK  = (1 << 5),
    };

public:

    /*!
    @brief      ���캯��
    */
    CommEventHandler();
    /*!
    @brief      ���캯����ͬʱ������۵ķ�Ӧ��ָ��
    @param      reactor �����صķ�Ӧ��ָ��
    */
    CommEventHandler(CommRefactor *reactor);
    /*!
    @brief      ��������
    */
    virtual ~CommEventHandler();

public:

    /*!
    @brief      ȡ�ض�Ӧ��ZEN_SOCKET ���
    @return     ZEN_SOCKET CommEventHandler ��Ӧ��ZEN_SOCKET ���
    */
    virtual int get_handle(void) const = 0;

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

    /*!
    @brief      ȡ�õ�ǰ�ı�־λ
    @return     int ���صĵ�ǰ��MASKֵ
    */
    inline int get_mask();

    /*!
    @brief      ���õ�ǰ��־λ
    @param      mask ���õ�MASKֵ
    */
    inline void set_mask(int mask);

    /*!
    @brief      enable mask�����ı�־λ
    @param      en_mask �򿪵�MASK��ֵ
    */
    inline void enable_mask(int en_mask);

    /*!
    @brief      disable mask�����ı�־λ
    @param      dis_mask �رյ�MASKֵ
    */
    inline void disable_mask(int dis_mask);

    /*!
    @brief      ���÷�Ӧ��
    @param      reactor
    */
    virtual void reactor (CommRefactor *reactor);

    /*!
    @brief      ȡ���Լ������ķ�Ӧ��
    @return     *
    */
    virtual CommRefactor *reactor (void) const;

    //��ʱ���������������û���ڷ�Ӧ�����漯�ɶ�ʱ���Ĵ���
    //virtual int handle_timeout (const ZEN_Time_Value &tv, const void *arg = 0);

protected:

    ///��Ӧ��
    CommRefactor       *reactor_;

    ///��������ӦҪ������¼�MASK
    int                event_mask_;
};

//ȡ�õ�ǰ�ı�־λ
inline int CommEventHandler::get_mask()
{
    return event_mask_;
}

//���õ�ǰ��־λ
inline void CommEventHandler::set_mask(int mask)
{
    event_mask_ = mask;
}

//enable mask�����ı�־λ
inline void CommEventHandler::enable_mask(int en_mask)
{
    event_mask_ |= en_mask;
}
//disable mask�����ı�־λ
inline void CommEventHandler::disable_mask(int dis_mask)
{
    event_mask_ &= (~dis_mask);
}

#endif // COMM_EVENT_HANDLER_H_
