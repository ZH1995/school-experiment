# -*- coding: UTF-8 -*-
# @file   comment_list
# @author zh1995
# @date   17-4-17
# @brief
import time
from base_page import BasePage
from model.service.data.comment import Comment
from model.service.data.user import User


class CommentList(BasePage):
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
        if self._get_param("message_id") is None:
            raise Exception("message_id is none")
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
        message_id = int(self._get_param("message_id"))
        current_page = int(self._get_param("current_page"))
        page_size = int(self._get_param("page_size"))

        # 计算偏移
        offset = current_page * page_size

        # 获取文章列表
        ds_comment = Comment()
        comment_list = ds_comment.get_comment_list_by_message_id(message_id, offset, page_size)
        return {
            "data": {
                "list": self._format_comment_list(comment_list)
            }
        }

    def _format_comment_list(self, comment_list):
        """
        格式化评论列表
        :param comment_list:  
        :return: 
        """
        if comment_list is None:
            return comment_list
        new_comment_list = []
        for comment in comment_list:

            ds_user = User()
            head_img = ds_user.get_head_img_by_uid(comment[0])
            name = ds_user.get_uname_by_uid(comment[0])
            reply_name = ""
            if comment[2] != 0:
                reply_name = ds_user.get_uname_by_uid(comment[3])
            new_comment_list.append(
                {
                    "authorId": comment[0],
                    "authorHeadImg": head_img[0],
                    "authorName": name[0],
                    "commentContent": comment[1],
                    "isReply": comment[2],
                    "replyIid": comment[3],
                    "replyName": reply_name[0] if comment[2] != 0 else "",
                    "createTime": time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(comment[4])),
                }
            )
        self.logger.info(new_comment_list)
        return new_comment_list

