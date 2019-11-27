#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <windows.h>
#include <string.h>
#define king 0x265A
#define Queen 0x265B
#define Rook 0x265C
#define Bishop 0x265D
#define Knight 0x265E
#define Pawn 0x265F
#define MAKEWHITE wprintf(L"\x1b[30m\x1b[47m")
#define MAKEBLACK wprintf(L"\x1b[37m\x1b[40m")
#define MAKEBLUE wprintf(L"\x1b[34m\x1b[44m")
#define MAKERED wprintf(L"\x1b[31m\x1b[41m")

typedef struct xy{
    int x, y; // xy축 좌표
}xy;

typedef struct UNIT{
    int move; // 이동횟수
    wchar_t type; // 말의 종류
    char WB;// 말의종류, 색깔
}UNIT;

UNIT arr[10][10]; // 체스판
char turn[3]="WB", player[2][20]={};
int tmp=0; // 턴 표시 1=검, 0=흰

void Setting(){ // 기본 말 위치
    setlocale( LC_ALL, "ko_KR.UTF-8" );
    wchar_t x[8]={Rook,Knight,Bishop,Queen,king,Bishop,Knight,Rook};
    for (int i=0;i<=9;i++){
        for (int j=0;j<=9;j++)
            arr[i][j].type=arr[i][j].move=arr[i][j].WB=0;
    }
    for (int i=1;i<=8;i++){
        arr[2][i].type=arr[7][i].type=Pawn;
        arr[1][i].type=arr[8][i].type=x[i-1];
        arr[2][i].WB=arr[1][i].WB='B';
        arr[7][i].WB=arr[8][i].WB='W';
    }
    wprintf(L"player 1: ");
    scanf("%s",player[0]);
    wprintf(L"player 2: ");
    scanf("%s",player[1]);
}

