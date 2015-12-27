/// @file       comm_game_axis.h
/// @date       2015/12/1
/// 
/// @author     elvisguan
///
/// @brief 
/// @details
///  
///

#ifndef COMM_GAME_AXIS_H_
#define COMM_GAME_AXIS_H_

#include "svr_proto.h"
#include <map>

// ��ͼ��С
#define GAME_MAP_BOARD_SIZE 1500

struct AXIS
{
    uint32_t x_axis;
    uint32_t y_axis;
};

class GameAxis
{
public:
	GameAxis();

	~GameAxis();

	void born(const unsigned int uin);

    void move(const uint32_t &time);

    void get_sight_data(const unsigned int &uin, svr_proto::PlayerSight &pkg_sight);

    void check_and_print_axis();

    static GameAxis *instance();
    
private:
	void move_to_next_axis(AXIS &axis);
    
private:
    // <uin, ����>
    std::map<uint32_t, AXIS> client_axis_;
    // <ʱ���, <uin, ����> >
    std::map<uint32_t, std::map<uint32_t, AXIS> > axis_records_;
};


#endif // COMM_GAME_AXIS_H_