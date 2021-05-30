/**
7月17日是Mr.W的生日，ACM-THU为此要制作一个体积为Nπ的M层生日蛋糕，每层都是一个圆柱体。
设从下往上数第i(1 <= i <= M)层蛋糕是半径为Ri, 高度为Hi的圆柱。当i < M时，要求Ri > Ri+1且Hi > Hi+1。
由于要在蛋糕上抹奶油，为尽可能节约经费，我们希望蛋糕外表面（最下一层的下底面除外）的面积Q最小。
令Q = Sπ
请编程对给出的N和M，找出蛋糕的制作方案（适当的Ri和Hi的值），使S最小。
（除Q外，以上所有数据皆为正整数）
Input
有两行，第一行为N（N <= 10000），表示待制作的蛋糕的体积为Nπ；第二行为M(M <= 20)，表示蛋糕的层数为M。
Output
仅一行，是一个正整数S（若无解则S = 0）。
Sample Input
100
2
Sample Output
68
Hint
圆柱公式
体积V = πR2H
侧面积A' = 2πRH
底面积A = πR2
**/

/**
思路：
先将pi 直接去掉， 不用管， 可以直接约调；
然后再将体积， 面积先算出来， 已被用；
void init(){
	for(int i = 1; i < 21; i ++){
		minV[i] = minV[i-1] + i*i*i; 
		minS[i] = minS[i-1] + i*i*2;
	}
}
让后还需要剪枝， 记住要剪得非常干净， 否则过不了
	// 剪枝 
	if(V + minV[C-1]>n){
		return ;
	} // 体积超过 
	if(S + minS[C-1] > ans){
		return;
	} // 面积比最小的大 
	//把后面的面积已最大半径估算，剪枝 
	int SS = (n-V)/R*2 + S;
	if(SS > ans){
		return ;
	} 
  if(V > n)return ; // 体积超标
  四种剪枝， 少一种都不行， 会时间超限；
  要从n+1较大的一端开始遍历， 一边找到最优解，而不遗漏;
  
**/

//具体代码：
#include<iostream>
using namespace std;
const int inf = 1e9;
const int N = 22;
// 这个提可以不要管pi的， 可以先约掉
int minV[N];
int minS[N]; 
int n, m;
int ans;
void init(){
	for(int i = 1; i < 21; i ++){
		minV[i] = minV[i-1] + i*i*i; 
		minS[i] = minS[i-1] + i*i*2;
	}
}

void Dfs(int V, int S, int C, int H, int R){
	if(V > n)return ; // 体积超标
	if(C == 0){
		if(V == n && S < ans){
			ans = S;
		}
		return ;
	} 
	
	// 剪枝 
	if(V + minV[C-1]>n){
		return ;
	} // 体积超过 
	if(S + minS[C-1] > ans){
		return;
	} // 面积比最小的大 
	//把后面的面积已最大半径估算，剪枝 
	int SS = (n-V)/R*2 + S;
	if(SS > ans){
		return ;
	} 
	
	for(int i = R-1; i >= C; i --) {
		if(C == m)	S = i*i;
		int HH = min((H-1),(n-V-minV[C-1])/(i*i)); //用顶部面积处理，预留最大的高度节省时间
		for(int j = HH; j >= C; j --){
			Dfs( V+i*i*j,S+2*i*j, C-1, j, i);
		}	
	}
	return ;
}
int main(){
	init(); //打表
	while(cin >> n >> m){
		ans = inf;
		Dfs(0, 0, m, n+1, n+1);
		if(ans == inf){
			cout << 0 << endl;
		}else{
			cout << ans << endl;
		}
	} 
	return 0;
} 
