//Nearest Neighbor法
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <stdbool.h>
#include <unistd.h>

#define NAME_SIZE 50

typedef struct p{
    float x;
    float y;
}POSITION;

void NN(float **dist,int n,int s,int *path,float *all_dist_min);

int main(int argc,char *argv[]){
    int i,j;
    int city_N;
    FILE *fp;
    float **dist;
    float all_dist_min;
    int s;

    if(argv[1]==NULL){
        printf("filename missed!\n");
        return -1;
    }

    fp = fopen(argv[1],"r");
    if(fp==NULL){
        printf("%s file not open!\n",argv[1]);
        return -1;
    }else {
		printf("%s file opened!\n", argv[1]);
	}

    s = atoi(argv[2]);

    if(!(0<=s || s<city_N))
        printf("start point is out of range!\n");

    fscanf(fp,"%d",&city_N);
    //printf("city_N = %d\n",city_N);

    char **cityname;
    POSITION *position;
    int *path;

    cityname = (char **)malloc(city_N * sizeof(char *));
    path = (int *)malloc(city_N * sizeof(int));
    for (i = 0; i < city_N; i++) {
        cityname[i] = (char *)malloc(NAME_SIZE * sizeof(char));
    }
    position = (POSITION *)malloc(city_N * sizeof(POSITION));

    for(i=0; i<city_N; i++){
        fscanf(fp,"%s %f %f",cityname[i],&position[i].x,&position[i].y);
        position[i].x *= 1000;
        position[i].y *= 1000;
        //printf("%s %f %f\n",cityname[i],position[i].x,position[i].y);
    }

    //完全グラフの隣接行列と重み行列を作成
    dist = (float **)malloc(city_N * sizeof(float *));
    for(i=0; i<city_N; i++){
        dist[i] = (float *)malloc(city_N * sizeof(float));
    }

    for(i=0; i<city_N; i++){
        for(j=0; j<city_N; j++){
            if(i==j)
                dist[i][j] = 0;
            else 
                dist[i][j] = sqrt(pow(position[i].x-position[j].x,2)+pow(position[i].y-position[j].y,2));
        }
    }

    printf("Nearest Neightbor法...\n");
    NN(dist,city_N,s,path,&all_dist_min);

    printf("\n");
    printf("最短経路は\n");
    for(i=0; i<city_N; i++){
        printf("%s → ",cityname[path[i]]);
    }
    printf("の順です。\n");

    printf("最短経路の距離は %f です。\n",all_dist_min);

    return 0;
}

//Nearest Neightbor法
void NN(float **dist,int n,int s,int *path,float *all_dist_min){
    int i,j,v;
    int *checked;
    *all_dist_min = 0;
    
    checked = (int *)malloc(n * sizeof(int));

    for(i=0; i<n; i++){
        checked[i] = 0;
    }

    checked[s] = 1;
    v = s;

    //すべての頂点を訪れたらループ終了
    i=0;
    while(i!=n){
        //現在の頂点から最も近い頂点を探す
        float min = FLT_MAX;
        for(j=0; j<n; j++){
            if(checked[j]==0 && dist[v][j]<min){
                min = dist[v][j];
                v = j;
                printf("頂点number%dの最小値更新 → %f\n",j,min);
                *all_dist_min += min;
            }
        }
        path[i] = v;
        checked[v] = 1;
        i++;
    }
}
