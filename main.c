#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <Windows.h>
#define B_king 0x2654
#define B_Queen 0x2655
#define B_Knight 0x2656
#define B_Bishop 0x2657
#define B_Rook 0x2658
#define B_Pawn 0x2659
#define W_king 0x265A
#define W_Queen 0x265B
#define W_Knight 0x265C
#define W_Bishop 0x265D
#define W_Rook 0x265E
#define W_Pawn 0x265F
#define MAKEWHITE wprintf(L"\x1b[47m\x1b[30m")
#define MAKEBLACK wprintf(L"\x1b[37m\x1b[40m")
// 폰=P, 나이트=N, 룩=R, 비숍=B, 퀸=Q, 킹=K;

typedef struct xy{
    int x, y; // xy축 좌표
}xy;

typedef struct UNIT{
    int move; // 이동횟수
    wchar_t type;
    char WB;// 말의종류, 색깔
}UNIT;

UNIT arr[10][10]; // 체스판
char turn[3]="WB";
int tmp=0; // 턴 표시 1=검, 0=흰

void Setting(){ // 기본 말 위치
    setlocale(LC_ALL,"");
    wchar_t w[8]={W_Rook,W_Knight,W_Bishop,W_Queen,W_king,W_Bishop,W_Knight,W_Rook};
    wchar_t b[8]={B_Rook,B_Knight,B_Bishop,B_Queen,B_king,B_Bishop,B_Knight,B_Rook};
    for (int i=0;i<=9;i++){
        for (int j=0;j<=9;j++)
            arr[i][j].type=arr[i][j].move=arr[i][j].WB=0;
    }
    for (int i=1;i<=8;i++){
        arr[7][i].type=W_Pawn;
        arr[2][i].type=B_Pawn;
        arr[1][i].WB=arr[2][i].WB='B';
        arr[1][i].type=b[i-1];
        arr[8][i].type=w[i-1];
        arr[7][i].WB=arr[8][i].WB='W';
    }
}

