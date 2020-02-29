#pragma once
#ifndef RFTS_TRANS_ARGS_H
#define RFTS_TRANS_ARGS_H


struct trans_args
{
	int afreq;//采集平率
	int tfreq;//传输频率
	int size;//每个物理量数据的大小
	int kind;//每个节点要测试几种
	int sensor_num;//每个节点有几个探头
	int node_num;//总共多少个节点
};



#endif /* end of include guard: RFTS_TRANS_ARG_H */