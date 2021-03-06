/*
 * Copyright (c) 2010-2020 Mellanox Technologies LTD. All rights reserved.
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



#ifndef AR_MGR_H_
#define AR_MGR_H_

/* osm_config.h needs to be before all other includes */
#include <opensm/osm_config.h>
#include <typeinfo>
#include <string>
#include <stack>
using namespace std;

#include <opensm/osm_opensm.h>
#include <opensm/osm_helper.h>
#include <opensm/osm_log.h>
#include <opensm/osm_event_plugin.h>
#include <vendor/osm_vendor_api.h>


#include "opensm/osm_armgr_types.hpp"
using namespace OSM;

namespace OSM {
	class AdaptiveRoutingAlgorithm;
	class PlftBasedArAlgorithm;
    class ArKdorAlgorithm;
}

#include "opensm/osm_parallel_port_groups_calculator.hpp"
typedef vector <bool> BoolVec;
typedef map <u_int64_t, u_int16_t> GuidToGroupMap;
typedef GuidToGroupMap::iterator GuidToGroupMapIter;

struct AnalizeDFSetupData {
	stack <ARSWDataBaseEntry*> m_group_stack;
	SwDbEntryPrtList m_spines;
	SwDbEntryPrtList m_leafs;

	u_int16_t hca_to_sw_lid_mapping[IB_LID_UCAST_END_HO + 1];
	DfSwData* sw_lid_to_df_data_mapping[IB_LID_UCAST_END_HO + 1];

	AnalizeDFSetupData() {
		memset(hca_to_sw_lid_mapping, 0, sizeof(hca_to_sw_lid_mapping));
		memset(sw_lid_to_df_data_mapping, 0, sizeof(sw_lid_to_df_data_mapping));
	}
};

/* ============================================================================ */
class OSMAdaptiveRoutingManager {
public:
    /*
     * Methods
     */

    /**
     * Constructor OSMAdaptiveRoutingManager
     *
     * @param p_osm pointer to OpenSM structure
     */
    OSMAdaptiveRoutingManager(osm_opensm_t *p_osm,
                              ar_algorithm_t ar_algorithm);

    /**
     *  Destructor OSMAdaptiveRoutingManager
     */
    ~OSMAdaptiveRoutingManager();

    /**
     * Update fabric nodes. Update node info for all nodes
     *
     * @return int 0 if succeeded, otherwise 1
     */
    void UpdateFabricSwitches();

    /**
     * Construct and Init AdaptiveRoutingManager inner data structures
     *
     * @return int return 1 is succeeded, otherwise 0
     */
    int Construct();
    
    /**
     * Run an adaptive routing manager preprocessing phase
     *
     * @return int return 1 is succeeded, otherwise 0
     */
    int Preprocess();

    /**
     * Configure all nodes that support adaptive routing in the
     * fabric with adaptive routing parameters with user defined
     * parameters or default if none where given.
     *
     * @return int return 1 is succeeded, otherwise 0
     */
    int Route();

    /**
     * Calculate adaptive routing settings according to fat tree algorithm 
     * for the given sw_db_entry 
     */
    void ARCalculateSwitchPortGroupsTree(
        ARSWDataBaseEntry &sw_db_entry,
        uint8_t max_rank,
        u_int16_t *hca_to_sw_lid_mapping,
        uint8_t *sw_lid_to_rank_mapping);

    /**
     * Get SL to VL mapping for certain port
     *
     * @param osm_phys_port the port
     * @param iport_num the in port of the traffic
     * @param oport_num the out port of the traffic
     * @param sl2vl pointer to an array for mapping sl to vl
     */
    int GetSL2VL(osm_physp_t *osm_phys_port, uint8_t iport_num, uint8_t oport_num,
		 uint8_t (*sl2vl)[IB_NUMBER_OF_SLS]);
    /**
     * Dump the switch adaptive routing settings
     *
     * @param sw_db_entry the entry of the switch in the db
     */
    void ARDumpSWSettings(ARSWDataBaseEntry &sw_db_entry);

