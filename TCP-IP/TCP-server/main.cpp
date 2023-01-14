#include <cstdio>
#include <iostream>
#include <process.h>
#include <string>
#include <winsock2.h>
#include <set>
#include <time.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
const int PORT = 8009;
char s[1024];
char s2[5];
void recvProc(void *p)
{
    SOCKET socka = (SOCKET)p; //void*转换回来

    int n = 0;
    set<char> bianhao;
    bianhao.clear();
    char pre = '0';
    string result = "";
    while((n = recv(socka, s, sizeof(s), 0)) > 0){
        s[n] = '\0';
        if(s[2] == '0'){ // 校验序列无误
            if(bianhao.count(s[3])){
                // 已接受过该帧
                s2[0] = 'A';
                s2[1] = 'C';
                s2[2] = 'K';
                s2[3] = pre;
                s2[4] = '\0';
                cout << "服务器端发送信息(已收到该帧)：" << s2 << endl;
                send(socka, s2, strlen(s2), 0);
            }
            else{
                cout << "服务器端接收信息：" << s << endl;
                bianhao.insert(s[3]);
                result += s[1];
                s2[0] = 'A';
                s2[1] = 'C';
                s2[2] = 'K';
                if(s[0] == '0'){
                    s2[3] = '1';
                    pre = '1';
                    s2[4] = '\0';
                }else if(s[0] == '1'){
                    s2[3] = '0';
                    pre = '0';
                    s2[4] = '\0';
                }
                cout << "服务器端发送信息：" << s2 << endl;
                send(socka, s2, strlen(s2), 0);
            }
        }
        else{
            // 校验出错，重传
            cout << "服务器端发送信息（校验异常）：" << s << endl;
            s2[0] = 'A';
            s2[1] = 'C';
            s2[2] = 'K';
            s2[3] = pre;
            s2[4] = '\0';
            cout << "服务器端发送信息：" << s2 << endl;
            send(socka, s2, strlen(s2), 0);
        }
    }
    cout << "服务器最终接受结果为：" << result << endl;
    result = "";
}
int main()
{
    int n;
    WSADATA wd;
    n = WSAStartup(MAKEWORD(2, 2), &wd);
    if (n)
    {
        cout << "WSAStartup函数错误！" << endl;
        return -1;
    }
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (INVALID_SOCKET == sock)
    {
        cout << "socket建立失败!" << endl;
        cout << "错误码是：" << WSAGetLastError() << endl;
        return -1;
    }
    sockaddr_in sa = { AF_INET, htons(PORT) };
    n = bind(sock, (sockaddr*)&sa, sizeof(sa));
    if (n == SOCKET_ERROR)
    {
        cout << "bind绑定端口失败！" << endl;
        cout << "错误码是：" << WSAGetLastError() << endl;
        return -1;
    }
    else
    {
        cout << "端口发布成功:" << PORT << endl;
    }
    listen(sock, 5); //第二个参数一般设置5

    char s[256] = { 0 };
    while (true)
    {
        SOCKET socka = accept(sock, NULL, NULL); //第二三个参数是连接者的ip和端口等信息，是返回类型的值，不需要可以置null
        _beginthread(recvProc, 0, (void*)socka); //void*指向任何类型的指针
    }
    return 0;
}
