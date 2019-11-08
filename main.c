#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
// ��=P, ����Ʈ=N, ��=R, ���=B, ��=Q, ŷ=K;

typedef struct xy{
    int x, y; // xy�� ��ǥ
}xy;

typedef struct UNIT{
    int move; // �̵�Ƚ��
    char type, WB;// ��������, ���
}UNIT;

UNIT arr[10][10]; // ü����
char turn[3]="WB";
int tmp=0; // �� ǥ�� 1=��, 0=��

void Setcolor (int text, int back){ // ���ڻ�,  ���� �ٲٱ�
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),text|(back<<4));
}

void Setting(){ // �⺻ �� ��ġ
    char a[8]={'R','N','B','Q','K','B','N','R'};
    for (int i=0;i<=9;i++){
        for (int j=0;j<=9;j++)
            arr[i][j].type=arr[i][j].move=arr[i][j].WB=0;
    }
    for (int i=1;i<=8;i++){
        arr[2][i].type=arr[7][i].type='P';
        arr[1][i].WB=arr[2][i].WB='B';
        arr[1][i].type=arr[8][i].type=a[i-1];
        arr[7][i].WB=arr[8][i].WB='W';
    }
}

int Check(xy curr, xy next, char type){ // �� ���� �̵��������� üũ
    if (type=='P'){ // ��
        if (arr[curr.x][curr.y].WB=='W'){ // ���
            if (arr[curr.x][curr.y].move==0 && next.x-curr.x==-2 && curr.y==next.y)
                return 1;
            if (next.x-curr.x==-1 && curr.y==next.y)
                return 1;
            if (arr[next.x][next.y].WB=='B' && next.x-curr.x==-1 && (next.y-curr.y==1 || next.y-curr.y==-1))
                return 1;
        }
        if (arr[curr.x][curr.y].WB=='B'){ // ������
            if (arr[curr.x][curr.y].move==0 && next.x-curr.x==2 && curr.y==next.y)
                return 1;
            if (next.x-curr.x==1 && curr.y==next.y)
                return 1;
            if (arr[next.x][next.y].WB=='W' && next.x-curr.x==1 && (next.y-curr.y==1 || next.y-curr.y==-1))
                return 1;
        }
        // �����ϴٸ� return 1;
    }
    else if (type=='N'){ // ����Ʈ
        // �����ϴٸ� return 1;
    }
    else if (type=='R'){ // ��
        if (curr.x == next.x) {
            int y = curr.y < next.y ? 1 : -1;
            int testy = curr.y;
            while (testy != next.y) {
                testy += y;
                if (arr[curr.x][testy].type != 0) {
                    return 0;
                }
            }
        }
        else if (curr.y == next.y) {
            int x = curr.x < next.x ? 1 : -1;
            int testx = curr.x;
            while (testx != next.x) {
                testx += x;
                if (arr[testx][curr.y].type != 0) {
                    return 0;
                }
            }
        }
        return 1;
        // �����ϴٸ� return 1;
    }
    else if (type=='B'){ // ���
        if (abs(curr.x - next.x) == abs(curr.y - next.y)) {
            int x, y;
            x = curr.x < next.x ? 1 : -1;
            y = curr.y < next.y ? 1 : -1;
            int testx = curr.x, testy = curr.y;
            while (testx != next.x && testy != curr.y) {
                testx += x;
                testy += y;
                if (arr[testx][testy].type != 0) {
                    return 0;
                }
            }
            return 1;
        } else {
            return 0;
        }
        // �����ϴٸ� return 1;
    }
    else if (type=='Q'){ // ��
        // �����ϴٸ� return 1;
    }
    else if (type=='K'){ // ŷ
        // �����ϴٸ� return 1;
    }
    return 0;
}

int Move(xy ab, char c){ //�̵�
    xy curr={ab.x/10,ab.x%10}, next={ab.y/10,ab.y%10};
    if (c!=arr[curr.x][curr.y].WB){
        printf("�ڽ��� ���� �ƴմϴ�. �ٽ� �Է��� �ּ���.\n");
        return 1;
    }
    if (arr[curr.x][curr.y].WB==arr[next.x][next.y].WB){
        printf("�̹� �Ʊ����� �����ϴ� ��ġ�Դϴ�. �ٽ� �Է��� �ּ���.\n");
        return 1;
    }
    if (Check(curr,next,arr[curr.x][curr.y].type)){
        arr[next.x][next.y]=arr[curr.x][curr.y];
        arr[next.x][next.y].move++;
        arr[curr.x][curr.y].move=0;
        arr[curr.x][curr.y].type=0;
        arr[curr.x][curr.y].WB=0;
        printf("%c%d�� ���� %c%d�� �̵��Ǿ����ϴ�.\n",ab.x/10-1+'A',ab.x%10,ab.y/10-1+'A',ab.y%10);
        return 0;
    }
    else{
        printf("�Ұ����� ��ġ�Դϴ�. �ٽ� �Է��� �ּ���.\n");
        return 1;
    }
}

