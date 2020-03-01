#pragma once
#ifndef RFTS_TRANS_ARGS_H
#define RFTS_TRANS_ARGS_H
#include<ctime>
namespace 
{
struct data//数据结构
{
	short    int nodeid;    //节点ID
	unsigned char sensorid; //传感器ID
	unsigned char type;	//数据类型,束流位置？长度？
	struct   timespec time; //时间
	double   value;		//值
};



struct trans_args
{
	int afreq;//采集平率
	int tfreq;//传输频率
	int size;//每个物理量数据的大小
	int kind;//每个节点要测试几种
	int sensor_num;//每个节点有几个探头
	int node_num;//总共多少个节点
};

}
#endif /* end of include guard: RFTS_TRANS_ARG_H */
