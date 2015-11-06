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
                //created 2 vectors to push parse through to split up commands that have two words seprated by a space
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
                // checking to see if there are two words or one words in the command inputted
                if(SingleArgumentCheck==false)
                {
                    for(int i = 0; i < ArgumentLoopHolder.size(); i++)
                    {
                        ExecArgumentHold[i]=(ArgumentLoopHolder.at(i));
                    }
                }
                // using execvp code to call commands given that were put into the arrays
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
             //checking for outcome of whether or not child worked. 
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

    //while the terminal is still running
    while(true)
    {   
        string FullStringHolder;
        string queuestringHold;

        int i =0;
        bool queuetest = false;
        cout << "($)";
        getline(cin,FullStringHolder);
        //getting output string and im putting it into fullstringholder
        if(FullStringHolder.empty())
        {
        }
        else
        {
            //checking to see if teh beginning char is a space
            if(FullStringHolder.at(i)==' ')
            {
                i = i+1;
            }
        }
        for(i; i < FullStringHolder.size();i++)
        {   
            //checking to see if it is a ;, if so that means you can push the current word stored at queuestringhold into the queue
            if( FullStringHolder.at(i) == ';')
            {
                QueueForArguments.push(queuestringHold);
                QueueForArguments.push(";");
                i=i+1;
                while(FullStringHolder.at(i) ==' ')
                {
                  i=i+1;
                }
                queuestringHold.clear();
                queuetest=true;
            }
            //checking to see if it is a |, if so that means you can push the current word stored at queuestringhold into the queue
            if( FullStringHolder.at(i)== '|')
            {
                QueueForArguments.push(queuestringHold);
                QueueForArguments.push("||");
                queuestringHold.clear();
                i = i+2;
                while(FullStringHolder.at(i)==' ')
                {
                    i=i+1;
                }
                queuetest =true;
            }
            //checking to see if it is a &, if so that means you can push the current word stored at queuestringhold into the queue
            if(FullStringHolder.at(i) == '&')
            {
               QueueForArguments.push(queuestringHold);
               QueueForArguments.push("&&");
               queuestringHold.clear();
               i =i+2;
               while(FullStringHolder.at(i) ==' ')
               {
                   i=i+1;
               }
               queuetest=true;
            }
            //checking to see if it is a '#', means that you can end the loop and that the queue is now stocked
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
                //takes in the first string of the queue and sees if is exit.
                CharHolder= QueueForArguments.front();
                if(CharHolder == "exit"||CharHolder == " exit"||CharHolder == "exit ")
                {
                    exitcheck = true;
                }
                //checking to see if the current string we are looking at from teh queue is ";"
                if(CharHolder == ";")
                 {
                     // delete teh string ";"
                     // then push the new front of queue into holder
                     QueueForArguments.pop();
                     CharHolder = QueueForArguments.front();
                     if(CharHolder == "exit"||CharHolder == " exit"||CharHolder == "exit ")
                     {
                         exitcheck = true;
                     }

                 }
                //checking to see if teh current string we are looking at from the queue is "||"
                if(CharHolder == "||")
                {
                    //delete the string "||"
                    QueueForArguments.pop();
                    // push new front of queue into holder
                    CharHolder =  QueueForArguments.front();
                    
                    // if the function worked 
                    if(HoldIfRan == 1)
                    {
                        if(!QueueForArguments.empty())
                        {
                            //pop the queue again                       
                            QueueForArguments.pop();
                            if(QueueForArguments.size() !=0)
                            {
                                //move the next queue into the holder to prepare for next loop
                                CharHolder = QueueForArguments.front();
                                SecondRoundFlag= true;
                            }
                            else
                            {

                                CharHolder = " ";
                            }

                        }
                    }
                    else
                    {
                         if(CharHolder == "exit"||CharHolder == " exit"||CharHolder == "exit ")
                         {
                             exitcheck = true;
                         }                       
                    }
                
                }
                //checking to see if teh current string we are look from the queue is "&&"
                if(CharHolder =="&&")
                {
                    //pop front of the queue
                    QueueForArguments.pop();
                    // move the next queue.front() into the holder
                    CharHolder = QueueForArguments.front();

                     // if the past command worked
                    if(HoldIfRan== 0)
                    {
                       if(!QueueForArguments.empty())
                       {
                            //pop the queue again  
                            QueueForArguments.pop();
                            if(QueueForArguments.size()!=0)
                            {
                                 // move the next queue.front() into the holder to get ready for next loop
                                CharHolder = QueueForArguments.front();
                                SecondRoundFlag= true;
                            }
                            else
                            {
                                CharHolder = " ";
                            }
                       }
                    }
                    else
                    {
                        if(CharHolder == "exit"||CharHolder == " exit"||CharHolder == "exit ")
                        {
                            exitcheck = true;
                        }
                    }
                }
                if(CharHolder=="#")
                {

                }
                if(exitcheck == true)
                {
                    //checking to see if it was an exit
                    break;
                }
                if(QueueForArguments.size()!=0 && SecondRoundFlag ==false&& exitcheck == false)
                {
                     //usingDocommand function and then popping queue
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
