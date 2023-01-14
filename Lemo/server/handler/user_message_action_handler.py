# -*- coding: UTF-8 -*-
# @file   user_message_action_handler
# @author zh1995
# @date   17-4-14
# @brief
import logging
import json
import tornado.web
from model.service.page.user_message_action import UserMessageAction


class UserMessageActionHandler(tornado.web.RequestHandler):
    """

    """

    def initialize(self):
        self.logger = logging.getLogger(name='handler')
        self.add_header("Access-Control-Allow-Origin", "*")
        self.handler_name = "UserMessageActionHandler"

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
            "status": argument["status"],
            "user_action": argument["userAction"],
            "ip": self.request.remote_ip,
        }
        action_res = UserMessageAction("UserMessageAction").execute(req)
        action_res = json.dumps(action_res).encode('utf8')

        self.logger.info("%s_over", self.handler_name)
        self.write(action_res)

