
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
    ifstream fin("test.txt");

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
 // cout << ans+10000<<endl;
 //   cout<<ans<<endl;
    code[u].push_back(ans+10000);
    dp[u].push_back(0);
    length[u]++;
}

void build(int i)
{
    code[i].clear();
    dp[i].clear();
  /*
    while(getline(cin,s) && s != "***END***")
    {
       hash(s,i);
    }
   */
       while(getline(fin,s) && s != "***END***")
    {
      //  cout<<"hash me:"<<s<<endl;
       hash(s,i);
    }

}
int main()
{
    int n;
    string c;
    string name[100];
   while(getline(fin,c))
     {
         n = c[0]-48;
         int len = 0,max_len = 0;
         memset(length,0,sizeof(length));

        // getchar();   // prevent skip get_line
         for(int i = 0 ;i < n; i++)
         {
          //   getline(cin, name[i]);
                getline(fin,name[i]);
       //         cout<<name[i]<<"i "<<i<<endl;
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
            for(int j = 0 ;j < n; j++)        //fragments to compare
            {
           //   for(int k = 0 ; k < length[j] ; k++)   // numbers of fragments (after hash)
            //  {
             //     cout<<"length"<<length[j]<<endl;
             //   cout<<"code"<<code[j][k]<<endl;
           //  cout<<"n"<<n<<endl;
                 if(dp[j][length[j]-1] == max_len && max_len!=0)  //if got same number
                 {
                   cout << " " << name[j];
                 //  break;
                 }

            }
            cout<<endl;
     //    for(int i=0;i<4;i++)
     //    cout<<"code:"<<code[0][i]<<endl;

     }
    return 0;
}

/*
#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <iostream>
#include <vector>
using  namespace  std;

typedef  unsigned  long  long  ull;

const  ull X = 123;
const  int  N = 105;

int  n, next[1000005];
string name[N];
string s;
vector< int > ans;
vector<ull> code[N];

void  hash(string s,  int  u) {
    string ss =  "" ;
    int  l = 0, r = s.length() - 1, len = s.length();;
    while  (s[l] ==  ' '  && l < len) l++;
    while  (s[r] ==  ' '  && r >= 0) r--;
    for  ( int  i = l; i <= r; i++) {
    ss += s[i];
    while  (s[i] ==  ' '  && s[i + 1] ==  ' '  && i < r) i++;
    }
    if  (ss ==  "" )  return ;
    ull ans = 0;
    for  ( int  i = ss.length() - 1; i >= 0; i--)
    ans = ans * X + ss[i];
    cout<<"l"<<l<<"r"<<r<<"ans"<<ans<<endl;
    code[u].push_back(ans);
}

void  build( int  i) {
    code[i].clear();
    while  (getline(cin, s) && s !=  "***END***" ) {
    hash(s, i);
    }
}

vector<ull> T;

void  getnext() {
    int  N = T.size();
    next[0] = next[1] = 0;
    int  j = 0;
    for  ( int  i = 2 ; i <= N; i++) {
    while  (j && T[i - 1] != T[j]) j = next[j];
    if  (T[i - 1] == T[j]) j++;
    next[i] = j;
    }
}

int  find() {
    int  ans = 0;
    int  N = code[n].size(), m = T.size(), j = 0;
    for  ( int  i = 0; i < N; i++) {
    while  (j && code[n][i] != T[j]) j = next[j];
    if  (code[n][i] == T[j]) j++;
    ans = max(ans, j);
    if  (j == m)
        return  m;
    }
    return  ans;
}

int  cal( int  u) {
    int  ans = 0;
    int  sz1 = code[u].size();
    for  ( int  i = 0; i < sz1; i++) {
    T.clear();
    for  ( int  j = i; j < sz1; j++)
        T.push_back(code[u][j]);
    getnext();
    ans = max(ans, find());
    }
    return  ans;
}

void  solve() {
    int  Max = 0;
    ans.clear();
    for  ( int  i = 0; i < n; i++) {
    int  tmp = cal(i);
    if  (tmp > Max) {
        Max = tmp;
        ans.clear();
        ans.push_back(i);
    }
    else  if  (tmp == Max) ans.push_back(i);
    }
    cout << Max;
    if  (Max) {
    for  ( int  i = 0; i < ans.size(); i++)
        cout <<  " "  << name[ans[i]];
    }
    cout << endl;
}

int  main() {
    while  (cin >> n) {
    getchar();
    for  ( int  i = 0; i < n; i++) {
        getline(cin, name[i]);
        build(i);
    }
    build(n);
    solve();
    }
    return  0;
}
*/
