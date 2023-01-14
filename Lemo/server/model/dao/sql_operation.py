# -*- coding: UTF-8 -*-
# @file   sql_operation
# @author zh1995
# @date   17-4-1
# @brief

from db_pool import pool
import logging
import traceback


class SQL(object):
    """
        sql基本操作
    """
    def __init__(self):
        self.logger = logging.getLogger(name="model")

    def execute_one(self, sql, arg=()):
        """
        执行sql语句并提交，适用于执行语句
        :param sql: sql语句
        :param arg: 变量
        :return: 成功：获取的所有数据     失败：抛出异常
        """
        self.logger.debug("进入execute_one方法")
        self.logger.debug("sql语句：data=%s", sql)
        try:
            # 1.连接数据库
            conn = pool.connection()

            # 2.获取油标cursor
            cur = conn.cursor()

            # 3.执行提交
            result = cur.execute(sql, arg)
            conn.commit()

            # 4.关闭数据库连接
            conn.close()
            self.logger.debug("退出insert方法")
            return result
        except Exception, e:
            self.logger.error("e = %s", e)
            self.logger.error(traceback.format_exc())
            self.logger.error("sql_operations.execute_one方法sql语句执行失败")
            raise e

    def fetch_all(self, sql, arg=()):
        """
        执行sql语句并获取所有数据，适用于select语句
        :param sql: sql语句
        :param arg: 变量
        :return: 成功：获取的所有数据     失败：抛出异常
        """
        self.logger.debug("进入fetch_all方法")
        self.logger.debug("sql语句：data=%s", sql)
        try:
            # 1.连接数据库
            conn = pool.connection()

            # 2.获取油标cursor
            cur = conn.cursor()

            # 3.执行获取信息
            cur.execute(sql, arg)
            result = cur.fetchall()

            # 4.关闭数据库
            conn.close()
            self.logger.debug("退出fetch_all方法")
            return result
        except Exception, e:
            self.logger.error("e = %s", e)
            self.logger.error(traceback.format_exc())
            self.logger.error("sql_operations.fetch_all方法sql语句执行失败")
            raise e

    def fetch_one(self, sql, arg=()):
        """
        执行sql语句并获取一条数据，适用于select语句
        :param sql: sql语句
        :param arg: 变量
        :return: 成功：获取的数据   失败：抛出异常
        """
        self.logger.debug("进入fetch_one方法")
        self.logger.debug("sql语句：data=%s", sql)
        try:
            # 1.连接数据库
            conn = pool.connection()

            # 2.获取油标cursor
            cur = conn.cursor()

            # 3.执行获取信息
            cur.execute(sql, arg)
            result = cur.fetchone()

            # 4.关闭数据库
            conn.close()
            self.logger.debug("退出fetch_one方法")
            return result
        except Exception, e:
            self.logger.error("e = %s", e)
            self.logger.error(traceback.format_exc())
            self.logger.error("sql_operations.fetch_one方法sql语句执行失败")
            raise e