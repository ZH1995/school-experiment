# -*- coding: UTF-8 -*-
# @file   message
# @author zh1995
# @date   17-4-2
# @brief
from model.dao.sql_operation import SQL


class Message(object):
    """
    文章类
    """
    def __init__(self):
        """
        初始化类
        """
        self._dao_sql = SQL()

    def get_message_list_by_tag_id(self, tag_id, offset=0, limit=10):
        """
        获取文章列表
        :param offset: 
        :param limit: 
        :return: 
        """
        sql_sentence = "SELECT message_id, message_title, cover_pic FROM tblMessage WHERE tag_id=%s ORDER BY create_time DESC LIMIT %s, %s"
        param_list = (tag_id, offset, limit)
        return self._dao_sql.fetch_all(sql_sentence, param_list)

    def get_message_content_by_message_id(self, message_id):
        """
        
        :param message_id: 
        :return: 
        """
        sql_sentence = "SELECT message_title, cover_pic, author_name, author_img, message_content, look_num, create_time FROM tblMessage WHERE message_id=%s"
        param_list = (message_id, )
        return self._dao_sql.fetch_one(sql_sentence, param_list)

    def get_good_num_by_message_id(self, message_id):
        """
        
        :param message_id: 
        :return: 
        """
        sql_sentence = "SELECT good_num FROM tblMessage WHERE message_id=%s"
        param_list = (message_id, )
        return self._dao_sql.fetch_one(sql_sentence, param_list)

    def update_good_num_by_message_id_and_status(self, message_id, status):
        """
        
        :param message_id: 
        :param status: 
        :return: 
        """
        if status == 0:
            sql_sentence = "UPDATE tblMessage SET good_num=good_num-1 WHERE message_id=%s"
        else:
            sql_sentence = "UPDATE tblMessage SET good_num=good_num+1 WHERE message_id=%s"
        param_list = (message_id, )
        return self._dao_sql.execute_one(sql_sentence, param_list)

    def add_look_num_by_message_id(self, message_id):
        """
        
        :param message_id: 
        :return: 
        """
        sql_sentence = "UPDATE tblMessage SET look_num = look_num + 1 WHERE message_id=%s"
        param_list = (message_id, )
        return self._dao_sql.execute_one(sql_sentence, param_list)

    def get_message_list_by_message_id_list(self, message_id_list):
        """
        
        :param message_id_list: 
        :return: 
        """
        sql_sentence = "SELECT message_id, message_title, cover_pic FROM tblMessage WHERE message_id in (%s)"
        new_message_id_list = ', '.join(map(lambda x: '%s', message_id_list))
        sql_sentence = sql_sentence % (new_message_id_list, )
        return self._dao_sql.fetch_all(sql_sentence, tuple(message_id_list))