int Check(xy curr, xy next, wchar_t type){ // 각 말이 이동가능한지 체크
    if (type==Pawn){ // 폰
        if (arr[curr.x][curr.y].WB=='W'){ // 흰색
            if (next.x-curr.x==-1 && (next.y-curr.y==1 || next.y-curr.y==-1)) {
                if (arr[next.x][next.y].WB=='B')
                    if (next.x==1)
                        return 2;
                    else
                        return 1;
                else if (next.x==3 && arr[next.x+1][next.y].type==Pawn && arr[next.x+1][next.y].move==1 && arr[next.x+1][next.y].WB=='B'){
                    arr[next.x+1][next.y].move=arr[next.x+1][next.y].type=arr[next.x+1][next.y].WB=0;
                    return 1;
                }
            }
            if (arr[next.x][next.y].WB=='B')
                return 0; 
            if (arr[curr.x][curr.y].move==0 && next.x-curr.x==-2 && curr.y==next.y)
                return 1;
            if (next.x-curr.x==-1 && curr.y==next.y) {
                if (next.x==1)
                    return 2;
                else
                    return 1;
            }
        }
        if (arr[curr.x][curr.y].WB=='B'){ // 검은색
            if (next.x-curr.x==1 && (next.y-curr.y==1 || next.y-curr.y==-1)) {
                if (arr[next.x][next.y].WB=='W')
                    if (next.x==8)
                        return 2;
                    else
                        return 1;
                else if (next.x==6 && arr[next.x-1][next.y].type==Pawn && arr[next.x-1][next.y].move==1 && arr[next.x-1][next.y].WB=='W'){
                    arr[next.x-1][next.y].move=arr[next.x-1][next.y].type=arr[next.x-1][next.y].WB=0;
                    return 3;
                }
            }
            if (arr[next.x][next.y].WB=='W')
                return 0;
            if (arr[curr.x][curr.y].move==0 && next.x-curr.x==2 && curr.y==next.y)
                return 1;
            if (next.x-curr.x==1 && curr.y==next.y)
                if(next.x==8)
                    return 2;
                else
                    return 1;
        }
        // 가능하다면 return 1;
    }
    else if (type==Knight){ // 나이트
        if (abs(curr.x-next.x)==1 && abs(curr.y-next.y)==2)
            return 1;
        else if (abs(curr.x-next.x)==2 && abs(curr.y-next.y)==1)
            return 1;
        // 가능하다면 return 1;
    }
    else if (type==Rook){ // 룩
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
    else if (type==Bishop){ // 비숍
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
    else if (type==Queen){ // 퀸
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
    else if (type==king){ // 킹
        if (curr.x==next.x && arr[curr.x][curr.y].move==0){ //킹이 좌우로 움직이고 킹이 이동한 적이 없을 때
            UNIT prev=arr[next.x][next.y];
            arr[next.x][next.y]=arr[curr.x][curr.y];
            arr[curr.x][curr.y].move=arr[curr.x][curr.y].type=arr[curr.x][curr.y].WB=0;
            for (int i=1;i<=8;i++){
                for (int j=1;j<=8;j++){
                    if (arr[i][j].WB!=turn[tmp]){
                        xy enemy={i,j};
                        if (Check(enemy,curr,arr[i][j].type)){ //현재 체크 상태인 경우 리턴 0
                            arr[curr.x][curr.y]=arr[next.x][next.y];
                            arr[next.x][next.y]=prev;
                            return 0;
                        }
                        if (Check(enemy,next,arr[i][j].type)){ // 다음 이동이 자살일 경우 리턴 0
                            arr[curr.x][curr.y]=arr[next.x][next.y];
                            arr[next.x][next.y]=prev;
                            return 0;
                        }
                    }
                }
            }
            arr[curr.x][curr.y]=arr[next.x][next.y];
            arr[next.x][next.y]=prev;
            if (curr.y-next.y==2 && arr[curr.x][1].move==0){ //킹이 좌로 2칸 움직이고 룩이 이동한 적이 없을 때
                for(int i=curr.y-1;i>1;i--){ //킹과 룩 사이 기물 체크
                    if (arr[curr.x][i].type!=0)  //기물이 있으면 리턴 0
                        return 0;
                }
                arr[next.x][next.y+1]=arr[curr.x][1];
                arr[next.x][next.y+1].move++;
                arr[curr.x][1].move=arr[curr.x][1].WB=arr[curr.x][1].type=0;
                return 1;
            }
            if (curr.y-next.y==-2 && arr[curr.x][8].move==0){ //킹이 우로 2칸 움직이고 룩이 이동한 적이 없을 때
                for(int i=curr.y+1;i<8;i++){ //킹과 룩 사이 기물 체크
                    if(arr[curr.x][i].type!=0)  //기물이 있으면 리턴 0
                        return 0;
                }
                arr[next.x][next.y-1]=arr[curr.x][8];
                arr[next.x][next.y-1].move++;
                arr[curr.x][8].move=arr[curr.x][8].WB=arr[curr.x][8].type=0;
                return 1;
            }
        }
        if (abs(curr.x-next.x)<=1 && abs(curr.y-next.y)<=1){
            UNIT prev=arr[next.x][next.y];
            arr[next.x][next.y]=arr[curr.x][curr.y];
            arr[curr.x][curr.y].move=arr[curr.x][curr.y].type=arr[curr.x][curr.y].WB=0;
            for (int i=1;i<=8;i++){
                for (int j=1;j<=8;j++){
                    if (arr[i][j].WB!=turn[tmp]){
                        xy enemy={i,j};
                        if (Check(enemy,next,arr[i][j].type)){
                            arr[curr.x][curr.y]=arr[next.x][next.y];
                            arr[next.x][next.y]=prev;
                            return 0;
                        }
                    }
                }
            }
            arr[curr.x][curr.y]=arr[next.x][next.y];
            arr[next.x][next.y]=prev;
            return 1;
        }
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
        if (Check(curr,next,arr[curr.x][curr.y].type)==2){ // 승급
            wchar_t s[4] = {Queen, Bishop, Knight, Rook};
            int i;
            wprintf(L"폰 승급조건 달성\n");
            wprintf(L"승급 기물 선택(0 : 퀸, 1 : 비숍, 2 : 나이트, 3 : 룩) : ");
            scanf("%d",&i);
            arr[curr.x][curr.y].type=s[i];
        }
        arr[next.x][next.y]=arr[curr.x][curr.y];
        arr[next.x][next.y].move++;
        arr[curr.x][curr.y].move=arr[curr.x][curr.y].type=arr[curr.x][curr.y].WB=0;
        wprintf(L"%c%d의 말이 %c%d로 이동되었습니다.\n",ab.x%10-1+'A',9-ab.x/10,ab.y%10-1+'A',9-ab.y/10);
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
    ab.x=9-ab.x, ab.y=9-ab.y;
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
    int a,b;
    if (player[0][0] & 0x80)
        a=strlen(player[0])/3*2;
    else
        a=strlen(player[0]);
    if(player[1][0] & 0x80)
        b=strlen(player[1])/3*2;
    else
        b=strlen(player[1]);
    setlocale(LC_CTYPE,"");
    wprintf(L"      [A]  [B]  [C]  [D]  [E]  [F]  [G]  [H]\n");
    wprintf(L"   ");
    tmp ?  MAKEBLUE : MAKERED;
    if ((44-b)%2==0){
        for(int i=0;i<(44-b)/2;i++) wprintf(L"#");
        wprintf(L"\x1b[37m");
        wprintf(L"%s",player[1]);
        tmp ? MAKEBLUE : MAKERED;
        for(int i=0;i<(44-b)/2;i++) wprintf(L"#");
        wprintf(L"\n");
    }
    else{
        for(int i=0;i<(43-b)/2;i++) wprintf(L"#");
        wprintf(L"\x1b[37m");
        wprintf(L"%s",player[1]);
        tmp ? MAKEBLUE : MAKERED;
        for(int i=0;i<(45-b)/2;i++) wprintf(L"#");
        wprintf(L"\n");
    }
    MAKEBLACK;
    for (int i=1;i<=8;i++){
        wprintf(L"   ");
        tmp ?  MAKEBLUE : MAKERED;
        wprintf(L"##");
        for (int j=1;j<=8;j++){
            (i+j)%2 ? MAKEBLACK : MAKEWHITE;
            wprintf(L"     ");
            MAKEBLACK;
        }
        tmp ?  MAKEBLUE : MAKERED;
        wprintf(L"##\n");
        MAKEBLACK;
        wprintf(L"[%d]",9-i);
        tmp ?  MAKEBLUE : MAKERED;
        wprintf(L"##");
        for (int j=1;j<=8;j++){
            if (arr[i][j].type){
                (i+j)%2 ? MAKEBLACK : MAKEWHITE;
                wprintf(L"  ");
                arr[i][j].WB=='W' ? wprintf(L"\x1b[31m") : wprintf(L"\x1b[34m");
                wprintf(L"%lc",arr[i][j].type);
                (i+j)%2 ? MAKEBLACK : MAKEWHITE;
                wprintf(L"  ");
                MAKEBLACK;
            }
            else{
                (i+j)%2 ? MAKEBLACK : MAKEWHITE;
                wprintf(L"     ");
                MAKEBLACK;
            }
        }
        tmp ?  MAKEBLUE : MAKERED;
        wprintf(L"##");
        MAKEBLACK;
        wprintf(L"[%d]\n",9-i);
        wprintf(L"   ");
        tmp ?  MAKEBLUE : MAKERED;
        wprintf(L"##");
        for (int j=1;j<=8;j++){    
            (i+j)%2 ? MAKEBLACK : MAKEWHITE;
            wprintf(L"     ");
            MAKEBLACK;
        }
        tmp ?  MAKEBLUE : MAKERED;
        wprintf(L"##\n");
        MAKEBLACK;
    }
    wprintf(L"   ");
    tmp ?  MAKEBLUE : MAKERED;
    if ((44-a)%2==0){
        for(int i=0;i<(44-a)/2;i++) wprintf(L"#");
        wprintf(L"\x1b[37m");
        wprintf(L"%s",player[0]);
        tmp ? MAKEBLUE : MAKERED;
        for(int i=0;i<(44-a)/2;i++) wprintf(L"#");
        wprintf(L"\n");
    }
    else{
        for(int i=0;i<(43-a)/2;i++) wprintf(L"#");
        wprintf(L"\x1b[37m");
        wprintf(L"%s",player[0]);
        tmp ? MAKEBLUE : MAKERED;
        for(int i=0;i<(45-a)/2;i++) wprintf(L"#");
        wprintf(L"\n");
    }
    MAKEBLACK;
    wprintf(L"      [A]  [B]  [C]  [D]  [E]  [F]  [G]  [H]\n");
}

int Stalemate(){ // 스테일메이트 판별
    xy nowking={0,0};
    int dir[8][2]={{1,1},{1,0},{1,-1},{0,1},{0,-1},{-1,1},{-1,0},{-1,-1}};
    for (int i=1;i<=8;i++){ // 움직일수 있는 기물이 킹뿐인지 체크
        for (int j=1;j<=8;j++){
            if (arr[i][j].type==king && arr[i][j].WB==turn[tmp]) // 킹의 위치 저장
                nowking.x=i, nowking.y=j;
            else if (arr[i][j].WB==turn[tmp]){ // 다른아군이 있을경우 그 아군이 이동가능하면 탈출
                xy curr={i,j};
                for (int x=1;x<=8;x++){
                    for (int y=1;y<=8;y++){
                        xy next={x,y};
                        if (Check(curr,next,arr[i][j].type))
                            return 0;
                    }
                }
            }
        }
    }
    for (int i=0;i<8;i++){ // 킹이 이동가능한 칸이 한칸이라도 있는지 체크
        xy kingmove={nowking.x+dir[i][0],nowking.y+dir[i][1]};
        if (kingmove.x<1 || kingmove.y<1 || kingmove.x>8 || kingmove.y>8)
            continue;
        if (arr[kingmove.x][kingmove.y].WB!=turn[tmp] && Check(nowking,kingmove,king))
            return 0;
    }
    return 1;
}

int Checkmate(){ // 체크메이트 판별
    xy nowking={0,0};
    int dir[8][2]={{1,1},{1,0},{1,-1},{0,1},{0,-1},{-1,1},{-1,0},{-1,-1}};
    for (int i=1;i<=8;i++){
        for (int j=1;j<=8;j++){ // 킹의 위치 저장
             if (arr[i][j].type==king && arr[i][j].WB==turn[tmp])
                nowking.x=i,nowking.y=j;
        }
    }
    for (int i=0;i<8;i++){ // 킹이 이동가능한 칸이 한칸이라도 있는지 체크
        xy kingmove={nowking.x+dir[i][0],nowking.y+dir[i][1]};
        if (kingmove.x<1 || kingmove.y<1 || kingmove.x>8 || kingmove.y>8)
            continue;
        if (arr[kingmove.x][kingmove.y].WB!=turn[tmp] && Check(nowking,kingmove,king))
            return 0;
    }

    for (int i=1;i<=8;i++){
        for (int j=1;j<=8;j++){
            if (arr[i][j].WB!=turn[tmp]){ 
                xy enemy={i,j};
                if (Check(enemy,nowking,arr[i][j].type)){ // 킹위치에 이동가능한 적말들 체크 (체크상태임을 확인가능)
                    int chk=1;
                    for (int x=1;x<=8;x++){
                        for (int y=1;y<=8;y++){
                            if (arr[i][j].WB==turn[tmp] && arr[i][j].type!=king){ // 자신을 제외한 아군말 위치 체크
                                xy friend={x,y};
                                for (int xx=1;xx<=8;xx++){
                                    for (int yy=1;yy<=8;yy++){
                                        xy friendmove={xx,yy};
                                        if ((!(x==xx && y==yy)) && Check(friend,friendmove,arr[x][y].type)){ // 아군의 모든 이동 가능한경우 체크 (제자리 제외)
                                            UNIT prev=arr[friendmove.x][friendmove.y];
                                            arr[friendmove.x][friendmove.y]=arr[friend.x][friend.y];
                                            arr[friend.x][friend.y].move=arr[friend.x][friend.y].type=arr[friend.x][friend.y].WB=0; // 임시로 아군말을 이동
                                            if (!Check(enemy,nowking,arr[i][j].type)) // 다시 적군말이 킹을 공격할수 있는지 확인후 불가능하게 바뀌었을때
                                                chk=0;
                                            arr[friend.x][friend.y]=arr[friendmove.x][friendmove.y]; // 제자리로 원위치
                                            arr[friendmove.x][friendmove.y]=prev;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    if (chk) // 아군말로 막을수 있는경우가 하나도 없는경우
                        return 1;
                    //상대말 이동경로를 막을 수 있는 모든 우리말을 체크
                }
            }
        }
    }
    return 0; // 모든 공격이 다 막힐수 있을때
}

int Kingsdie(){
    xy nowking={-1,-1};
    for (int i=1;i<=8;i++){
        for (int j=1;j<=8;j++){ // 킹의 위치 저장
             if (arr[i][j].type==king && arr[i][j].WB!=turn[tmp])
                nowking.x=i,nowking.y=j;
        }
    }
    if (nowking.x==-1 && nowking.y==-1)
        return 1;
    return 0;
}


int main(){
    system("clear");
    Setting();
    while (1){
        int a;
        system("clear");
        Print();
        wprintf(L"항복하기 : 1\n");
        scanf("%d",&a);
        if (a){
            wprintf(L"%s이 항복했습니다. %s의 승리입니다.\n", player[tmp], player[tmp^1]);
            break;
        }
        while (Move(Scan(),turn[tmp]));
        if (Kingsdie()){
            system("clear");
            Print();
            wprintf(L"킹을 죽였습니다. %s의 승리입니다.\n", player[tmp]);
            break;
        }
        tmp^=1; // 턴이 넘어감
        if (Checkmate()){
            system("clear");
            Print();
            wprintf(L"체크메이트 입니다. %s의 승리입니다.\n", player[tmp^1]);
            break;
        }
        if (Stalemate()){
            system("clear");
            Print();
            wprintf(L"스테일메이트 입니다. 무승부입니다.\n");
            break;
        }
    }
    wprintf(L"게임이 종료됩니다.");
    return 0;
}