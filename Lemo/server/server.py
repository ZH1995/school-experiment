# -*- coding: UTF-8 -*-
# @file   server
# @author zh1995
# @date   17-4-1
# @brief

import os
import sys
import handler
import logging.config
import tornado.ioloop
from tornado.options import define, options

sys.path.append(os.getcwd())

logging.config.fileConfig(r'config/logging.conf')

define("port", default=10101, help="run on the given port", type=int)

settings = {
    'debug': True
}

handlers = [
    (r"/user/login", handler.login_handler.LoginHandler),
    (r"/user/register", handler.register_handler.RegisterHandler),
    (r"/user/modify", handler.modify_user_info_handler.ModifyUserInfoHandler),
    (r"/message/list", handler.message_list_handler.MessageListHandler),
    (r"/message/content", handler.message_content_handler.MessageContentHandler),
    (r"/message/userAction", handler.user_message_action_handler.UserMessageActionHandler),
    (r"/action/list", handler.user_action_list_handler.UserActionListHandler),
    (r"/comment/write", handler.write_comment_handler.WriteCommentHandler),
    (r"/comment/list", handler.comment_list_handler.CommentListHandler),
    (r"/message/hotspot", handler.hotspot_handler.HotspotHandler),
]

if __name__ == "__main__":
    application = tornado.web.Application(handlers=handlers, **settings)
    application.listen(options.port)
    tornado.ioloop.IOLoop.instance().start()