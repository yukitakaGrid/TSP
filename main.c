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

void completeEnumerationMethod(float **d,int *data,int *mindata,float *m,int index,int n);

int main(int argc,char *argv[]){
    int i,j;
    int city_N;
    FILE *fp;
    float **dist;
    float dist_min = FLT_MAX;

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
    int *pathData_buffer;
    int *pathData_min;

    cityname = (char **)malloc(city_N * sizeof(char *));
    pathData_buffer = (int *)malloc(city_N * sizeof(int));
    pathData_min = (int *)malloc(city_N * sizeof(int));
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

    printf("完全列挙法...\n");
    completeEnumerationMethod(dist,pathData_buffer,pathData_min,&dist_min,0,city_N);

    printf("\n");
    printf("最短経路は\n");
    for(i=0; i<city_N; i++){
        printf("%s → ",cityname[pathData_min[i]]);
    }
    printf("の順です。\n");

    printf("最短経路の距離は %f です。\n",dist_min);

    return 0;
}

void completeEnumerationMethod(float **d,int *data,int *mindata,float *m,int index,int n){
    int i,j;
    if(index==n){
        float sum = 0;
        for(i=0; i<n-1; i++)
            sum += d[data[i]][data[i+1]];
        if(sum<*m){
            *m = sum;
            for(i=0; i<n; i++)
                mindata[i] = data[i];
        }

        /*for (int i = 0; i < n; i++) {
            printf("%d ", data[i]);
        }
        printf("\n%f\n",sum);*/

        return;
    }

    for(i=0; i<n; i++){
        //printf("深さ:%d 与えられる値:%d\n",index,i);
        bool isConfirmed = false;
        for(j=0; j<index; j++)
            if(data[j]==i)
                isConfirmed=true;

        if(isConfirmed)
            continue;

        data[index] = i;
        completeEnumerationMethod(d,data,mindata,m,index+1,n);
        //sleep(1); //debug用
    }
}
