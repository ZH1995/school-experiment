# -*- coding: UTF-8 -*-
# @file   user_message_action
# @author zh1995
# @date   17-4-14
# @brief
from base_page import BasePage
from model.service.data.user_message_action_map import UserMessageActionMap
from model.service.data.message import Message


class UserMessageAction(BasePage):
    """
    用户文章行为类
    """

    def _check_param(self):
        """
        参数校验
        :return: 
        """
        if self._get_param("uid") is None:
            raise Exception("uid is none")
        if self._get_param("user_action") is None:
            raise Exception("user action is none")

    def _execute(self, req):
        """
        执行函数
        :param req: 
        :return: 
        """
        # 转义参数
        uid = int(self._get_param("uid"))
        message_id = int(self._get_param("message_id"))
        status = int(self._get_param("status"))
        user_action = int(self._get_param("user_action"))

        # 是否已存在关系
        ds_user_message_action_map = UserMessageActionMap()
        self.logger.info("user_action = %s", user_action)
        map_id = ds_user_message_action_map.get_id_by_uid_and_message_id(uid, message_id, user_action)
        self.logger.info("map_id = %s", map_id)

        ds_message = Message()
        # 下线状态
        if status == 0:
            # 置为上线
            res = ds_user_message_action_map.update_status_by_map_id(map_id[0], status)
            # 下线点赞写Message表
            if user_action == 1 and ds_message.get_good_num_by_message_id(message_id) > 0:
                ds_message.update_good_num_by_message_id_and_status(message_id, status)
        else:
            # 上线状态
            if map_id is None:
                res = ds_user_message_action_map.add_new_action_map(uid, message_id, user_action)
            else:
                res = ds_user_message_action_map.update_status_by_map_id(map_id[0], status)
                # 上线点赞写Message表
                if user_action == 1:
                    ds_message.update_good_num_by_message_id_and_status(message_id, status)
        if res is None:
            self.logger.info("user message action map fail")
        return {
            "data": True
        }
