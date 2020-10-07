/*******************************************************
*   Created by : Tuyet N. Pham
*   Created on : July 20, 2019
*   Copyright 2019, Tuyet N. Pham, All rights reserved.
*******************************************************/
#include <stdio.h>
#include <iostream>
#include <string.h>

#ifndef SMS_H
#define SMS_H

class sms{

    private:
        std::string CLI_SID;
        std::string CLI_TOKEN;
        std::string CLI_NUMBER;
        std::string message;
        std::string headerstring;
        std::string ctactNUMBER;
        std::string prgName;
        bool CALLPYSCRIPT();                            

    public:
        sms();
        sms(std::string TOKEN, std::string API, std::string PHONENUMBER, std::string thismessage, std::string thisheaderstring, std::string conNum); 
        void setUSER(std::string API, std::string USERNAME, std::string phonenumber);
        void setMessage(std::string message, std::string headerstring);
        void setContact(std::string conNum);
        void setprogr_name(std::string progname);
        bool sendMessage();                                                 
        ~sms();         
};

#endif 