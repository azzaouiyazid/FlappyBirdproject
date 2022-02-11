#include <iostream> 
#include <fstream>
#include <iomanip>
#include <ctime>
#include <conio.h>
#include <cstdlib>
#include <windows.h>


using namespace std;

ifstream ifp;  
ofstream ofp;

char c[30][21]; 
int n[30][21];  
int highscore;
int contr,tuk=0,score=0,t=0,bt=0,birdx=0,birdy=0; 
bool err;

void game();  
void walls();
void screen();
void menu();
void endgame();
void scorecheck();
void help();
void bird();
void credits();
bool gameover();

int main()
{
srand(time(0));  
ifp.open("options.txt"); 
if(ifp.is_open()) 
{
    ifp>>highscore;
    ifp.close();
    err=false;  
}
else
{
    highscore=0; 
    err=true;
}

int a=0,b;
char choice; 
while(1) 
{
    if(a==0) goto play; 
    if(a>0)              
    {
        score=0;
        cout<<"Do you want to play again? [y/n] ";
        cin>>choice;
        if(choice=='n') goto quit;
        else goto play;
    }
    play:
    menu(); 
    cin>>choice;
    switch(choice)
    {
        case '1':
        {
            game(); 
            break;
        }
        case '2': 
        {
            help(); 
            goto play;
            break;
        }
        case '3':
        {
            credits();
            goto play;
            break;
        }
        case '4':
        {
            goto quit; 
            break;
        }
        default:
        {
            goto play;
            break;
        }
    }
    a++; 
}
quit:
{
   cout<<"quit.";
}

return 0;
}

void game()  
{
    int x,y;
    char s;
    for(y=0;y<21;y++)  
    {
        for(x=0;x<30;x++)
        {
            if(y<20)
            {
            c[x][y]=' ';
            n[x][y]=0;
            }
            if(y==20)
            {
                c[x][y]='-';
                n[x][y]=2;
            }
        }
    }
    c[10][10]='*';  
    screen();      
    while(1)       
    {
        s='~'; 
        Sleep(0.2*1000); 
        t++;             
        if(kbhit()) 
        {
            s=getch();        
            if(s!='~') tuk=1;
        }
        for(x=0;x<30;x++) 
        {
            c[x][20]='-';
            n[x][20]=2;
        }
        bird();                       
        scorecheck();                
        if(gameover()==true) goto gameEnd;   
        walls();                             
        if(score>highscore) highscore=score;  
        screen();                            

        if(tuk>0) tuk++;          
        if(tuk==3) tuk=0;         
    }
    gameEnd:   //ends game
    {
        if(score>highscore) highscore=score;
        if(err==false)              
        {
            ofp.open("options.txt");
            ofp<<highscore;
            ofp.close();
        }
        screen();    
        endgame();
        return;
    }
}

void screen()   
{
    int x,y;
    system("cls");    
    for(y=0;y<21;y++) 
    {
        for(x=0;x<30;x++)
        {
            if(x<29) cout<<c[x][y];
            if(x==29) cout<<c[x][y]<<endl;
        }
    }
    cout<<""<<endl;
    cout<<"Your Score: "<<score;
}

void walls()  
{
    int x,y,r;
    if(t==10)  
    {
        r=(rand()%11)+5;  
        for(y=0;y<20;y++)  
        {
            c[29][y]='|';  
            n[29][y]=2;    
        }
        c[29][r-1]=' ';  
        c[29][r]=' ';
        c[29][r+1]=' ';
        n[29][r-1]=0;
        n[29][r]=0;
        n[29][r+1]=0;
        t=0;
        goto mouvement; 
    }
    else goto mouvement;
    mouvement:                 
    {
        for(y=0;y<20;y++)  
        {
            for(x=0;x<30;x++)
            {
                if(c[x][y]=='|')  
                {
                    if(x>0)
                    {
                        c[x-1][y]='|';
                        n[x-1][y]=2;
                        c[x][y]=' ';
                        n[x][y]=0;
                    } 
                    if(x==0) 
                    {
                        c[x][y]=' ';
                        n[x][y]=0;
                    }
                }
            }
        }
    }
}

