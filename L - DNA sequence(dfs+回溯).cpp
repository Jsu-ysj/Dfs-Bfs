/**
21世纪是生物科技飞速发展的时代。我们都知道基因是由DNA组成的，而DNA的基本组成单位是A,C,G,T。在现代生物分子计算中，如何找到DNA之间的最长公共子序列是一个基础性问题。
但是我们的问题不是那么简单：现在我们给定了数个DNA序列，请你构造出一个最短的DNA序列，使得所有我们给定的DNA序列都是它的子序列。
例如，给定"ACGT","ATGC","CGTT","CAGT",你可以构造的一个最短序列为"ACAGTGCT"，但是需要注意的是，这并不是此问题的唯一解。
输入
第一行含有一个数t，代表数据组数。
每组数据的第一行是一个数n，代表给定的DNA序列数量；接下来的n行每行一个字符串s，代表给定的n个DNA序列。
1<=n<=8，1<=|s|<=5
输出
对于每一组数据，输出一行中含有一个数，代表满足条件的最短序列的长度。
样例输入
1
4
ACGT
ATGC
CGTT
CAGT
样例输出
8
**/

/**思路
该题就是竖着比较， 先预设一个len
		for(int i = 0; i < n; i ++){
//			cin >> str[i];
//			int len =  str[i].length();
//			max_len = max(max_len, len);
			cin >> str[i].a; str[i].length = str[i].a.length();
			max_len = max(str[i].length, max_len); 
		}
    这里不能用String 二维数组， 会超时， 每一次都需要用str.length()
    
    然后就是竖着遍历，发现不够提前添加：
    if(!flag || okLen + getLen() + 1> Len){
			continue;
		}//相当于剪枝
**/

//具体代码:
#include<bits/stdc++.h>
using namespace std;
const int N = 10;
//string str[N]; 这样写超时 ， 每次都要计算len
struct node{
	string a;
	int length;
}str[N]; 
int pos[N];
char DNA[4] = {'A', 'G', 'C', 'T'};
int n;
int Len;
int getLen(){
	int lenRest = 0;
	for(int i = 0; i < n; i ++){
//		int len = str[i].length();
//		lenRest = max(lenRest, len - pos[i]);
		lenRest = max(str[i].length - pos[i], lenRest);
	}
	return lenRest;
}
int dfs(int okLen){
	int lenRest = getLen();
	if(okLen == Len && lenRest == 0){
		return 1;
	}
	int tmp[10];
	memcpy(tmp, pos, sizeof(pos));
	for(int i = 0; i < 4; i ++){
		memcpy(pos, tmp, sizeof(tmp));
		int flag = 0;
		for(int j = 0; j < n; j ++){
			if(str[j].a[pos[j]] == DNA[i]){
				flag = 1;
				pos[j] ++;
			}
		}
		if(!flag || okLen + getLen() + 1> Len){
			continue;
		}
		 if(dfs(okLen + 1)){
			return 1;
		}
	}
	return 0;
}
int main(){
	int T; cin >> T;
	while(T --){
		cin >> n;
		int max_len = 0;
		for(int i = 0; i < n; i ++){
//			cin >> str[i];
//			int len =  str[i].length();
//			max_len = max(max_len, len);
			cin >> str[i].a; str[i].length = str[i].a.length();
			max_len = max(str[i].length, max_len); 
		}
	  	Len = max_len;
		while(true){
			memset(pos, 0, sizeof(pos));
			if(dfs(0)){
				break;
			}
			Len++;
		}
		cout << Len << endl;
	}
	return 0;
}
