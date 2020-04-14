/*
 * Copyright (c) 2019-2020 Mellanox Technologies LTD. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *	- Redistributions of source code must retain the above
 *	  copyright notice, this list of conditions and the following
 *	  disclaimer.
 *
 *	- Redistributions in binary form must reproduce the above
 *	  copyright notice, this list of conditions and the following
 *	  disclaimer in the documentation and/or other materials
 *	  provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#ifndef _AR_KDOR_ALGORITHM_H_
#define _AR_KDOR_ALGORITHM_H_

#include "opensm/osm_armgr_types.hpp"
#include "opensm/osm_ar_plft_based_algorithm.hpp"

#define INVALID_DIM_INDEX 0xFF
#define MAX_KDOR_PLFT_NUMBER 4

typedef uint8_t port_index_t;
typedef int8_t dim_sign_t;
typedef uint8_t dim_index_t;
typedef uint16_t dim_size_t;

namespace OSM {

class KdorSwData;
class ArKdorAlgorithm;
struct KdorConnection;
struct KdorRouteInfo;

typedef list <osm_physp_t*> PhysPortsList;
typedef PhysPortsList::iterator PhysPortsListIter;
typedef vector <KdorConnection*> ConnectionVec;
typedef vector <KdorRouteInfo> KdorRouteInfoVec;


typedef map <osm_switch_t*, KdorConnection> SwToConnectionMap;
typedef SwToConnectionMap::iterator SwToConnectionMapIter;
typedef pair <SwToConnectionMapIter, bool> SwToConnectionMapInsertRes;

struct KdorGroupData {
	GroupData* group_data_array[MAX_KDOR_PLFT_NUMBER - 1];
};

typedef map <u_int16_t, KdorGroupData> LidToKdorGroupDataMap;
typedef LidToKdorGroupDataMap::iterator LidToKdorGroupDataMapIter;
typedef LidToKdorGroupDataMap::const_iterator LidToKdorGroupDataMapConstIter;
typedef pair <LidToKdorGroupDataMapIter, bool> LidToKdorGroupDataMapInsertRes;

enum kdor_turn_t {
	KDOR_TURN_TYPE_0 = 0,	/*  +-Low   -> +-High */
	KDOR_TURN_TYPE_1,	/*  +-High  ->  +Low  */
	KDOR_TURN_TYPE_2,	/*  +-High  ->  -Low  */
	KDOR_TURN_TYPE_LAST
};

enum bfs_status_t {
	BFS_INIT,
	BFS_QUEUED,
	BFS_DONE
};

struct KdorConnection {
	/* If m_remote_switch == NULL this is a connection to all non sw ports */
	osm_switch_t   *m_remote_switch;
	PhysPortsList   m_ports; /* Elements of type, osm_physp_t* */
	PortsBitset     m_ports_bitset;
	PhysPortsListIter  m_next_port_for_routing;	/* Will be used for load-balancing DLIDs among ports */
	dim_index_t     m_dim_idx;
	dim_sign_t      m_dim_sign;

	KdorConnection() :
	m_remote_switch(NULL), m_next_port_for_routing(0),
	m_dim_idx(0), m_dim_sign(0){}

	ARSWDataBaseEntry *GetRemoteSwitchDbEntry() {
		return((ARSWDataBaseEntry *)(m_remote_switch->priv));
	}

	string ToString() const;

};

struct KdorRouteInfo {
	KdorConnection     *m_connection;
	uint8_t             m_vl_inc;    /* kdor plane number */
	kdor_turn_t         m_turn_type; /* First turn type that is used in the path */

private:
	static uint8_t turn_type_wait[KDOR_TURN_TYPE_LAST];
public:

	KdorRouteInfo() : m_connection(NULL), m_vl_inc(0),
	m_turn_type(KDOR_TURN_TYPE_0) {}

	void Init() {
		m_connection = NULL;
		m_vl_inc = 0;
		m_turn_type = KDOR_TURN_TYPE_0;
	}

	bool operator<(const KdorRouteInfo& __rhs) const;
};

struct KdorAlgorithmData : public TreeAlgorithmData {

	LidToKdorGroupDataMap m_lid_to_kdor_group_map;

	/*
	 * Add lid to non empty group_data in ginen kdor_group_data
	 * And update lid_to_kdor_group_map
	 */
	void AddLidToKdorGroupData(uint16_t lid_num,
				   uint16_t sw_lid_num,
				   KdorGroupData &kdor_group_data,
				   bool is_new_group,
				   osm_log_t *p_osm_log);
private:

