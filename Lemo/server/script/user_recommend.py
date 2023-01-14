# -*- coding: UTF-8 -*-
# @file   recommend
# @author zh1995
# @date   17-5-15
# @brief
import MySQLdb
import redis


class UserRecommend(object):

    def __init__(self):
        self.db = MySQLdb.connect("localhost", "root", "123456", "lemo")
        self.cursor = self.db.cursor()

    def get_all_mid_list(self):
        sql = "SELECT message_id FROM tblMessage"
        self.cursor.execute(sql)
        res = self.cursor.fetchall()
        mid_list = []
        for row in res:
            mid_list.append(row[0])
        return mid_list

    def get_all_uid_list(self):
        sql = "SELECT uid FROM tblUser"
        self.cursor.execute(sql)
        res = self.cursor.fetchall()
        uid_list = []
        for row in res:
            uid_list.append(row[0])
        return uid_list

    def get_mid_user_dict(self, mid_list):
        mid_user_dict = {}
        for mid in mid_list:
            sql = "SELECT DISTINCT uid FROM tblUserMessageActionMap WHERE message_id=" + str(mid) + " AND status=1"
            self.cursor.execute(sql)
            res = self.cursor.fetchall()
            uid_list = []
            for row in res:
                uid_list.append(row[0])
            if len(uid_list) is not 0:
                mid_user_dict[mid] = uid_list
        return mid_user_dict

    def get_uid_mid_dict(self, uid_list):
        uid_mid_dict = {}
        for uid in uid_list:
            sql = "SELECT DISTINCT message_id FROM tblUserMessageActionMap WHERE uid=" + str(uid) + " AND status=1"
            self.cursor.execute(sql)
            res = self.cursor.fetchall()
            mid_list = []
            for row in res:
                mid_list.append(row[0])
            if len(mid_list) is not 0:
                uid_mid_dict[uid] = mid_list
        return uid_mid_dict

# 数据库操作，获取推荐的文章列表
recommend_obj = UserRecommend()
# 找文章下所有有交互的用户
mid_list = recommend_obj.get_all_mid_list()
mid_user_dict = recommend_obj.get_mid_user_dict(mid_list)

# 找每个用户有过交互的文章
uid_list = recommend_obj.get_all_uid_list()
uid_mid_dict = recommend_obj.get_uid_mid_dict(uid_list)


# redis操作，缓存基于用户推荐用到的信息
pool = redis.ConnectionPool(host="127.0.0.1", port=6379, db=0)
r = redis.StrictRedis(connection_pool=pool)

for uid in uid_mid_dict:
    key_name = "recommend_uid_" + str(uid)
    if r.exists(key_name):
        r.delete(key_name)
    for item in uid_mid_dict[uid]:
        r.lpush(key_name, item)
    r.expire(key_name, 3600)

for mid in mid_user_dict:
    key_name = "recommend_mid_" + str(mid)
    if r.exists(key_name):
        r.delete(key_name)
    for item in mid_user_dict[mid]:
        r.lpush(key_name, item)
    r.expire(key_name, 3600)
print "done\n"


