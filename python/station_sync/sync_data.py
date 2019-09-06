# coding = utf-8
import re
import json
import pymysql
import requests
from datetime import datetime
import time
API_HOST = 'http://202.201.1.136:8000'


#################################################################
################改变属性名为当前web中的标准名字##################
#################################################################

#对有规律的字段自动分析
RENAME_HANDLERS = {
    'Ta_':['air_temperature_','Ta_2_1_1_(\d+)_','Ta_(\d+)m_Avg'],
    'RH_':['air_humidity_','RH_19_3_1_(\d+)_','RH_(\d+)m_Avg'],
    'WS_':['air_wind_speed_','WS_16_33_1_(\d+)_' ,'WS_(\d+)'],
    'WD_':['air_wind_direction_','WD_16_33_1_(\d+)_' ,'WD_(\d+)'],
    'SWP':['soil_water_potential_','SWP_1_(\d+)_','SWP_4_41_1_(\d+)_'],
    'SWC':['soil_water_content_','SWC_11_36_1_(\d+)_','SWC_1_(\d+)_'],
    'TS_':['soil_temperature_','TS_2_38_1_(\d+)_','TS_1_(\d+)_'],
    'EC_':['soil_elec_rate_','EC_99_99_1_(\d+)_','EC_1_(\d+)']
}
#对无规律的字段一一映射名字
TABLE_NAME_DICT = {
    'TmStamp': 'timestamp',
    'P_Avg': 'air_pressure',
    'Par_Avg': 'photo_active_radiation',
    'CNR4_short_down_Avg': 'photo_downward_short_radiation',
    'CNR4_short_up_Avg': 'photo_upward_short_radiation',
    'CNR4_long_down_corr_Avg': 'photo_downward_long_radiation',
    'CNR4_long_up_corr_Avg': 'photo_upward_long_radiation',
    'Sun_time_1_1_1_Tot': 'photo_sunshine_hours',
    'SHF_1_1_1_Avg': 'soil_heat_flux_5',
    'SHF_1_1_2_Avg': 'soil_heat_flux_10',
    'Rain_Tot': 'air_rainfall',
    'TargTempC_Avg': 'photo_infrared_temperature',
}


def auto_change_filed_name(origin_str,prefix_str,pattern1,pattern2):
    result = re.compile(pattern1).search(origin_str) or re.compile(pattern2).search(origin_str)
    if result:
        return prefix_str + result.group(1)
    else:
        return None



##################################################
#                  Public Utils                  #
##################################################

# Get Database Connection
def get_db_conn():
    try:
        server = 'localhost'
        db_name = 'station'
        db_user = 'lndb'
        db_password = 'lndb'
        conn = pymysql.connect(server, db_user, db_password, db_name)
        return conn
    except Exception as e:
        print('[Error] Failed to get database connection. Reason:', e)
        return None

# Get Table List
def get_table_list(type='10'):
    conn = get_db_conn()
    cursor = conn.cursor()
    cursor.execute("show tables")
    rows = cursor.fetchall()
    ret_list = []
    for row in rows:
        if 'MIN' in row[0] and 'arch' not in row[0] and type in row[0]:
            ret_list.append(row[0])
    cursor.close()
    conn.close()
    return ret_list

# get_data dict
def get_table_data_dict(table,alldata):
    conn = get_db_conn()
    cursor = conn.cursor()
    cursor.execute("describe "+table)
    cols = cursor.fetchall()
    col_box = []
    ret_dict = {}
    for col in cols:
        col_box.append(col[0])
    for col in col_box:
        if alldata: 
            cursor.execute("Select  " + col + "  FROM " + table)
        else:
            cursor.execute("Select " + col + "  FROM " +table + " order by RecNum desc limit 1")
        rows = cursor.fetchall()
        ret_dict[col] = []
        for row in rows:
            ret_dict[col].append(row[0])
    renamed_ret_dict = {}
    for k, v in ret_dict.items():
        if k in TABLE_NAME_DICT:
            renamed_ret_dict[TABLE_NAME_DICT[k]] = v
        else:
            r=re.compile("[TRWSTE][aHSDWSC][_PC]")
            re_ret=r.search(k)
            if re_ret:
                chk = auto_change_filed_name(k,RENAME_HANDLERS[re_ret.group(0)][0],RENAME_HANDLERS[re_ret.group(0)][1],RENAME_HANDLERS[re_ret.group(0)][2])
                if chk:
                    renamed_ret_dict[chk] = v
    return renamed_ret_dict

