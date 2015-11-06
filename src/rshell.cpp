#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <vector>
#include <queue>
using namespace std;
int DoCommand(string x)
{
    string CharHolder = x;
    pid_t c_pid, pid;
    int status;
    c_pid = fork();
    if( c_pid < 0)
    {
        perror("fork failed");
        exit(1);
    }
    else if (c_pid == 0)
    {
               vector<char> CommandArrayHolder;
                vector<char> CommandLoopholder;
                int x;
                bool check = false;
                bool wentintospaceCheck = false;
                for(int i=0;i < CharHolder.size();i++)
                {

                    if(CharHolder.at(i)!=' ')
                    {
                        CommandLoopholder.push_back(CharHolder.at(i));
                    }
                    if(CharHolder.at(i) ==' ')
                    {
                        x=i;
                        wentintospaceCheck = true;
                        check = true;
                    }
                    if(check)
                    {
                       break;
                    }
                    CommandArrayHolder= CommandLoopholder;
                }
                bool SingleArgumentCheck = false;
                char ExecCommandHold[30] = {NULL};
                char ExecArgumentHold[30] = {NULL};
                vector<char> ArgumentLoopHolder;
                if(wentintospaceCheck == false)
                {
                    SingleArgumentCheck = true;
                }
                else
                {
                    for(int j = x+1; j < CharHolder.size();j++)
                    {
                        ArgumentLoopHolder.push_back(CharHolder.at(j));
                    }

                }
                for(int i = 0; i < CommandArrayHolder.size(); i++)
                {
                    ExecCommandHold[i]=(CommandArrayHolder.at(i));
                }
                if(SingleArgumentCheck==false)
                {
                    for(int i = 0; i < ArgumentLoopHolder.size(); i++)
                    {
                        ExecArgumentHold[i]=(ArgumentLoopHolder.at(i));
                    }
                }
                if(SingleArgumentCheck ==true)
                {
                    char* argOne[2]{ExecCommandHold, NULL};
                    execvp(argOne[0],argOne);

                    perror("invalid command");
                }
                else
                {
                    char* args[3]{ExecCommandHold,ExecArgumentHold,NULL};
                    execvp(args[0], args);
                    perror("invalid command");
                }


    }
     else if (c_pid > 0)
     {
         while(waitpid(-1,&status,0) != c_pid);
         {
             if( WIFEXITED(status))
             {
                 if (WIFEXITED(status)==0)
                 {
                 }
                 else
                 {
                    return 1;
                 }
             }
                 else
                 {
                    cout << "something weird happened" << endl;
                 }
       }
   }
}
int main()
{
    bool exitcheck = false;
    queue<string> QueueForArguments;
    while(true)
    {


        string FullStringHolder;
        string queuestringHold;

        int i =0;
        bool queuetest = false;
        cout << "($)";
        getline(cin,FullStringHolder);
        if(FullStringHolder.empty())
        {
        }
        else
        {
            if(FullStringHolder.at(i)==' ')
            {
                i = i+1;
            }
        }
        for(i; i < FullStringHolder.size();i++)
        {
            if( FullStringHolder.at(i) == ';')
            {
                QueueForArguments.push(queuestringHold);
                QueueForArguments.push(";");
                i=i+1;
                if(FullStringHolder.at(i) ==' ')
                {
                  i=i+1;
                }
                queuestringHold.clear();
                queuetest=true;
            }
            if( FullStringHolder.at(i)== '|')
            {
                QueueForArguments.push(queuestringHold);
                QueueForArguments.push("||");
                queuestringHold.clear();
                i = i+2;
                if(FullStringHolder.at(i)==' ')
                {
                    i=i+1;
                }
                queuetest =true;
            }
            if(FullStringHolder.at(i) == '&')
            {
               QueueForArguments.push(queuestringHold);
               QueueForArguments.push("&&");
               queuestringHold.clear();
               i =i+2;
               if(FullStringHolder.at(i) ==' ')
               {
                   i=i+1;
               }
               queuetest=true;
            }
            if(FullStringHolder.at(i)=='#')
            {
                QueueForArguments.push(queuestringHold);
                break;
            }

            if(FullStringHolder.at(i)!='|'||FullStringHolder.at(i)!=';'||FullStringHolder.at(i)!='&')
            {
                 queuestringHold.push_back(FullStringHolder.at(i));
            }
            if(i==FullStringHolder.size()-1)
            {
                QueueForArguments.push(queuestringHold);
                queuestringHold.clear();
            }
        }
            int HoldIfRan; 
           string CharHolder;
            bool SecondRoundFlag = false;
            while(!QueueForArguments.empty())
            {

                CharHolder= QueueForArguments.front();
                if(CharHolder == "exit"||CharHolder == " exit"||CharHolder == "exit ")
                {
                    exitcheck = true;
                }
                if(CharHolder == ";")
                 {
                     QueueForArguments.pop();
                     CharHolder = QueueForArguments.front();
                     if(CharHolder == "exit"||CharHolder == " exit"||CharHolder == "exit ")
                     {
                         exitcheck = true;
                     }

                 }
                if(CharHolder == "||")
                {
                    QueueForArguments.pop();
                    CharHolder =  QueueForArguments.front();
                    if(CharHolder == "exit"||CharHolder == " exit"||CharHolder == "exit ")
                    {
                        exitcheck = true;
                    }

                    if(HoldIfRan == 1)
                    {
                        if(!QueueForArguments.empty())
                        {
                            QueueForArguments.pop();
                            if(QueueForArguments.size() !=0)
                            {
                                CharHolder = QueueForArguments.front();
                                SecondRoundFlag= true;
                            }
                            else
                            {
                                CharHolder = " ";
                            }

                        }
                    }
                }
                if(CharHolder =="&&")
                {
                    QueueForArguments.pop();
                    CharHolder = QueueForArguments.front();
                    if(CharHolder == "exit"||CharHolder == " exit"||CharHolder == "exit ")
                    {
                        cout << "here" << endl;
                        exitcheck = true;
                    }

                    if(HoldIfRan== 0)
                    {
                       if(!QueueForArguments.empty())
                       {
                            QueueForArguments.pop();
                            if(QueueForArguments.size()!=0)
                            {
                                CharHolder = QueueForArguments.front();
                                SecondRoundFlag= true;
                            }
                            else
                            {
                                CharHolder = " ";
                            }
                       }
                    }
                }
                if(CharHolder=="#")
                {

                }
                if(exitcheck == true)
                {
                    break;
                }
                if(QueueForArguments.size()!=0 && SecondRoundFlag ==false&& exitcheck == false)
                {

                    //cout << "go in " << endl;
                    HoldIfRan = DoCommand(CharHolder);
                    QueueForArguments.pop();
                }
                SecondRoundFlag = false;
            }
            //cout <<"came to the end" << endl;
            if(exitcheck == true)
            {
                break;
            }
    }
    if(exitcheck ==true)
    {
        exit(0);
    }
}
