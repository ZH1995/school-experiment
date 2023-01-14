# -*- coding: UTF-8 -*-
# @file   modify_user_info
# @author zh1995
# @date   17-4-17
# @brief
import random
from base_page import BasePage
from model.service.data.user import User


class ModifyUserInfo(BasePage):
    """
    注册类
    """

    def _check_param(self):
        """
        参数校验
        :return: 
        """
        if self._get_param("uid") is None:
            raise Exception("uid is invalid")

    def _execute(self, req):
        """
        执行函数
        :param req: 
        :return: 
        """
        uid = int(self._get_param("uid"))
        username = u''.join(self._get_param("username")).encode("utf-8")
        user_sign = u''.join(self._get_param("user_sign")).encode("utf-8")
        head_img = str(self._get_param("head_img"))

        ds_user = User()
        # 不换头像
        if head_img == "":
            update_user_res = ds_user.update_user_info_no_img(uid, username, user_sign)
        else:
            # 产生新随机图片
            random_index = random.randint(1, 7)
            new_head_img = "http://localhost:80/headImg/" + str(random_index) + ".jpg"
            while new_head_img == head_img:
                random_index = random.randint(1, 7)
                new_head_img = "http://localhost:80/headImg/" + str(random_index) + ".jpg"
            update_user_res = ds_user.update_user_info(uid, username, user_sign, new_head_img)

        if update_user_res == 0:
            return {
                "errno": -1
            }

        head_img = ds_user.get_head_img_by_uid(uid)

        return {
            "data": {
                "uid": uid,
                "uname": username,
                "headImg": head_img[0],
                "userSign": user_sign
            }
        }


