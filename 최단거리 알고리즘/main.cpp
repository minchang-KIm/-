#include<stdio.h>
#include<string.h>
#define MAX 105
#define MAX_INT 2147483647
FILE * file;
int data_map[MAX][MAX], D[MAX], R[MAX],route[MAX];
char city[MAX][40], stack[MAX], s_city[10] = {0}, t_city[10] = {0}; //city�� ������ �̸����� �����ϰ�, s_city�� ���۵��ø�, t_city�� �������ø� �����ϴ� �迭�Դϴ�.
int n, m;

int s_city_num(){ // ���۵��ø� �� ������ �ش��ϴ� ���ڿ� ������Ų ���� ��ȯ�ϴ� �Լ��Դϴ�.
    int i;
    for(i = 0; i < n; i++){
        if(strcmp(city[i], s_city) == 0) return i;
    }
}

int t_city_num(){ // �������ø� �� ������ �ش��ϴ� ���ڿ� ������Ų ���� ��ȯ�ϴ� �Լ��Դϴ�.
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

int pow(int a, int b){ // �Ǽ��� ������ �ϸ� ������ ���� ������ ������ �����Լ��� ���������մϴ�.
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
        while((t = fgetc(file)) != '\n' && t != EOF){ // ����ġ�� �Է¹ޱ� ���ؼ� �ݺ��մϴ�.
            stack[num] = t; // stack�� ����ġ�� �ش��ϴ� �� �ڸ����� �ֽ��ϴ�.
            num++; // stack�� ���̸� 1 ������ŵ�ϴ�.
        }
        for(i = num - 1; i >= 0; i--){ // ����ġ�� ������ �ڸ�����ŭ �ݺ��մϴ�.
            value += (stack[i] - '0') * pow(10, num - i - 1); // ����ġ�� ������ݴϴ�.
        }
        num = 0; // stack�� ���̸� 0���� �ʱ�ȭ�մϴ�.
        data_map[x][y] = value;
        data_map[y][x] = value;
    }
    file = fopen("city.txt", "r"); // ������ �̸��� ����� �ؽ�Ʈ�� �н��ϴ�.
    i = 0;
    j = 0;
    while((t = fgetc(file)) != EOF){ // ������ �̸��� �ѱ���� �޾ƿɴϴ�.
        if(t == '\n'){ // �ٹٲ��� �Ǹ�
            i++; // i�� 1 ������Ű��
            j = 0; // j�� 0���� �ʱ�ȭ�մϴ�.
        }
        else{
            city[i][j] = t; // city�迭�� �����̸��� �� ���ھ� �ֽ��ϴ�.
            j++; // j�� 1������ŵ�ϴ�.
        }
    }
    gets(s_city); // ���۵��ø� ������ ���·� �Է¹޽��ϴ�.
    gets(t_city); // �������ø� ������ ���·� �Է¹޽��ϴ�.
    dijkstra(s_city_num(), t_city_num());
    fclose(file); // ������ �ݾ��ݴϴ�.
    return 0;
}
