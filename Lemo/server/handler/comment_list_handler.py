# -*- coding: UTF-8 -*-
# @file   comment_list_handler
# @author zh1995
# @date   17-4-17
# @brief
import logging
import json
import tornado.web
from model.service.page.comment_list import CommentList


class CommentListHandler(tornado.web.RequestHandler):
    """

    """

    def initialize(self):
        self.logger = logging.getLogger(name='handler')
        self.add_header("Access-Control-Allow-Origin", "*")
        self.handler_name = "CommentList"

    def post(self):
        """

        :return: 
        """
        self.logger.info("%s_start", self.handler_name)
        try:
            argument = json.loads(self.request.body)
            self.logger.info("arguments=%s", argument)
        except Exception, e:
            self.logger.error("e = %s", e)
            return
        req = {
            "uid": argument['uid'],
            "message_id": argument['messageId'],
            "current_page": argument['currentPage'],
            "page_size": argument['pageSize'],
            "ip": self.request.remote_ip,
        }
        comment_list = CommentList("CommentList").execute(req)
        comment_list = json.dumps(comment_list).encode('utf8')

        self.logger.info("%s_over", self.handler_name)
        self.write(comment_list)

