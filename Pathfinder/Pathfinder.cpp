/*
	author: MD. Tamimul Ehsan
	last modified: August 8, 2008
*/
# include "iGraphics.h"
# include "gl.h"
#include<bits/stdc++.h>
using namespace std;

#define SC_WIDTH 1280
#define SC_HEIGHT 600

int menue[10],temppoint[2];

pair<int,int> source;
pair<int,int> dest,destmid,src;
vector< pair<int,int> >wall;
pair<int,int> wallappend;
int bwallappend;
bool locked=false;
bool found=false;

queue< pair<int,int> >q,q2;
stack< pair<int,int> > stk;
map< pair<int,int>,pair<int,int> > parent,parent2;
int vis[100][100],vis2[100][100];
int dx[]={-1,1,0,0};
int dy[]={0,0,-1,1};

void create_matrix(){
    sort(wall.begin(),wall.end());
    for(int i=0;i<wall.size();i++){
        vis[wall[i].first][ wall[i].second ]=1;
    }
}
void revpath(){
    int x1=destmid.first;int y1=destmid.second;
    while(x1!=dest.first or y1!=dest.second){

        pair<int,int> temp=parent2[{x1,y1}];
       // cout<<x1<<" "<<y1<<"     "<<temp.first<<" "<<temp.second<<endl;
        parent[temp]={x1,y1};
        x1=temp.first,y1=temp.second;
    }
}
void bfs(){
   if(q.size()!=0 and found==false){
    pair<int,int> u= q.front();
    int x=u.first; int y=u.second;
    q.pop();
    for(int i=0;i<4;i++){
        int ax=x+dx[i]; int ay=y+dy[i];
        if(ax>=0 and ay>=0 and ax<=80 and ay<=37 and vis[ax][ay]==0 and vis2[ax][ay]==0){
            vis[ax][ay]=1000;
            if(dest==make_pair(ax,ay) ) found=true;
            parent[{ax,ay}]={x,y};
            q.push({ax,ay});
        }
        else if(ax>=0 and ay>=0 and ax<=80 and ay<=37 and vis2[ax][ay]!=0 and vis[ax][ay]==0) destmid={ax,ay},parent[{ax,ay}]={x,y},found=true,revpath();
    }
   }
}

void bfs2(){
   if(q2.size()!=0 and found==false){
    pair<int,int> u= q2.front();
    int x=u.first; int y=u.second;
    q2.pop();
    for(int i=0;i<4;i++){
        int ax=x+dx[i]; int ay=y+dy[i];
        if(ax>=0 and ay>=0 and ax<=80 and ay<=37 and vis2[ax][ay]==0 and vis[ax][ay]==0){
            vis2[ax][ay]=1000;
            //if(dest==make_pair(ax,ay) ) found=true;
            parent2[{ax,ay}]={x,y};
            q2.push({ax,ay});
        }
        //else if(ax>=0 and ay>=0 and ax<=80 and ay<=37 and vis2[ax][ay]==0 and vis[ax][ay]!=0) destmid={ax,ay},found=true;
    }
   }
}

void dfs(){

    if(!stk.empty() and found==false ){
        pair<int,int> u=stk.top();
        stk.pop();
        int x=u.first; int y=u.second;
        vis[x][y]=1300;
        for(int i=0;i<4;i++){
            int ax=x+dx[i]; int ay=y+dy[i];
            if(ax>=0 and ay>=0 and ax<=80 and ay<=37 and vis[ax][ay]==0 and vis2[ax][ay]==0){
            vis[ax][ay]=1000;
            if(dest==make_pair(ax,ay) ) found=true;
            parent[{ax,ay}]={x,y};
            stk.push({ax,ay});
        }
        }
    }
}

