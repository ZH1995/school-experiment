# -*- coding: UTF-8 -*-
# @file   collect_list_handler
# @author zh1995
# @date   17-4-13
# @brief
import logging
import json
import tornado.web
from model.service.page.user_action_list import UserActionList


class UserActionListHandler(tornado.web.RequestHandler):
    """

    """

    def initialize(self):
        self.logger = logging.getLogger(name='handler')
        self.add_header("Access-Control-Allow-Origin", "*")
        self.handler_name = "UserActionListHandler"

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
            "user_action": argument["userAction"],
            "current_page": argument['currentPage'],
            "page_size": argument['pageSize'],
            "ip": self.request.remote_ip,
        }
        action_list = UserActionList("UserActionList").execute(req)
        action_list = json.dumps(action_list).encode('utf8')

        self.logger.info("%s_over", self.handler_name)
        self.write(action_list)

