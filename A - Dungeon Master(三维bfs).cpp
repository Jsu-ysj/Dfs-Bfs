/**
Description - 题目描述
XHK被困在一个三维的网吧中,现在要寻找最短路径逃生！ 空间由立方体单位构成 你每次向上下前后左右移动一个单位需要一分钟 
你不能对角线移动并且四周封闭 是否存在逃出生天的可能性？如果存在，则需要多少时间？

Input - 输入
　　输入第一行是一个数表示空间的数量。 　　每个空间的描述的第一行为L，R和C（皆不超过30）。 　
  L表示空间的高度。 　　R和C分别表示每层空间的行与列的大小。 　　随后L层地牢，每层R行，每行C个字符。 　
  每个字符表示空间的一个单元。'#'表示不可通过单元，'.'表示空白单元。你的起始位置在'S'，出口为'E'。 　　
  每层空间后都有一个空行。L，R和C均为0时输入结束。

Output - 输出
　　每个空间对应一行输出。
　　如果可以逃生，则输出如下
Escaped in x minute(s).
　　x为最短脱离时间。
　　如果无法逃生，则输出如下
Trapped!

Sample Input - 输入样例
3 4 5
S....
.###.
.##..
###.#

#####
#####
##.##
##...

#####
#####
#.###
####E

1 3 3
S##
#E#
###

0 0 0

Sample Output - 输出样例
Escaped in 11 minute(s).
Trapped!

**/

/**
思路：这个题目适合广搜， 用bfs；
应为该搜索是三维搜索，所以需要在原先搜索上再加一维，用三维数组char mp[N][N][N];
同时也用bool vis[N][N][N]标记；
数组存下六个搜索方向：
int to[6][3] = {{1,0,0},{-1,0,0},{0,1,0},{0,-1,0},{0,0,1},{0,0,-1}};
剩下就是三维bfs；
bool check(node a){
	bool flag = false;
	if(a.l >= 1 && a.l <= L){
		if(a.r >= 1 && a.r <= R){
			if(a.h >= 1 && a.h <= H){
				if(mp[a.l][a.r][a.h] != '#' && !vis[a.l][a.r][a.h]){
					flag = true;
				}
			}
		}
	}
	return flag;
}
int Bfs(){
	//q.clear();
	while(!q.empty()){
		q.pop();
	}
	q.push(start);
	vis[start.l][start.r][start.h] = 1;
	while(!q.empty()){
		node now = q.front();
		q.pop();
		if(now.l==end.l&&now.r==end.r&&now.h==end.h){
			return now.step;
		}
		node next;
		for(int i = 0; i < 6; i ++){
			next.l = now.l + to[i][0];
			next.r = now.r + to[i][1];
			next.h = now.h + to[i][2];
			next.step = now.step + 1;
			if(check(next)){
				q.push(next);
				vis[next.l][next.r][next.h] = 1;
			}
		}
	}
	return 0;
}
关键代码！！！！！

**/
//具体代码：
#include<iostream>
#include<queue>
using namespace std;
const int N = 100; 
struct node{
	int l, r, h;
	int step;
};
int L, R, H;
node start, end;
queue<node >q;
char mp[N][N][N];
bool vis[N][N][N];
int to[6][3] = {{1,0,0},{-1,0,0},{0,1,0},{0,-1,0},{0,0,1},{0,0,-1}};

bool check(node a){
	bool flag = false;
	if(a.l >= 1 && a.l <= L){
		if(a.r >= 1 && a.r <= R){
			if(a.h >= 1 && a.h <= H){
				if(mp[a.l][a.r][a.h] != '#' && !vis[a.l][a.r][a.h]){
					flag = true;
				}
			}
		}
	}
	return flag;
}
int Bfs(){
	//q.clear();
	while(!q.empty()){
		q.pop();
	}
	q.push(start);
	vis[start.l][start.r][start.h] = 1;
	while(!q.empty()){
		node now = q.front();
		q.pop();
		if(now.l==end.l&&now.r==end.r&&now.h==end.h){
			return now.step;
		}
		node next;
		for(int i = 0; i < 6; i ++){
			next.l = now.l + to[i][0];
			next.r = now.r + to[i][1];
			next.h = now.h + to[i][2];
			next.step = now.step + 1;
			if(check(next)){
				q.push(next);
				vis[next.l][next.r][next.h] = 1;
			}
		}
	}
	return 0;
}
int main(){
	while(cin >> L >> R >> H && L+R+H){
		start.l = start.h = start.r = 0;
		end.h = end.l = end.r = 0;
		for(int i = 1; i <= L; i ++){ // 高 
			for(int j = 1;  j <= R; j ++){ // 宽 
				for(int k = 1; k <= H; k ++){ // 长 
					cin >> mp[i][j][k];
					vis[i][j][k] = 0;
					if(mp[i][j][k] == 'S'){
						start.l = i;
						start.r = j;
						start.h = k;
						start.step = 0;
					}
					if(mp[i][j][k] == 'E'){
						end.l = i;
						end.r = j;
						end.h = k;
						end.step = 0;
					} 
				}
			}
		}
		int ans = Bfs();
	    if(ans){
	    	 cout<<"Escaped in "<< ans <<" minute(s)."<<endl;
		}else{
			cout << "Trapped!" << endl;
		}
	}
 	return 0;
}