void bird()  
{
    int x,y;
    if(tuk>0) 
    {
        bt=0;
        for(y=0;y<20;y++)   
        {
            for(x=0;x<30;x++)
            {
                if(c[x][y]=='*')
                {
                    if(y>0)
                    {
                    c[x][y-1]='*';  
                    c[x][y]=' ';
                    birdx=x;       
                    birdy=y-1;      
                    return;         
                    }
                }
            }
        }
    }
    else  
    {
        bt++;
        for(y=0;y<20;y++)
        {
            for(x=0;x<30;x++)
            {
                if(c[x][y]=='*')
                {
                    if(y<20)  
                    {
                        if(bt<3)   
                        {
                            c[x][y+1]='*';
                            c[x][y]=' ';
                            birdx=x;
                            birdy=y+1;
                            return;
                        }
                        else if(bt>4)  
                        {
                        
                            c[x][y+3]='*';
                            c[x][y]=' ';
                            birdx=x;
                            birdy=y+3;
                            return;
                        }
                        else if(bt>2 && bt<5)
                        {
                            c[x][y+2]='*';
                            c[x][y]=' ';
                            birdx=x;
                            birdy=y+2;
                            return;
                        }
                    }
                    else
                    {
                        return; 
                    }
                }
            }
        }
    }
}
void scorecheck()  
 {
    int y;
    for(y=0;y<20;y++)
    {
        if(c[birdx][y]=='|')  
        {
            score++;
            return;
        }
    }
}

bool gameover()  
{
    int x,y,f=0;
    if(birdy>19) 
    {
        c[birdx][19]='*';  
        c[birdx][20]='-';
        f=1;          
        goto quit;
    }
    else
    {    
        if(n[birdx][birdy]>0 && (c[birdx][birdy]=='|' || c[birdx][birdy]=='*'))
        {
            c[birdx][birdy]='|';
            c[birdx-1][19]='*';
            f=1;
            goto quit;
        }
    }
    quit:
    if(f==1) return true;
    else return false;
}

void endgame() 
{
    screen();  
    
    cout<<" ------------------------------------------------------------------------- "<<endl;
    cout<<"|    *****      *     *       * ******       ****  *       ****** ****    |"<<endl;
    cout<<"|   *          * *    * *   * * *           *    *  *     * *     *   *   |"<<endl;
    cout<<"|   *  ****   *   *   *  * *  * *****       *    *   *   *  ****  ****    |"<<endl;
    cout<<"|   *  *  *  *******  *   *   * *           *    *    * *   *     * *     |"<<endl;
    cout<<"|    *****  *       * *       * ******       ****      *    ***** *   *   |"<<endl;
    cout<<" ------------------------------------------------------------------------- "<<endl;
    cout<<"                        Y O U R   S C O R E : "<<score<<endl<<endl;
    cout<<"                        H I G H   S C O R E : "<<highscore<<endl;
    
}

void menu() 
{
    system("cls");
    cout<<"                  Yazid's Bird " <<endl ;
    cout<<""<<endl<<endl;
    cout<<"                  High Score:  "<<highscore<<endl<<endl;
    cout<<""<<endl<<endl;
    cout<<"                     M E N U:    "<<endl<<endl;
    cout<<"                  1: Start Game  "<<endl<<endl;
    cout<<"                  2: Help        "<<endl<<endl;
    cout<<"                  3: Credits     "<<endl<<endl;
    cout<<"                  4: Exit        "<<endl<<endl;
}

void credits()
{
    char inp;
    system("cls");
    while(true)
    {
    
    cout<<"                programmer: azzaouiyazid "<<endl<<endl;
    cout<<"Go back? [y/n]  ";
    cin>>inp;
    if(inp=='y') return;
    else system("cls");
    }
}

void help()
{
    char inp;
    system("cls");
    while(true)
    {
    
    cout<<"                   Controls: Press any key to fly up.         "<<endl<<endl;
    cout<<"             Goal: Fly through the holes between the walls.   "<<endl;
    cout<<"             When you pass through the hole,you get 1 point.  "<<endl;
    cout<<"            But be careful, don't hit the walls or the ground!"<<endl<<endl;
    cout<<"Go back? [y/n]  ";
    cin>>inp;
    if(inp=='y') return;
    else system("cls");
    }
}