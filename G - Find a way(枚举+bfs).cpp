/**
题目简介：
伊菲的家在乡下，而梅基的家在市中心。于是，伊菲和梅基安排在KFC见面。西安有很多KFC，他们想选择一个花费总时间最短的KFC见面。
现在给你一张西安的地图，伊菲和梅基都可以上、下、左、右移动到相邻的地点，每移动一个位置花费11分钟。

Input
输入包含多个测试用例。
每个测试用例包括前两个整数n，m.（2<=n，m<=200）。
接下来的n行，每行包含m个字符。
“Y”表示伊菲的初始位置。
“M”表示梅基初始位置。
“#”死路；
'.'可走的路。
“@” KCF

Output
对于每个测试用例，输出伊菲和梅基花费的最短总时间。总有一家KFC可以让他们见面。

Sample Input
4 4
Y.#@
….
.#..
@..M
4 4
Y.#@
….
.#..
@#.M
5 5
Y..@.
.#…
.#…
@..M.
#…#

Sample Output
66
88
66
**/

/**
思路：用dfs遍历Y到每一个终点@的步数，用二维数组来存储步数；
void Bfs(int x, int y){
	memset(vis, 0, sizeof(vis));
	vis[x][y] = true;
	node temp;
	temp.x = x;
	temp.y = y;
	temp.step = 0;
	queue<node >q;
	q.push(temp);
	while(!q.empty()){
		node now = q.front();
		q.pop();
		if(mp[now.x][now.y] == '@'){
			mWay[now.x][now.y] = now.step;
		}
		node next;
		for(int i = 0; i <= 3; i ++){
			int xx = now.x+toX[i];
			int yy = now.y+toY[i];
			if(mp[xx][yy] != '#'&&xx>0&&yy>0&&xx<=n&&yy<=m&&!vis[xx][yy]){
				vis[xx][yy] = true;
				next.step = now.step+1; 
				next.x = xx;
				next.y = yy;
				q.push(next);
			}
		}
	}
}
另一个相同， 粘贴一遍， 换一个二维数组就好；
然后暴力枚举每一个终点，求最小值；
**/

//具体代码：
#include<bits/stdc++.h>
using namespace std;
const int N = 200 + 10;
const int inf = 0x3f3f3f3f;
struct node{
	int x, y;
	int step;
};
int yWay[N][N];
int mWay[N][N];
char mp[N][N];
bool vis[N][N];
int n, m;
int toX[4]{1,-1,0,0};
int toY[4]{0,0,1,-1};

void bfs(int x, int y){
	memset(vis, 0, sizeof(vis));
	vis[x][y] = true;
	node temp;
	temp.x = x;
	temp.y = y;
	temp.step = 0;
	queue<node >q;
	q.push(temp);
	while(!q.empty()){
		node now = q.front();
		q.pop();
		if(mp[now.x][now.y] == '@'){
			yWay[now.x][now.y] = now.step;
		}
		node next;
		for(int i = 0; i <= 3; i ++){
			int xx = now.x+toX[i];
			int yy = now.y+toY[i];
			if(mp[xx][yy] != '#'&&xx>0&&yy>0&&xx<=n&&yy<=m&&!vis[xx][yy]){
				vis[xx][yy] = true;
				next.step = now.step+1; 
				next.x = xx;
				next.y = yy;
				q.push(next);
			}
		}
	}
}
void Bfs(int x, int y){
	memset(vis, 0, sizeof(vis));
	vis[x][y] = true;
	node temp;
	temp.x = x;
	temp.y = y;
	temp.step = 0;
	queue<node >q;
	q.push(temp);
	while(!q.empty()){
		node now = q.front();
		q.pop();
		if(mp[now.x][now.y] == '@'){
			mWay[now.x][now.y] = now.step;
		}
		node next;
		for(int i = 0; i <= 3; i ++){
			int xx = now.x+toX[i];
			int yy = now.y+toY[i];
			if(mp[xx][yy] != '#'&&xx>0&&yy>0&&xx<=n&&yy<=m&&!vis[xx][yy]){
				vis[xx][yy] = true;
				next.step = now.step+1; 
				next.x = xx;
				next.y = yy;
				q.push(next);
			}
		}
	}
}
int main(){
	int start1, end1, start2, end2;
	while(cin >> n >> m&&n+m){
		for(int i = 1; i <= n; i ++){
			scanf("%s",mp[i]+1);	
		}
		for(int i = 1; i <= n; i ++){
			for(int j = 1; j <= m; j ++){
				if(mp[i][j] == 'Y'){
					start1 = i;
					end1 = j;
				}
				if(mp[i][j] == 'M'){
					start2 = i;
					end2 = j;
				}
			}
			
		}
		for(int i = 1; i <= n; i++){
			for(int j = 1; j <= m; j++){
				mWay[i][j] = yWay[i][j] = inf;
			}
		}
		bfs(start1, end1);
		Bfs(start2, end2);
		int ans = inf;
		for(int i = 1; i <= n; i++){
			for(int j = 1; j <= m; j++){
				if(mp[i][j] == '@')
					ans = min(ans, mWay[i][j]+yWay[i][j]);
			}
		}
		cout << 11*ans << endl;
	}
	return 0;
}
