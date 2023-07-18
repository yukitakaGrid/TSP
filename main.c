#include <stdio.h>
#include <stdlib.h>

typedef struct p{
    float x;
    float y;
}POSITION;

int main(int argc,char *argv[]){
    int i;
    int city_N;
    FILE *fp;

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
        //printf("%s %f %f\n",cityname[i],position[i].x,position[i].y);
    }

    //hello world

    //printf("%d\n",city_N);

    return 0;
}