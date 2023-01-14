# -*- coding: UTF-8 -*-
# @file   db_pool
# @author zh1995
# @date   17-4-1
# @brief

import MySQLdb
from DBUtils.PooledDB import PooledDB

# 数据库连接池
pool = PooledDB(MySQLdb, 3, host='127.0.0.1', user='root', passwd='123456', db='lemo', port=3306, charset="utf8")