###################################################
#                    SDK Utils                    #
###################################################
def get_user_key(username, password):
    post_data={
            'username':username,
            'password':password
            }
    response= requests.post(API_HOST + '/api/v1/user/login', data=post_data)
    response.encoding="utf-8"
    ret=response.json();
    if ret["status"]:
        return ret["key"]
    else:
        print("Error! login failed, reason is:", ret["error"])
        return None

# Add Site
def add_station(site_name, administrator, school, address, chinese_name, longitude, latitude, collector_number,key):
    post_data = {
        'site_name': site_name,
        'administrator': administrator,
        'school': school,
        'address': address,
        'status': 1,
        'chinese_name': chinese_name,
        'longitude': longitude,
        'latitude': latitude,
        'collector_number': collector_number,
        'key': key
    }
    req = requests.post(API_HOST + '/api/v1/site/add', data=post_data)
    ret = json.loads(req.content.decode("utf-8"))
    if ret['status']:
        return True
    else:
        print('[Error] Failed to add station , reason:', ret['error'])
        return False

def get_station_list(key):
    parameters={'key':key}
    response=requests.get(API_HOST+"/api/v1/user/station/get",parameters)
    response.encoding="utf-8"
    ret=response.json()
    if ret["status"]:
        return ret["data"]
    else :
        print("Error! get station list failed, reason is:", ret["error"])
        return None


def judge_station_existed(station_list, station):
    if station in station_list:
        return True
    else:
        return False


# Report Data by Minute
def report_data(json_data, key, url):
    req = requests.post(url, params={'key':key},json=json_data)
    req.encoding="utf-8"
    ret = req.json()
    if ret['status']:
        return True
    else:
        print('[Error] Failed to report data, reason:', ret['error'])
        return False

###################################################
#                 Data Collectors                 #
###################################################

def handle_day(all_data,key):
    tables_day = get_table_list(type='1440')
    for table in tables_day:
        name = table.split('_MIN_')[0].replace('-AWS', '')
        table_info_dict = get_table_data_dict(table,all_data)
        length = len(table_info_dict['timestamp'])
        send_json_box = []
        for i in range(0, length):
            item = {}
            for k in table_info_dict.keys():
                item[k] = table_info_dict[k][i]
            item['site_name'] = name
            item['timestamp'] = item['timestamp'].strftime('%Y-%m-%d %H:%M')
            send_json_box.append(item)
        send_json_dict={'data':send_json_box}
        report_data(send_json_dict, key, API_HOST + '/api/v1/data/station/transfer_daydata')

def handle_minute(all_data, key):
    tables_10 = get_table_list()
    for table in tables_10:
        station_name = table.split('_MIN_')[0].replace('-AWS', '')
        table_info_dict = get_table_data_dict(table,all_data)
        length = len(table_info_dict['timestamp'])
        send_json_dict = {}
        send_json_dict['site_name'] = station_name
        send_json_dict['data'] = []
        for i in range(0, length):
            item = {}
            for k in table_info_dict.keys():
                item[k] = table_info_dict[k][i]
            item['timestamp'] = item['timestamp'].strftime('%Y-%m-%d %H:%M')
            send_json_dict['data'].append(item)
        report_data(send_json_dict, key, API_HOST + '/api/v1/data/station/transfer_mindata')

#############################################################################
if __name__ == '__main__':
    user_key=get_user_key("walcheng","123456")
    if not judge_station_existed(get_station_list(user_key),{"chinese_name":"胡杨楼站","name":"hylz"}):
        if not add_station("hylz","dslab","lzu","none","胡杨楼站","36.0510793966","103.8689573922","0001",user_key):
            pass  
    handle_minute(True,user_key)
    handle_day(False,user_key)
    # count=0
    # while True:
        # time.sleep(600)
        # handle_minute(False,user_key)
        # count+=1
        # if count==144:
            # handle_day()
            # count=0

    
    

