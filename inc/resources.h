/*******************************************************
*   Created by : Tuyet N. Pham
*   Created on : July 20, 2019
*   Copyright 2019, Tuyet N. Pham, All rights reserved.
*******************************************************/

#include <iostream>
#include <string>
#include <sstream>
#include <bits/stdc++.h> 
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <time.h>
#include <stdlib.h>
#include "../inc/sms.h"

/*COLORS - LINUX ONLY*/
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      
#define RED     "\033[31m"      
#define GREEN   "\033[32m"      
#define YELLOW  "\033[33m"     
#define BLUE    "\033[34m"      
#define MAGENTA "\033[35m"      
#define CYAN    "\033[36m"    
#define WHITE   "\033[37m" 


/*USER INFORMATION TYPE --- Hold users informations, easier to use in sets*/ 
typedef struct usrinfo {
        std::string usrname;
        std::string hashpass;
        std::string phonenum; 
        bool locked = false;
} usrinfo;

/*CODESET TYPE --- The 2step code used for authentication, and user number*/
typedef struct CODESET {
    std::string code;
    std::string phonenumber;
} coset;

/*HASH TYPE --- It's purpose is to generate a hash of the password with XOR and multipliers*/
typedef struct hash {
    private :

        unsigned long long H1 = 61172345992453;
        unsigned long long H2 = 234687890891;
        unsigned long long H3 = 2456222788223;
        std::string hexx(unsigned long long  hashval){
            std::string hexstring;
            std::stringstream hexval;
            hexval << std::hex << hashval;
            hexstring = hexval.str();
            return hexstring;
        }

        std::string hashing(std::string input){
             unsigned long long  hashval;
            for(int i = 0; i < input.size(); i++)
            {
                hashval = hashval | (input[i]);
                hashval = hashval * H1 * H2 * H3;
            }
            return hexx(hashval);
        }

    public :
        std::string genhash(std::string input){
           return hashing(input);
        }
} hash;



int MMENU();                          //Main menu

//ADD USER
bool ADDLOGIN();                      //Adding a user
bool USRCHECK_R(std::string);         //Checking for a repeat username 
bool PHONECHECK_R(std::string);       //Chekcing for a repeat phone number
bool USRCHECK_F(std::string);         //Checking for username formating
bool PHONECHECK_F(std::string);       //Checking for phone number formating
std::string GETPASS();                //Get password from user
bool SAVETO(usrinfo * thisu);         //Save to the list

//LOGIN
bool LOGIN();                                                       //Get credential
bool USERCREDCHECK(std::string username, std::string password);     //Check username credential
std::string GENCODE();                                              //Generate the code
bool SENDSMS(std::string phonenumber);                              //sending the client the message
bool RECIEVER(std::string phonenumber);                             //Check the user's reply with the code on file.

//CHECKING
bool CHECK4LIST();                      //Check for the passwdlist
bool CREATELIST();                      //Create passwdlist if not have
bool CHECKTWILIO();                     //Make sure twilio file exists

//LOADING FROM DATABASE
bool LOADTO(std::string filename);      //load into vector usrsinfo
void LOADTOAUX(std::string line);       //Creating entry with every line


void DELCODE(std::string phonenumber);  //Delete the code in accordance to the phone number
bool FREEALL();                         //Free the addrs of usr in both vectors
void FRONTPAGE();                       //Show after successful login




