/*******************************************************
*   Created by : Tuyet N. Pham
*   Created on : July 20, 2019
*   Copyright 2019, Tuyet N. Pham, All rights reserved.
*******************************************************/

#include "../inc/resources.h"
#include <set> 
#include <fstream>
#include <utility>
#include <bits/stdc++.h> 
#include <vector>
#include "twilioresources.h"
const std::string PROG_NAME = ".twiliosms.py";
const std::string HEADER = "2step---{#";
const std::string FILENAME = "etc/.passwdlist.txt";                    //USER INFO, NEEDED
std::vector<usrinfo*> oldu;                                            //To Hold all of the loaded and new users.
std::vector<coset*> codes;                                             //To hold all of the codes sent, will only hold for 30 seconds then delete. 
usrinfo * currusr;                                                     //FOR FRONT PAGE 


/*****************************************
 *  struct usrinfo {
 *      john ---> john;passsword;8175579555
 *  }
 * 
 * Briefs of functions below. 
 * Additional information of functions
 * will be at their location.
 * 
 *****************************************/


int main()
{   
    if(!CHECKTWILIO()){
        std::cout << "Twilio file doesn't exist or isn't where it is suppose to be.\n";
        exit(1);
    }
    else{

        if(CHECK4LIST())
        {
            if(LOADTO(FILENAME))
            {
                bool exit = false;
                do
                {
                    int choice;
                    choice = MMENU();
                    switch (choice)
                    {
                    case 1:             
                                    //LOGIN
                                    if(LOGIN()){
                                        FRONTPAGE();
                                    }
                        break;      
                    case 2:
                                    //ADD LOGIN
                                    ADDLOGIN();
                                    
                        break;      
                    case 3:         //EXIT
                                    FREEALL();
                                    exit = true;
                        break;      
                    default:
                        std::cout << "\nWrong input. Try again.\n";
                        usleep(200*1000);
                        break;
                    }

                }while(!exit);
            }
            else{
                std::cout << "\nSomething went wron while loading... Try again." << std::endl;
            }
        }
    }
    return 0;
}


/* 
 * CHECKTWILIO
 * @param : none
 * return : bool
 * desc : checks for the twilio file
 */
bool CHECKTWILIO(){
    std::ifstream FILE;
    std::string prog_full = "etc/" + PROG_NAME;

    FILE.open(prog_full);
    if(!FILE.is_open()){
        FILE.close();
        return false;
    }
    FILE.close();
    return true;
}


/* 
 * CREATELIST
 * @param : none
 * return : bool
 * desc : creates the password list if the directory doesn't have it.
 */
bool CREATELIST(){

    std::ofstream FILE;
    FILE.open(FILENAME);

    if(FILE.is_open()){
        FILE.close();
        return true;
    }
    else{
        FILE.close();
        return false;
    }
}


/* 
 * CHECK4LIST
 * @param : none
 * return : int
 * desc : checks to see if the password list is in the directory, if it's not then create one.
 */
bool CHECK4LIST(){
    std::ifstream FILE;
    FILE.open(FILENAME);

    if(!FILE.is_open()){

        std::cout << "\nThe password list doesn't exist..";
        std::cout << "\nLet me make you one!";

        FILE.close();
        std::cout << "\n\n[";     
        std::cout << RED;
        for (int i = 0; i < 15; i++) {
            usleep(100 * 1000);
            std::cout << "|";  
            fflush(stdout);
        }
        std::cout << RESET << "]";     


        if(CREATELIST()){
            std::cout << "\nDone!, Start adding your new account information "
                    << "so you can start logging in.\n";
        }
        else{
            std::cout << "\nSomething went wrong and I couldn't add a file for you."
                    << "Please add the file manually and name it 'passwdlist.txt'.";
            return false;
        }
    }
    return true;
}


/* 
 * LOADTO
 * @param : string
 * return : bool
 * desc : Loading in the user login information. Splits by line and send line to LOADTOAUX
 */
