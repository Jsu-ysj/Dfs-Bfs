/**
题目简介：
还记得2020年招新赛中“编织字符串”这一道题吗？
tls在ac完以后想出了一个更有趣的问题，具体是这样的：
给定两个长度均为len的字符串s1、s2和一个长度为len*2的字符串s，
每一次我们按照编织字符串的操作将s1和s2拼接起来（注意这里s2先拼接，具体请看样例），得到长度为len*2的字符串s'
然后令s1为s'的前一半，s2为s'的后一半，反复以上操作。
若在某一次中s'和s相等则结束循环。
假设有s1="JNU",s2="ACM",s="NAMJUC"
第一次操作后得到s'="AJCNMU"，与s不相等。
令s1="AJC",s2="NMU"
第二次操作后得到s'="NAMJUC"，与s相等，结束循环。
输出操作次数为2
Input
第一行一个整数T(1≤T≤1000)，代表测试数据组个数。
对于每组数据，第一行为len(1≤len≤100)，第二行为字符串s1，第三行为字符串s2，第四行为字符串s。
输入保证s1和s2长度均为len，s长度为len*2
Output
对每一组数据，输出数据组编号和答案。
如果无论经过多少次操作也无法结束循环，答案输出-1
Sample Input
2
3
JNU
ACM
NAMJUC
3
JNU
ACM
ACMJNU
Sample Output
1 2
2 -1
**/

/**
思路： 就是用几个字符串简单模拟， 用map来查重，重复则弹出，输出-1；
**/

//题解：
#include<iostream>
#include<cstring>
#include<map> 
using namespace std;
map<string, int >mp;
int main(){
	string a, b, c, s;
	int T;
	cin >> T;
	int k = 0;
	bool flag = true;
	while(T --){
		flag = true;
		++k;
		int len;
		cin >> len;
		cin >> a >> b >> s;
		mp.clear();
		int cnt = 0;
		while(true){
			cnt++;
			c.clear();
			for(int i = 0; i < len; i ++){
				c += b[i];
				c += a[i];
			}
			if(c == s){
				break;
			}
			if(mp[c]){
				flag = false;
				break;
			}else{
				mp[c] = 1;
			}
			a.clear();
			b.clear();
			for(int i = 0; i < len; i ++){
				a += c[i];
				b += c[i+len]; 
			}
		}
		cout << k << " ";
		if(flag){
			cout << cnt << endl;
		}else{
			cout << -1 << endl;
		}
	}
	return 0;
} 
