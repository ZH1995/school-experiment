# -*- coding: UTF-8 -*-
# @file   write_comment_handler
# @author zh1995
# @date   17-4-17
# @brief
import logging
import json
import tornado.web
from model.service.page.write_comment import WriteComment


class WriteCommentHandler(tornado.web.RequestHandler):
    """

    """

    def initialize(self):
        self.logger = logging.getLogger(name='handler')
        self.add_header("Access-Control-Allow-Origin", "*")
        self.handler_name = "WriteComment"

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
            "uid": argument["uid"],
            "reply_uid": argument["replyUid"],
            "message_id": argument["messageId"],
            "comment_content": argument["commentContent"],
            "ip": self.request.remote_ip,
        }
        write_comment_res = WriteComment("WriteComment").execute(req)
        write_comment_res = json.dumps(write_comment_res).encode('utf8')

        self.logger.info("%s_over", self.handler_name)
        self.write(write_comment_res)

