/*
 * Copyright (c) 2019-2020 Mellanox Technologies LTD. ALL RIGHTS RESERVED.
 * See file LICENSE for terms.
 */

#ifndef PARALLEL_PORT_GROUPS_CALCULATOR_H
#define PARALLEL_PORT_GROUPS_CALCULATOR_H

#include "osm_thread_pool.hpp"
#include "opensm/osm_ar_algorithm.hpp"

class OSMAdaptiveRoutingManager;

namespace OSM {

/*
 * Invoke method on all switches in parallel using multi threading
 */
class OSMParallelPortGroupsCalculator : public OSMThreadPoolTasksCollection {

	OSMAdaptiveRoutingManager *m_ar_mgr_;
	OSMThreadPool             *m_thread_pool_;
	ARSWDataBase              *m_sw_db_;

	uint8_t                    m_max_rank_;
	u_int16_t                 *m_hca_to_sw_lid_mapping_;
	uint8_t                   *m_sw_lid_to_rank_mapping_;
	LidMapping                m_lid_mapping_;

public:

	OSMParallelPortGroupsCalculator(OSMAdaptiveRoutingManager *p_ar_mgr,
					OSMThreadPool *p_thread_pool,
					osm_log_t *p_osm_log,
					ARSWDataBase *p_sw_db) :
	OSMThreadPoolTasksCollection(p_osm_log),
	m_ar_mgr_(p_ar_mgr),
	m_thread_pool_(p_thread_pool),
	m_sw_db_(p_sw_db),
	m_max_rank_(0),
	m_hca_to_sw_lid_mapping_(NULL),
	m_sw_lid_to_rank_mapping_(NULL){}

	~OSMParallelPortGroupsCalculator();

	void CalculatePortGroupsTree(uint8_t max_rank,
				     u_int16_t hca_to_sw_lid_mapping[],
				     uint8_t sw_lid_to_rank_mapping[]);

	int CalculatePortGroups(AdaptiveRoutingAlgorithm *ar_algorithm);

	OSMAdaptiveRoutingManager *GetAdaptiveRoutingManager() { return m_ar_mgr_;}
	uint8_t GetMaxRank() { return m_max_rank_;}
	u_int16_t *GetHcaToSwLidMapping() { return m_hca_to_sw_lid_mapping_;}
	uint8_t *GetSwLidToRankMapping() { return m_sw_lid_to_rank_mapping_;}
	LidMapping *GetLidMapping() { return &m_lid_mapping_;}
};
} /* end of namespace OSM */

#endif /* PARALLEL_PORT_GROUPS_CALCULATOR_H */
