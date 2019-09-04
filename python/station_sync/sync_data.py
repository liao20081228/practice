# coding = utf-8
import re
import json
import pymysql
import requests
from datetime import datetime
import time
API_HOST = 'http://202.201.1.136:8000'
##########################################3

RENAME_HANDLERS = [
    'analysis_air_temperature',
    'analysis_air_humidity',
    'analysis_air_windspeed',
    'analysis_air_windspeed',
    'analysis_air_winddirection',
    'analysis_soil_waterpotential',
    'analysis_soil_watercontent',
    'analysis_soil_temperatrue',
    'analysis_soil_elecrate',
]

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
    'WS_4':'wind speed',
    'WD_4':'wind directtion'
}

##################################################
#                 Table Col Utils                #
##################################################

def analysis_air_temperature(str):
    r = re.compile('Ta_2_1_1_(.+)_')
    result = r.search(str)
    if result:
        return 'air_temperature_' + result[1]
    else:
        r = re.compile('Ta_(.+)_Avg')
        result = r.search(str)
        if result:
            return 'air_temperature_' + result[1].strip('m')
        else:
            return None

def analysis_air_humidity(str):
    r = re.compile('RH_19_3_1_(.+)_')
    result = r.search(str)
    if result:
        return 'air_humidity_' + result[1].strip('m')
    else:
        r = re.compile('RH_(.+)_Avg')
        result = r.search(str)
        if result:
            return 'air_humidity_' + result[1].strip('m')
        else:
            return None

def analysis_air_windspeed(str):
    r = re.compile('WS_16_33_1_(.+)_')
    result = r.search(str)
    if result:
        return 'air_wind_speed_' + result[1].strip('m')
    else:
        r = re.compile('WS_([0-9]+)')
        result = r.search(str)
        if result:
            return 'air_wind_speed_' + result[1].strip('m')
        else:
            return None

def analysis_air_winddirection(str):
    r = re.compile('WD_16_33_1_(.+)_')
    result = r.search(str)
    if result:
        return 'air_wind_direction_' + result[1].strip('m')
    else:
        r = re.compile('WD_(.+)')
        result = r.search(str)
        if result:
            return 'air_wind_direction_' + result[1].strip('m')
        else:
            return None

def analysis_soil_waterpotential(str):
    r = re.compile('SWP_1_([0-9]+)_')
    result = r.search(str)
    if result:
        return 'soil_water_potential_' + result[1].strip('m')
    else:
        r = re.compile('SWP_4_41_1_([0-9]+)_')
        result = r.search(str)
        if result:
            return 'soil_water_potential_' + result[1].strip('m')
        else:
            return None

def analysis_soil_watercontent(str):
    r = re.compile('SWC_11_36_1_(.+)_')
    result = r.search(str)
    if result:
        return 'soil_water_content_' + result[1].strip('m')
    else:
        r = re.compile('SWC_1_([0-9]+)_')
        result = r.search(str)
        if result:
            return 'soil_water_content_' + result[1].strip('m')
        else:
            return None

def analysis_soil_temperatrue(str):
    r = re.compile('TS_2_38_1_(.+)_')
    result = r.search(str)
    if result:
        return 'soil_temperature_' + result[1].strip('m')
    else:
        r = re.compile('TS_1_([0-9]+)_')
        result = r.search(str)
        if result:
            return 'soil_temperature_' + result[1].strip('m')
        else:
            return None

