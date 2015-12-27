/// @file       svr_config.h
/// @date       2013/12/05 20:56
///
/// @author
///
/// @brief      ���ù���
///
///

#ifndef SVR_CONFIG_H_
#define SVR_CONFIG_H_

class SvrConfig
{
public:
    SvrConfig();
    ~SvrConfig();

    int load(const char *cfg_path);

public:
    char listen_ip_[16]; //
    unsigned short listen_port_; //
    unsigned int max_client_; // ��������������
    char log_path_[256]; // ��־���·��
    int log_level_; // ��־����: debug info error

    char data_dir_[256]; // �����ļ����Ŀ¼

};

#endif // SVR_CONFIG_H_