bool LOADTO(std::string filename){

    std::fstream FILE;
    FILE.open(filename);
    std::string line;

    if(!FILE.is_open()){
        return false;
    }

    while(getline(FILE, line)){
        LOADTOAUX(line);
    }

    std::cout << "\nLoading list\n";
    std::cout << "[";
    std::cout << RED;     
    for (int i = 0; i < 15; i++) {         
      usleep(100*1000);       
      std::cout << "|";  
      fflush(stdout);
    }
    std::cout << RESET << "]\n";

    FILE.close();
    return true;
}


/* 
 * LOADTOAUX
 * @param : string
 * return : none
 * desc : split the string up by delim ';'
 */
void LOADTOAUX(std::string line){
    
    usrinfo * USER = new usrinfo;
    std::istringstream ff(line);
    std::string temp;
    std::string key; 
    int count = 0;
    
    while(getline(ff, temp, ';')){
        if(count == 0){
            USER->usrname = temp;
            key = temp;
        }
        else if(count == 1)
            USER->hashpass = temp;
        else
            USER->phonenum = temp;
        count++;
    }

    oldu.push_back(USER);
}


/* 
 * MMENU()
 * @param : none
 * return : int
 * desc : Show menu
 */
int MMENU(){
    int choice;
    //system("clear");
    std::cout << BLUE << "\n========= Menu =========\n" << RESET
            << "\n1. Login"
            << "\n2. Add account"
            << "\n3. Quit\n--> ";
    std::cin >> choice;
    if(!std::cin) 
    {
        choice = 1000;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return choice;
}


/* 
 * FREEALL()
 * @param : none
 * return : bool
 * desc : free all allocated memory for usrinfo struct
 */
bool FREEALL(){

    for(auto & g: oldu)
        delete g;
    oldu.clear();

    for(auto & f : codes)
        delete f;
    codes.clear();

    //delete currusr;

    return true;
}


/* 
 * ADDLOGIN()
 * @param : none
 * return : bool
 * desc : Add a user to the list
 */
bool ADDLOGIN(){
    bool good = false;
    hash hasher;                                  //How we hash our password
    std::string temp;
    usrinfo * thisu = new usrinfo;
    std::cin.clear();
    std::cin.ignore();
    
    do{
        system("clear");
        std::cout << GREEN << "\n================ ADD LOGIN PAGE ================== " << CYAN << "\n[ Enter 'q' in username to go to main menu. ]\n" << RESET;
        bool okusername = false;
        bool okphone = false;
        bool okpass = false;


        while(!okusername){
            std::cout << "\nEnter your desire username WITHOUT spaces: ";
            std::getline(std::cin, temp);
            if(temp == "q" || temp == "Q")
                return 0;
            else{
                if(!USRCHECK_R(temp)|| !USRCHECK_F(temp))  {
                    std::cout << "\nYour name is taken or your username has incorrect formatting. Try Again.";
                    temp.clear();
                    okusername = false;
                }
                else
                    okusername = true;
            }
        }
        thisu->usrname = temp;
        temp.clear();


        while(!okphone){
            std::cout << "\nEnter your phone number (e.g. 8178915555) : ";
            std::getline(std::cin, temp);
            if(temp == "q" || temp == "Q")
                return 0;
            else{
                if(!PHONECHECK_R(temp) || !PHONECHECK_F(temp)){
                    std::cout << "\nYour phone number is already in use or has incorrect formatting. Try again.\n";
                    temp.clear();
                    okphone = false;
                }
                else
                    okphone = true;
            }
        }
        thisu->phonenum = temp;
        temp.clear();


        while(!okpass){
            temp = GETPASS();
            if(temp == "q" || temp == "Q")
                return 0;
            else{
                std::cout << "\nGreat! You're ready to login.";
                okpass = true;
            }
        }
        temp = hasher.genhash(temp);
        thisu->hashpass = temp;
        temp.clear();

        if(okpass && okphone && okusername)
            good = true;
        else
            std::cout << "\nSomething went wrong. Try again.";

    } while (!good);

    /* std::cout << "\n" << thisu->usrname << std::endl;
    std::cout << thisu->phonenum << std::endl;
    std::cout << thisu->hashpass << std::endl;
    */

    oldu.push_back(thisu);
    if(!SAVETO(thisu)){
        std::cout << "Something went wrong, couldn't save to file.";
    }

    return true;
}               


/* 
 * USRCHECK_R()
 * @param : string
 * return : bool
 * desc : Check to see if the username already exists
 */
bool USRCHECK_R(std::string username){
   for(auto g : oldu){
       if(username == g->usrname)
           return false;
   }
   return true;
}              


/* 
 * PHONECHECK_R()
 * @param : string
 * return : bool
 * desc : Check to see if the phone number already exists
 */
bool PHONECHECK_R(std::string phonenumber){

    for(auto g : oldu){
        if(phonenumber == g->phonenum)
            return false;
    }
    return true;
}   


/* 
 * USRCHECK_F()
 * @param : string
 * return : bool
 * desc : Check to see if the username's format is correct
 */
bool USRCHECK_F(std::string username){

    std::size_t found = username.find(' ');
    if (found != std::string::npos)
        return false;
    return true;
}           


/* 
 * PHONECHECK_F()
 * @param : string
 * return : bool
 * desc : Check to see if the phonenumber's format is correct
 */
bool PHONECHECK_F(std::string phonenumber){

    std::size_t found = phonenumber.find(' ');
    if (found!=std::string::npos)
        return false;
    if(phonenumber.length() < 10)
        return false;
    return true;
}


/* 
 * GETPASS()
 * @param : none
 * return : string
 * desc : Gets the password from user for adding logins
 */
std::string GETPASS(){

    bool goodpass = false;
    std::string finl;

    while(!goodpass){
        std::string temp="";
        std::string temp2="";
        
        std::cout << "\nEnter your password : ";
        
        termios oldt;
        tcgetattr(STDIN_FILENO, &oldt);
        
        termios newt = oldt;
        newt.c_lflag &= ~ECHO;
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        
        getline(std::cin, temp);

        if(temp == "q" || temp == "Q")
            return temp;

        std::cout << "\nEnter your password again : ";
        getline(std::cin, temp2);
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt); 

        if(temp==temp2){
            goodpass = true;
            finl = temp;
        }
        else{
            std::cout << "\nPassword doesn't match, try again.";
            goodpass = false;
        }
    }
    return finl;
}


