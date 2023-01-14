# -*- coding: UTF-8 -*-
# @file   base_page
# @author zh1995
# @date   17-4-1
# @brief

import logging
import traceback
import redis
import time


class BasePage(object):
    """
    页面基类
    """

    def __init__(self, pageName):
        """
        基类初始化
        :param pageName: 
        
        """
        self.pageName = pageName
        self.logger = logging.getLogger(name="model")

    def execute(self, req):
        """
        
        :param req: 
        :return: 
        """
        self.logger.info("%s_start", self.pageName)
        self.req = req
        self.res = {
            "errno": 0,
            "errmsg": '',
        }
        try:
            self._check_param()
            if self._limit_accept(self.req["ip"]) is False:
                return self.res
            res = self._execute(req)
            if isinstance(res, dict) and isinstance(self.res, dict):
                self.res.update(res)
        except Exception, e:
            self.logger.error("e = %s", e)
            self.logger.error(traceback.format_exc())
            self.logger.error("%s_fail", self.pageName)
            self.res["errno"] = -1
            self.res["errmsg"] = e
        self.logger.info("%s_over", self.pageName)
        return self.res

    def _check_param(self):
        """
        
        :return: 
        """
        return

    def _limit_accept(self, ip):
        """
        
        :return: 
        """
        unix_time = time.time()
        key = ip + ":" + self.pageName + ":" + str(unix_time)
        pool = redis.ConnectionPool(host='127.0.0.1', port=6379, db=0)
        r = redis.Redis(connection_pool=pool)
        if r.exists(key):
            r.incr(key)
            count = int(r.get(key))
            if count > 10:
                return False
        else:
            r.set(key, 1)
            expired_time = 2
            r.expire(key, expired_time)
        return True

    def _execute(self, req):
        """
        
        :param req: 
        :return: 
        """
        return

    def _get_param(self, param_name=''):
        """
        获取参数
        :param param_name: 
        :return: 
        """
        if self.req[param_name] is None:
            return self.req
        return self.req[param_name]