    /**
     * Print Exception
     *
     * @param e exception
     * @param p_osm_log log file
     */
    static void printException(exception& e, osm_log_t * p_osm_log) {
        string e_what(e.what( ));
        string e_type(typeid(e).name( ));
        OSM_LOG(p_osm_log, OSM_LOG_ERROR,
                "AR_MGR - caught an exception: %s. Type: %s\n",
                e_what.c_str(), e_type.c_str());
    }

    /**
     * Decide if two adaptive_routing_info structs are equal or not
     *
     * @param p_ar_info1 struct one to compare
     * @param p_ar_info2 struct two to compare
     * @param ignoreE if true, do not compare E attribute
     *
     * @return true if equal or false otherwise
     */
    static bool IsEqualSMPARInfo(ib_ar_info_t *p_ar_info1, ib_ar_info_t *p_ar_info2,
                                 bool ignoreE, bool ignoreTop);

	void UpdateCalculatedArGroupTable(osm_ar_subgroup_t *p_subgroup,
					 uint16_t group_number,
					 PortsBitset &group_bitmask,
					 unsigned &calculated_max_pg_id);
private:
    /*
     * members
     */
    osm_opensm_t                    *m_p_osm;               /** Pointer to osm opensm struct */
    osm_vendor_t                    *m_p_osm_vendor;        /** Pointer to osm vendor struct */
    osm_subn_t                      *m_p_osm_subn;          /** Pointer to osm subnet struct */
    osm_log_t                       *m_p_osm_log;           /** Pointer to osm log */

    OSMThreadPool                   m_thread_pool;
    OSMParallelPortGroupsCalculator m_port_groups_calculator;

    struct ARSWDataBase             m_sw_db;                /** Switchs database */
    struct MasterDataBase           m_master_db;            /** Master settings database */

    string                          m_conf_file_name;       /** Name of user input file */

    struct timeval                  *m_p_error_window_arr;  /** Error window array */

    bool                            m_is_permanent_error;   /** Indicates permanent error occurred
                                                                                 * (will not be solved after heavy sweep) */
    bool                            m_is_temporary_error;   /** Indicates temporary error occurred
                                                                                 * (will be solved after heavy sweep) */

    bool                            m_df_configured;        /** If true should remove df configuration
                                                             * if protocol is not DF PLUS*/
    AdaptiveRoutingAlgorithm       *m_ar_algorithm;         /** Pointer to topology specific algorithm */


    bool                            m_sw_info_configured;  /** If true should remove sw info configuration
                                                             * if protocol is not DF PLUS*/

    uint16_t                        m_max_df_group_number;
    GuidToGroupMap                  m_guid_to_dfp_group;
    bool                            m_group_discovered;

    uint32_t                        m_options_file_crc;

    bool                            m_is_init;

    /*
     * Methods
     */

    /**
     * Reset error window mechanism. Remove old errors
     */
    void ResetErrorWindow();

    /**
     * Set default configuration values
     */
    void SetDefaultConfParams();

    /**
     * Take the configuration values that have been parsed
     */
    void TakeParsedConfParams();

    /**
     * Check if file exists and have permissions
     *
     * @return true if exists, otherwise false
     */
    bool IsFileExists(const char *file_name);

    /**
     * Merge between default settings and user option settings
     */
    void UpdateUserOptions();

    /**
     * Check if more than m_max_errors occurred during the
     *  last m_error_window. If so, throw an exception
     *
     * @throw Throws int when condition holds
     *
     * @param rc return value that indicates if an error has occurred
     */
    void CheckRC(int& rc);

    /**
     * Parse OSM parameters for cc_mgr conf file
     *
     * @param osm_params
     */
    void ParseConfFileName(char* osm_plugin_options);

    /**
     * Initialize objects.
     * Bind port to AR mads
     *
     * @return int 0 if succeeded, otherwise throw exception with int 1
     */
    int Init();

    /**
     * Check if device id is supported.
     *
     * @param node_info node info holds device id
     *
     * @return bool true if supported, otherwise false
     */
    bool IsDeviceIDSupported(const ARGeneralSWInfo& general_sw_info);