/* 
 * SAVETO()
 * @param : struct usrinfo 
 * return : bool
 * desc : Save to list
 */
bool SAVETO(usrinfo * thisu){
    std::fstream FILE;
    std::string delim = ";";
    FILE.open(FILENAME, std::ios::app);

    if(!FILE.is_open()){
        return false;
    }

    FILE << thisu->usrname;
    FILE << delim;
    FILE << thisu->hashpass;
    FILE << delim;
    FILE << thisu->phonenum << "\n";

    FILE.close();
    return true;
}


/* 
 * LOGIN()
 * @param : none
 * return : bool
 * desc : Logs you into the program only if you all correct credentials 
 */
bool LOGIN(){
    bool leave = false;
    std::string PHNUM;
    std::string USRNM;
    std::string PWRD;
    std::cin.clear();
    std::cin.ignore();
   
    do{
        system("clear");
        std::cout << GREEN << "\n================ LOGIN PAGE ================== " << CYAN << "\n[ Enter 'q' in username to go to main menu. ]\n" << RESET;
        std::cout << "\n\tUsername : ";
        getline(std::cin, USRNM);

        if(USRNM == "q" || USRNM == "Q"){
            leave == true;
            return false;
        }

        termios oldt;
        tcgetattr(STDIN_FILENO, &oldt);
        termios newt = oldt;
        newt.c_lflag &= ~ECHO;
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);

        std::cout << "\tPassword : ";
        getline(std::cin, PWRD);
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt); 

        if(!USERCREDCHECK(USRNM, PWRD)){
            std::cout << "\n\nCredentials not met, try again.";
            continue;
        }
        
        for(auto & usr : oldu){
            if(usr->usrname == USRNM)
            {
                coset * thiscodeset = new coset;
                thiscodeset->code = GENCODE();
                thiscodeset->phonenumber = usr->phonenum;
                PHNUM = usr->phonenum;
                codes.push_back(thiscodeset);
                break;
            }
        }


        if(!RECIEVER(PHNUM)){
            DELCODE(PHNUM);
            std::cout << "The code recieved did not match, try again";
            return false;
        }
        else{
            for(auto & usr : oldu){
                if(usr->phonenum == PHNUM){
                    currusr = usr;
                }
            }
            return true;
        } 

    } while(!leave);
    return false;
}


