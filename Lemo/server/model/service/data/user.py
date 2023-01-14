# -*- coding: UTF-8 -*-
# @file   user
# @author zh1995
# @date   17-4-1
# @brief

import datetime
import time
from model.dao.sql_operation import SQL


class User(object):
    """
    登录类
    """
    def __init__(self):
        """
        初始化类
        """
        self._dao_sql = SQL()

    def get_user_info_by_phone_and_pwd(self, phone_number, password):
        """
        根据电话号、密码获取用户信息
        :param phone_number: 
        :param password: 
        :return: 
        """
        sql_sentence = "SELECT uid, uname, head_img, user_sign FROM tblUser WHERE phone_number=%s and password=%s"
        param_list = (phone_number, password)
        return self._dao_sql.fetch_one(sql_sentence, param_list)

    def add_new_user(self, username, phone_number, password, head_img=""):
        """
        
        :param username:
        :param phone_number:
        :param password: 
        :param headimg: 
        :return: 
        """
        sql_sentence = "INSERT INTO tblUser (`uname`, `phone_number`, `password`, `head_img`, `create_time`) VALUES (%s, %s, %s, %s, %s)"
        create_time = int(time.mktime(datetime.datetime.now().timetuple()))
        param_list = (username, phone_number, password, head_img, create_time)
        return self._dao_sql.execute_one(sql_sentence, param_list)

    def get_uname_by_uid(self, uid):
        """
        
        :param uid: 
        :return: 
        """
        sql_sentence = "SELECT uname from tblUser WHERE uid=%s"
        param_list = (uid, )
        return self._dao_sql.fetch_one(sql_sentence, param_list)

    def get_head_img_by_uid(self, uid):
        """
        
        :param uid: 
        :return: 
        """
        sql_sentence = "SELECT head_img from tblUser WHERE uid=%s"
        param_list = (uid, )
        return self._dao_sql.fetch_one(sql_sentence, param_list)

    def update_user_info(self, uid, uname, user_sign, new_head_img):
        """
        
        :param uid: 
        :param uname: 
        :param user_sign: 
        :param new_head_img: 
        :return: 
        """
        sql_sentence = "UPDATE tblUser set uname=%s, user_sign=%s, head_img=%s WHERE uid=%s"
        param_list = (uname, user_sign, new_head_img, uid)
        return self._dao_sql.execute_one(sql_sentence, param_list)

    def update_user_info_no_img(self, uid, uname, user_sign):
        """

        :param uid: 
        :param uname: 
        :param user_sign: 
        :return: 
        """
        sql_sentence = "UPDATE tblUser set uname=%s, user_sign=%s WHERE uid=%s"
        param_list = (uname, user_sign, uid)
        return self._dao_sql.execute_one(sql_sentence, param_list)
