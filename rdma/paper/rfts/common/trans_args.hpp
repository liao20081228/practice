#pragma once
#ifndef HPP_RFTS_TRANS_ARGS_HPP
#define HPP_RFTS_TRANS_ARGS_HPP
#include<ctime>
#include<iostream>
namespace rfts 
{
struct data//数据结构
{
	unsigned short int nodeid;    //节点ID
	unsigned char sensorid; //传感器ID
	unsigned char type;	//数据类型,束流位置？长度？
	struct   timespec time; //时间
	double   value;		//值
};

struct transargs
{
	unsigned int afreq;//采集平率
	unsigned int tfreq;//传输频率
	unsigned char size;//每个物理量数据的大小
	unsigned char  kind;//每个节点要测试几种
	unsigned char sensor_num;//每个节点有几个探头
	unsigned short node_num;//总共多少个节点
	friend std::ostream& operator<< (std::ostream& out, transargs& ref)
	{
		out << "afreq : " << ref.afreq << std::endl
		<< "tfreq : " << ref.tfreq << std::endl;
	}
};



}
#endif /* end of include guard: RFTS_TRANS_ARG_H */