def analysis_soil_elecrate(str):
    r = re.compile('EC_99_99_1_(.+)_')
    result = r.search(str)
    if result:
        return 'soil_elec_rate_' + result[1].strip('m')
    else:
        r = re.compile('EC_1_([0-9]+)')
        result = r.search(str)
        if result:
            return 'soil_elec_rate_' + result[1].strip('m')
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
    print(ret_list,"\n")
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
    print(col_box,"\n")
    for col in col_box:
        if alldata: 
            cursor.execute("Select " + col + "  FROM " + table)
        else:
            cursor.execute("Select " + col + "  FROM " +table + "order by RecNum desc limit 1")
        rows = cursor.fetchall()
        print("rows  is :",rows,"\n")
        ret_dict[col] = []
        for row in rows:
            print("row is :",row,"\n")
            ret_dict[col].append(row[0])
    print(ret_dict,"\n")
    renamed_ret_dict = {}
    for k, v in ret_dict.items():
        if k in TABLE_NAME_DICT:
            renamed_ret_dict[TABLE_NAME_DICT[k]] = v
        # else:
            # for handler in RENAME_HANDLERS:
                # chk = eval(handler + '(k)')
                # if chk:
                    # renamed_ret_dict[chk] = v
    
    # break

    print(table, renamed_ret_dict,"\n")
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
def add_site(site_name, administrator, school, address, chinese_name, longitude, latitude, collector_number,key):
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
        print('[Error] Failed to report data, reason:', ret['error'])
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
def report_data_by_min(json_dict):
    post_data = {
        'json': json.dumps(json_dict),
        'key': API_KEY
    }

    req = requests.post(API_HOST + '/api/v1/data/station/transfer_mindata/', data=post_data)
    ret = json.loads(req.content.decode("utf-8"))
    if ret['status']:
        return True
    else:
        print('[Error] Failed to report data, reason:', ret['error'])
        return False

# Report Data by Day
def report_data_by_day(json_dict):
    post_data = {
        'json': json.dumps(json_dict),
        'key': API_KEY
    }
    req = requests.post(API_HOST + '/api/v1/data/station/transfer_daydata/', data=post_data)
    ret = json.loads(req.content.decode("utf-8"))
    if ret['status']:
        return True
    else:
        print('[Error] Failed to report data, reason:', ret['error'])
        return False

###################################################
#                 Data Collectors                 #
###################################################

def handle_day(all_data=False):
    tables_day = get_table_list(type='1440')
    print('[Info] day tables:', len(tables_day))
    for table in tables_day:
        site_name = table.split('_MIN_')[0].replace('-AWS', '')
        print('[Info] Handling Site:', site_name)
        table_info_dict = get_table_data_dict(table,all_data)
        length = len(table_info_dict['timestamp'])
        send_json_box = []
        for i in range(0, length):
            item = {}
            for k in table_info_dict.keys():
                item[k] = table_info_dict[k][i]
            item['site_name'] = site_name
            item['timestamp'] = item['timestamp'].strftime('%Y-%m-%d %H:%M')
            send_json_box.append(item)
        report_data_by_day(send_json_box)

def handle_minute(all_data=False):
    tables_10 = get_table_list()
    print('[Info] 10 minutes tables:', len(tables_10))
    for table in tables_10:
        site_name = table.split('_MIN_')[0].replace('-AWS', '')
        print('[Info] Handling Site:', site_name)
        table_info_dict = get_table_data_dict(table,all_data)
        length = len(table_info_dict['timestamp'])
        send_json_dict = {}
        send_json_dict['site_name'] = site_name
        send_json_dict['json_list'] = []
        for i in range(0, length):
            item = {}
            for k in table_info_dict.keys():
                item[k] = table_info_dict[k][i]
            item['timestamp'] = item['timestamp'].strftime('%Y-%m-%d %H:%M')
            send_json_dict['json_list'].append(item)
        report_data_by_min(send_json_dict)

if __name__ == '__main__':
    user_key=get_user_key("walcheng","123456")
    if not judge_station_existed(get_station_list(user_key),{"chinese_name":"胡杨楼站","name":"hylz"}):
        add_site()
    

    # handle_day(True)
    # handle_minute(True)
    # count=0
    # while True:
        # handle_minute()
        # time.sleep(600)
        # count+=1
        # if count==144:
            # handle_day()
            # count=0

    
    

