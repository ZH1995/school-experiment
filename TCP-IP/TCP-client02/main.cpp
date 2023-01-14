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
        cout << "WSAStartup��������!" << endl;
        return -1;
    }
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (INVALID_SOCKET == sock)
    {
        cout << "socket����ʧ�ܣ�" << endl;
        return -1;
    }
    sockaddr_in sa = { AF_INET };   //�������һ���˿�
    n = bind(sock, (sockaddr*)&sa, sizeof(sa));
    if (n == SOCKET_ERROR)
    {
        cout << "bind����ʧ�ܣ�" << endl;
        cout << "�������ǣ�" << WSAGetLastError() << endl;
        return -1;
    }
    sa.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//115.200.33.112
    sa.sin_port = htons(PORT);
    n = connect(sock, (sockaddr*)&sa, sizeof(sa)); //ָ���˿ڷ�������
    if (n == SOCKET_ERROR)
    {
        cout << "connect����ʧ�ܣ�" << endl;
        cout << "�������ǣ�" << WSAGetLastError() << endl;
        return -1;
    }
    srand(time(NULL));
    time_t first, second;
    while (true)
    {
        fflush(stdin);
        gets(s);
        // ���鷢��
        int index = 0;
        int chaoshi_time = 0;
        int jiaoyan_time = 0;
        while(index < strlen(s)){

            // ���췢������
            char gen_s[5];
            // ֡��ţ�ż��0������1
            if(index & 1) gen_s[0] = '1';
            else gen_s[0] = '0';
            // ����֡
            gen_s[1] = s[index];
            // ���λ,0�����޴�

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
            // ����
            cout << "�ͻ��˷�����Ϣ��" << gen_s << endl;
            first = time(NULL); // ��ʼ����ʱ��
            send(sock, gen_s, strlen(gen_s), 0);
            // ��ʱ���������
            int timming = rand() % 2;
            if(timming != 0 && chaoshi_time < 2){
                // ������ʱ
                Sleep(3000);
                chaoshi_time ++;
            }
            else{
                Sleep(1000);
                if(chaoshi_time >= 2)
                    chaoshi_time = 0;
            }
            // ����
            fflush(stdin);
            recv(sock, s2, sizeof(s2), 0);
            second = time(NULL); // ��ֹʱ��
            if(difftime(second, first) - 2 <= 1e-9){
                // ���Լ���������һλ
                if(s2[3] != gen_s[0]){
                    cout << "�ͻ��˽�����Ϣ��" << s2 << endl;
                    index ++;
                }
                else{
                    cout << "У���ط�" << endl;
                }
            }
            else{
                cout << "��ʱ�ط�" << endl;
                continue;
            }
        }
    }
    return 0;
}
