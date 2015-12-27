/// @file       comm_game_axis.cpp
/// @date       2015/12/1
/// 
/// @author     elvisguan
///
/// @brief      ����������
/// @details
/// 
///
#include "comm_game_axis.h"
#include <string>
#include <assert.h>
#include "comm_log.h"
#include <stdio.h>
#include <fstream>
#include <sstream>

GameAxis::GameAxis()
{
    client_axis_.clear();
    axis_records_.clear();
}

GameAxis::~GameAxis()
{
}

GameAxis *GameAxis::instance()
{
    static GameAxis s_game_axis;
    return &s_game_axis;
}

// ��ҵ�¼ʱ����ͼ���������һ������(����������µ�¼ʱ��Ҳ������ɣ��ɽ���ͼ��Ϊ����)
void GameAxis::born(const uint32_t uin)
{
    AXIS rand_axis;
	rand_axis.x_axis = rand() % GAME_MAP_BOARD_SIZE;
	rand_axis.y_axis = rand() % GAME_MAP_BOARD_SIZE;
     
    client_axis_.insert(std::make_pair(uin, rand_axis));

    // �����û����ƶ�ǰ�����û���¼���������ɵ��û����ݼӵ���¼��
    time_t timestamp = time(NULL);
    std::map<uint32_t, std::map<uint32_t, AXIS> >::iterator iter = axis_records_.find(timestamp);
    if (iter != axis_records_.end())
    {
        iter->second.insert(std::make_pair(uin, rand_axis));
    }
}

// ����ƶ�һ�����صķ���,�ĸ��ǵ�����ֱ���(0,0),(GAME_MAP_BOARD_SIZE,0),(GAME_MAP_BOARD_SIZE,GAME_MAP_BOARD_SIZE),(0,GAME_MAP_BOARD_SIZE)
void GameAxis::move_to_next_axis(AXIS &axis)
{
    while (1)
    {
        // 0--����,1--����,2--����,3--����
	    int rand_move_direct = rand() % 4;

        // �������ڵ�ͼ��Ե��Ҫ�ƶ��ķ�����1~2���ǷǷ��ģ���ʱ��Ҫ�������ѡȡ����
        if (0 == rand_move_direct && axis.y_axis != GAME_MAP_BOARD_SIZE)
        {
            axis.y_axis += 1;
            break;
        }
        else if (1 == rand_move_direct && axis.x_axis != GAME_MAP_BOARD_SIZE)
        {
            axis.x_axis += 1;
            break;
        }
        else if (2 == rand_move_direct && axis.y_axis != 0)
        {
            axis.y_axis -= 1;
            break;
        }
        else if (3 == rand_move_direct && axis.x_axis != 0)
        {
            axis.x_axis -= 1;
            break;
        }
    }
}

void GameAxis::move(const uint32_t &timestamp)
{
    /* ��������server�Ķ�ʱ��ÿs������client����ƶ�һ������,����select��ʱ�������ź��ж�
       �������յ�client�˵�ÿsһ�εĻ�ȡ��Ұ���ݵ�ʱ��Ա�ʱ��������������1s�����ƶ����� */

    // ȡ��¼�����һ��Ԫ��
    std::map<uint32_t, std::map<uint32_t, AXIS> >::reverse_iterator iter_last = axis_records_.rbegin();
    if (iter_last != axis_records_.rend())
    {
        if (iter_last->first >= timestamp)
            return;
    }

    // �Ƿ���Ҫ��ӡ
    check_and_print_axis();
    
    // ѭ������client������
    std::map<uint32_t, AXIS>::iterator iter = client_axis_.begin();
    for (; iter != client_axis_.end(); iter++)
    {
        move_to_next_axis(iter->second);
    }

    axis_records_.insert(std::make_pair(time(NULL), client_axis_));
}

