# -*- coding: UTF-8 -*-
# @file   recommend
# @author zh1995
# @date   17-5-15
# @brief
import MySQLdb
import redis


class Recommend(object):

    def __init__(self):
        self.db = MySQLdb.connect("localhost", "root", "123456", "lemo")
        self.cursor = self.db.cursor()

    def get_all_message_list(self):
        sql = "SELECT message_id, look_num, good_num, tag_id FROM tblMessage"
        self.cursor.execute(sql)
        res = self.cursor.fetchall()
        message_list = []
        for row in res:
            feature_dict = {
                "look_num": row[1],
                "good_num": row[2],
                "tag_id": row[3],
            }
            message_dict = {
                row[0]: feature_dict,
            }
            message_list.append(message_dict)
        return message_list

    def add_collect_num_to_message_list(self, message_list):
        new_message_list = []
        for dict in message_list:
            for mid in dict:
                sql = "SELECT count(1) FROM tblUserMessageActionMap WHERE message_id=" + str(mid) + " AND status=1 AND user_action=2 "
                self.cursor.execute(sql)
                res = self.cursor.fetchone()
                feature_dict = dict[mid]
                feature_dict["collect_num"] = res[0]
                message_dict = {
                    mid: feature_dict,
                }
                new_message_list.append(message_dict)
        return new_message_list

    def calculate_all_message_weight(self, message_list):
        message_weight_dict = {}
        for dict in message_list:
            for mid in dict:
                tag_score = 0
                if dict[mid]["tag_id"] is 1:
                    tag_score = 1
                elif dict[mid]["tag_id"] is 2:
                    tag_score = 3
                elif dict[mid]["tag_id"] is 3:
                    tag_score = 1
                elif dict[mid]["tag_id"] is 4:
                    tag_score = 2
                elif dict[mid]["tag_id"] is 5:
                    tag_score = 1
                elif dict[mid]["tag_id"] is 6:
                    tag_score = 2
                weight = tag_score * 0.2 + dict[mid]["look_num"] * 0.1 + dict[mid]["collect_num"] * 0.3 + dict[mid]["good_num"] * 0.4
                message_weight_dict[mid] = weight
        return message_weight_dict

    def get_mid_list(self, message_weight_dict):
        mid_list = []
        for dict in message_weight_dict:
            mid_list.append(dict[0])
        return mid_list

# 数据库操作，获取推荐的文章列表
recommend_obj = Recommend()
message_list = recommend_obj.get_all_message_list()
message_list = recommend_obj.add_collect_num_to_message_list(message_list)
message_weight_dict = recommend_obj.calculate_all_message_weight(message_list)
message_weight_dict = sorted(message_weight_dict.iteritems(), key=lambda val: val[1], reverse=True)
mid_list = recommend_obj.get_mid_list(message_weight_dict)

# redis操作，缓存推荐文章ID列表
pool = redis.ConnectionPool(host="127.0.0.1", port=6379, db=0)
r = redis.StrictRedis(connection_pool=pool)
key_name = "recommend_mid_list"
if r.exists(key_name):
    r.delete(key_name)
for mid in mid_list:
    r.lpush(key_name, mid)
r.expire(key_name, 3600)

print "done\n"

