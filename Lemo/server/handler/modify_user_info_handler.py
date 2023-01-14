# -*- coding: UTF-8 -*-
# @file   modify_info_handler
# @author zh1995
# @date   17-4-17
# @brief
import json
import logging
import tornado.web
from model.service.page.modify_user_info import ModifyUserInfo


class ModifyUserInfoHandler(tornado.web.RequestHandler):
    """

    """

    def initialize(self):
        self.logger = logging.getLogger(name='handler')
        self.add_header("Access-Control-Allow-Origin", "*")
        self.handler_name = "ModifyUserInfoHandler"

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
            "username": argument["userName"],
            "user_sign": argument["userSign"],
            "head_img": argument["headImg"],
            "ip": self.request.remote_ip,
        }
        user_info = ModifyUserInfo("ModifyUserInfo").execute(req)
        user_info = json.dumps(user_info).encode('utf8')

        self.logger.info("%s_over", self.handler_name)
        self.write(user_info)

