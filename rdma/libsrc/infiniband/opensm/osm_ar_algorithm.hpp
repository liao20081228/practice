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

#ifndef _AR_ALGORITHM_H_
#define _AR_ALGORITHM_H_

#include "opensm/osm_armgr_types.hpp"
#include "osm_calculate_port_groups_task.hpp"

#define MAX_OP_VL_CODE 5

class OSMAdaptiveRoutingManager;

namespace OSM {

struct LidMapping {
	u_int16_t m_lid_to_sw_lid_mapping[IB_LID_UCAST_END_HO + 1];
	u_int16_t m_lid_to_base_lid_mapping[IB_LID_UCAST_END_HO + 1];

	LidMapping() { Clear(); }

	void Clear() {
		memset(m_lid_to_sw_lid_mapping, 0, sizeof(m_lid_to_sw_lid_mapping));
		memset(m_lid_to_base_lid_mapping, 0, sizeof(m_lid_to_base_lid_mapping));
	}
};

struct PlftDefInfo {
	uint8_t lid_offset;
	uint8_t lid_space;
	uint8_t table_idx;
};

class AdaptiveRoutingAlgorithm {
protected:
	osm_log_t                   *m_p_osm_log; /* Pointer to osm log */
	GuidToSWDataBaseEntry       &m_sw_map_;
	OSMAdaptiveRoutingManager   &m_ar_mgr_;

	supported_feature_t 	    m_algorithm_feature_;

	/* Temporary algorithm data */
	LidMapping 			m_lid_mapping_;

public:
	AdaptiveRoutingAlgorithm(osm_log_t *p_osm_log,
				 GuidToSWDataBaseEntry &sw_map,
				 OSMAdaptiveRoutingManager &ar_mgr,
				 supported_feature_t algorithm_feature) :
	m_p_osm_log(p_osm_log), m_sw_map_(sw_map),
	m_ar_mgr_(ar_mgr), m_algorithm_feature_(algorithm_feature) {}

	virtual ~AdaptiveRoutingAlgorithm() {}

	virtual ar_algorithm_t GetAlgorithm() = 0;
	virtual int Preprocess() = 0;
	virtual int RunCycle() = 0;

	virtual int Init() = 0;
	virtual void Clear() = 0;

	osm_log_t *GetLog() { return m_p_osm_log;}

	int BuildLidMapping(LidMapping &lid_mapping);

	virtual OSMThreadPoolTask *GetCalculatePortGroupsTask(
		ARSWDataBaseEntry &db_entry) = 0;

	virtual void ClearAlgorithmConfiguration() = 0;

	virtual void CalculateSwitchPortGroups(
		ARSWDataBaseEntry &sw_db_entry,
		LidMapping *p_lid_mapping,
		LidToConnectionArray &lid_to_connections,
		LidToPortArray &base_lid_to_port) = 0;

	virtual int GetSL2VL(osm_physp_t *osm_phys_port,
			     uint8_t iport_num, uint8_t oport_num,
			     uint8_t (*sl2vl)[IB_NUMBER_OF_SLS])
	{
		return -1;
	}


protected:

	bool IsFeatureActive(ARSWDataBaseEntry &sw_db_entry,
			     supported_feature_t m_feature)
	{
		return((sw_db_entry.m_support[SUPPORT_AR] == SUPPORTED) &&
		       (sw_db_entry.m_support[m_feature] == SUPPORTED) &&
		       (sw_db_entry.m_option_on));
	}

private:
	int SetHcaLidMapping(osm_physp_t *p_hca_physp,
			     osm_node_t *p_remote_sw_node,
			     LidMapping &lid_mapping);
};

} /* end of namespace OSM */

#endif /* _AR_ALGORITHM_H_ */
