#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
// 폰=P, 나이트=N, 룩=R, 비숍=B, 퀸=Q, 킹=K;

typedef struct xy{
    int x, y; // xy축 좌표
}xy;

typedef struct UNIT{
    int move; // 이동횟수
    char type, WB;// 말의종류, 흰검
}UNIT;

UNIT arr[10][10]; // 체스판
char turn[3]="WB";
int tmp=0; // 턴 표시 1=검, 0=흰

void Setcolor (int text, int back){ // 글자색, 배경색 바꾸기
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),text|(back<<4));
}

void Setting(){ // 기본 말 위치
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

int Check(xy curr, xy next, char type){ // 각 말이 이동가능한지 체크
    if (type=='P'){ // 폰
        if (arr[curr.x][curr.y].WB=='W'){ // 흰색
            if (arr[curr.x][curr.y].move==0 && next.x-curr.x==-2 && curr.y==next.y)
                return 1;
            if (next.x-curr.x==-1 && curr.y==next.y)
                return 1;
            if (arr[next.x][next.y].WB=='B' && next.x-curr.x==-1 && (next.y-curr.y==1 || next.y-curr.y==-1))
                return 1;
        }
        if (arr[curr.x][curr.y].WB=='B'){ // 검은색
            if (arr[curr.x][curr.y].move==0 && next.x-curr.x==2 && curr.y==next.y)
                return 1;
            if (next.x-curr.x==1 && curr.y==next.y)
                return 1;
            if (arr[next.x][next.y].WB=='W' && next.x-curr.x==1 && (next.y-curr.y==1 || next.y-curr.y==-1))
                return 1;
        }
        // 가능하다면 return 1;
    }
    else if (type=='N'){ // 나이트
        if (abs(curr.x-next.x)==1 && abs(curr.y-next.y)==2)
            return 1;
        else if (abs(curr.x-next.x)==2 && abs(curr.y-next.y)==1)
            return 1;
        // 가능하다면 return 1;
    }
    else if (type=='R'){ // 룩
        if (curr.x==next.x){
            int y=curr.y<next.y ? 1 : -1;
            int testy=curr.y;
            while (1){
                testy+=y;
                if (testy==next.y)
                    return 1;
                else if (arr[curr.x][testy].type!=0)
                    break;
            }
        }
        else if (curr.y==next.y){
            int x=curr.x<next.x ? 1 : -1;
            int testx=curr.x;
            while (1){
                testx+=x;
                if (testx==next.x)
                    return 1;
                else if (arr[testx][curr.y].type!=0)
                    break;
            }
        }
        // 가능하다면 return 1;
    }
    else if (type=='B'){ // 비숍
        if (abs(curr.x-next.x)==abs(curr.y-next.y)){
            int x, y;
            x=curr.x<next.x ? 1 : -1;
            y=curr.y<next.y ? 1 : -1;
            int testx=curr.x, testy=curr.y;
            while (1){
                testx+=x;
                testy+=y;
                if (testx==next.x && testy==next.y)
                    return 1;
                if (arr[testx][testy].type!=0)
                    break;
            }
        }
        // 가능하다면 return 1;
    }
    else if (type=='Q'){ // 퀸
        // 가능하다면 return 1;
    }
    else if (type=='K'){ // 킹
        // 가능하다면 return 1;
    }
    return 0;
}

int Move(xy ab, char c){ //이동
    xy curr={ab.x/10,ab.x%10}, next={ab.y/10,ab.y%10};
    if (curr.x<1 || curr.x>8 || curr.y<1 || curr.y>8 || next.x<1 || next.x>8 || next.y<1 || next.y>8){
        printf("체스판 밖입니다. 다시 입력해 주세요.\n");
        return 1;
    }
    if (c!=arr[curr.x][curr.y].WB){
        printf("자신의 말이 아닙니다. 다시 입력해 주세요.\n");
        return 1;
    }
    if (arr[curr.x][curr.y].WB==arr[next.x][next.y].WB){
        printf("이미 아군말이 존재하는 위치입니다. 다시 입력해 주세요.\n");
        return 1;
    }
    if (Check(curr,next,arr[curr.x][curr.y].type)){
        arr[next.x][next.y]=arr[curr.x][curr.y];
        arr[next.x][next.y].move++;
        arr[curr.x][curr.y].move=0;
        arr[curr.x][curr.y].type=0;
        arr[curr.x][curr.y].WB=0;
        printf("%c%d의 말이 %c%d로 이동되었습니다.\n",ab.x/10-1+'A',ab.x%10,ab.y/10-1+'A',ab.y%10);
        return 0;
    }
    else{
        printf("불가능한 위치입니다. 다시 입력해 주세요.\n");
        return 1;
    }
}

xy Scan(){ // 입력
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

void Print(){// 출력
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
/*
int Stalemate(){ // 스테일메이트 판별
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

int Checkmate(){ // 체크메이트 판별
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
*/
int main(){
    Setting();
    while (1){
        int a;
        Print();
        if (tmp)
            printf("검은색의 턴입니다.\n");
        else
            printf("흰색의 턴입니다.\n");
        printf("말 이동 : 0, 항복하기 : 1\n");
        scanf("%d",&a);
        if (a){
            if (tmp)
                printf("검은색이 항복했습니다. 흰색의 승리입니다.\n");
            else
                printf("흰색이 항복했습니다. 검은색의 승리입니다.\n");
            break;
        }
        while (Move(Scan(),turn[tmp]));
        tmp^=1; // 턴이 넘어감
        /*
        if (Checkmate()){
            if (tmp)
                printf("체크메이트 입니다. 검은색의 승리입니다.\n");
            else
                printf("체크메이트 입니다. 흰색의 승리입니다.\n");
            break;
        }
        if (Stalemate()){
            printf("스테일메이트 입니다. 무승부입니다.\n");
            break;
        }
        */
    }
    printf("게임이 종료됩니다.");
    return 0;
}
