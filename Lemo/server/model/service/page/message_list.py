# -*- coding: UTF-8 -*-
# @file   message_list
# @author zh1995
# @date   17-4-2
# @brief
from base_page import BasePage
from model.service.data.message import Message


class MessageList(BasePage):
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
        if self._get_param("tag_id") is None:
            raise Exception("tag_id is none")
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
        # 转义参数
        uid = int(self._get_param("uid"))
        tag_id = int(self._get_param("tag_id"))
        current_page = int(self._get_param("current_page"))
        page_size = int(self._get_param("page_size"))

        # 计算偏移
        offset = current_page * page_size

        # 获取文章列表
        ds_message = Message()
        message_list = ds_message.get_message_list_by_tag_id(tag_id, offset, page_size)
        return {
            "data": {
                "list": self._format_message_list(message_list)
            }
        }

    def _format_message_list(self, message_list):
        """
        格式化文章列表
        :param message_list:  
        :return: 
        """
        if message_list is None:
            return message_list
        new_message_list = []
        for message in message_list:
            new_message_list.append(
                {
                    "messageId": message[0],
                    "messageTitle": message[1],
                    "coverPic": message[2],
                }
            )
        return new_message_list
