#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <string>
#include <winsock2.h>
#include <time.h>
#include <cstdlib>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
const int PORT = 8009;
char s[256];
char s2[256];

int main()
{
    int n;
    WSADATA wd;
    n = WSAStartup(MAKEWORD(2, 2), &wd);
    if (n)
    {
        cout << "WSAStartup函数错误!" << endl;
        return -1;
    }
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (INVALID_SOCKET == sock)
    {
        cout << "socket建立失败！" << endl;
        return -1;
    }
    sockaddr_in sa = { AF_INET };   //随机分配一个端口
    n = bind(sock, (sockaddr*)&sa, sizeof(sa));
    if (n == SOCKET_ERROR)
    {
        cout << "bind函数失败！" << endl;
        cout << "错误码是：" << WSAGetLastError() << endl;
        return -1;
    }
    sa.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//115.200.33.112
    sa.sin_port = htons(PORT);
    n = connect(sock, (sockaddr*)&sa, sizeof(sa)); //指定端口发送数据
    if (n == SOCKET_ERROR)
    {
        cout << "connect函数失败！" << endl;
        cout << "错误码是：" << WSAGetLastError() << endl;
        return -1;
    }
    srand(time(NULL));
    time_t first, second;
    while (true)
    {
        fflush(stdin);
        gets(s);
        // 分组发送
        int index = 0;
        int chaoshi_time = 0;
        int jiaoyan_time = 0;
        while(index < strlen(s)){

            // 构造发送数据
            char gen_s[5];
            // 帧序号，偶数0，奇数1
            if(index & 1) gen_s[0] = '1';
            else gen_s[0] = '0';
            // 数据帧
            gen_s[1] = s[index];
            // 验错位,0代表无错

            int jiaoyan = rand() % 2;
            if(jiaoyan == 0){
                gen_s[2] = '0';
            }
            else{
                gen_s[2] = '1';
                jiaoyan_time ++;
            }
            if(jiaoyan_time >= 2 && gen_s[2] == '1'){
                jiaoyan_time = 0;
                gen_s[2] = '0';
            }
            gen_s[3] = (char)(index + '0');
            gen_s[4] = '\0';
            // 发送
            cout << "客户端发送信息：" << gen_s << endl;
            first = time(NULL); // 开始发送时间
            send(sock, gen_s, strlen(gen_s), 0);
            // 超时随机数种子
            int timming = rand() % 2;
            if(timming != 0 && chaoshi_time < 2){
                // 设置延时
                Sleep(3000);
                chaoshi_time ++;
            }
            else{
                Sleep(1000);
                if(chaoshi_time >= 2)
                    chaoshi_time = 0;
            }
            // 接收
            fflush(stdin);
            recv(sock, s2, sizeof(s2), 0);
            second = time(NULL); // 截止时间
            if(difftime(second, first) - 2 <= 1e-9){
                // 可以继续发送下一位
                if(s2[3] != gen_s[0]){
                    cout << "客户端接收信息：" << s2 << endl;
                    index ++;
                }
                else{
                    cout << "校验重发" << endl;
                }
            }
            else{
                cout << "超时重发" << endl;
                continue;
            }
        }
    }
    return 0;
}
