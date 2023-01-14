#include <iostream>
#include <MySQL.h>
#include <cstdio>
#include <string>
#include <cstring>
#include <cstdlib>
#include <fstream>
using namespace std;


void solve()
{
    string tp;
    ifstream infile("admin.txt");
    string tp1 , tp2 , username , tp4;
    vector< pair<string , string> > admin;
    while(infile >> tp1 >> tp2)
    {
        pair<string , string> p(tp1 , tp2);
        admin.push_back(p);
    }
    infile.close();
    cout << "Name:";
    int flag = 0;
    while(cin >> username)
    {
        cout << "Password:";
        cin >> tp4;
        for(vector< pair<string , string> >::iterator it = admin.begin() ; it != admin.end() ; it ++)
        {
            if((*it).first == username && (*it).second == tp4)
            {
                flag = 1;
                break;
            }
        }
        if(flag)    break;
        cout << "Name:";
    }
    MySQL mysql;
    string Command , TableName , AttributeName;
    cout << ">>>";
    while(cin >> Command)
    {
        if(Command == "create")
        {
            cin >> Command;
            if(Command == "table")
            {
                cin >> TableName;
                mysql.CreateTable(TableName);
            }
            else if(Command == "index")
            {
                string indexName , fen;
                cin >> indexName >> Command >> TableName >> AttributeName >> fen;
                if(indexName != (TableName + "_index") || Command != "on" || fen != ";")
                {
                    cout << "Input Erro! Please input again······" << endl;
                    continue;
                }
                mysql.CreateIndex(TableName , AttributeName);
            }
            else
            {
                cout << "Input Erro! Please input again······" << endl;
                continue;
            }
        }
        else if(Command == "drop")
        {
            cin >> Command;
            if(Command == "table")
            {
                cin >> TableName >> Command;
                mysql.DropTable(TableName);
            }
            else
            {
                cout << "Input Erro! Please input again······" << endl;
                continue;
            }
        }
        else if(Command == "insert")
        {
            cin >> Command;
            if(Command == "into")
            {
                cin >> TableName;
                cin >> Command;
                mysql.InsertElement(TableName , username);
            }
            else
            {
                cout << "Input Erro! Please input again······" << endl;
                continue;
            }
        }
        else if(Command == "select")
        {
            cin >> Command;
            if(Command == "*")
            {
                cin >> Command;
                cin >> TableName;
                cin >> Command;

                if(Command == ";")
                    mysql.SelectTable(TableName);
                else
                {
                    cout << "Input Erro! Please input again······" << endl;
                    continue;
                }
            }
            else
            {

            }
        }
        else if(Command == "singleTou;")
        {
            cout << "        >>>";
            cin >> Command;
            if(Command != "select")
            {
                    cout << "Input Erro! Please input again······" << endl;
                    continue;
            }
            vector<string> attribute;
            string tp , fen;
            while(cin >> tp)
            {
                if(tp == "from")    break;
                else if(tp == ",")  continue;
                else attribute.push_back(tp);
            }
            cin >> TableName >> fen;
            mysql.SingleTou(TableName , attribute);
        }
        else if(Command == "singleSel;")
        {
            cout << "        >>>";
            cin >> Command;
            if(Command != "select")
            {
                    cout << "Input Erro! Please input again······" << endl;
                    continue;
            }
            string all , from , where , tp1 , tp2 , tp3 , ope[31];
            cin >> all >> from >> TableName >> where;
            vector< pair<string , string> > vec;
            int id = 1;
            while(cin >> tp1)
            {
                if(tp1 == ";")  break;
                else if(tp1 == ",") continue;
                else
                {
                    cin >> tp2 >> tp3;
                    pair<string , string> p(tp1 , tp3);
                    vec.push_back(p);
                    ope[id++] = tp2;
                }
            }
            mysql.SingleSelect(TableName , vec , ope);
        }
        else if(Command == "singleSelTou;")
        {
            cout << "        >>>";
            cin >> Command;
            if(Command != "select")
            {
                    cout << "Input Erro! Please input again······" << endl;
                    continue;
            }
            vector<string> attribute;
            string tp;
            while(cin >> tp)
            {
                if(tp == "from")    break;
                else if(tp == ",") continue;
                else attribute.push_back(tp);
            }
            cin >> TableName;
            string where , tp1 , tp2 , tp3 , ope[31];
            cin >> where;
            vector< pair<string , string> > vec;
            int id = 1;
            while(cin >> tp1)
            {
                if(tp1 == ";")  break;
                else if(tp1 == ",") continue;
                else
                {
                    cin >> tp2 >> tp3;
                    pair<string , string> p(tp1 , tp3);
                    vec.push_back(p);
                    ope[id++] = tp2;
                }
            }
            mysql.SingleSelTou(TableName , attribute , vec , ope);
        }
        else if(Command == "moreSel;")
        {
            cout << "        >>>";
            cin >> Command;
            if(Command != "select")
            {
                    cout << "Input Erro! Please input again······" << endl;
                    continue;
            }
            string all , from , tp , tp1 , tp2 , tp3 , ope[31];
            vector<string> tablename;
            cin >> all >> from;
            while(cin >> tp)
            {
                if(tp == "where") break;
                else if(tp == ",") continue;
                else tablename.push_back(tp);
            }
            vector< pair<string , string> > vec;
            int id = 1;
            while(cin >> tp1)
            {
                if(tp1 == ";")  break;
                else if(tp1 == ",") continue;
                else
                {
                    cin >> tp2 >> tp3;
                    pair<string , string> p(tp1 , tp3);
                    vec.push_back(p);
                    ope[id++] = tp2;
                }
            }
            mysql.MoreSelect(tablename , vec , ope);
        }
        else if(Command == "moreSelLian;")
        {
            cout << "        >>>";
            cin >> Command;
            if(Command != "select")
            {
                    cout << "Input Erro! Please input again······" << endl;
                    continue;
            }
            string all , from , tp , tp1 , tp2 , tp3 , ope[31];
            vector<string> tablename;
            cin >> all >> from;
            while(cin >> tp)
            {
                if(tp == "where") break;
                else if(tp == ",") continue;
                else tablename.push_back(tp);
            }
            vector< pair<string , string> > vec;
            int id = 1;
            while(cin >> tp1)
            {
                if(tp1 == ";")  break;
                else if(tp1 == ",") continue;
                else
                {
                    cin >> tp2 >> tp3;
                    pair<string , string> p(tp1 , tp3);
                    vec.push_back(p);
                    ope[id++] = tp2;
                }
            }
            mysql.MoreSelLian(tablename , vec , ope);
        }

        else if(Command == "moreTouLian;")
        {
            cout << "        >>>";
            cin >> Command;
            if(Command != "select")
            {
                    cout << "Input Erro! Please input again······" << endl;
                    continue;
            }
            vector<string> att;
            string tp;
            while(cin >> tp)
            {
                if(tp == "from") break;
                else if(tp == ",") continue;
                else att.push_back(tp);
            }
            vector<string> tablename;
            while(cin >> tp)
            {
                if(tp == "where") break;
                else if(tp == ",") continue;
                else tablename.push_back(tp);
            }
            vector< pair<string , string> > tiaojian;
            string tp1 , tp2 , tp3 , ope[31];
            int id = 1;
            while(cin >> tp1)
            {
                if(tp1 == ";") break;
                else if(tp1 == ",") continue;
                else
                {
                    cin >> tp2 >> tp3;
                    pair<string , string> p(tp1 , tp3);
                    tiaojian.push_back(p);
                    ope[id++] = tp2;
                }
            }
            mysql.MoreTouLian(att , tablename , tiaojian , ope);
         }
         else if(Command == "moreSelTouLian;")
         {
             cout << "        >>>";
            cin >> Command;
            if(Command != "select")
            {
                    cout << "Input Erro! Please input again······" << endl;
                    continue;
            }
            vector<string> att;
            string tp;
            while(cin >> tp)
            {
                if(tp == "from") break;
                else if(tp == ",") continue;
                else att.push_back(tp);
            }
            vector<string> tablename;
            while(cin >> tp)
            {
                if(tp == "where") break;
                else if(tp == ",") continue;
                else tablename.push_back(tp);
            }
            vector< pair<string , string> > tiaojian;
            string tp1 , tp2 , tp3 , ope[31];
            int id = 1;
            while(cin >> tp1)
            {
                if(tp1 == ";") break;
                else if(tp1 == ",") continue;
                else
                {
                    cin >> tp2 >> tp3;
                    pair<string , string> p(tp1 , tp3);
                    tiaojian.push_back(p);
                    ope[id++] = tp2;
                }
            }
            mysql.MoreSelTouLian(att , tablename , tiaojian , ope);
         }
        else if(Command == "update")
        {
            cin >> TableName;
            cin >> Command;
            mysql.UpdateAttribute(TableName , username);
        }
        else if(Command == "delete")
        {
            cin >> Command;
            cin >> TableName;
            mysql.DeleteRecord(TableName , username);
        }
        else if(Command == "alter")
        {
            cin >> Command;
            cin >> TableName;
            cin >> Command;
            if(Command == "add")
                mysql.AddAttribute(TableName);
            else if(Command == "drop")
            {
                cin >> AttributeName;
                cin >> Command;
                mysql.DropAttribute(TableName , AttributeName);
            }
        }
        else if(Command == "adduser;")
        {
            string user , pass;
            cin >> user >> pass;
            mysql.Adduser(user , pass);
        }
        else if(Command == "deluser;")
        {
            string user , pass;
            cin >> user >> pass;
            mysql.Deluser(user , pass);
        }
        else if(Command == "giveq;")
        {
            cout << "    >>>";
            vector<string> quan;
            string tp;
            while(cin >> tp)
            {
                if(tp == "from") break;
                else if(tp == ",") continue;
                else quan.push_back(tp);
            }
            string user , fen;
            cin >> user >> fen;
            mysql.GiveQ(quan , user);
        }
        else if(Command == "delq;")
        {
            cout << "    >>>";
            vector<string> quan;
            string tp;
            while(cin >> tp)
            {
                if(tp == "from") break;
                else if(tp == ",") continue;
                else quan.push_back(tp);
            }
            string user , fen;
            cin >> user >> fen;
            mysql.DelQ(quan , user);
        }
        else if(Command == "exit;")
            break;
        else
        {
            cout << " Input Erro! Please input again······" << endl;
            continue;
        }
        cout << ">>>";
    }
}

int main()
{
    solve();
    return 0;
}
