/** 题目简介：
Now an emergent task for you is to open a password lock. The password is consisted of four digits. 
Each digit is numbered from 1 to 9.
Each time, you can add or minus 1 to any digit. When add 1 to '9', the digit will change to be '1'
and when minus 1 to '1', the digit will change to be '9'. You can also exchange the digit with its neighbor. 
Each action will take one step.

Now your task is to use minimal steps to open the lock.

Note: The leftmost digit is not the neighbor of the rightmost digit.
Input
The input file begins with an integer T, indicating the number of test cases.

Each test case begins with a four digit N, indicating the initial state of the password lock. 
Then followed a line with anotther four dight M, indicating the password which can open the lock. There is one blank line after each test case.
Output
For each test case, print the minimal steps in one line.
Sample Input
2
1234
2144

1111
9999
Sample Output
2
4
Sponsor
**/

/**思路：
分别模拟加+:
  for(int i = 0; i < 4; i ++){
			next = now;
			next.a[i] ++;
			if(next.a[i] == 10){
				next.a[i] = 1;
			}
			if(!vis[next.a[0]][next.a[1]][next.a[2]][next.a[3]]){
				vis[next.a[0]][next.a[1]][next.a[2]][next.a[3]] = 1;
				next.step++;
				q.push(next);			
			}	
		}
减：
  for(int i = 0; i < 4; i ++){
			next = now;
			next.a[i] --;
			if(next.a[i] == 0){
				next.a[i] = 9;
			}
			if(!vis[next.a[0]][next.a[1]][next.a[2]][next.a[3]]){
				vis[next.a[0]][next.a[1]][next.a[2]][next.a[3]] = 1;
				next.step++;
				q.push(next);			
			}	
		}
		
 换位：
 for(int i = 0; i < 3; i ++){
			next = now;
			next.a[i] = now.a[i+1];
			next.a[i+1] = now.a[i]; 
			if(!vis[next.a[0]][next.a[1]][next.a[2]][next.a[3]]){
				vis[next.a[0]][next.a[1]][next.a[2]][next.a[3]] = 1;
				next.step++;
				q.push(next);			
			}	
		}
	} 
  与密码相比较即可；
**/

// 具体代码：
#include<bits/stdc++.h>
using namespace std;
const int N = 10 + 1;
int vis[N][N][N][N];
struct node{
	int a[4];
	int step;
};
int start[4];
int End[4]; 

void bfs(){
	memset(vis, 0, sizeof(vis));
	node temp;
	for(int i = 0; i < 4; i ++){
		temp.a[i] = start[i];
	}
	temp.step = 0;
	queue<node>q;
	while(!q.empty()){
		q.pop();
	}
	q.push(temp);
	vis[start[0]][start[1]][start[2]][start[3]] = 1;
	while(!q.empty()){
		node now;
		now = q.front();
		q.pop();
		int flag = true;
		for(int i = 0; i < 4; i ++){
			if(now.a[i] != End[i]){
				flag = false;
				break;
			}
		}
		if(flag){
			cout << now.step << endl;
			return ;
		}
		node next;
		for(int i = 0; i < 4; i ++){
			next = now;
			next.a[i] ++;
			if(next.a[i] == 10){
				next.a[i] = 1;
			}
			if(!vis[next.a[0]][next.a[1]][next.a[2]][next.a[3]]){
				vis[next.a[0]][next.a[1]][next.a[2]][next.a[3]] = 1;
				next.step++;
				q.push(next);			
			}	
		}
		
		for(int i = 0; i < 4; i ++){
			next = now;
			next.a[i] --;
			if(next.a[i] == 0){
				next.a[i] = 9;
			}
			if(!vis[next.a[0]][next.a[1]][next.a[2]][next.a[3]]){
				vis[next.a[0]][next.a[1]][next.a[2]][next.a[3]] = 1;
				next.step++;
				q.push(next);			
			}	
		}
		
		for(int i = 0; i < 3; i ++){
			next = now;
			next.a[i] = now.a[i+1];
			next.a[i+1] = now.a[i]; 
			if(!vis[next.a[0]][next.a[1]][next.a[2]][next.a[3]]){
				vis[next.a[0]][next.a[1]][next.a[2]][next.a[3]] = 1;
				next.step++;
				q.push(next);			
			}	
		}
	} 
	
}
int main(){
	int T;
	cin >> T;
	while(T --){
		for(int i = 0; i < 4; i ++) 
			scanf("%1d", &start[i]);
		for(int i = 0; i < 4; i ++)
			scanf("%1d", & End[i]);
		bfs(); 
	}
	return 0;
}
