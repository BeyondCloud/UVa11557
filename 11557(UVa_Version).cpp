#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <vector>
#include <cstring>
#include <fstream>
using namespace std;
typedef unsigned long long ull;
short length[10001];
vector<ull> code[100];
vector<int> dp[100];
vector<int> ans;
string s;

void hash(string s,int u)
{
    ull ans = 0;
    for(int i = 0;i < s.length() ; i++)
    {
     if(s[i] == ' ')
           continue;
     else if(s[i-1] == ' ' && i!=0)
          ans = ans * 117 + s[i];
     else
          ans = ans * 123 + s[i];

    }

    code[u].push_back(ans+10000);
    dp[u].push_back(0);
    length[u]++;
}

void build(int i)
{
    code[i].clear();
    dp[i].clear();

    while(getline(cin,s) && s != "***END***")
    {
       hash(s,i);
    }



}
int main()
{
    int n;
    string name[100];
   while(cin>>n)
     {
         int len = 0,max_len = 0;
         memset(length,0,sizeof(length));

         getchar();   // prevent skip get_line
         for(int i = 0 ;i < n; i++)
         {
             getline(cin, name[i]);
             build(i);
         }
         build(n);   //this is main codes
         //compare code
           for(int i = 0 ;i < length[n]; i++) //single line of sample
         {
           for(int j = 0 ;j < n; j++)        //fragments to compare
            {
              for(int k = 0 ; k < length[j] ; k++)   // numbers of fragments (after hash)
              {
                 len = 0;
                 if(code[j][k] == code[n][i])  //if got same number
                 {
                     len++;
                     for(int l = 1; l< length[j] - k ; l++)
                     {
                         if(code[j][k+l] == code[n][i+l] && i+l < length[n])
                            {
                    //            cout<<"code"<<code[n][i+l];
                                len++;
                            }
                         else
                            break;

                     }
                 //    cout<<"len"<<len<<endl;

                 }
                    if(len >= max_len)
                    {
                         max_len = len;
                         dp[j][length[j]-1] = max_len;
                    }

                     //        cout<<"dp"<<dp[j][k]<<"j"<<j<<"k"<<k<<endl;
              }
            }
         }

         cout<<max_len;
            for(int j = 0 ;j < n; j++)
            {

                 if(dp[j][length[j]-1] == max_len && max_len!=0)
                 {
                   cout << " " << name[j];
                 }
            }
            puts("");
     }
    return 0;
}
