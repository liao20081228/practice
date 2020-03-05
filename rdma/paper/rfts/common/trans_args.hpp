#pragma once
#ifndef HPP_RFTS_TRANS_ARGS_HPP
#define HPP_RFTS_TRANS_ARGS_HPP
#include<ctime>
#include<iostream>
namespace rfts 
{
struct data//数据结构
{
	uint16_t		nodeid;		//节点ID
	uint8_t			sensorid;	//传感器ID
	uint8_t			type;		//数据类型,束流位置？长度？
	struct timespec		time;		//时间
	uint64_t		number;		//编号
	long double		value;		//数据值
};

struct transargs
{
	unsigned int afreq;			//采集平率
	unsigned int tfreq;			//传输频率
	unsigned int size_per_data;		//每个物理量数据的大小
	unsigned int kind_per_sensor;		//一个探头产生几种数据
	unsigned int sensor_num_per_node;	//每个节点有几个探头
	unsigned int node_num;			//总共多少个节点
	friend std::ostream& operator << (std::ostream& out, transargs& ref)
	{
		out << "afreq : "		<< ref.afreq			<< "\n"
		    << "tfreq : "		<< ref.tfreq			<< "\n"
		    << "size_per_data  : "	<< ref.size_per_data		<< "\n"
		    << "kind_per_sensor: "	<< ref.kind_per_sensor		<< "\n"
		    << "sensor_num_per_node: "	<< ref.sensor_num_per_node	<< "\n"
		    << "node_num  : "		<< ref.node_num			<< "\n";
		return out;
	}
};



}
#endif /* end of include guard: RFTS_TRANS_ARG_H */