    /**
     * Update Switch from sm database to local database
     *
     * @param node_info node info
     *
     * @return int 0 if succeeded, otherwise 1
     */
    void UpdateSW(const ARGeneralSWInfo& general_sw_info);

    /**
     * Add switches that don't exist ar_mgr from osm database
     *  and update all switches in ar_mgr

     */
    void AddNewAndUpdateExistSwitches();

    /**
     * Remove switches that don't exist in m_p_osm_subn
     *  from ar_mgr database
     */
    void RemoveAbsentSwitches();

    /**
     * Mark switch as not supports for feature for all future cycles
     *
     * @param sw_db_entry the entry of the switch in the db
     * @param feature [AR|DF|RN]
     * @param type the reason that this switch is marked as not supports
     */
    //void MarkSWNotSupport(ARSWDataBaseEntry &sw_db_entry,
    //                      supported_feature_t feature,
    //                      support_errs_t type);
    /**
     * Check if switch supports for feature
     *
     * @param sw_db_entry the entry of the switch in the db
     * @param feature [AR|DF|RN]
     * @return true if supported or false otherwise
     */
    //bool IsNotSupported(ARSWDataBaseEntry &sw_db_entry,
    //                    supported_feature_t feature);

    /**
     * Mark switch as not supports for adaptive routing for all future cycles
     *
     * @param sw_db_entry the entry of the switch in the db
     * @param type the reason that this switch is marked as not supports
     */
    void MarkSWNotSupportAR(ARSWDataBaseEntry &sw_db_entry,
            support_errs_t type);

    /**
     * Check if switch supports for adaptive routing
     *
     * @param sw_db_entry the entry of the switch in the db
     *
     * @return true if supported or false otherwise
     */
    bool IsARNotSupported(ARSWDataBaseEntry &sw_db_entry);

    /**
     * Mark switch as supports for adaptive routing
     *
     * @param sw_db_entry the entry of the switch in the db
     */
    void MarkSWSupportAR(ARSWDataBaseEntry &sw_db_entry);

    /**
     * Check if adaptive routing is active in a switch (both support and enable)
     *
     * @param sw_db_entry the entry of the switch in the db
     *
     * @return true if active or false otherwise
     */
    bool IsARActive(ARSWDataBaseEntry &sw_db_entry);

    /**
     * Check if Dragonfly is active in a switch (both support and AR
     * enable)
     *
     * @param sw_db_entry the entry of the switch in the db
     *
     * @return true if active or false otherwise
     */
    bool IsDFActive(ARSWDataBaseEntry &sw_db_entry);

    /**
     * Mark all switch as supports / not supports adaptive routing
     *
     * @return number of unsupportes switches
     *
     */
    int ARInfoGetProcess();

    /**
     * Set Required ARInfo R/W values for all supportes switches
     *
     */
    void SetRequiredARInfo(ARSWDataBaseEntry &db_entry);
    /**
     * Get calculated GroupCap from all supportes switches
     *
     * @return number of unsupportes switches
     *
     */
    int  ARInfoGetGroupCapProcess();

    /**
     *  Configure ARInfo on needed ones
     *
     * @return number of unsupportes switches
     *
     */
    int ARInfoSetProcess();

    /**
     *  Configure RoutingNotification tree settings on needed
     *  switches
     *
     *
     */
    void TreeRoutingNotificationProcess();

    /**
     * Update DB used to copy a single group to moltiple
     * groups
     *
     * @param sw_db_entry the entry of the switch in the db
     * @param assign_groups the calculated GroupsList object
     */
    void ARUpdateSWGroupToCopy(
        ARSWDataBaseEntry &sw_db_entry,
        GroupsList &assign_groups);

    /**
     * Update update a single GroupElement in the switch group table
     *
     * @param sw_db_entry the entry of the switch in the db
     * @param calculated_element the calculated group element
     * @param group_number the calculated group number
     */
    void ARUpdateSWGroupElement(
        ARSWDataBaseEntry &sw_db_entry,
        osm_ar_subgroup_t &calculated_element,
        u_int16_t group_number);

