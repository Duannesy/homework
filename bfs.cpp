#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> Pa;
int bfs(){
	int dx,dy;
	queue<Pa> que;
	int i,j;
	int a;
	scanf("%d %d\n",&i,&j);
	char grd[i][j];
	int k,l;
	for(k=0;k<i;k++){
		for(l=0;l<j;l++){
			scanf("%c\n",&grd[k][l]);
		}
	}
	for(k=0;k<i;k++){
		for(l=0;l<j;l++){
			if(grd[k][l]=='W'){
				que.push(Pa(k,l));
				grd[k][l]=='.';
				while(que.size()){
					Pa p=que.front();
					que.pop();
					for(dx=-1;dx<2;dx++){
						for(dy=-1;dy<2;dy++){
							if(grd[p.first+dy][p.second+dx]=='W'&& 0<=dx+p.second && dx+p.second<=j && 0<=dy+p.first && dy+p.first<=i){
								grd[p.first+dy][p.second+dx]=='.';
								que.push(Pa(p.first+dy,p.second+dx));
							}
						}
					}
						
				}
				a++;
			}
			
		}
	}
	return a;
}
int main(){
	int sum=bfs();
	printf("%d",sum);
	return 0;
}
