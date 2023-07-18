#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct p{
    float x;
    float y;
}POSITION;

int main(int argc,char *argv[]){
    int i,j;
    int city_N;
    FILE *fp;
    float **dist;

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

    fscanf(fp,"%d",&city_N);
    //printf("city_N = %d\n",city_N);

    char **cityname;
    POSITION *position;

    cityname = (char **)malloc(city_N * sizeof(char *));
    for (i = 0; i < city_N; i++) {
        cityname[i] = (char *)malloc(20 * sizeof(char));
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

    

    return 0;
}