// ��ȡָ���������Ұ����
void GameAxis::get_sight_data(const uint32_t &uin, svr_proto::PlayerSight &pkg_sight)
{
    // ��ȡָ����ҵ�������Ϣ
    AXIS axis;
    std::map<uint32_t, AXIS>::iterator iter = client_axis_.find(uin);
    if (iter != client_axis_.end())
    {
        axis.x_axis = iter->second.x_axis;
        axis.y_axis = iter->second.y_axis;
    }
    // ��ҵ�������Ϣ������,������һ�ε�¼
    else
    {
        error_log("Error: player axis can't be found, uin[%u], genarate now.", uin);
        
        born(uin);
        std::map<uint32_t, AXIS>::iterator iter_born = client_axis_.find(uin);
        // ��ʱһ�����ڣ��������ж�һ��
        if (iter_born != client_axis_.end())
        {
            axis.x_axis = iter_born->second.x_axis;
            axis.y_axis = iter_born->second.y_axis;
        }
        else
            error_log("Error: player axis can't be found!!");
    }
    
    // ָ����Ļ����Ϊ1440x900
    // ��ָ������Ϊ�е㣬������ȡ��������ı߽�ֵ
    int x_axis_min = axis.x_axis - 1440 / 2;
    int x_axis_max = axis.x_axis + 1440 / 2;
    int y_axis_min = axis.y_axis - 900 / 2;
    int y_axis_max = axis.y_axis + 900 / 2;
    if (x_axis_min < 0)
        x_axis_min = 0;
    if (x_axis_max > GAME_MAP_BOARD_SIZE)
        x_axis_max = GAME_MAP_BOARD_SIZE;
    if (y_axis_min < 0)
        y_axis_min = 0;
    if (y_axis_max > GAME_MAP_BOARD_SIZE)
        y_axis_max = GAME_MAP_BOARD_SIZE;
    

    // client��pkg��ȫ�ֱ����������Ȱѽṹ�����
    pkg_sight.sight_.count_ = 0;

    // ѭ������client������
    iter = client_axis_.begin();
    for (; iter != client_axis_.end(); iter++)
    {
        AXIS client_axis = iter->second;
        if (client_axis.x_axis <= (uint32_t)x_axis_max \
            && client_axis.x_axis >= (uint32_t)x_axis_min \
            && client_axis.y_axis <= (uint32_t)y_axis_max \
            && client_axis.y_axis >= (uint32_t)y_axis_min)
        {
            int index = pkg_sight.sight_.count_;
            pkg_sight.sight_.axis_[index].x_axis_ = client_axis.x_axis;
            pkg_sight.sight_.axis_[index].y_axis_ = client_axis.y_axis;
            pkg_sight.sight_.count_++;
        }
    }
}

// ÿ����Ӵ�ӡһ�Σ���¼����300��ʱ����¼һ��
void GameAxis::check_and_print_axis()
{
    if (axis_records_.size() <= 300)
        return;

    // time:uin,x.y;uin,x.y#time:...��ʽ�����㹤�߻�ԭ�ԶԱȿͻ�������
    std::string record = "";
	std::map<uint32_t, std::map<uint32_t, AXIS> >::iterator iter = axis_records_.begin();
    for (; iter != axis_records_.end(); iter++)
    {
        if ("" != record)
            record.append("\n");

        std::stringstream ss_time;
        std::string time;
        
        ss_time << iter->first;
        ss_time >> time;
        record += time + ":";
        
        std::string temp = "";
        std::map<uint32_t, AXIS> client_axis = iter->second;
        std::map<uint32_t, AXIS>::iterator iter_client = client_axis.begin();
        for (; iter_client != client_axis.end(); iter_client++)
        {
            std::stringstream ss_x;
            std::stringstream ss_y;
            std::stringstream ss_uin;
            
            std::string x;
            std::string y;
            std::string uin;
            ss_x << iter_client->second.x_axis;
            ss_x >> x;
            ss_y << iter_client->second.y_axis;
            ss_y >> y;
            ss_uin << iter_client->first;
            ss_uin >> uin;

            if ("" != temp)
                temp += ";";
            
            temp += uin + "," + x + "." + y;
        }
        record += temp;
    }

    axis_records_.clear();

    //д��ָ�����ļ�,�ļ���Ϊʱ���+axis_record
    time_t now_time = time(NULL);
    std::string time;
    std::stringstream ss;
    ss << now_time;
    ss >> time;
    std::string ouputfilename = "log/" + time + ".axis_record";
    
    std::ofstream fout;
    fout.open(ouputfilename.c_str(), std::ios::out|std::ios::trunc);
    fout << record;
    fout.close();
}
