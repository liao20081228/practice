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

#ifndef _PLFT_BASED_AR_ALGORITHM_H_
#define _PLFT_BASED_AR_ALGORITHM_H_

#include "opensm/osm_ar_algorithm.hpp"

#define MAX_OP_VL_CODE 5

typedef vector <vector <bool> > BoolVecVec;

namespace OSM {

typedef uint8_t sl2vl_t[IB_NUMBER_OF_SLS];

class PlftBasedArAlgorithm : public AdaptiveRoutingAlgorithm {
protected:

	/*
	 * max supported planes in algorithm
	 * currently support only planes_number == plfts_number
	 */
	const uint8_t   m_planes_number_;
	const uint8_t   m_min_vl_number_;

	/* sl2vl */
	sl2vl_t         m_sl2vl_per_op_vls_[MAX_OP_VL_CODE+1];
	uint16_t        m_en_sl_mask_; /* used to calculate m_slvl_per_op_vl_ */
	bool            m_update_sl2vl_;
	/* vl2vl */
	sl2vl_t         m_vl2vl_per_op_vls_[MAX_OP_VL_CODE+1];
	sl2vl_t         m_inc_vl2vl_per_op_vls_[MAX_OP_VL_CODE+1];


public:
	PlftBasedArAlgorithm(osm_log_t *p_osm_log,
			     GuidToSWDataBaseEntry &sw_map,
			     OSMAdaptiveRoutingManager &ar_mgr,
			     supported_feature_t algorithm_feature,
			     uint8_t planes_number,
			     uint8_t min_vl_number) :
	AdaptiveRoutingAlgorithm(p_osm_log, sw_map, ar_mgr, algorithm_feature),
	m_planes_number_(planes_number),
	m_min_vl_number_(min_vl_number),
	m_en_sl_mask_(0),
	m_update_sl2vl_(false)
	{
		memset(m_sl2vl_per_op_vls_, 0, sizeof(m_sl2vl_per_op_vls_));
		BuildVl2VlPerOpVl();
	}

	virtual ~PlftBasedArAlgorithm() {}

	virtual int Preprocess() = 0;
	virtual int RunCycle() = 0;

	virtual int Init() = 0;
	virtual void Clear() = 0;

	virtual OSMThreadPoolTask *GetCalculatePortGroupsTask(
		ARSWDataBaseEntry &db_entry) = 0;

	virtual void ClearAlgorithmConfiguration();
	virtual void CalculateSwitchPortGroups(
		ARSWDataBaseEntry &sw_db_entry,
		LidMapping *p_lid_mapping,
		LidToConnectionArray &lid_to_connections,
		LidToPortArray &base_lid_to_port) = 0;

	virtual int GetSL2VL(osm_physp_t *osm_phys_port,
			     uint8_t iport_num, uint8_t oport_num,
			     uint8_t (*sl2vl)[IB_NUMBER_OF_SLS]);

protected:
	virtual int GetSwitchSL2VL(osm_physp_t *osm_phys_port,
				   uint8_t iport_num,
				   uint8_t oport_num,
				   osm_node_t *p_node,
				   uint64_t guid,
				   uint8_t (*sl2vl)[IB_NUMBER_OF_SLS]) const = 0;

	virtual uint16_t GetPlftMaxSupportedLidNumber(
		ARSWDataBaseEntry &sw_db_entry) = 0;
	virtual void SetPlftMaxSupportedLidNumber(
		ARSWDataBaseEntry &sw_db_entry, u_int8_t plft_max_supported_lid_number) = 0;

	virtual void RestorePriv(ARSWDataBaseEntry &sw_db_entry) = 0;
	virtual void ClearSwitchAlgotithmData(ARSWDataBaseEntry &sw_db_entry) = 0;

	int SetRequiredPLFTInfo(ARSWDataBaseEntry &db_entry);

	/*
	 * Update sw PrivateLFTDef and to_set_plft_def according to plft info
	 * and required plft number and size
	 */
	int SetPlftDef(ARSWDataBaseEntry &db_entry,
		       uint8_t bank_size_kb,
		       uint8_t banks_number,
		       uint8_t plft_size_kb,
		       uint8_t plfts_number);

	void CycleEnd(int rc);

	void SetPlftInfoProcess();
	void SetPlftDefProcess();
	void MapPlftsProcess();
	int PlftProcess();

	string SLToVLMappingToStr(const sl2vl_t &sl2vl) const;

	void BuildSl2VlPerOpVl(uint16_t en_sl_mask);

private:
	int SetHcaLidMapping(osm_physp_t *p_hca_physp,
			     osm_node_t *p_remote_sw_node,
			     LidMapping &lid_mapping);

	void BuildVl2VlPerOpVl();

};
} /* End of namespace OSM */

#endif /* _AR_ALGORITHM_H_ */
