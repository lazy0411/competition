/// @file       comm_key_value_config.h
/// @date       2013/12/05 21:03
///
/// @author
///
/// @brief      ��������ڹ����ֵ�����͵������ļ�

#ifndef COMM_KEY_VALUE_CONFIG_H_
#define COMM_KEY_VALUE_CONFIG_H_

#include <map>
#include <string>

class CommKeyValueConfig
{
public:
    CommKeyValueConfig();
    virtual ~CommKeyValueConfig();

    enum
    {
        EKP_OK = 0,
        EKP_INVALID_PARAM = -1, // ��������
        EKP_VALUE_BUF_TOO_SHORT = -2, // value��buf����
    };

    enum IntValueType
    {
        EVALUE_INT10 = 0, // ��������������10���Ʊ�ʾ
        EVALUE_INT16 = 1, // ��������������16���Ʊ�ʾ
    };

    ///
    /// @fn
    /// @brief  �������ļ���������
    ///
    /// @param  conf_file_path [in] Ҫ���ص������ļ�·��
    ///
    /// @return 0 ���سɹ� ��0 ����ʧ�ܣ��п������ļ������ڣ���û�ж�ȡȨ��
    ///
    int load_from_file(const char *conf_file_path);

    ///
    /// @fn
    /// @brief  ��ȡ���ص��ַ������͵�������ֵ
    ///
    /// @param  config_name [in] Ҫ��ȡ������������
    /// @param  value [out] ���������ֵ
    /// @param  value_len [in] value�Ŀռ䳤��
    /// @param  default_value [in] �����������ڣ���ʹ�ô�Ĭ��ֵ
    ///
    /// @return 0�ɹ�����0��������
    ///
    int get_str(const char *config_name, char *value,
                unsigned int value_len, const char *default_value = NULL);

    ///
    /// @fn
    /// @brief  ��ȡ���ص��������͵�������ֵ
    ///
    /// @param  config_name [in] Ҫ��ȡ������������
    /// @param  value [out] ���������ֵ
    /// @param  type [in] �����������еĽ���
    /// @param  default_value [in] �����������ڣ���ʹ�ô�Ĭ��ֵ
    ///
    /// @return 0�ɹ�����0��������
    ///
    int get_int(const char *config_name, int *value, int default_value = 0, IntValueType type = EVALUE_INT10);

    ///
    /// @fn
    /// @brief  ��ȡ���ص�short���͵�������ֵ
    ///
    /// @param  config_name [in] Ҫ��ȡ������������
    /// @param  value [out] ���������ֵ
    /// @param  type [in] �����������еĽ���
    /// @param  default_value [in] �����������ڣ���ʹ�ô�Ĭ��ֵ
    ///
    /// @return 0�ɹ�����0��������
    ///
    int get_short(const char *config_name, short *value, short default_value = 0, IntValueType type = EVALUE_INT10);

    ///
    /// @fn
    /// @brief  ��ȡ���ص�bool���͵�������ֵ
    ///
    /// @param  config_name [in] Ҫ��ȡ������������
    /// @param  value [out] ���������ֵ
    /// @param  default_value [in] �����������ڣ���ʹ�ô�Ĭ��ֵ
    ///
    /// @return 0�ɹ�����0��������
    ///
    int get_bool(const char *config_name, bool *value, bool default_value = false);

private:

    // ���һ��Ԫ��
    void add_item(const std::string &name, const std::string &value);

    // �õ���Ӧkey��ֵ
    const std::string *get_item_value(const std::string &name) const;

private :
    std::map<std::string, std::string> values_;

}; // end of KeyValueConfig

#endif // COMM_KEY_VALUE_CONFIG_H_