	void AddLidToKdorGroupData(uint16_t lid_num,
				   KdorGroupData &kdor_group_data);
};

class KdorSwData {
	OSMCalculatePortGroupsTask  m_calculate_port_groups_task_;

	void               *m_saved_priv_;
	ARSWDataBaseEntry  &m_db_entry_;
	uint32_t            m_sw_idx_;

	KdorRouteInfoVec    m_route_info_; 	/* sw_idx_ to route info; */
	SwToConnectionMap   m_connections_;	/* Inter-switch connections */
	ConnectionVec       m_port_num_to_connection_tbl_;  /* Will be used for fast lookup in VL2VL */

	/* Meta-data for BFS traversing during routing */
	bfs_status_t        m_route_status_;
	uint16_t            m_route_distance_;

public:
	/* plft_max_supported_lid_number is restricted by plft table size */
	uint16_t            m_plft_max_supported_lid_number;

public:
	KdorSwData(ARSWDataBaseEntry &db_entry,
		   OSMParallelPortGroupsCalculator *p_port_groups_calculator) :
	m_calculate_port_groups_task_(p_port_groups_calculator),
	m_saved_priv_(NULL), m_db_entry_(db_entry), m_sw_idx_(0),
	m_route_status_(BFS_INIT), m_route_distance_(0),
	m_plft_max_supported_lid_number(0) {}

	void Resize(uint32_t ports_num);

	void InitRouteInfo() {
		m_route_status_ = BFS_INIT;
		m_route_distance_ = 0;
	}

	KdorRouteInfo &GetRouteInfo(KdorSwData *p_dst_switch_data) {
		return m_route_info_[p_dst_switch_data->m_sw_idx_];
	}

	int Init(ArKdorAlgorithm &algorithm,
		 ARSWDataBaseEntry &db_entry,
		 uint32_t sw_idx,
		 uint32_t switches_number);

	void SetRouteStatus(bfs_status_t status) { m_route_status_ = status;}
	bfs_status_t GetRouteStatus() const { return m_route_status_;}

	void SetRouteDistance(uint16_t dist) { m_route_distance_ = dist;}
	uint16_t GetRouteDistance() const { return m_route_distance_;}

	OSMThreadPoolTask *GetCalculatePortGroupsTask() {
		return &m_calculate_port_groups_task_;
	}

	SwToConnectionMap &GetConnections() { return m_connections_;}
	const KdorConnection *GetPortConnection(uint8_t port_num) const;

	void *GetSavedPriv() { return m_saved_priv_;}

};

class ArKdorAlgorithm : public PlftBasedArAlgorithm {

protected:
	uint8_t         m_max_vlinc_; /* max static routing vl increase */

	KdorSwData     *m_sw_lid_to_kdor_data_[IB_LID_UCAST_END_HO + 1];

	sl2vl_t     m_turn_1_vl2vl_per_op_vls_[MAX_OP_VL_CODE+1];
	sl2vl_t     m_turn_2_vl2vl_per_op_vls_[MAX_OP_VL_CODE+1];
	sl2vl_t     *m_turn_type_to_vl2vl_per_op_vls_[KDOR_TURN_TYPE_LAST];

	ib_port_sl_to_plft_map_t m_plft_map_;

public:
	ArKdorAlgorithm(osm_log_t *p_osm_log,
			GuidToSWDataBaseEntry &sw_map,
			OSMAdaptiveRoutingManager &ar_mgr,
			supported_feature_t algorithm_feature,
			uint8_t planes_number,
			uint8_t min_vl_number) :
	PlftBasedArAlgorithm(p_osm_log, sw_map, ar_mgr,
			     algorithm_feature, planes_number, min_vl_number),
	m_max_vlinc_(0) {
		memset(m_sw_lid_to_kdor_data_, 0, sizeof(m_sw_lid_to_kdor_data_));
		BuildKdorVl2VlPerOpVl();
		BuildKdorPlftMap();
	}

	virtual ~ArKdorAlgorithm(){}

	virtual int Preprocess();
	virtual int RunCycle();

	virtual void Clear() {}
	virtual int Init();

	virtual OSMThreadPoolTask *GetCalculatePortGroupsTask(
		ARSWDataBaseEntry &db_entry);

	virtual void CalculateSwitchPortGroups(
		ARSWDataBaseEntry &sw_db_entry,
		LidMapping *p_lid_mapping,
		LidToConnectionArray &lid_to_connections,
		LidToPortArray &base_lid_to_port);

