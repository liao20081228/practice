/*
 * Copyright (c) 2004-2009 Voltaire, Inc. All rights reserved.
 * Copyright (c) 2002-2008 Mellanox Technologies LTD. All rights reserved.
 * Copyright (c) 1996-2003 Intel Corporation. All rights reserved.
 * Copyright (c) 2012 Lawrence Livermore National Lab.  All rights reserved.
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
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
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

/*
 * Abstract:
 *    OSM Congestion Control types and prototypes
 *
 * Author:
 *    Albert Chu, LLNL
 */

#ifndef OSM_CONGESTION_CONTROL_H
#define OSM_CONGESTION_CONTROL_H

#include <iba/ib_types.h>
#include <complib/cl_types_osd.h>
#include <complib/cl_dispatcher.h>
#include <opensm/osm_subnet.h>
#include <opensm/osm_log.h>
//#include <opensm/osm_sm.h>
#include <opensm/osm_base.h>

/****s* OpenSM: Base/OSM_DEFAULT_CC_KEY
 * NAME
 *       OSM_DEFAULT_CC_KEY
 *
 * DESCRIPTION
 *       Congestion Control Key used by OpenSM.
 *
 * SYNOPSIS
 */
#define OSM_DEFAULT_CC_KEY 0

#define OSM_CC_DEFAULT_MAX_OUTSTANDING_QUERIES 500

#define OSM_CC_TIMEOUT_COUNT_THRESHOLD 3

#define CC_MAX_PROFILES_NAME_LEN 32

/****s* OpenSM: CongestionControl/osm_congestion_control_t
*  This object should be treated as opaque and should
*  be manipulated only through the provided functions.
*/
struct osm_sm;

typedef struct osm_congestion_control {
	struct osm_opensm *osm;
	osm_subn_t *subn;
	struct osm_sm *sm;
	osm_log_t *log;
	osm_mad_pool_t *mad_pool;
	atomic32_t trans_id;
	osm_vendor_t *vendor;
	osm_bind_handle_t bind_handle;
	cl_disp_reg_handle_t cc_disp_h;
	ib_net64_t port_guid;
	atomic32_t outstanding_mads;
	atomic32_t outstanding_mads_on_wire;
	cl_qlist_t mad_queue;
	cl_spinlock_t mad_queue_lock;
	cl_event_t cc_poller_wakeup;
	cl_event_t outstanding_mads_done_event;
	cl_event_t sig_mads_on_wire_continue;
	cl_thread_t cc_poller;
	osm_thread_state_t thread_state;
	ib_sw_cong_setting_t sw_cong_setting;
	ib_ca_cong_setting_t ca_cong_setting;
	ib_cc_tbl_t cc_tbl[OSM_CCT_ENTRY_MAD_BLOCKS];
	unsigned int cc_tbl_mads;
} osm_congestion_control_t;
/*
* FIELDS
*       subn
*             Subnet object for this subnet.
*
*       log
*             Pointer to the log object.
*
*       mad_pool
*             Pointer to the MAD pool.
*
*       mad_ctrl
*             Mad Controller
*********/

#define OSM_CC_MAX_PROFILE_NUM IB_CC_PORT_PROFILES_BLOCK_SIZE

typedef enum _osm_cc_group_type_enum {
	OSM_CC_GROUP_NOT_DEFINED = 0,
	OSM_CC_GROUP_ALL_SWITCHES,
	OSM_CC_GROUP_SWITCH_PORTS
} osm_cc_group_type_enum;

osm_cc_group_type_enum osm_cc_get_group_type(IN const char *str);

typedef struct osm_cc_mgr {
	cl_fmap_t cc_profiles_map;
	cl_qlist_t sl_profiles_conf;
	cl_qlist_t vl_profiles_conf;
	cl_qlist_t sw_conf;
	cl_qlist_t ca_conf;
} osm_cc_mgr_t;

typedef struct osm_cc_profile {
	uint8_t percent;
	uint64_t min;
	uint64_t max;
} osm_cc_profile_t;

typedef struct osm_cc_sw_conf {
	cl_list_item_t list_item;
	osm_cc_group_type_enum group_type;
	boolean_t enable;
	uint8_t aqs_weight;
	uint8_t aqs_time;
} osm_cc_sw_conf_t;

typedef struct osm_cc_hca_rp_params_conf {
	boolean_t enable_clamp_tgt_rate;
	boolean_t enable_clamp_tgt_rate_after_time_inc;
	uint32_t rpg_time_reset;
	uint32_t rpg_byte_reset;
	uint8_t  rpg_threshold;
	uint32_t rpg_max_rate;
	uint16_t rpg_ai_rate;
	uint16_t rpg_hai_rate;
	uint8_t rpg_gd;
	uint8_t rpg_min_dec_fac;
	uint32_t rpg_min_rate;
	uint32_t rate_to_set_on_first_cnp;
	uint16_t dce_tcp_g;
	uint32_t dce_tcp_rtt;
	uint32_t rate_reduce_monitor_period;
	uint16_t initial_alpha_value;
} osm_cc_hca_rp_params_conf_t;

typedef struct osm_cc_hca_np_params_conf {
	uint16_t min_time_between_cnps;
	boolean_t cnp_sl_mode;
	uint8_t cnp_sl;
} osm_cc_hca_np_params_conf_t;

typedef struct osm_cc_ca_conf {
	cl_list_item_t list_item;
	osm_cc_group_type_enum group_type;
	boolean_t enable_notify;
	boolean_t enable_react;
	osm_cc_hca_rp_params_conf_t hca_rp_params;
	osm_cc_hca_np_params_conf_t hca_np_params;
} osm_cc_ca_conf_t;

typedef struct osm_cc_sl_conf {
	cl_list_item_t list_item;
	osm_cc_group_type_enum group_type;
	uint8_t sl2profile_num[IB_NUMBER_OF_SLS];
} osm_cc_sl_conf_t;

typedef struct osm_cc_profiles_conf {
	cl_fmap_item_t fmap_item;
	char name[CC_MAX_PROFILES_NAME_LEN];
	uint8_t mode;
	osm_cc_profile_t profiles[OSM_CC_MAX_PROFILE_NUM];
} osm_cc_profiles_conf_t;

typedef struct osm_cc_vl_conf {
	cl_list_item_t list_item;
	osm_cc_group_type_enum group_type;
	osm_cc_profiles_conf_t* vl_to_profiles[IB_MAX_NUM_VLS];
} osm_cc_vl_conf_t;

void osm_cc_mgr_construct(IN osm_cc_mgr_t * p_mgr);

void osm_cc_mgr_destroy(IN osm_cc_mgr_t * p_mgr);

struct osm_opensm;

int osm_congestion_control_setup(struct osm_opensm *osm);

int osm_congestion_control_wait_pending_transactions(struct osm_opensm *osm);

ib_api_status_t osm_congestion_control_init(osm_congestion_control_t * p_cc,
					    struct osm_opensm *osm,
					    const osm_subn_opt_t * p_opt);

ib_api_status_t osm_congestion_control_bind(osm_congestion_control_t * p_cc,
					    ib_net64_t port_guid);

void osm_congestion_control_invalidate(osm_congestion_control_t * p_cc);

void osm_congestion_control_shutdown(osm_congestion_control_t * p_cc);

void osm_congestion_control_destroy(osm_congestion_control_t * p_cc);


#endif				/* ifndef OSM_CONGESTION_CONTROL_H */
