# -*- coding: UTF-8 -*-
# @file   message_list_handler
# @author zh1995
# @date   17-4-2
# @brief

import logging
import json
import tornado.web
from model.service.page.message_list import MessageList


class MessageListHandler(tornado.web.RequestHandler):
    """

    """

    def initialize(self):
        self.logger = logging.getLogger(name='handler')
        self.add_header("Access-Control-Allow-Origin", "*")
        self.handler_name = "MessageListHandler"

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
            "tag_id": argument['tagId'],
            "current_page": argument['currentPage'],
            "page_size": argument['pageSize'],
            "ip": self.request.remote_ip,
        }
        message_list = MessageList("MessageList").execute(req)
        message_list = json.dumps(message_list).encode('utf8')

        self.logger.info("%s_over", self.handler_name)
        self.write(message_list)
