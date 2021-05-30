/**
可怜的fish在一次次被魔王掳走一次次被勇者们救回来之后，而今，不幸的他再一次面临生命的考验。
魔王已经发出消息说将在T时刻吃掉fish，因为他听信谣言说吃fish的肉也能长生不老。年迈的国王正
是心急如焚，告招天下勇者来拯救fish。不过fish早已习以为常，他深信智勇的勇者肯定能将他救出。
现据密探所报，fish被关在一个两层的迷宫里，迷宫的入口是S（0，0，0），fish的位置用P表示，时
空传输机用# 表示，墙用*表示，平地用.表示。勇者们一进入时空传输机就会被转到另一层的相对位置，
但如果被转到的位置是墙的话，那勇者们就会被撞死。勇者们在一层中只能前后左右移动，每移动一格
花1时刻。层间的移动只能通过时空传输机，且不需要任何时间。
Input
输入的第一行C表示共有C个测试数据，每个测试数据的前一行有三个整数N，M，T。 N，M迷宫的大
小N* M（1 <= N,M <=10) 。T如上所意。接下去的前N* M表示迷宫的第一层的布置情况，后N* M表示迷宫第二层的布置情况。
Output
如果勇者们能够在T时刻能找到fish就输出“YES”，否则输出“NO”。
Sample Input
1
5 5 14
S*#*.
.#...
.....
****.
...#.

..*.P
#.*..
***..
...*.
*.#..
Sample Output
YES
**/

/**
思路：二维bfs加一维来维护一层， 二层
有一个巧妙点：
for(int  j = 0; j < n; j ++){
			for(int k = 0 ; k < m ; k ++){
				if(Map[0][j][k]=='#'&&Map[1][j][k]=='*'){
					Map[0][j][k] = '*';
				}
				if(Map[0][j][k]=='*'&&Map[1][j][k]=='#'){
					Map[1][j][k] = '*';
				}
				if(Map[0][j][k]=='#'&&Map[1][j][k]=='#'){
					Map[0][j][k] = Map[1][j][k] = '*';
				}
			}
		}
    像这种情况直接给他堵死 换城墙 以免判断：
    **/

//具体代码：
#include<bits/stdc++.h>
using namespace std;
const int N = 20;
struct node{
	int x;
	int y;
	int z;
	int step;
};
int n, m, t;
int vis[N][N][N];
char Map[N][N][N];
int tox[] = {0, 0, 1, -1};
int toy[] = {1, -1, 0, 0};
void bfs(){
	memset(vis, 0 , sizeof(vis));
	node temp;
	temp.x = temp.y = temp.z = temp.step = 0;
	queue<node >q;
     while(!q.empty()){
     	q.pop();
	 }
	 q.push(temp);
	 vis[0][0][0] = 1;
	 while(!q.empty()){
	 	node now;
	 	now = q.front();
	 	q.pop();
	 	if(Map[now.z][now.x][now.y] == 'P'){
	 		cout << "YES" << endl;
	 		return ;
		 }
		 node next;
		 for(int i = 0; i < 4; i ++){
		 	int xx = now.x + tox[i];
		 	int yy = now.y + toy[i];
		 	int zz = now.z;
 		 	if(Map[zz][xx][yy] == '#'){
		 		zz = 1 -zz;
			 }
			 if(xx>=0&&xx<n&&yy>=0&&yy<m&&!vis[zz][xx][yy]&&Map[zz][xx][yy]!='*'&&now.step<t){
				 next.x = xx, next.y = yy, next.z = zz, next.step = now.step+1;
			 	vis[zz][xx][yy] = 1;
			 	q.push(next);
			 }
		 }
	 }
	 cout << "NO" << endl;
}
int main(){
	int T;
	cin >> T;
	while(T --){
		cin >> n >> m >> t;
		for(int i = 0; i <= 1; i ++){
			for(int j = 0; j < n; j ++){
				for(int k = 0; k < m; k ++){
					cin >> Map[i][j][k];
				}
			}
		}
//		for(int i = 0; i <= 1; i ++){
//			for(int j = 0; j < n; j ++){
//				for(int k = 0; k < m; k ++){
//					cout <<  Map[i][j][k];
//				}cout << endl;
//			}	
//		}
		for(int  j = 0; j < n; j ++){
			for(int k = 0 ; k < m ; k ++){
				if(Map[0][j][k]=='#'&&Map[1][j][k]=='*'){
					Map[0][j][k] = '*';
				}
				if(Map[0][j][k]=='*'&&Map[1][j][k]=='#'){
					Map[1][j][k] = '*';
				}
				if(Map[0][j][k]=='#'&&Map[1][j][k]=='#'){
					Map[0][j][k] = Map[1][j][k] = '*';
				}
			}
		}
		bfs();
	}
	return 0;
} 