    /**
     * Update the switch group table top with the calculated one
     *
     * @param sw_db_entry the entry of the switch in the db
     * @param calculated_groups_number total groups number in the calculated table
     */
    void ARUpdateSWGroupTableTop(ARSWDataBaseEntry &sw_db_entry,
            u_int16_t calculated_groups_number);

    /**
     * Update the switch lft table with the calculated one
     *
     * @param sw_db_entry the entry of the switch in the db
     * @param p_ar_calculated_lft_table the calculated lft table
     * @param calculated_max_lid the last lid that is valid in the calculated table
     */
    void ARUpdateSWLFTTable(ARSWDataBaseEntry &sw_db_entry,
            struct SMP_ARLinearForwardingTable p_ar_calculated_lft_table[],
            u_int16_t calculated_max_lid);

    /**
     * Update the SX switch lft table with the calculated one
     *
     * @param sw_db_entry the entry of the switch in the db
     * @param p_ar_calculated_lft_table the calculated lft table
     * @param calculated_max_lid the last lid that is valid in the calculated table
     */
    void ARUpdateSWLFTTable(ARSWDataBaseEntry &sw_db_entry,
            struct SMP_ARLinearForwardingTable_SX p_ar_calculated_lft_table[],
            u_int16_t calculated_max_lid);

    void UpdateRNRcvString(ARSWDataBaseEntry &sw_db_entry,
                           uint8_t max_rank,
                           uint8_t sw_rank,
                           uint8_t max_consume_rank);

    void UpdateRNXmitPortMask(
            ARSWDataBaseEntry &sw_db_entry,
            PortsBitset &ca_ports,
            PortsBitset &sw_ports,
            bool is_down_sw);

    /**
     * Calculate adaptive routing settings according to parallel links algorithm
     */
    void ARCalculatePortGroupsParallelLinks();

    /**
     * Calculate adaptive routing settings according to fat tree algorithm
     */
    void ARCalculatePortGroupsTree();

    /**
     * Update data structures on adding new lid to AR groups
     */
    void AddLidToARGroup(uint16_t lid_num, uint16_t sw_lid_num,
                         GroupData* p_group_data,
                         TreeAlgorithmData &algorithm_data,
                         bool is_new_group,
                         bool is_group_per_leaf_sw);

    /**
     * Print the given group_data object to log file
     */
    void PrintGroupData(const char * str, GroupData &group_data);

    /**
     * Assign group number and table number to discovered groups
     */
    int AssignPortGroups(ARSWDataBaseEntry &sw_db_entry, TreeAlgorithmData &algorithm_data);

    int AssignPerLeafSwitchGroups(ARSWDataBaseEntry &sw_db_entry,
                                  TreeAlgorithmData &algorithm_data);

    int GetContainedGroupList(GroupsList& group_list, PortsBitset &group_bitmask, GroupsList& contained_group_list, PortsBitset &total_bitmask);

    /**
     * Get GroupList ordered by group size ad lids number
     */
    int GetOrderedGroupList(TreeAlgorithmData &algorithm_data, GroupsList& group_list);

    void ARCopyGroupTableProcess();

    /**
     * Run an adaptive routing cycle on all switches
     */
    int ARCycle();

    /**
     * Mark all switch flags for osm
     *  Some switches were configured with adaptive routing and some need to
     *  be configured with osm with ucast lft table
     */
    void AROSMIntegrationProcess();

    /**
     * Map CAs lids to connected SW lid
     *
     * @param hca_to_sw_lid_mapping
     */
     int SetHcaToSwLidMapping(osm_physp_t *p_hca_physp,
                             osm_node_t *p_remote_sw_node,
                             u_int16_t *hca_to_sw_lid_mapping );

    //The allocation of group number to leaf sw is saved
    //after the first allocation
    u_int16_t AllocateSwArGroup(uint16_t sw_lid, uint16_t group_cap);

    /** ----------  DRAGON FLY PLUS ---------- */

    /**
     * Run DragonFly routing cycle on all switches
     *
     * @return non zero on failure
     */
    int ARDragonFlyCycle();

    void ARDragonFlyCycleEnd(int rc);

    void ClearAllDragonflyConfiguration();

