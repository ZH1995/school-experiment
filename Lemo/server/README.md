# lemo-server

Based on Tornado framework. It provide data support for lemo-app. 


# 自媒体系统服务端

基于Tornado框架，主要为自媒体系统客户端提供数据支持。服务端的架构设计从安全性、可扩展性、解耦合等多方面考虑。
- 首先对于安全性
    - 系统选用HTTP的POST方式进行数据传输，对接收的参数手动进行转义，防止参数注入风险；
    - Model层通过Redis对接口调用频率进行检测，防止DDOS风险；
    - SQL层采用Python自带的预编译方式，防止SQL注入风险；
- 其次对于可扩展性
    - 分离应用层、服务层、数据逻辑层、存储层，新的需求来到时，对底层的变动降到最小，增强未来系统的扩展性。
- 最后解耦合
    - Model层将通用方法抽象出来，具体业务统一继承Base类，在每个具体业务的文件内编写自己用到的方法。
    - 数据库每个表为一个单独文件，减少数据库表间的耦合。
    
推荐策略分为两种情况：

- 没有系统内交互的新用户，即没有对文章点赞、收藏过的用户。根据文章的浏览量、点赞量、收藏量、标签，分别赋予不同百分比，根据结果由高到低排序进行推荐
- 有系统内交互的用户，采用基于用户的推荐。找到和当前用户相似的前K个用户，在这K个用户有过交互的文章中，选取当前用户没有过交互的文章进行推荐。

出于性能和效率考量，推荐策略采用线下和线上相结合的方式。即以Redis缓存部分或全部结果，以供服务端逻辑中使用，加快推荐数据的产生速度，同时以定时脚本的方式更新Redis中的数据，以保证推荐结果的时效性。


