# -*- coding: UTF-8 -*-
# @file   register
# @author zh1995
# @date   17-4-1
# @brief
import random
from base_page import BasePage
from model.service.data.user import User


class Register(BasePage):
    """
    注册类
    """

    def _check_param(self):
        """
        参数校验
        :return: 
        """
        if self._get_param("username") is None:
            raise Exception("User name is invalid")
        if self._get_param("phone_number") is None:
            raise Exception("Phone number is invalid")
        if self._get_param("password") is None:
            raise Exception("Password is invalid")

    def _execute(self, req):
        """
        执行函数
        :param req: 
        :return: 
        """
        username = u''.join(self._get_param("username")).encode("utf-8")
        phone_number = str(self._get_param("phone_number"))
        password = str(self._get_param("password"))
        if self.__is_exist(phone_number, password) is True:
            return {
                "errno": -1,
                "errmsg": "account has exist",
            }

        # 产生随机图片
        random_index = random.randint(1, 7)
        head_img = "http://localhost:80/headImg/" + str(random_index) + ".jpg"
        ds_user = User()
        create_user_res = ds_user.add_new_user(username, phone_number, password, head_img)
        if create_user_res == 0:
            return {
                "errno": -1,
                "errmsg": "create account fail",
            }

        user_info = ds_user.get_user_info_by_phone_and_pwd(phone_number, password)
        if user_info is None:
            return {
                "errno": -1,
            }
        return {
            "data": {
                "uid": user_info[0],
                "uname": user_info[1],
                "headImg": user_info[2],
                "userSign": user_info[3]
            }
        }

    def __is_exist(self, phone_number, password):
        """
        
        :param phone_number: 
        :param password: 
        :return: 
        """
        ds_user = User()
        uid = ds_user.get_user_info_by_phone_and_pwd(phone_number, password)
        if uid is None:
            return False
        return True
