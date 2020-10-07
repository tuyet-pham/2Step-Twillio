/*******************************************************
*   Created by : Tuyet N. Pham
*   Created on : July 20, 2019
*   Copyright 2019, Tuyet N. Pham, All rights reserved.
*******************************************************/
#include "../inc/sms.h"

sms::sms(){}
sms::~sms(){}

/*
*   Constructor ( TOKEN , 
*                    SID, 
*            PHONENUMBER, 
*                message, 
*                heading, 
*         contact_number )
*/
sms::sms(std::string TOKEN, std::string SID, std::string PHONENUMBER, std::string thismessage, std::string thisheaderstring,  std::string conNum) : 
    CLI_TOKEN(TOKEN), CLI_SID(SID), CLI_NUMBER(PHONENUMBER), message(thismessage), headerstring(thisheaderstring), ctactNUMBER(conNum)
{
    this->sms::setUSER(SID, TOKEN, PHONENUMBER);
    this->sms::setMessage(thismessage, thisheaderstring);
    this->sms::setContact(conNum);
}


/* 
 * CALLPYSCRIPT
 * @param : none
 * return : bool
 * desc : invoke the python scrypt that send the message via twilio API
 */
bool sms::CALLPYSCRIPT(){
    std::string scrptpath = "python3 etc/.twiliosms.py " + this->CLI_SID + " " + this->CLI_TOKEN + " " 
        + this->CLI_NUMBER + " " + this->message + " " + this->headerstring + " " + this->ctactNUMBER;
    if(system(scrptpath.c_str()) == 5){
        std::cout << "Something is wrong with the script!\n";
	system("PAUSE");
        return false;
    }
    return true;
}


/* 
 * setUSER
 * @param : string, string, string
 * return : void
 * desc : set user info
 */
void sms::setUSER(std::string SID, std::string TOKEN, std::string PHONENUMBER){
    this->CLI_SID = SID;
    this->CLI_TOKEN = TOKEN;
    this->CLI_NUMBER = PHONENUMBER;
}


/* 
 * setMessage
 * @param : string, string
 * return : void
 * desc : setting the message
 */
void sms::setMessage(std::string message, std::string headerstring){
    this->message= message;
    this->headerstring = headerstring;
}


/* 
 * setContact
 * @param : string
 * return : void
 * desc : settting the reciever's number
 */
void sms::setContact(std::string conNum){
    this->ctactNUMBER = conNum;
}


/* 
 * sendMessage
 * @param : none
 * return : bool
 * desc : calling the CALLPYSCRIPT() function to invoke the python script
 */
bool sms::sendMessage(){
    if(CALLPYSCRIPT()){
        return true;
    }
    return false;
}

/* 
 * setprogr_name
 * @param : string
 * return : void
 * desc : setting the name of the python script. 
 */
void sms::setprogr_name(std::string progname){
    this->prgName = progname;
}
