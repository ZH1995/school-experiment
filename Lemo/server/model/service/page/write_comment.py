# -*- coding: UTF-8 -*-
# @file   write_comment
# @author zh1995
# @date   17-4-17
# @brief
import time
from base_page import BasePage
from model.service.data.message import Message
from model.service.data.comment import Comment


class WriteComment(BasePage):
    """
    写评论类
    """

    def _check_param(self):
        """
        参数校验
        :return: 
        """
        if self._get_param("uid") is None:
            raise Exception("uid is invalid")
        if self._get_param("message_id") is None:
            raise Exception("message page is invalid")
        if self._get_param("comment_content") is None:
            raise Exception("comment content is invalid")

    def _execute(self, req):
        """
        执行函数
        :param req: 
        :return: 
        """
        # 转义参数
        uid = int(self._get_param("uid"))
        reply_uid = int(self._get_param("reply_uid"))
        message_id = int(self._get_param("message_id"))
        comment_content = self._get_param("comment_content")
        comment_content = u''.join(comment_content).encode("utf-8")

        ds_comment = Comment()
        # 回复评论
        if reply_uid != 0:
            res = ds_comment.add_reply_comment(uid, reply_uid, message_id, comment_content)
        # 文章评论
        else:
            res = ds_comment.add_message_comment(uid, message_id, comment_content)
        return {
            "data": res
        }
