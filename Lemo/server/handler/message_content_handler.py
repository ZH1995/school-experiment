# -*- coding: UTF-8 -*-
# @file   message_content
# @author zh1995
# @date   17-4-2
# @brief

import logging
import json
import tornado.web
from model.service.page.message_content import MessageContent


class MessageContentHandler(tornado.web.RequestHandler):
    """

    """

    def initialize(self):
        self.logger = logging.getLogger(name='handler')
        self.add_header("Access-Control-Allow-Origin", "*")
        self.handler_name = "MessageContent"

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
            "message_id": argument["messageId"],
            "ip": self.request.remote_ip,
        }
        message_content = MessageContent("MessageContent").execute(req)
        message_content = json.dumps(message_content).encode('utf8')

        self.logger.info("%s_over", self.handler_name)
        self.write(message_content)
