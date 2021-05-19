/**
题目简介：
小明给你两个容器，分别能装下A升水和B升水，并且可以进行以下操作
FILL(i)        将第i个容器从水龙头里装满(1 ≤ i ≤ 2);
DROP(i)        将第i个容器抽干
POUR(i,j)      将第i个容器里的水倒入第j个容器（这次操作结束后产生两种结果，一是第j个容器倒满并且第i个容器依旧有剩余，二是第i个容器里的水全部倒入j中，第i个容器为空）
现在要求你写一个程序，来找出能使其中任何一个容器里的水恰好有C升，找出最少操作数并给出操作过程
Input
有且只有一行，包含3个数A,B,C（1<=A,B<=100,C<=max(A,B)）

Output
第一行包含一个数表示最小操作数K
随后K行每行给出一次具体操作，如果有多种答案符合最小操作数，输出他们中的任意一种操作过程，如果你不能使两个容器中的任意一个满足恰好C升的话，输出“impossible”
Sample Input
3 5 4
Sample Output
6
FILL(2)
POUR(2,1)
DROP(1)
POUR(2,1)
FILL(2)
POUR(2,1)
**/

/**
思路:
用二维数组vis[N][N]模拟， 标记这个状态；
模拟6种情况：
if(!vis[0][now.y]) {
			vis[0][now.y] = 1;
			next = now;
			next.step ++;
			next.x = 0;
			next.op[next.step] = "DROP(1)";
			q.push(next);
		}
		if(!vis[now.x][0]){
			vis[now.x][0] = 1;
			next = now;
			next.step ++;
			next.y = 0;
			next.op[next.step] = "DROP(2)";
			q.push(next);
		}
		if(!vis[a][now.y]){
			vis[a][now.y] = 1;
			next = now;
			next.step ++;
			next.x = a;
			next.op[next.step] = "FILL(1)";
			q.push(next);
		}
		if(!vis[now.x][b]){
			vis[now.x][b] = 1;
			next = now;
			next.step ++;
			next.y = b;
			next.op[next.step] = "FILL(2)";
			q.push(next);
		}
		if(now.x+now.y>b&&!vis[now.x+now.y-b][b]){
			vis[now.x+now.y-b][b] = 1;
			next = now;
			next.step ++;
			next.x = now.x+now.y-b;
			next.y = b;
			next.op[next.step]="POUR(1,2)";
			q.push(next);
		}
		if(now.x+now.y<=b&&!vis[0][now.x+now.y]){
			vis[0][now.x+now.y] = 1;
			next = now;
			next.step ++;
			next.x = 0;
			next.y = now.x + now.y;
			next.op[next.step]="POUR(1,2)";
			q.push(next);
		}
		if(now.x+now.y>a&&!vis[a][now.x+now.y-a]){
			vis[a][now.x+now.y-a] = 1;
			next = now;
			next.step ++;
			next.x = a;
			next.y = now.x + now.y-a;
			next.op[next.step]="POUR(2,1)";
			q.push(next);
		}
		if(now.x+now.y<=a&&!vis[now.x+now.y][0]){
			vis[now.x+now.y][0] = 1;
			next = now;
			next.step ++;
			next.x = now.x=now.y;
			next.y = 0;
			next.op[next.step]="POUR(2,1)";
			q.push(next);
		}
    
    结束条件：
    if(now.x == c || now.y == c){
			flag = true;
			endd = now;
			return ;
		}
    
**/

// 具体代码：
#include<iostream>
#include<queue>
#include<cstring>
using namespace std;
const int N = 1e3+10;
struct node{
	int x, y;
	int step;
	string op[N];
}endd;
int vis[N][N]; // 标记
int  a, b, c;
bool flag = false;
void bfs(){
	queue<node > q;
	memset(vis, 0, sizeof(vis));
	node now;
	now.x = 0;
	now.y = 0;
	now.step = 0;
	q.push(now);
	node next;
	while(!q.empty()){
		now = q.front();
		q.pop();
		if(now.x == c || now.y == c){
			flag = true;
			endd = now;
			return ;
		}
		if(!vis[0][now.y]) {
			vis[0][now.y] = 1;
			next = now;
			next.step ++;
			next.x = 0;
			next.op[next.step] = "DROP(1)";
			q.push(next);
		}
		if(!vis[now.x][0]){
			vis[now.x][0] = 1;
			next = now;
			next.step ++;
			next.y = 0;
			next.op[next.step] = "DROP(2)";
			q.push(next);
		}
		if(!vis[a][now.y]){
			vis[a][now.y] = 1;
			next = now;
			next.step ++;
			next.x = a;
			next.op[next.step] = "FILL(1)";
			q.push(next);
		}
		if(!vis[now.x][b]){
			vis[now.x][b] = 1;
			next = now;
			next.step ++;
			next.y = b;
			next.op[next.step] = "FILL(2)";
			q.push(next);
		}
		if(now.x+now.y>b&&!vis[now.x+now.y-b][b]){
			vis[now.x+now.y-b][b] = 1;
			next = now;
			next.step ++;
			next.x = now.x+now.y-b;
			next.y = b;
			next.op[next.step]="POUR(1,2)";
			q.push(next);
		}
		if(now.x+now.y<=b&&!vis[0][now.x+now.y]){
			vis[0][now.x+now.y] = 1;
			next = now;
			next.step ++;
			next.x = 0;
			next.y = now.x + now.y;
			next.op[next.step]="POUR(1,2)";
			q.push(next);
		}
		if(now.x+now.y>a&&!vis[a][now.x+now.y-a]){
			vis[a][now.x+now.y-a] = 1;
			next = now;
			next.step ++;
			next.x = a;
			next.y = now.x + now.y-a;
			next.op[next.step]="POUR(2,1)";
			q.push(next);
		}
		if(now.x+now.y<=a&&!vis[now.x+now.y][0]){
			vis[now.x+now.y][0] = 1;
			next = now;
			next.step ++;
			next.x = now.x=now.y;
			next.y = 0;
			next.op[next.step]="POUR(2,1)";
			q.push(next);
		}
	}
	return ;
} 
int main(){
	cin >> a >> b >> c;
	flag = false;
	bfs();
	if(!flag){
		cout <<  "impossible" << endl;
	}else{
		cout << endd.step << endl;
		for(int i = 1; i <= endd.step; i ++){
			cout << endd.op[i] << endl;
		}
	}
	return 0;
} 