xy Scan(){ // �Է�
    char a, b;
    xy ab;
    scanf(" %c%d %c%d", &a, &ab.x, &b, &ab.y);
    if (a>='a' && a<='z')
        ab.x+=(a-'a'+1)*10;
    else
        ab.x+=(a-'A'+1)*10;
    if (b>='a' && b<='z')
        ab.y+=(b-'a'+1)*10;
    else
        ab.y+=(b-'A'+1)*10;
    return ab;
}

void Print(){// ���
    printf("    [1] [2] [3] [4] [5] [6] [7] [8]\n");
    printf("   #################################\n");
    for (int i=1;i<=8;i++){
        printf("   #   #   #   #   #   #   #   #   #\n");
        printf("[%c]",i+'A'-1);
        for (int j=1;j<=8;j++){
            if (arr[i][j].type){
                printf("# ");
                if (arr[i][j].WB=='W')
                    Setcolor(7,8);
                else
                    Setcolor(0,8);
                printf("%c",arr[i][j].type);
                Setcolor(7,0);
                printf(" ");
            }
            else
                printf("#   ");
        }
        printf("#[%c]\n",i+'A'-1);
        printf("   #   #   #   #   #   #   #   #   #\n");
        printf("   #################################\n");
    }
    printf("    [1] [2] [3] [4] [5] [6] [7] [8]\n");
}

int Stalemate(){ // �����ϸ���Ʈ �Ǻ�
    xy king={0,0};
    int chk[8]={0}, dir[8][2]={{1,1},{1,0},{1,-1},{0,1},{0,-1},{-1,1},{-1,0},{-1,-1}};
    for (int i=1;i<=8;i++){
        for (int j=1;j<=8;j++){
            if (arr[i][j].type=='K' && arr[i][j].WB==tmp)
                king.x=i,king.y=j;
            else if (arr[i][j].WB==tmp)
                return 0;
        }
    }
    for (int i=1;i<=8;i++){
        for (int j=1;j<=8;j++){
            if (arr[i][j].WB!=tmp){
                for (int k=0;k<8;k++){
                    if (chk[k])
                        continue;
                    xy kingmove={king.x+dir[k][0],king.y+dir[k][1]}, enemy={i,j};
                    if (Check(enemy,kingmove,arr[i][j].type))
                        chk[k]=1;
                }
            }
        }
    }
    for (int i=0;i<8;i++){
        if (!chk[i])
            return 0;
    }
    return 1;
}

int Checkmate(){ // üũ����Ʈ �Ǻ�
    xy king={0,0};
    int chk[9]={0}, dir[9][2]={{1,1},{1,0},{1,-1},{0,1},{0,0},{0,-1},{-1,1},{-1,0},{-1,-1}};
    for (int i=1;i<=8;i++){
        for (int j=1;j<=8;j++){
            if (arr[i][j].type=='K' && arr[i][j].WB==tmp)
                king.x=i,king.y=j;
        }
    }
    for (int i=1;i<=8;i++){
        for (int j=1;j<=8;j++){
            if (arr[i][j].WB!=tmp){
                for (int k=0;k<9;k++){
                    if (chk[k])
                        continue;
                    xy kingmove={king.x+dir[k][0],king.y+dir[k][1]}, enemy={i,j};
                    if (Check(enemy,kingmove,arr[i][j].type))
                        chk[k]=1;
                }
            }
        }
    }
    for (int i=0;i<9;i++){
        if (!chk[i])
            return 0;
    }
    return 1;
}

int main(){
    Setting();
    while (1){
        int a;
        Print();
        if (tmp)
            printf("�������� ���Դϴ�.\n");
        else
            printf("����� ���Դϴ�.\n");
        printf("�� �̵� : 0, �׺��ϱ� : 1\n");
        scanf("%d",&a);
        if (a){
            if (tmp)
                printf("�������� �׺��߽��ϴ�. ����� �¸��Դϴ�.\n");
            else
                printf("����� �׺��߽��ϴ�. �������� �¸��Դϴ�.\n");
            break;
        }
        while (Move(Scan(),turn[tmp]));
        tmp^=1; // ���� �Ѿ
        if (Checkmate()){
            if (tmp)
                printf("üũ����Ʈ �Դϴ�. �������� �¸��Դϴ�.\n");
            else
                printf("üũ����Ʈ �Դϴ�. ����� �¸��Դϴ�.\n");
            break;
        }
        if (Stalemate()){
            printf("�����ϸ���Ʈ �Դϴ�. ���º��Դϴ�.\n");
            break;
        }
    }
    printf("������ ����˴ϴ�.");
    return 0;
}
