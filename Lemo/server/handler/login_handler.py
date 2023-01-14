# -*- coding: UTF-8 -*-
# @file   login_handler
# @author zh1995
# @date   17-4-1
# @brief

import json
import logging
import tornado.web
from model.service.page.login import Login


class LoginHandler(tornado.web.RequestHandler):
    """

    """

    def initialize(self):
        self.logger = logging.getLogger(name='handler')
        self.add_header("Access-Control-Allow-Origin", "*")

    def post(self):
        """
        通过账号、密码登录
        @:param string account
        @:param string passward
        """
        self.logger.info("LoginHandler_start")
        try:
            argument = json.loads(self.request.body)
            self.logger.info("arguments=%s", argument)
        except Exception, e:
            self.logger.error("e = %s", e)
            return
        req = {
            "phone_number": argument['phoneNumber'],
            "password": argument['password'],
            "ip": self.request.remote_ip,
        }
        self.logger.info(req)
        user_info = Login("Login").execute(req)
        user_info = json.dumps(user_info).encode('utf8')

        self.logger.info("LoginHandler_over")
        self.write(user_info)