/*void qbfs(){
    queue< pair<int,int> > emp;
    swap(emp,q);
    for(int i=0;i<100;i++) for(int j=0;j<100;j++) vis[i][j]=0;
     parent.clear();
    q.push(src);
    while(!q.empty() ){
        pair<int,int> u= q.front();
    int x=u.first; int y=u.second;
        q.pop();
         for(int i=0;i<4;i++){
        int ax=x+dx[i]; int ay=y+dy[i];
        if(ax>=0 and ay>=0 and ax<=80 and ay<=37 and vis[ax][ay]==0 /*and vis2[ax][ay]==0*//*){
            vis[ax][ay]=1;
            if(dest==make_pair(ax,ay) ) break;
            parent[{ax,ay}]={x,y};
            q.push({ax,ay});
        }
        //else if(ax>=0 and ay>=0 and ax<=80 and ay<=37 and vis2[ax][ay]!=0 and vis[ax][ay]==0) destmid={ax,ay},parent[{ax,ay}]={x,y},found=true,revpath();
    }
    }
}*/
void pathfinder(){
    if(menue[1] )q.push(src);
    else if(menue[2]){
            q.push(src);
            q2.push({dest.first,dest.second});}
    else if(menue[3]){
        stk.push(src);
    }

}

void drawgrid(){
    iSetColor(0,0,0);
    for(int i=0;i<=1280;i=i+16){
        iLine(i,0,i,600);
    }
    for(int i=0;i<=600;i=i+16){
        iLine(0,i,1280,i);
    }
}
void drawwall(){
    for(int i=0;i<wall.size();i++){
        int a=wall[i].first;
        int b=wall[i].second;
        iFilledRectangle(a*16,b*16,16,16);
    }
}
void fillwall(int x1,int y1){
    int x2=wallappend.first;
    int y2=wallappend.second;
    if(x1<x2){
        for(int i=x1;i<=x2;i++){
        wall.push_back({i,y1});
        }
    }
    else{
        for(int i=x1;i>=x2;i--){
        wall.push_back({i,y1});
        }
    }
    if(y1<y2){
        for(int i=y1;i<=y2;i++){
        wall.push_back({x2,i});
        }
    }
    else{
        for(int i=y1;i>=y2;i--){
        wall.push_back({x2,i});
        }
    }


    wallappend={x1,y1};
}
void showmodes(){
    iCircle(1130,500,10,100);
    iText(1150,495,"locked");

    iCircle(1130,470,10,100);
    iText(1150,465,"Wall append(w)");
    iSetColor(256,0,0);
    if(locked==true) iFilledCircle(1130,500,10,100);
    if(bwallappend) iFilledCircle(1130,470,10,100);
}
void showvis(){
    for(int i=0;i<90;i++)
    for(int j=0;j<90;j++){
        if(vis[i][j]!=0){
            if(vis[i][j]>1000) iSetColor(255,100,0);
            else if(vis[i][j]>600)iSetColor(0,256,0);
            else if(vis[i][j]>300) iSetColor(0,200,100);
            else if(vis[i][j]==1) iSetColor(0,100,50);
            iFilledRectangle(i*16,j*16,16,16);
            vis[i][j]=max(1,vis[i][j]-1);
        }
    }

     for(int i=0;i<90;i++)
    for(int j=0;j<90;j++){
        if(vis2[i][j]!=0){
            if(vis2[i][j]>600)iSetColor(0,256,0);
            else if(vis2[i][j]>300) iSetColor(0,200,100);
            else if(vis2[i][j]==1) iSetColor(0,100,50);
            iFilledRectangle(i*16,j*16,16,16);
            vis2[i][j]=max(1,vis2[i][j]-1);
        }
    }
}
void showpath(){
    int x1=dest.first; int y1=dest.second;
    while(x1!=src.first or y1!=src.second){
        pair<int,int> temp=parent[{x1,y1}];
        iSetColor(256,256,0);
        iFilledRectangle(x1*16,y1*16,16,16);
        x1=temp.first;y1=temp.second;
       // if(x1==y1==0) found=true;
    }
}
void showmenue(){
    iSetColor(0,255,255); iFilledRectangle(500,400,100,40); iSetColor(0,0,0); iText(530,410,"BFS",GLUT_BITMAP_HELVETICA_18);
    iSetColor(0,255,255); iFilledRectangle(500,320,100,40); iSetColor(0,0,0); iText(530,330,"BFS2",GLUT_BITMAP_HELVETICA_18);
    iSetColor(0,255,255); iFilledRectangle(500,240,100,40); iSetColor(0,0,0); iText(530,250,"DFS",GLUT_BITMAP_HELVETICA_18);

}