int Check(xy curr, xy next, wchar_t type){ // 각 말이 이동가능한지 체크
    if (type==W_Pawn || type==B_Pawn){ // 폰
        if (arr[curr.x][curr.y].WB=='W'){ // 흰색
            if (arr[next.x][next.y].WB=='B')
                return 0; 
            if (arr[curr.x][curr.y].move==0 && next.x-curr.x==-2 && curr.y==next.y)
                return 1;
            if (next.x-curr.x==-1 && curr.y==next.y)
                return 1;
            if (arr[next.x][next.y].WB=='B' && next.x-curr.x==-1 && (next.y-curr.y==1 || next.y-curr.y==-1))
                return 1;
        }
        if (arr[curr.x][curr.y].WB=='B'){ // 검은색
            if (arr[next.x][next.y].WB=='W')
                return 0; 
            if (arr[curr.x][curr.y].move==0 && next.x-curr.x==2 && curr.y==next.y)
                return 1;
            if (next.x-curr.x==1 && curr.y==next.y)
                return 1;
            if (arr[next.x][next.y].WB=='W' && next.x-curr.x==1 && (next.y-curr.y==1 || next.y-curr.y==-1))
                return 1;
        }
        // 가능하다면 return 1;
    }
    else if (type==W_Knight || type==B_Knight){ // 나이트
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
    else if (type==W_Bishop || type==B_Bishop){ // 비숍
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
    else if (type==W_Queen || type==B_Queen){ // 퀸
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
    else if (type==W_king || type==B_king){ // 킹
        // 가능하다면 return 1;
    }
    return 0;
}

int Move(xy ab, char c){ //이동
    xy curr={ab.x/10,ab.x%10}, next={ab.y/10,ab.y%10};
    if (curr.x<1 || curr.x>8 || curr.y<1 || curr.y>8 || next.x<1 || next.x>8 || next.y<1 || next.y>8){
        wprintf(L"체스판 밖입니다. 다시 입력해 주세요.\n");
        return 1;
    }
    if (c!=arr[curr.x][curr.y].WB){
        wprintf(L"자신의 말이 아닙니다. 다시 입력해 주세요.\n");
        return 1;
    }
    if (arr[curr.x][curr.y].WB==arr[next.x][next.y].WB){
        wprintf(L"이미 아군말이 존재하는 위치입니다. 다시 입력해 주세요.\n");
        return 1;
    }
    if (Check(curr,next,arr[curr.x][curr.y].type)){
        arr[next.x][next.y]=arr[curr.x][curr.y];
        arr[next.x][next.y].move++;
        arr[curr.x][curr.y].move=0;
        arr[curr.x][curr.y].type=0;
        arr[curr.x][curr.y].WB=0;
        wprintf(L"%c%d의 말이 %c%d로 이동되었습니다.\n",ab.x%10-1+'A',ab.x/10,ab.y%10-1+'A',ab.y/10);
        return 0;
    }
    else{
        wprintf(L"이동이 불가능한 위치입니다. 다시 입력해 주세요.\n");
        return 1;
    }
}

xy Scan(){ // 입력
    char a, b;
    xy ab;
    scanf(" %c%d %c%d", &a, &ab.x, &b, &ab.y);
    ab.x*=10, ab.y*=10;
    if (a>='a' && a<='z')
        ab.x+=(a-'a'+1);
    else
        ab.x+=(a-'A'+1);
    if (b>='a' && b<='z')
        ab.y+=(b-'a'+1);
    else
        ab.y+=(b-'A'+1);
    return ab;
}

void Print(){// 출력
    setlocale(LC_CTYPE,"");
    wprintf(L"     [A]   [B]   [C]   [D]   [E]   [F]   [G]   [H]\n");
    wprintf(L"   ");
    wprintf(L"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
    for (int i=1;i<=8;i++){
        wprintf(L"   ");
        for (int j=1;j<=8;j++){
            wprintf(L"■     ");
        }
        wprintf(L"■\n");
        wprintf(L"[%d]",i);
        for (int j=1;j<=8;j++){
            if (arr[i][j].type){
                wprintf(L"■  ");
                wprintf(L"%lc",arr[i][j].type);
                wprintf(L"  ");
            }
            else{
                wprintf(L"■     ");
            }
        }
        wprintf(L"■");
        wprintf(L"[%d]\n",i);
        wprintf(L"   ");
        for (int j=1;j<=8;j++){
            wprintf(L"■     ");
        }
        wprintf(L"■\n");
        wprintf(L"   ");
        wprintf(L"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
    }
    wprintf(L"     [A]   [B]   [C]   [D]   [E]   [F]   [G]   [H]\n");
}

int Stalemate(){ // 스테일메이트 판별
    xy king={0,0};
    int chk[8]={0}, dir[8][2]={{1,1},{1,0},{1,-1},{0,1},{0,-1},{-1,1},{-1,0},{-1,-1}};
    for (int i=1;i<=8;i++){
        for (int j=1;j<=8;j++){
            if ((arr[i][j].type==W_king || arr[i][j].type==B_king) && arr[i][j].WB==turn[tmp])
                king.x=i, king.y=j;
            else if (arr[i][j].WB==turn[tmp])
                return 0;
        }
    }
    for (int i=1;i<=8;i++){
        for (int j=1;j<=8;j++){
            if (arr[i][j].WB!=turn[tmp]){
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
/*
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
        system("clear");
        Print();
        if (tmp)
            wprintf(L"검은색의 턴입니다.\n");
        else
            wprintf(L"흰색의 턴입니다.\n");
        wprintf(L"말 이동 : 0, 항복하기 : 1\n");
        scanf("%d",&a);
        if (a){
            if (tmp)
                wprintf(L"검은색이 항복했습니다. 흰색의 승리입니다.\n");
            else
                wprintf(L"흰색이 항복했습니다. 검은색의 승리입니다.\n");
            break;
        }
        while (Move(Scan(),turn[tmp]));
        tmp^=1; // 턴이 넘어감
        /*
        if (Checkmate()){
            if (tmp)
                wprintf(L"체크메이트 입니다. 검은색의 승리입니다.\n");
            else
                wprintf(L"체크메이트 입니다. 흰색의 승리입니다.\n");
            break;
        }
        */
        if (Stalemate()){
            wprintf(L"스테일메이트 입니다. 무승부입니다.\n");
            break;
        }
    }
    wprintf(L"게임이 종료됩니다.");
    return 0;
}