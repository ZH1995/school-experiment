# -*- coding: UTF-8 -*-
# @file   message_comment_map
# @author zh1995
# @date   17-4-13
# @brief
import time
import datetime
from model.dao.sql_operation import SQL


class Comment(object):
    """
    评论类
    """
    def __init__(self):
        """
        初始化类
        """
        self._dao_sql = SQL()

    def get_comment_num_by_message_id(self, message_id):
        """
        根据文章ID获取文章评论总数
        :param message_id: 
        :return: 
        """
        sql_sentence = "SELECT count(1) FROM tblComment WHERE message_id=%s"
        param_list = (message_id, )
        return self._dao_sql.fetch_all(sql_sentence, param_list)

    def add_reply_comment(self, uid, reply_uid, message_id, comment_content):
        """
        
        :param uid: 
        :param reply_uid: 
        :param message_id: 
        :param comment_content: 
        :return: 
        """
        sql_sentence = "INSERT INTO tblComment (`uid`, `comment_content`, `is_reply`, `reply_uid`, " \
                        "`create_time`, `message_id`) VALUES(%s, %s, %s, %s, %s, %s)"
        create_time = int(time.mktime(datetime.datetime.now().timetuple()))
        param_list = (uid, comment_content, 1, reply_uid, create_time, message_id)
        return self._dao_sql.execute_one(sql_sentence, param_list)

    def add_message_comment(self, uid, message_id, comment_content):
        """
        
        :param uid: 
        :param message_id: 
        :param comment_content: 
        :return: 
        """
        sql_sentence = "INSERT INTO tblComment (`uid`, `comment_content`, `is_reply`, `create_time`, `message_id`) VALUES" \
                       "(%s, %s, %s, %s, %s)"
        create_time = int(time.mktime(datetime.datetime.now().timetuple()))
        param_list = (uid, comment_content, 0, create_time, message_id)
        return self._dao_sql.execute_one(sql_sentence, param_list)

    def get_comment_list_by_message_id(self, message_id, offset=0, limit=10):
        """
        
        :param message_id: 
        :param offset: 
        :param limit: 
        :return: 
        """
        sql_sentence = "SELECT uid, comment_content, is_reply, reply_uid, create_time FROM tblComment " \
                       "WHERE message_id=%s ORDER BY create_time DESC LIMIT %s, %s"
        param_list = (message_id, offset, limit)
        return self._dao_sql.fetch_all(sql_sentence, param_list)