	virtual int GetSwitchSL2VL(osm_physp_t *osm_phys_port,
				   uint8_t iport_num, uint8_t oport_num,
				   osm_node_t *p_node,
				   uint64_t guid,
				   uint8_t (*sl2vl)[IB_NUMBER_OF_SLS]) const;

	void CalculateRouteInfo(KdorConnection &connection,
				KdorSwData *p_remote_switch_data,
				KdorSwData *p_dst_switch_data,
				KdorRouteInfo &route_info) {
		CalculateRouteInfo(connection,
				   p_remote_switch_data->GetRouteInfo(p_dst_switch_data),
				   route_info);
	}

	void CalculateRouteInfo(KdorConnection &connection,
				KdorRouteInfo &remote_route_info,
				KdorRouteInfo &route_info);

	virtual int SetDirection(osm_switch_t* src,
				 osm_switch_t* dst,
				 KdorConnection &connection) = 0;

protected:
	virtual uint16_t GetPlftMaxSupportedLidNumber(ARSWDataBaseEntry &sw_db_entry);
	virtual void SetPlftMaxSupportedLidNumber(
		ARSWDataBaseEntry &sw_db_entry, u_int8_t plft_max_supported_lid_number);

	virtual void RestorePriv(ARSWDataBaseEntry &sw_db_entry);
	virtual void ClearSwitchAlgotithmData(ARSWDataBaseEntry &sw_db_entry);

private:
	bool SetCapable();

	void SetPlftConfiguration();

	/* Buils static unicast route info */
	int BuildStaticRouteInfo();

	int BuildStaticRouteInfoToSwitch(SwDbEntryPrtList &bfs_q,
					 ARSWDataBaseEntry &dst_db_entry);

	int ProcessNeighborsBfs(SwDbEntryPrtList &bfs_q,
				ARSWDataBaseEntry *p_sw_db_entry,
				ARSWDataBaseEntry *p_dst_db_entry);

	/* Calculate Groups and pLFTs */
	int CalculatePortGroups();

	void CalculateArGroups(ARSWDataBaseEntry &sw_db_entry,
			       u_int16_t *lid_to_sw_lid_mapping,
			       KdorAlgorithmData &algorithm_data);

	void CalculateArPlfts(ARSWDataBaseEntry &sw_db_entry,
			      LidMapping *p_lid_mapping,
			      KdorAlgorithmData &algorithm_data,
			      LidToConnectionArray &lid_to_connections,
			      LidToPortArray &base_lid_to_port);

	void CalculateArPlft(ARSWDataBaseEntry &sw_db_entry,
			     KdorAlgorithmData &algorithm_data,
			     u_int8_t ucast_lft_port,
			     unsigned dest_lid,
			     int plft_id,
			     LidToKdorGroupDataMapConstIter &ar_kdor_groups_iter,
			     OUT uint8_t &lid_state,
			     OUT uint16_t &ar_group_id);

	uint8_t GetStaticUcastLftPort(ARSWDataBaseEntry &sw_db_entry,
				      LidMapping *p_lid_mapping,
				      KdorConnection *dst_sw_lid_to_conection[],
				      uint8_t base_lid_to_port[],
				      uint16_t dest_lid);

	kdor_turn_t GetTurnType(const KdorConnection &from_connection,
				const KdorConnection &to_connection) const;
	/* Get static routing from the given switch */
	void BuildDstSwLidToConnection(ARSWDataBaseEntry &sw_db_entry,
				       KdorConnection *dst_sw_lid_to_conection[]);
	void BuildKdorVl2VlPerOpVl();
	void BuildKdorPlftMap();

	void SetPlftMap();
	void SetPlftMap(ARSWDataBaseEntry &sw_db_entry);
};

#define HC_PLANES_NUMBER 4

class ArHcAlgorithm : public ArKdorAlgorithm {

public:

	ArHcAlgorithm(osm_log_t *p_osm_log,
		      GuidToSWDataBaseEntry &sw_map,
		      OSMAdaptiveRoutingManager &ar_mgr) :
	ArKdorAlgorithm(p_osm_log, sw_map, ar_mgr,
			SUPPORT_HC,
			HC_PLANES_NUMBER, HC_PLANES_NUMBER) {}

	virtual ~ArHcAlgorithm(){}

	virtual int SetDirection(osm_switch_t* src,
				 osm_switch_t* dst,
				 KdorConnection &connection);

	virtual ar_algorithm_t GetAlgorithm() { return AR_ALGORITHM_KDOR_HC;}

};
} /* end of namespace OSM */

#endif /*_AR_KDOR_ALGORITHM_H_ */
