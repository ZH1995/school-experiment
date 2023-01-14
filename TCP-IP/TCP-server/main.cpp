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
    SOCKET socka = (SOCKET)p; //void*ת������

    int n = 0;
    set<char> bianhao;
    bianhao.clear();
    char pre = '0';
    string result = "";
    while((n = recv(socka, s, sizeof(s), 0)) > 0){
        s[n] = '\0';
        if(s[2] == '0'){ // У����������
            if(bianhao.count(s[3])){
                // �ѽ��ܹ���֡
                s2[0] = 'A';
                s2[1] = 'C';
                s2[2] = 'K';
                s2[3] = pre;
                s2[4] = '\0';
                cout << "�������˷�����Ϣ(���յ���֡)��" << s2 << endl;
                send(socka, s2, strlen(s2), 0);
            }
            else{
                cout << "�������˽�����Ϣ��" << s << endl;
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
                cout << "�������˷�����Ϣ��" << s2 << endl;
                send(socka, s2, strlen(s2), 0);
            }
        }
        else{
            // У������ش�
            cout << "�������˷�����Ϣ��У���쳣����" << s << endl;
            s2[0] = 'A';
            s2[1] = 'C';
            s2[2] = 'K';
            s2[3] = pre;
            s2[4] = '\0';
            cout << "�������˷�����Ϣ��" << s2 << endl;
            send(socka, s2, strlen(s2), 0);
        }
    }
    cout << "���������ս��ܽ��Ϊ��" << result << endl;
    result = "";
}
int main()
{
    int n;
    WSADATA wd;
    n = WSAStartup(MAKEWORD(2, 2), &wd);
    if (n)
    {
        cout << "WSAStartup��������" << endl;
        return -1;
    }
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (INVALID_SOCKET == sock)
    {
        cout << "socket����ʧ��!" << endl;
        cout << "�������ǣ�" << WSAGetLastError() << endl;
        return -1;
    }
    sockaddr_in sa = { AF_INET, htons(PORT) };
    n = bind(sock, (sockaddr*)&sa, sizeof(sa));
    if (n == SOCKET_ERROR)
    {
        cout << "bind�󶨶˿�ʧ�ܣ�" << endl;
        cout << "�������ǣ�" << WSAGetLastError() << endl;
        return -1;
    }
    else
    {
        cout << "�˿ڷ����ɹ�:" << PORT << endl;
    }
    listen(sock, 5); //�ڶ�������һ������5

    char s[256] = { 0 };
    while (true)
    {
        SOCKET socka = accept(sock, NULL, NULL); //�ڶ����������������ߵ�ip�Ͷ˿ڵ���Ϣ���Ƿ������͵�ֵ������Ҫ������null
        _beginthread(recvProc, 0, (void*)socka); //void*ָ���κ����͵�ָ��
    }
    return 0;
}
