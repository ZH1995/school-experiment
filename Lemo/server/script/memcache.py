# -*- coding: UTF-8 -*-
# @file   memcache
# @author zh1995
# @date   17-5-15
# @brief
import memcache

mem= memcache.Client(['127.0.0.1:12000'])
print mem.set('say', 'hello,memcache', 60) #display - True
value = mem.get('say')
print value #display - hello,memcache
