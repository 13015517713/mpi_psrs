#include "common.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

float rand_float(float s){
	return 4*s*(1-s);
}
void matrix_gen(float *a,ll N,float seed){
	float s=seed;
	for(ll i=0;i<N;i++){
		s=rand_float(s);
		a[i]=s;
	}
}
static int cmp(const void *p1, const void *p2){
    return (*(float*)p1) > (*(float*)p2);
}
void q_sort(void *start, ll n){
    qsort(start, n, sizeof(float), cmp);
}
void pperror(const char *str){
    perror(str);
    exit(1);
}
void write_to_file(float *start, ll n, char* filename){
    int fd = open(filename, O_RDWR|O_CREAT|O_TRUNC|O_APPEND);
    if (fd<0) {pperror("open errors.");}
    ll len = write(fd, start, float_size*n);
    if (len<0) pperror("write errors.");
    while(len < float_size*n){
        ll t_len = write(fd, start+int(len/float_size), float_size*n-len);
        if (t_len<0) pperror("write errors.");
        len += t_len; 
    }
    close(fd);
}
int main(){
    ll n = ll(space_size/float_size);

    // 生成数据
    float data[n+1];
    float seed = 0.2;
    puts("generate starting.");
    matrix_gen(data, n, seed);
    puts("generate finished.");

    // 排序
    // clock_t begin = clock();
    // q_sort(data, n);
    // clock_t end = clock();
    // double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    // fprintf(stdout,"time cost %.5lf\n", time_spent);
    // exit(0);

    // 全部数据写到文件里
    // int fd = open("./data.all", O_WRONLY|O_CREAT|O_TRUNC|O_APPEND);
    // if (fd<0) pperror("open errors.");
    // ll len = write(fd, data, float_size*n);
    // if (len<0) pperror("write errors.");
    // while(len < float_size*n){
    //     ll t_len = write(fd, data+int(len/float_size), float_size*n-len);
    //     if (t_len<0) pperror("write errors.");
    //     len += t_len; 
    // }
    // close(fd);

    // 数据划分写到文件里
    int cur_len = 0;
    for (int i=1;i<=p;i++){
        int part_len;
        char filename[64];
        sprintf(filename, "%s/p_%d/part_%02d", basedir, p, i);
        if (i==p) part_len=n-cur_len;
        else part_len=n/p;
        write_to_file(data+cur_len, part_len, filename);
        cur_len += part_len;
    }


    return 0;
}