void allclear(){
    for(int i=0;i<100;i++) for(int j=0;j<100;j++) vis[i][j]=0,vis2[i][j]=0;
    stack< pair<int,int> > emp; swap(emp,stk);
    queue< pair<int,int> > empt; swap(q,empt);
    queue< pair<int,int> > empt2; swap(q2,empt2);
    for(int i=0;i<10;i++) menue[i]=0;
    found=false;
    menue[0]=1;
    create_matrix();

}

void iDraw()
{
    //place your drawing codes here

    iClear();
    iSetColor(256,256,256);
    iFilledRectangle(0,0,SC_WIDTH,SC_HEIGHT);
    if(menue[7]){
        showvis();
       if(found) showpath();
    }


    drawgrid();
    drawwall();
    showmodes();
    iSetColor(255, 100, 10);

    if(menue[0]==true){
        showmenue();
    }
    if(menue[8])    { iSetColor(0,0,0); iFilledRectangle(380,280,200,50); iSetColor(255,255,255); iText(400,300,"Click to input source",GLUT_BITMAP_HELVETICA_18);}
    if(menue[9])    { iSetColor(0,0,0); iFilledRectangle(380,280,250,50); iSetColor(255,255,255); iText(400,300,"Click to input destination",GLUT_BITMAP_HELVETICA_18);}


    iSetColor(255,0,0); iFilledCircle(src.first*16+8,src.second*16+8,8);
    iSetColor(0,0,2555); iFilledCircle(dest.first*16+8,dest.second*16+8,8);

    iSetColor(255, 255, 255);
    iText(10, 10, "Press p for pause, r for resume, END for exit.");
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
    //place your codes here
    if(bwallappend==0) wall.push_back({mx/16,my/16});
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if(!locked){
                if(bwallappend==1) {
                wallappend={mx/16,my/16};
                bwallappend=2;
        }
            else if(bwallappend==2) fillwall(mx/16,my/16);
            if(bwallappend==0) wall.push_back({mx/16,my/16});
        }

        if(menue[0]){
            int x=mx/100; int y=my/40;
            if(x==5 and y== 10) menue[1]=true;
            else if(x==5 and y==8) menue[2]=true;
            else if(x==5 and y==6) menue[3]=true; //xxx
            menue[0]=false;
            menue[7]=true;
            pathfinder();
        }
        else if(menue[8]){
            src={mx/16,my/16};
            menue[9]=true; menue[8]=false;
        }
        else if(menue[9]){
            dest={mx/16,my/16};
            menue[9]=false; menue[0]=true;
        }
       /* else if(menue[7] and found ){
            if(src==make_pair(mx/16,my/16)) temppoint[0]=true;
            if(dest==make_pair(mx/16,my/16)) temppoint[1]=true;
        }*/
        else if(temppoint[0]==true or temppoint[1]==true){
            if(temppoint[0]==true) src={mx/16,my/16};
            else dest={mx/16,my/16};
            menue[6]=true;
            pathfinder();
        }
    }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {

    }
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
    if(key == 'p')
    {
        //do something with 'q'
        iPauseTimer(0);
    }
    if(key == 'r')
    {
        iResumeTimer(0);
    }
    if(key=='w') {
        if(bwallappend>0) bwallappend=0;
        else bwallappend=1;
    }
    if(key=='c' and !locked){
        locked=true;
        menue[8]=true;
        create_matrix();
       // pathfinder();
    }
    if(key=='n' and found){
        allclear();
    }
    //place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{

    if(key == GLUT_KEY_END)
    {
        exit(0);
    }
    //place your codes for other keys here
}

void timer(){
    bfs();
    bfs2();
    dfs();

}
int main()
{
//    PlaySound((LPCSTR) "C:\\Users\\Public\\Music\\Sample Music\\Sleep Away.mp3", NULL, SND_FILENAME | SND_ASYNC);
//    DWORD dwError = GetLastError();

    //place your own initialization codes here.
    src={1380/16-1,630/16-1};
    dest={1380/16-1,630/16-1};
    iSetTimer(1,bfs);
    iSetTimer(1,bfs2);
    iSetTimer(1,dfs);
    iInitialize(SC_WIDTH,SC_HEIGHT, "PathFinder");

    return 0;
}