/* 
 * USERCREDCHECK()
 * @param : string, string
 * return : bool
 * desc : Check your username and password
 */
bool USERCREDCHECK(std::string username,std::string password){
    hash hasher;                                  //How we hash our password
    for(auto g : oldu){
        if(username == g->usrname){
            if(hasher.genhash(password) == g->hashpass){
                return true;
            }
        }
    }
    return false;
}   



/* 
 * GENCODE()
 * @param : none
 * return : string
 * desc : generate the code
 */
std::string GENCODE(){
    srand (time(NULL));
    int RCODE = rand()%(100000 - 50000 + 1) + 50000;

    std::stringstream ss;
    ss << RCODE;
    return ss.str();
}



/* 
 * DELCODE()
 * @param : string
 * return : void
 * desc : Deleting code from data base when they get it right or when they timed out
 */
void DELCODE(std::string phonenum){
    for(auto & h : codes){
        if(h->phonenumber == phonenum){
            delete h;
        }
    }
    codes.clear();
}                              


/* 
 * FRONTPAGE()
 * @param : none
 * return : void
 * desc : Shows front page;
 */
void FRONTPAGE(){
    system("clear");
    std::cout << CYAN << "\n\t\t\t\t\t================== " << BLUE << "Home Page" << CYAN << " ===================" << RESET;
    std::cout << "\n\n\t\t\t\t\t\t\tHello " << MAGENTA << currusr->usrname << "!" << RESET;
    std::cout << "\n\n\t\t\t\t\t       [" << YELLOW << " Home " << RESET << "]   [" << YELLOW << " Portal " << RESET << "]   [" << YELLOW << " Settings " << RESET "]\n\n\n";
    FREEALL();
    exit(0);
}

/* 
 * SENDSMS()
 * @param : string
 * return : bool
 * desc : use the sms class to send message to user
 */
bool SENDSMS(std::string phonenumber){

    std::string code; 
    sms autho;
    for(auto f : codes){
        if(f->phonenumber == phonenumber){
            code = f->code;
        }
    }
    autho.setMessage(code, HEADER);
    autho.setContact(phonenumber);
    autho.setUSER(OURSID, CLI_TOKEN, CLI_NUM);
    autho.setprogr_name(PROG_NAME);

    if(!autho.sendMessage()){
        return false;
    }
    return true;
}


/* 
 * RECIEVER()
 * @param : string
 * return : bool
 * desc : check the user reply with the code on file.
 */
bool RECIEVER(std::string phonenumber){

    if(!SENDSMS(phonenumber)){
        return false;
    }
    //std::cin.ignore();
    std::cin.clear();
    system("clear");
    
    std::string code; 
    bool leave = false;
    bool match = false;

    for(auto f : codes){
        if(f->phonenumber == phonenumber){
            code = f->code;
        }
    }
   

    do {
        std::string usrcode;
        std::cout << "\nYour code was sent to +" << phonenumber << ".\nPlease enter the code below OR enter 'q' to leave. \n>> ";
        std::getline(std::cin, usrcode);
        if(usrcode == "q"){
            leave = true;
        }
        else if(usrcode == code){
            leave = true;
            match = true;
        }
        else
        {
            std::cout << "The code entered was not correct, Try again." << std::endl;
        }

    } while(!leave);

    if(leave && match){
        return true;
    }
    if(leave && !match){
        return false;
    }
}
