/**

简单介绍一下八数码问题：
在一个3×3的九宫格上，填有1~8八个数字，空余一个位置，例如下图：
1	2	3
4	5	6
7	8	 
在上图中，由于右下角位置是空的，你可以移动数字，比如可以将数字6下移一位：
1	2	3	 	1	2	3
4	5	6	→	4	5	 
7	8	 	 	7	8	6
或者将数字8右移一位：
1	2	3	 	1	2	3
4	5	6	→	4	5	6
7	8	 	 	7	 	8
1~8按顺序排列的情况称为“初始状态”（如最上方图）。“八数码问题”即是求解对于任意的布局，将其移动至“初始状态”的方法。
给定一个现有的九宫格布局，请输出将它移动至初始状态的移动方法的步骤。
Input
输入包含多组数据，处理至文件结束。每组数据占一行，包含8个数字和表示空位的‘x’，各项以空格分隔，表示给定的九宫格布局。
例如，对于九宫格
1	2	3
 	4	6
7	5	8
输入应为：1 2 3 x 4 6 7 5 8
注意，输入的数字之间可能有(不止一个？)空格。
Output
对于每组输入数据，输出一行，即移动的步骤。向上、下、左、右移动分别用字母u、d、l、r表示；如果给定的布局无法移动至“初始 状态”，请输出unsolvable。
如果有效的移动步骤有多种，输出任意即可。
Sample Input
2  3  4  1  5  x  7  6  8
Sample Output
ullddrurdllurdruldr
**/

/**思路
和我的课设差不多, 要节省时间， 使用Cantor来简化 
Cantor就是一个比它大的后数， 乘以对应位阶乘
const int jiecheng[9]={1,1,2,6,24,120,720,5040,40320}; //阶乘
int Cantor(int m[][3]){
    int res  = 0;
    
    //保存到以为数组方便计算
    int tmp[10],cnt = 0;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            tmp[cnt++] = m[i][j];
        }
    }

    //计算康托值
    for(int i = 0; i < 9; i++){
        int k = 0;
        for(int j = i+1; j < 9; j++){
            if(tmp[j] < tmp[i]) k++;
        }
        res+= jiecheng[9-i-1]*k;
    }
    return res;
}

然后就是bsf遍历
**/

//具体代码
#include<bits/stdc++.h>
using namespace std;
const int N  = 4e5+10;
const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1};
const char op[7] ="dlur";
bool vis[N];
int pre[N];
char preMay[N];

struct node{
    int m[3][3];
    int ok;
    int x,y;
}End;


const int jiecheng[9]={1,1,2,6,24,120,720,5040,40320}; //阶乘

int Cantor(int m[][3]){
    int res  = 0;
    
    //保存到以为数组方便计算
    int tmp[10],cnt = 0;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            tmp[cnt++] = m[i][j];
        }
    }

    //计算康托值
    for(int i = 0; i < 9; i++){
        int k = 0;
        for(int j = i+1; j < 9; j++){
            if(tmp[j] < tmp[i]) k++;
        }
        res+= jiecheng[9-i-1]*k;
    }
    return res;
}

void bfs(){

    queue<node> q;
    while(!q.empty()){
    	return ;
	}
    memset(vis,0,sizeof(vis));
    vis[End.ok] = true;
    q.push(End);
    pre[End.ok] = -1;
    while(!q.empty()){
        node now = q.front(); q.pop();
        for(int i = 0; i < 4; i++){
            int xx = now.x + dx[i];
			int yy = now.y + dy[i];
            if(xx <0 || xx >=3 || yy <0 || yy >= 3 ) continue;
            node next = now;
            swap(next.m[next.x][next.y],next.m[xx][yy]);
            next.ok = Cantor(next.m);
            if(vis[next.ok]) continue;

            vis[next.ok] = true;
            pre[next.ok] = now.ok;
            preMay[next.ok] = op[i];
            next.x = xx; next.y = yy;
            q.push(next);
        }
    }
}

void printRoad(int root){
    if(pre[root] == -1) return;
    printf("%c",preMay[root]);
    printRoad(pre[root]);
    
}

int main(){
    int cnt = 1;
    for(int i = 0; i < 3; i ++){
    	for(int j = 0; j < 3; j ++){
    		End.m[i][j] = cnt++;
		}
	}
    End.ok = Cantor(End.m);
    End.x = 2; End.y = 2;
    bfs();
     char str[20];
    while(gets(str)){
    	node Start;
        for(int i = 0,j = 0; j < 9 && str[i] != '\n'; i++){
            if(str[i] == ' ')continue;
            else if(str[i] == 'x') {
                Start.m[j/3][j%3] = 9;
                Start.x = j/3; Start.y = j%3;
            }
            else Start.m[j/3][j%3] = str[i]-'0';
            j++;
        }
        Start.ok = Cantor(Start.m);
        
        if(!vis[Start.ok]) printf("unsolvable\n");
        else{
            printRoad(Start.ok);
            printf("\n");
        }
    }
    return 0;
}