    /**
     * Init DragonFlyPlus Data structures on cycle begining
     *
     * @return non zero on failure
     */
    int InitDragonFlyPlus(AnalizeDFSetupData &setup_data);

    /**
     * Set SUPPORT_DF bit for all switches on fabric that are
     * DragonFlyPlusCapable
     *
     * @return true if the fabric is DragonFlyPlusCapable
     */
    bool SetDragonFlyPlusCapable();

    /**
     * Set required PLFT Info 
     * Checks if can support the rquirements.
     *
     * @return false if switch doesn't support the requirements for PLFT
     * true if does support.
     */
    bool SetRequiredPLFTInfo(ARSWDataBaseEntry *p_sw_entry);

    /**
     * Helper function for AnalizeDragonFlyPlusSetup
     *
     * @return non zero on failure
     */
    int MarkLeafsByCasNumber(AnalizeDFSetupData &setup_data,
                             SwDbEntryPrtList &leafs_list);

    int MarkLeafsByGroupsNumber(AnalizeDFSetupData &setup_data,
                                SwDbEntryPrtList &leafs_list);

    void SetGroupNumber(ARSWDataBaseEntry* p_sw_entry, u_int16_t group_number);

    int SetPrevGroupNumber(ARSWDataBaseEntry* p_sw_entry,
                           BoolVec &used_group_numbers);

    int DiscoverGroups(AnalizeDFSetupData &setup_data,
                       SwDbEntryPrtList &leafs_list,
                       BoolVec &used_group_numbers,
                       int cycle = 1);


    /**
     * Helper function for AnalizeDragonFlyPlusSetup update
     * m_up_ports and m_down_ports data structures
     *
     * @return non zero on failure
     */
    int SetPortsDirection();

    /**
     * Update SM osm_switch_t struct rank and coord values
     *
     */
    void UpdateSmDbSwInfo();

    /**
     * Helper function for AnalizeDragonFlyPlusSetup
     *
     * @return non zero on failure
     */
    int DiscoverLeaf(
        AnalizeDFSetupData &setup_data,
        ARSWDataBaseEntry* p_db_entry);

    /**
     * Helper function for AnalizeDragonFlyPlusSetup
     *
     * @return non zero on failure
     */
    int DiscoverSpine(
        AnalizeDFSetupData &setup_data,
        ARSWDataBaseEntry* p_db_entry);

    /**
     * Helper function for AnalizeDragonFlyPlusSetup
     *
     * @return non zero on failure
     */
    int SetLeaf(
        AnalizeDFSetupData &setup_data,
        SwDbEntryPrtList &leafs_list,
        osm_node_t *p_nod);

    /*
    int SetLeaf(
        AnalizeDFSetupData &setup_data,
        osm_node_t *p_node,
        osm_physp_t *p_physp,
        bool from_down);
        */

    /**
     * Helper function for AnalizeDragonFlyPlusSetup
     *
     * @return non zero on failure
     */
    int SetSpine(
        AnalizeDFSetupData &setup_data,
        osm_node_t *p_nod);

    /*
    int SetSpine(
        AnalizeDFSetupData &setup_data,
        osm_node_t *p_node,
        osm_physp_t *p_physp,
        bool from_down);
        */

    /**
     * Helper function for AnalizeDragonFlyPlusSetup
     *
     * @return non zero on failure
     */
    //int HandleLeafsWithoutHosts(AnalizeDFSetupData &setup_data,
    //                            int &max_group_number);

    /**
     * Analize Dragon Fly Plus Setup
     * Set SW type to LEAF or SPINE
     * Set ports as up or down ports
     * @param [out] setup_data
     *
     * @return non zero on failure
     */
    int AnalizeDragonFlyPlusSetup(AnalizeDFSetupData &setup_data);

    /** Helper method for ARCalculatePortGroupsDF*/
    void SavePortGroupsAndDump();

    void ARCalculatePortGroupsDFCleanup();

    int ARCalculatePLFTPortGroups(
        PathDescription paths_description[DLID_LOCATION_NUMBER][PATHS_NUMBER],
        bool enforce_complete_route,
        list <ARSWDataBaseEntry*> &switches,
        int plft_id,
        AnalizeDFSetupData &setup_data);

