# -*- coding: UTF-8 -*-
# @file   collect_list
# @author zh1995
# @date   17-4-13
# @brief
from base_page import BasePage
from model.service.data.user_message_action_map import UserMessageActionMap
from model.service.data.message import Message


class UserActionList(BasePage):
    """
    文章列表类
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
        if self._get_param("current_page") is None:
            raise Exception("current_page is none")
        if self._get_param("page_size") is None:
            raise Exception("page_size is none")

    def _execute(self, req):
        """
        执行函数
        :param req: 
        :return: 
        """
        self.logger.info("come in")
        # 转义参数
        uid = int(self._get_param("uid"))
        user_action = int(self._get_param("user_action"))
        current_page = int(self._get_param("current_page"))
        page_size = int(self._get_param("page_size"))

        # 计算偏移
        offset = current_page * page_size

        self.logger.info("uid = %s", uid)
        self.logger.info("user_action = %s", user_action)
        self.logger.info("current_page = %s", current_page)
        self.logger.info("page_size = %s", page_size)

        # 获取文章ID列表
        ds_user_message_action_map = UserMessageActionMap()
        message_id_tuple = ds_user_message_action_map.get_message_id_list_by_uid_and_user_action(uid, user_action, offset, page_size)
        self.logger.info("message_id_tuple = %s", message_id_tuple)
        if len(message_id_tuple) == 0:
            return {
                "data": {
                    "list": ""
                }
            }

        message_id_list = self._get_message_id_list(message_id_tuple)
        self.logger.info(message_id_list)
        # 根据ID列表批量获取文章
        ds_message = Message()
        message_list = ds_message.get_message_list_by_message_id_list(message_id_list)
        self.logger.info("m_list = %s", message_list)
        return {
            "data": {
                "list": self._format_message_list(message_id_list, message_list)
            }
        }

    def _get_message_id_list(self, message_id_tuple):
        """
        
        :param message_id_tuple: 
        :return: 
        """
        message_id_list = []
        for val in message_id_tuple:
            message_id_list.append(int(val[0]))
        return message_id_list

    def _format_message_list(self, message_id_list, message_list):
        """
        格式化收藏列表
        :param message_id_list:
        :param message_list:
        :return: 
        """
        if message_list is None:
            return ""
        new_message_list = []
        for message_id in message_id_list:
            for message in message_list:
                if message[0] == message_id:
                    new_message_list.append(
                        {
                            "messageId": message[0],
                            "messageTitle": message[1],
                            "coverPic": message[2]
                        }
                    )
                    break
        return new_message_list

