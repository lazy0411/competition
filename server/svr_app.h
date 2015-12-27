/// @file       svr_app.h
/// @date       2013/12/04 17:30
///
/// @author
///
/// @brief      ���߼��ඨ��
///

#ifndef SVR_APP_H
#define SVR_APP_H

#include "svr_config.h"
#include "svr_accept_handler.h"
#include "comm_game_axis.h"

// ���߼��ඨ��
class SvrApp
{
public:
    // ��ȡ����
    static SvrApp *instance();

    // ����
    int run(int argc, const char **argv);

    //static void on_timer_handle(int sig);

    const SvrConfig &get_config() const
    {
        return conf_;
    }

protected:
    // ��ʼ��
    int init(const char *cfg_path);

    // ��������
    int load_cfg(const char *cfg_path);

    SvrApp();
    ~SvrApp();

private:
    // �����ö���
    SvrConfig conf_;

    // �����¼�����
    SvrAcceptHandler accept_handler_;

    // �Ƿ��������
    bool is_run_;

    // ��������
    static SvrApp *instance_;
};

#endif
