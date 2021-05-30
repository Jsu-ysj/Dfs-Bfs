/**
Ignatius再次被魔王抓走了(搞不懂他咋这么讨魔王喜欢)……

这次魔王汲取了上次的教训，把Ignatius关在一个n*m的地牢里，并在地牢的某些地方安装了带锁的门，钥匙藏在地牢另外的某些地方。刚开始Ignatius被关在(sx,sy)的位置，离开地牢的门在(ex,ey)的位置。Ignatius每分钟只能从一个坐标走到相邻四个坐标中的其中一个。魔王每t分钟回地牢视察一次，若发现Ignatius不在原位置便把他拎回去。经过若干次的尝试，Ignatius已画出整个地牢的地图。现在请你帮他计算能否再次成功逃亡。只要在魔王下次视察之前走到出口就算离开地牢，如果魔王回来的时候刚好走到出口或还未到出口都算逃亡失败。
Input
每组测试数据的第一行有三个整数n,m,t(2<=n,m<=20,t>0)。接下来的n行m列为地牢的地图，其中包括:

. 代表路
* 代表墙
@ 代表Ignatius的起始位置
^ 代表地牢的出口
A-J 代表带锁的门,对应的钥匙分别为a-j
a-j 代表钥匙，对应的门分别为A-J

每组测试数据之间有一个空行。
Output
针对每组测试数据，如果可以成功逃亡，请输出需要多少分钟才能离开，如果不能则输出-1。
Sample Input
4 5 17
@A.B.
a*.*.
*..*^
c..b*

4 5 16
@A.B.
a*.*.
*..*^
c..b*
Sample Output
16
-1
**/

/**
思路：
该题就是魔王题升级版， 写法差不多， 要多注意时间， 用一个状态压缩就是一样了；
这里要巧妙地使用2进制 ， 又是个钥匙， 10种状态
1<<10 == 1024;
a, b, c, d, e, f, g, h, j;
每一位对应一位数位的1；
int door = 1<<(Map[next.x][next.y]-'A');
int key =  1 << (Map[next.x][next.y]-'a');
						next.key|=key;
 再用一个三维数组每一点的状态就好
 int vis[N][N][1025];
**/

//具体题解：
#include<bits/stdc++.h>
using namespace std;
const int N = 30;
struct node {
	int time;
	int key;
	int x;
	int y;
} start, End;
int tox[4] = {0, 0, 1, -1};
int toy[4] = {1, -1, 0, 0};
char Map[N][N];
int vis[N][N][1025];
int n, m , t;

int bfs() {
	start.time = 0, start.key = 0;
	queue<node >q;
	q.push(start);
	vis[start.x][start.y][start.key] = 1;
	while(!q.empty()) {
		node now = q.front();
		q.pop();
		if(now.x == End.x && now.y == End.y && now.time < t) {
			return now.time;
		}
		for(int i = 0; i < 4; i ++) {
			node next;
			next.x = now.x + tox[i];
			next.y = now.y + toy[i];
			next.key = now.key;
			next.time = now.time + 1;
			if(next.x>=1&&next.y>=1&&next.x<=n&&next.y<=m&&Map[next.x][next.y]!='*'&&!vis[next.x][next.y][next.key]) {
				if(Map[next.x][next.y]>='A'&&Map[next.x][next.y]<='J') {
					int door = 1<<(Map[next.x][next.y]-'A');
					if(!(next.key&door)) {
						continue;
					}
				} 
				 if(Map[next.x][next.y]>='a'&&Map[next.x][next.y]<='j') {
						int key =  1 << (Map[next.x][next.y]-'a');
						next.key|=key;
				}
				vis[next.x][next.y][next.key] = 1;
				q.push(next);
			}
			
		}
	}
	return -1;
}
int main() {
	while(cin >> n >> m >> t) {
		memset(vis, 0, sizeof(vis));
		memset(Map, 0, sizeof(Map));
		for(int i = 1; i <= n ; i ++) {
			for(int j = 1; j <= m; j ++) {
				cin >> Map[i][j];
				if(Map[i][j] == '^') {
					End.x = i, End.y = j;
				}
				if(Map[i][j] == '@') {
					start.x = i, start.y = j;
				}
			}
		}
		cout << bfs() << endl;
	}
	return 0;
}