    void PrintPSGroupData(const char * str,PSGroupData &group_data);

    bool IsRemoteSupportsDF(ARSWDataBaseEntry &sw_db_entry, u_int8_t port_num);

    bool IsRouteOnRemote(ARSWDataBaseEntry &sw_db_entry,
            int plft_id, u_int8_t port_num, uint16_t lid_num);

    bool IsTrueHopsOnRemote(ARSWDataBaseEntry &sw_db_entry,
            u_int8_t port_num, uint16_t lid_num, int hops_num);

    void ClearNoValidDFRouteToLid(ARSWDataBaseEntry &sw_db_entry,
            int plft_id)
    {
        sw_db_entry.m_p_df_data->m_plft[plft_id].m_no_df_valid_route.clear();
    }

    void SetNoValidDFRouteToLid(ARSWDataBaseEntry &sw_db_entry,
            int plft_id, uint16_t lid_num)
    {
        sw_db_entry.m_p_df_data->m_plft[plft_id].m_no_df_valid_route.insert(lid_num);
    }

    /*
    void ARUpdateDFGroupTable(ARSWDataBaseEntry &sw_db_entry,
            int plft_id);

    void ARUpdateDFGroupTable(ARSWDataBaseEntry &sw_db_entry,
            struct SMP_ARGroupTable p_ar_calculated_group_table[],
            u_int16_t calculated_max_group_id,
            int plft_id);
            */

    void ARUpdateDFLFTTable(ARSWDataBaseEntry &sw_db_entry,
            struct SMP_ARLinearForwardingTable_SX p_ar_calculated_lft_table[],
            u_int16_t calculated_max_lid,
            int plft_id);

    void ARDumpDFAnalizedSetup();

    //num_ports - num of phys ports, ports number not including port 0
    u_int8_t GetNextStaticPort(
            uint16_t *ports_load,
            PSPortsBitset &ps_group_bitmask,
            bool isHCA,
            u_int8_t num_ports);

    /**
     * Calculate adaptive routing settings according to Dragon Flay algorithm
     */
    int ARCalculatePortGroupsDF(AnalizeDFSetupData &setup_data);

    /**Set Private LFTs and VL2VL Mapping on the switch*/
    int ARMapPLFTsAndSetSL2VLAct();

    /**Set SL2VL definition on the hosts CAs */
    void ARMapSL2VLOnHosts();

    /**Set VL2VL definition on the switch*/
    void ARMapVL2VL(ARSWDataBaseEntry &sw_db_entry,
                    u_int8_t port_x);

    /** 
     * Helper for ARMapVL2VL get op_vl
     * validate that op_vl >1 or that out port is not switch
     * else return non zero to indicate not to set SL2VL
     */
    int GetOpVlForVL2VL(ARSWDataBaseEntry &sw_db_entry,
			osm_physp_t *p_physp,
			u_int8_t out_port,
			u_int8_t min_op_vls,
			u_int8_t &op_vls);

    /**Set Private LFTs definition on the switch*/
    int ARDefinePLFTs();

    /**Map in port/VL to PLFT*/
    void ARMapPLFTs(ARSWDataBaseEntry &sw_db_entry,
                    u_int8_t port_block);

    /*
     * Wait for pending transactions.
     */
    void WaitForPendingTransactions();

    /*
     * Validate switches capabilities.
     */
    int ValidateSwitchesCapabilites();

    /**
     * Get SL to VL mapping for certain port on DFP setup
     *
     * @param osm_phys_port the port
     * @param iport_num the in port of the traffic
     * @param oport_num the out port of the traffic
     * @param sl2vl pointer to an array for mapping sl to vl
     */
    int GetSL2VLDF(osm_physp_t *osm_phys_port, uint8_t iport_num, uint8_t oport_num,
		   uint8_t (*sl2vl)[IB_NUMBER_OF_SLS]);


    friend class OSM::AdaptiveRoutingAlgorithm;
    friend class OSM::PlftBasedArAlgorithm;
    friend class OSM::ArKdorAlgorithm;
};


#endif          /* AR_MGR_H_ */

