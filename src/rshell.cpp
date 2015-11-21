#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <vector>
#include <queue>
#include <sys/stat.h>
using namespace std;
int DoStat(string x, string flagstring)
{
    //cout << "current string in dostat function:"<< x << endl;
    //cout << "current flag:" << flagstring << endl; 
    //cout << "went inside function" << endl;
   // bool finalcheck = false;
    char HolderStat[100] ={};
    for(unsigned int  i =0; i <x.size(); i++)
    {
       HolderStat[i]=x.at(i);
       //cout << " value at x:  " <<  HolderStat[i];
    }
    //char* argOne[1]{HolderStat};
    struct stat buf;
    if(flagstring == "" || flagstring == "-e")
    {
           // finalcheck = true;
            if((stat(HolderStat,&buf) == 0 ))//&& //(S_ISDIR(buf.st_mode)) )
            {
                //cout << " it was true" << endl;
                return 1;
            }
            else //(!(stat(HolderStat,&buf) == 0 ))
            {
                //out << " it wasn't true" << endl;
                    return 0;
            }  
    }
    if(flagstring == "-d")
    {
            //finalcheck = true;   
            //cout << "went into here";
            if( ( (stat(HolderStat,&buf) == 0 ) ) && ( S_ISDIR(buf.st_mode) ) )
            {
                //cout << " it was true" << endl;
                return 1;
            }
            else //if(   !(   ((stat(HolderStat,&buf) == 0 ))  &&  ( S_ISDIR(buf.st_mode))   ) )
            {
                //cout << " it wasn't true" << endl;
        
                    return 0;
            }  
    }
    if(flagstring == "-f")
    {
            //finalcheck = true;
            if( ((stat(HolderStat,&buf) == 0 )) && ( S_ISREG(buf.st_mode) ) )
            {
                //cout << " it was true" << endl;
                return 1;
            }
            else  //if(   !(   ((stat(HolderStat,&buf) == 0 )) &&  ( S_ISREG(buf.st_mode))   ) )
            {
                //cout << " it wasn't true" << endl;
        
                    return 0;
            }   
    }
    else
    {
      return 75;
    }


    
    // (stat( x ,&buf) == 0 && S_ISREG(buf.st_mode));
    //return ((stat( x ,&buf) == 0 && S_ISREG(buf.st_mode)); && (stat( x ,&buf) == 0 && S_ISDIR(buf.st_mode)));
}
int DoCommand(string x)
{
    string CharHolder = x;
    pid_t c_pid;
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
                for(unsigned int i=0;i < CharHolder.size();i++)
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
                char ExecCommandHold[100] = {};
                char ExecArgumentHold[100] = {};
                vector<char> ArgumentLoopHolder;
                if(wentintospaceCheck == false)
                {
                    SingleArgumentCheck = true;
                }
                else
                {
                    for(unsigned int j = x+1; j < CharHolder.size();j++)
                    {
                        ArgumentLoopHolder.push_back(CharHolder.at(j));
                    }

                }
                for(unsigned int i = 0; i < CommandArrayHolder.size(); i++)
                {
                    ExecCommandHold[i]=(CommandArrayHolder.at(i));
                }
                // checking to see if there are two words or one words in the command inputted
                if(SingleArgumentCheck==false){
                    for(unsigned int i = 0; i < ArgumentLoopHolder.size(); i++)
                    {
                        ExecArgumentHold[i]=(ArgumentLoopHolder.at(i));
                    }
                }
                // using execvp code to call commands given that were put into the arrays
                if(SingleArgumentCheck ==true){
                    char* argOne[2]{ExecCommandHold, NULL};
                    execvp(argOne[0],argOne);

                    perror("invalid command");
                }
                else{
                    char* args[3]{ExecCommandHold,ExecArgumentHold,NULL};
                    execvp(args[0], args);
                    perror("invalid command");
                }


    }
     else if (c_pid > 0){
         while(waitpid(-1,&status,0) != c_pid);{
             //checking for outcome of whether or not child worked.
             if( WIFEXITED(status)){
                 if (WIFEXITED(status)==0){
                 }
                 else{
                    return 1;
                }
             }
                 else{
                    cout << "something weird happened" << endl;
                 }
       }
   }
  return 77;
}
int IndividualGroupCommandFunction( string x)
{
    bool wentin = false;
    int  outsidecheck;
    bool exitcheck = false;
    queue<string> QueueForArguments;

    //while the terminal is still running

        string FullStringHolder = x;
        string queuestringHold;

        int f = 0;
        //getting output string and im putting it into fullstringholder
        if(FullStringHolder.empty()){
        }
        else
        {
            //checking to see if teh beginning char is a space
            if(FullStringHolder.at(f)==' '){
                f = f+1;
            }
        }
        for(unsigned int i= f; i < FullStringHolder.size();i++){
            //checking to see if it is a ;, if so that means you can push the current word stored at queuestringhold into the queue
            if( FullStringHolder.at(i) == ';'){
                QueueForArguments.push(queuestringHold);
                QueueForArguments.push(";");
                i=i+1;
                while(FullStringHolder.at(i) ==' '){
                  i=i+1;
                }
                queuestringHold.clear();
            }
            //checking to see if it is a |, if so that means you can push the current word stored at queuestringhold into the queue
            if( FullStringHolder.at(i)== '|'){
                QueueForArguments.push(queuestringHold);
                QueueForArguments.push("||");
                queuestringHold.clear();
                i = i+2;
                while(FullStringHolder.at(i)==' '){
                    i=i+1;
                }

            }
            //checking to see if it is a &, if so that means you can push the current word stored at queuestringhold into the queue
            if(FullStringHolder.at(i) == '&'){
               QueueForArguments.push(queuestringHold);
               QueueForArguments.push("&&");
               queuestringHold.clear();
               i =i+2;
               while(FullStringHolder.at(i) ==' '){
                   i=i+1;
               }
            }
            //checking to see if it is a '#', means that you can end the loop and that the queue is now stocked
            if(FullStringHolder.at(i)=='#'){
                QueueForArguments.push(queuestringHold);
                break;
            }

            if(FullStringHolder.at(i)!='|'||FullStringHolder.at(i)!=';'||FullStringHolder.at(i)!='&'){
                 queuestringHold.push_back(FullStringHolder.at(i));
            }
            if(i==FullStringHolder.size()-1){
                QueueForArguments.push(queuestringHold);
                queuestringHold.clear();
            }
        }
            int HoldIfRan;
            string CharHolder;
            bool SecondRoundFlag = false;
            while(!QueueForArguments.empty()){
                //takes in the first string of the queue and sees if is exit.
                CharHolder= QueueForArguments.front();
                if(CharHolder == "exit"||CharHolder == " exit"||CharHolder == "exit "){
                    exitcheck = true;
                }
                //checking to see if the current string we are looking at from teh queue is ";"
                if(CharHolder == ";"){
                     // delete teh string ";"
                     // then push the new front of queue into holder
                     QueueForArguments.pop();
                     CharHolder = QueueForArguments.front();
                     if(CharHolder == "exit"||CharHolder == " exit"||CharHolder == "exit "){
                         exitcheck = true;
                     }

                 }
                //checking to see if teh current string we are looking at from the queue is "||"
                if(CharHolder == "||"){
                    //delete the string "||"
                    QueueForArguments.pop();
                    // push new front of queue into holder
                    CharHolder =  QueueForArguments.front();

                    // if the function worked
                    if(HoldIfRan == 1){
                        if(!QueueForArguments.empty()){
                            //pop the queue again
                            QueueForArguments.pop();
                            if(QueueForArguments.size() !=0){
                                //move the next queue into the holder to prepare for next loop
                                CharHolder = QueueForArguments.front();
                                SecondRoundFlag= true;
                            }
                            else{

                                CharHolder = " ";
                            }

                        }
                    }
                    else{
                         if(CharHolder == "exit"||CharHolder == " exit"||CharHolder == "exit "){
                             exitcheck = true;
                         }
                    }

                }
                //checking to see if teh current string we are look from the queue is "&&"
                if(CharHolder =="&&"){
                    //pop front of the queue
                    QueueForArguments.pop();
                    // move the next queue.front() into the holder
                    CharHolder = QueueForArguments.front();

                     // if the past command worked
                    if(HoldIfRan== 0){
                       if(!QueueForArguments.empty()){
                            //pop the queue again
                            QueueForArguments.pop();
                            if(QueueForArguments.size()!=0){
                                 // move the next queue.front() into the holder to get ready for next loop
                                CharHolder = QueueForArguments.front();
                                SecondRoundFlag= true;
                            }
                            else{
                                CharHolder = " ";
                            }
                       }
                    }
                    else{
                        if(CharHolder == "exit"||CharHolder == " exit"||CharHolder == "exit "){
                            exitcheck = true;
                        }
                    }
                }
                if(CharHolder=="#"){

                }
                if(exitcheck == true){
                    //checking to see if it was an exit
                    break;
                }
                if(QueueForArguments.size()!=0 && SecondRoundFlag ==false&& exitcheck == false){
                     //usingDocommand function and then popping queue
                    //cout << "go in " << endl;
                    // zero means it didn't work
                    // one means it worked
                    HoldIfRan = DoCommand(CharHolder);
                    //cout << "holdIfRan value: " <<  HoldIfRan << endl;
                    if(HoldIfRan != 1)
                    {
                        //cout << "went into check if holdifran is 0" << endl;
                        outsidecheck  = 0;
                    }
                    if(HoldIfRan ==1  && wentin == false )
                    {
                        //cout << "went into check if holdifran is 1" << endl;
                        outsidecheck = 1;
                        wentin = true;
                    }
                    QueueForArguments.pop();
                SecondRoundFlag = false;
            }
            //cout <<"came to the end" << endl;
    if(exitcheck ==true)
    {
        //cout << "went into exit" << endl;
        exit(99);
    }

  }
  //cout << "outsidecheck value" << outsidecheck << endl;
  return(outsidecheck);
}
int main()
{
     while(true){
        string FullStringHolder;
        string QueueStringHolder;
        bool parenthesischeck = false;
        bool outsideofParenthesis = true;
        cout << "($)";
        getline(cin,FullStringHolder);
        queue<string> OverallCommandHold;
        // Puts parenthesis arguemnts inside the queueue
        //cout << "fullstringholder: " << FullStringHolder.size() << endl;
        for(unsigned int i = 0; i<FullStringHolder.size();i++){
            //cout << "fullstringholder.at i : "  << FullStringHolder.at(i) << endl;
            if(QueueStringHolder == "test")
            {
                //cout << "went into test "  << endl;
                OverallCommandHold.push("test");
                QueueStringHolder.clear();
                while(FullStringHolder.at(i) == ' ')
                {
                    i= i+1;
                }
                
                if(FullStringHolder.at(i) == '/')
                {
                    //cout << "went into / " << endl;
                    i = i+1;
                }
            }
            if(FullStringHolder.at(i) =='[')
            {
                //cout << "went into  [ "  << endl;
                OverallCommandHold.push("[");
                i = i+1;
                while(FullStringHolder.at(i) == ' ')
                {
                    i = i+1;
                }
                //cout << "fullstringholder.at i : "  << FullStringHolder.at(i) << endl;
                if(FullStringHolder.at(i)=='/')
                {
                    //cout << "went into / " << endl;
                    i = i+1;
                }
                
            }
            if(QueueStringHolder == "-e")
            {
                OverallCommandHold.push("-e");
                QueueStringHolder.clear();
                
                if(FullStringHolder.at(i)==' ')
                {
                    //cout <<"went into space" << endl;
                    i= i+1;
                }
                //cout << "fullstringholder.at i : "  << FullStringHolder.at(i) << endl;
                if(FullStringHolder.at(i)=='/')
                {
                    //wecout <<"went into / check" << endl;
                    i = i+1;
                }
            }
            if(QueueStringHolder == "-f")
            {
                OverallCommandHold.push("-f");
                QueueStringHolder.clear();
                //cout << "fullstringholder.at i : "  << FullStringHolder.at(i) << endl;
                if(FullStringHolder.at(i)==' ')
                {
                    i= i+1;
                }
                if(FullStringHolder.at(i)=='/')
                {
                    i = i+1;
                }        
                
            }
            if(QueueStringHolder == "-d")
            {
                OverallCommandHold.push("-d");
                QueueStringHolder.clear();
                //cout << "fullstringholder.at i : "  << FullStringHolder.at(i) << endl;
                if(FullStringHolder.at(i)==' ')
                {
                    i= i+1;
                }
                if(FullStringHolder.at(i)=='/')
                {
                    i = i+1;
                }
            }
            if(FullStringHolder.at(i) == '(' ){
                //cout << "went into ( "<< endl;
                i = i+1;
                parenthesischeck = true;
                outsideofParenthesis = false;
                if(FullStringHolder.at(i) == ' ')
                {
                    i = i+1;
                }
            }
            if( (FullStringHolder.at(i)== '&')  && (outsideofParenthesis == true) ){
                //cout << "went into &&" << endl;
                OverallCommandHold.push(QueueStringHolder);
                OverallCommandHold.push("&&");
                //cout <<"going into queue: "<< QueueStringHolder << endl;
                QueueStringHolder.clear();
                outsideofParenthesis = false;
                //cout << "&& got pushed in " << OverallCommandHold.back() << endl;
                i = i+2;
                //cout << i << endl;
                while(FullStringHolder.at(i)==' '){
                    i=i+1;
                //cout << "went into space check " << endl;
                }
                if(FullStringHolder.at(i) =='(')
                {
                    
                    i = i+1;
                    outsideofParenthesis = false;
                }
                //
                //out << i << endl;
            }
            if( (FullStringHolder.at(i)== '|') && (outsideofParenthesis == true) ){
                //cout << "went into ||" << endl;
                OverallCommandHold.push(QueueStringHolder);
                //cout <<"going into queue: "<< QueueStringHolder << endl;
                OverallCommandHold.push("||");
                QueueStringHolder.clear();
                i = i+2;
                while(FullStringHolder.at(i)==' '){
                   i=i+1;
                }
                if(FullStringHolder.at(i) =='(')
                {
                    i = i+1;
                    outsideofParenthesis = false;
                }
                outsideofParenthesis = false;

           }
           //cout << "before ] " << endl;
            if(FullStringHolder.at(i) ==']')
            {  
                //cout << "went into  ] "  << endl;
                if( i < FullStringHolder.size())
                {
                    i=i+1;
                }
                //cout << QueueStringHolder << endl;
                //cout << "pushed into queue: " <<  QueueStringHolder <<  endl;
                OverallCommandHold.push(QueueStringHolder);
                QueueStringHolder.clear();
                if( i == FullStringHolder.size())
                {
                    break;
                }
            }
            if(FullStringHolder.at(i) == ')')
            {
                //cout << "went into  ) "  << endl;
                i = i+1;
                //cout <<QueueStringHolder  << endl;
                //cout << " went into end bracket, going to push in string" << endl;
                OverallCommandHold.push(QueueStringHolder);
                //cout <<"going into queue: "<< QueueStringHolder << endl;
                //cout << "the current back of the group: " << OverallCommandHold.back() << endl;
                QueueStringHolder.clear();
                parenthesischeck = false;
                outsideofParenthesis = true;
            }
            
                //cout << QueueStringHolder << endl;
                if( i < FullStringHolder.size())
                {
                    
                    QueueStringHolder.push_back(FullStringHolder.at(i));    
                    
                }
        }
        
        if(parenthesischeck == false){
            //cout << "went in" << endl;
            //cout <<  "this is last queue: " << QueueStringHolder << endl;
            OverallCommandHold.push(QueueStringHolder);
        }
        //cout << "queue size: "<< OverallCommandHold.size() << endl;
        string HolderForTestString;
        string CurrentQueueString;
        string flagstring = "";
        bool   testcheck = false;
        //bool   slashdoublecheck;
        int BeforeHold;
       // cout << " created teh quueue" << endl;
        while(!OverallCommandHold.empty()){
            //cout << "this is the current string: " << OverallCommandHold.front() << endl;
            CurrentQueueString = OverallCommandHold.front();
            //while( (CurrentQueueString.at(CurrentQueueString.size()-1)) == ' ')
            //{
            //   // cout <<"went inside space check" << endl;
            //    CurrentQueueString.erase(CurrentQueueString.size());
            //    
            //}
            if(CurrentQueueString == " ")
            {
                OverallCommandHold.pop();
                CurrentQueueString = OverallCommandHold.front();
            }
            
            else
            {
                if(CurrentQueueString == "["||CurrentQueueString == "test")
                {
                    //cout << "went into [ and test" << endl;

                    OverallCommandHold.pop();
                    CurrentQueueString = OverallCommandHold.front();
                    //while( CurrentQueueString.at(CurrentQueueString.size()-1 ) == ' ')
                    //{
                    //    
                    //   // cout <<"went inside space check" << endl;
                    //    CurrentQueueString.erase(CurrentQueueString.size()-1);
                    //    
                    //}
                    if(CurrentQueueString == "-e")
                    {
                        //cout << "went into -e" << endl;
                        flagstring = CurrentQueueString;
                       // cout << "flagstring: " <<flagstring << endl;
                        OverallCommandHold.pop();
                        CurrentQueueString = OverallCommandHold.front();
                    }
                    if(CurrentQueueString == "-d")
                    {
                        //cout << "went into -d" << endl;
                        flagstring = CurrentQueueString;
                        //cout << "flagstring: "<<flagstring << endl;
                        OverallCommandHold.pop();
                        CurrentQueueString = OverallCommandHold.front();
                    }
                    if(CurrentQueueString == "-f")
                    {
                        //cout << "went into -f" << endl;
                        flagstring = CurrentQueueString;
                        //cout << "flagstring: " <<flagstring <<endl;
                        OverallCommandHold.pop();
                        CurrentQueueString = OverallCommandHold.front();
                    }
                    if( CurrentQueueString.at(CurrentQueueString.size() -1 ) == ' ')
                    {
                        
                       // cout <<"went inside space check" << endl;
                        CurrentQueueString.erase(CurrentQueueString.size()-1);
                        
                    }
                   // cout << CurrentQueueString << endl;
                    //cout <<" CurrentQueueString before do stat:" << CurrentQueueString << endl;
                    //cout << flagstring << endl;
                    BeforeHold = DoStat(CurrentQueueString,flagstring);
                    //cout << "before hold val: " << BeforeHold << endl;
                    OverallCommandHold.pop();
                    //cout <<" CurrentQueueString after do stat: " << CurrentQueueString << endl;
                    CurrentQueueString = OverallCommandHold.front();
                    testcheck = true;
                 }
                    //out << "current queue string: " << CurrentQueueString << endl;

                if( CurrentQueueString == "&&")
                {
                    //cout <<" CurrentQueueString: " << CurrentQueueString << endl;
                    // cout << "went into &&adsfadsf " << endl;
                   
                    //cout << "went into here" << endl;
                    OverallCommandHold.pop();
                    //cout << "current queue string: " << CurrentQueueString << endl;
                    CurrentQueueString = OverallCommandHold.front();
                    //cout <<" CurrentQueueString: " << CurrentQueueString << endl;
                    testcheck = false;
                    //cout << BeforeHold << endl;
                   if(BeforeHold == 0)
                   {
                       
                        if(OverallCommandHold.size() == 1)
                        {
                            //cout << "went into here" << endl;
                            testcheck = true;
                            OverallCommandHold.pop();
                            //cout << "OverallCommandHold..size: " << OverallCommandHold.size() << endl;
                            CurrentQueueString = "";
                        }
                        else
                        {
                            testcheck = false;
                           // cout <<  " over here" << endl;
                            OverallCommandHold.pop();
                            CurrentQueueString = OverallCommandHold.front();
                            //cout <<" CurrentQueueString: " << CurrentQueueString << endl;
                        }
                   }
                }
                 //cout << "BeforeHold" << BeforeHold << endl;
                if( CurrentQueueString == "||")
                {
                   //cout << "went into || " << endl;
                     
                     //cout << "went into | | check" << endl;
                     OverallCommandHold.pop();
                     CurrentQueueString = OverallCommandHold.front();
                     //cout <<" CurrentQueueString: " << CurrentQueueString << endl;
    
                     //cout << "BeforeHold: " << BeforeHold << endl;
                     
                    testcheck = false;
                    if(BeforeHold == 1)
                    {
                        //cout << "OverallCommandHold: " << OverallCommandHold.size() << endl;
                        if(OverallCommandHold.size() == 1)
                        {
                            //cout << "went into here" << endl;
                            testcheck = true;
                            OverallCommandHold.pop();
                            CurrentQueueString = "";
                        }
                        else
                        {
                            testcheck = false;
                            //cout <<  " over here" << endl;
                            OverallCommandHold.pop();
                            CurrentQueueString = OverallCommandHold.front();
                            //cout <<" CurrentQueueString: " << CurrentQueueString << endl;
                        }

                        //cout << "past this " << endl;
                    }
                   // cout << "past this " << endl;
                    
                }
     
                string empty = "exit";
                //
                //cout << CurrentQueueString << endl;
                if( CurrentQueueString.compare(empty) == 0)
                {
                    //cout << "went into here" << endl;
                    exit(-3);
                }
                //cout <<"pas " << endl;
                if(CurrentQueueString== " ")
                {
                    testcheck = true;
                    
                    //cout << "went into here" << endl;
                }
                //cout <<"pas " << endl;
                if(testcheck == false)
                {
                   //cout << "went inside testcheck execvp" << endl;
                   //cout <<"queue string being pushed in:"<<  CurrentQueueString << endl;
                   BeforeHold = IndividualGroupCommandFunction(CurrentQueueString);
                   //cout << "beforehold value: " << BeforeHold << endl;
                }
                
                if(!OverallCommandHold.empty())
                {
                    OverallCommandHold.pop();
                    testcheck  = false;
                }
                                
                                
            }           
          
            
            // if return 0 means that it worked.
            // if it returned 1 it means it didn't work
            // if it returned 2 it means it was an exit ;
        }

     }
}
