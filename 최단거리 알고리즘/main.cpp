#include<stdio.h>
#include<string.h>
#define MAX 105
#define MAX_INT 2147483647
FILE * file;
int data_map[MAX][MAX], D[MAX], R[MAX],route[MAX];
char city[MAX][40], stack[MAX], s_city[10] = {0}, t_city[10] = {0}; //city는 도시의 이름들을 저장하고, s_city는 시작도시를, t_city는 도착도시를 저장하는 배열입니다.
int n, m;

int s_city_num(){ // 시작도시를 각 정점에 해당하는 숫자에 대응시킨 것을 반환하는 함수입니다.
    int i;
    for(i = 0; i < n; i++){
        if(strcmp(city[i], s_city) == 0) return i;
    }
}

int t_city_num(){ // 도착도시를 가 정점에 해당하는 숫자에 대응시킨 것을 반환하는 함수입니다.
    int i;
    for(i = 0; i < n; i++){
        if(strcmp(city[i], t_city) == 0) return i;
    }
}

void dijkstra(int s, int t){
    int i, j, h = 0;
    for(i = 0; i < n; i++){
        D[i] = MAX_INT;
        R[i] = 0;
        route[i] = i;
    }
    D[s] = 0;
    while(R[t] == 0){
        int min = MAX_INT, idx = 0;
        for(i = 0; i < n; i++){
            if(R[i] == 1) continue;
            else{
                if(min >= D[i]){
                    min = D[i];
                    idx = i;
                }
            }
        }
        R[idx] = 1;
        for(j = 0; j < n; j++){
            if(R[j] == 1) continue;
            else{
                if(data_map[idx][j] != 0){
                    if(D[j] > D[idx] + data_map[idx][j]){
                        D[j] = D[idx] + data_map[idx][j];
                        route[j] = idx;
                    }
                }
            }
        }
    }

    if(D[t] == MAX_INT) printf("none");
    else{
        while(1){
            if(i == s) break;
            if(h == 0){
                stack[h] = t;
                h++;
                i = t;
            }
            else{
                stack[h] = route[i];
                h++;
                i = route[i];
            }
        }
        for(i = h-1; i >= 0; i--) puts(city[stack[i]]);
        printf("\n%d", D[t]);
    }
}

int pow(int a, int b){ // 실수형 제곱을 하면 오류가 나기 때문에 정수형 제곱함수를 직접구현합니다.
    int i, t = 1;
    for(i = 0; i < b; i++){
        t *= a;
    }
    return t;
}

int main(){
    int x, y, value, num = 0, i, j;
    char N, M, t;
    file = fopen("map.txt", "r");
    N = fgetc(file);
    n = N - '0';
    t = fgetc(file);
    M = fgetc(file);
    m = M - '0';
    t = fgetc(file);
    while(t != EOF){
        t = fgetc(file);
        x = t - '0';
        t = fgetc(file);
        t = fgetc(file);
        y = t - '0';
        t = fgetc(file);
        value = 0;
        while((t = fgetc(file)) != '\n' && t != EOF){ // 가중치를 입력받기 위해서 반복합니다.
            stack[num] = t; // stack에 가중치에 해당하는 각 자릿수를 넣습니다.
            num++; // stack의 높이를 1 증가시킵니다.
        }
        for(i = num - 1; i >= 0; i--){ // 가중치의 숫자의 자릿수만큼 반복합니다.
            value += (stack[i] - '0') * pow(10, num - i - 1); // 가중치를 계산해줍니다.
        }
        num = 0; // stack의 높이를 0으로 초기화합니다.
        data_map[x][y] = value;
        data_map[y][x] = value;
    }
    file = fopen("city.txt", "r"); // 도시의 이름이 저장된 텍스트를 읽습니다.
    i = 0;
    j = 0;
    while((t = fgetc(file)) != EOF){ // 도시의 이름을 한글잤기 받아옵니다.
        if(t == '\n'){ // 줄바꿈이 되면
            i++; // i를 1 증가시키고
            j = 0; // j를 0으로 초기화합니다.
        }
        else{
            city[i][j] = t; // city배열에 도시이름을 한 글자씩 넣습니다.
            j++; // j를 1증가시킵니다.
        }
    }
    gets(s_city); // 시작도시를 문장의 형태로 입력받습니다.
    gets(t_city); // 도착도시를 문장의 형태로 입력받습니다.
    dijkstra(s_city_num(), t_city_num());
    fclose(file); // 파일을 닫아줍니다.
    return 0;
}
