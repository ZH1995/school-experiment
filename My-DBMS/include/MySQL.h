#ifndef MYSQL_H
#define MYSQL_H

#include <cstdio>
#include <cstdlib>
#include <string>
#include <set>
#include <vector>
using namespace std;

class MySQL : public string
{
    public:
        MySQL();
        void CreateTable(string TableName);
        void DropTable(string TableName);
        void InsertElement(string TableName , string username);
        void SelectTable(string TableName);
        void DeleteRecord(string TableName , string username);
        void UpdateAttribute(string TableName , string username);
        void AddAttribute(string TableName);
        void DropAttribute(string TableName , string AttributeName);
        bool CheckAttribute(string txt , string check_txt);
        virtual ~MySQL();

        bool IsTableExit(string TableName);
        vector<string> GetMegCreTab();
        bool CheckAttType(vector<string> vec);
        void WriTabAttFil(vector<string> vec , string TableName);
        void WriTabAttNumFil(vector<string> vec , string TableName);
        void CreTabFil(vector<string> vec , string TableName);
        vector<string> AddAttMsg();
        void AddAttNum(vector<string> vec , string TableName);
        void AddAttToTabAtt(vector<string> vec , string TableName);
        void AddAttToTab(vector<string> vec , string TableName);
        bool IsSamAtt(vector<string> vec , string TableName);
        bool IsAttExist(string TableName , string attribute);

        int DropAttToTabAtt(string TableName , string attribute);
        void DropAttNum(string TableName , string attribute);
        void DropAttToTab(string TableName , string attribute , int col);

        vector<string> GetInsertMsg(string TableName);
        bool JudgeInsertType(vector<string> vec , string TableName);
        int JudgeMoreInsert(vector<string>vec ,string TableName);
        void WriInsertToTabFil(vector<string>vec ,string TableName);
        int GetAttributeNum(string TableName);

        vector< pair< pair<string , string > , int > > GetDelRecMsg();


        int Get_col_tablename(string TableName , string att);
        int Get_ope(string ope);
        void Equal_zero(string TableName , int *vis ,  string att_val , int it_col);
        void Equal_one(string TableName , int *vis , string att_val , int it_col);
        void Equal_two(string TableName , int *vis , string att_val , int it_col);
        void Equal_three(string TableName , int *vis , string att_val , int it_col);
        void Equal_four(string TableName , int *vis , string att_val , int it_col);
        void Equal_five(string TableName , int *vis , string att_val , int it_col);

        void CreateIndex(string TableName , string attribute);
        string TransIntToStr(int n);

        void UpdateIndex(string TableName);

        void SingleSelect(string TableName , vector< pair<string , string> > P , string *ope);
        void SingleTou(string TableName , vector<string> AttributeName);
        void SingleSelTou(string TableName , vector<string> AttributeName , vector< pair<string , string> > P , string *Ope);

        void MoreSelect(vector<string> tablename , vector< pair<string , string> >vec , string *ope);
        string SplitAtt(string x);
        string SplitTable(string x);
        void Deal_zero(string tablename1 , string tablename2 , int col1 , int col2 , int &vis , int col_where1 , int col_where2);

        void MoreSelLian(vector<string> tablename , vector< pair<string , string> > vec , string *ope);
        bool CheckAttValue(string x);
        int GetTableNameNum(string tablename1 , vector<string>Tablename);

        void MoreTouLian(vector<string> att , vector<string> tablename , vector< pair<string , string> >tiaojian , string *ope);
        int GetMoreCol(vector<string> Tablename , string att);
        void MoreSelTouLian(vector<string> att , vector<string> tablename , vector< pair<string , string> > tiaojian , string *ope);

        void Adduser(string user , string pass);
        void Deluser(string user , string pass);

        void GiveQ(vector<string> quan , string user);
        void DelQ(vector<string> quan, string user);

    protected:
    private:
};

#endif // MYSQL_H
