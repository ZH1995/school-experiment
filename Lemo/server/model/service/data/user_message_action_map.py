# -*- coding: UTF-8 -*-
# @file   collect_user_map
# @author zh1995
# @date   17-4-13
# @brief
import time
import datetime
from model.dao.sql_operation import SQL


class UserMessageActionMap(object):
    """
    用户-收藏关系类
    """
    def __init__(self):
        """
        初始化类
        """
        self._dao_sql = SQL()

    def get_online_id_by_uid_and_message_id(self, uid, message_id, user_action):
        """
        
        :param uid: 
        :param message_id: 
        :param user_action: 
        :return: 
        """
        sql_sentence = "SELECT id FROM tblUserMessageActionMap WHERE uid=%s AND message_id=%s AND user_action=%s AND status=1"
        param_list = (uid, message_id, user_action)
        return self._dao_sql.fetch_one(sql_sentence, param_list)

    def get_id_by_uid_and_message_id(self, uid, message_id, user_action):
        """
        根据用户ID、文章ID、用户行为查找关系ID
        :param uid:
        :param message_id:
        :param user_action:
        :return: 
        """
        sql_sentence = "SELECT id FROM tblUserMessageActionMap WHERE uid=%s AND message_id=%s AND user_action=%s"
        param_list = (uid, message_id, user_action)
        return self._dao_sql.fetch_one(sql_sentence, param_list)

    def update_status_by_map_id(self, map_id, status):
        """
        根据关系ID、用户行为更新状态
        :param map_id: 
        :param status:
        :return: 
        """
        sql_sentence = "UPDATE tblUserMessageActionMap SET status=%s, create_time=%s WHERE id=%s"
        create_time = int(time.mktime(datetime.datetime.now().timetuple()))
        param_list = (status, create_time, map_id)
        return self._dao_sql.execute_one(sql_sentence, param_list)

    def add_new_action_map(self, uid, message_id, user_action):
        """
        添加新的行为关系
        :param uid: 
        :param message_id:
        :param user_action:
        :return: 
        """
        sql_sentence = "INSERT INTO tblUserMessageActionMap (`uid`, `message_id`, `create_time`, `user_action`) VALUES (%s, %s, %s, %s)"
        create_time = int(time.mktime(datetime.datetime.now().timetuple()))
        param_list = (uid, message_id, create_time, user_action)
        return self._dao_sql.execute_one(sql_sentence, param_list)

    def get_message_id_list_by_uid_and_user_action(self, uid, user_action, offset=0, limit=10):
        """
        
        :param uid: 
        :param user_action: 
        :param offset: 
        :param limit: 
        :return: 
        """
        sql_sentence = "SELECT message_id FROM tblUserMessageActionMap WHERE uid=%s AND user_action=%s AND status=1 ORDER BY create_time DESC LIMIT %s, %s"
        param_list = (uid, user_action, offset, limit)
        return self._dao_sql.fetch_all(sql_sentence, param_list)

    def get_online_record_count_by_uid(self, uid):
        """
        
        :param uid: 
        :return: 
        """
        sql_sentence = "SELECT COUNT(1) FROM tblUserMessageActionMap WHERE status=1 and uid=%s"
        param_list = (uid, )
        res = self._dao_sql.fetch_all(sql_sentence, param_list)
        return res[0][0]

    def has_online_relation(self, mid, uid):
        """
        
        :param mid: 
        :param uid: 
        :return: 
        """
        sql_sentence = "SELECT count(1) FROM tblUserMessageActionMap WHERE status=1 AND uid=%s AND message_id=%s"
        param_list = (uid, mid)
        res = self._dao_sql.fetch_one(sql_sentence, param_list)
        if res[0] > 0:
            return True
        return False

    def get_message_good_num_by_uid_and_mid(self, uid, message_id):
        sql_sentence = "SELECT count(1) FROM tblUserMessageActionMap WHERE status=1 AND uid=%s AND message_id=%s"
        param_list = (uid, message_id)
        res = self._dao_sql.fetch_one(sql_sentence, param_list)
        return res[0]

