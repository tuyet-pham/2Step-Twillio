----> PLEASE READ BEFORE RUNNING <----
(1) Make sure you have all the files : 
             =main.cpp, resources.h
             =sms.h, sms.cpp
             =.twiliosms.py
	     =twilioresources.h
             =Makefile

(2)  Program will add a password list called '.passwdlist.txt' to your directory. This will ensure the hashed password are consistent. So do not add your own.

(3) You will need to 'Add Account' first in order to log in with your newly created account.

(4) Makefile is included.

(5) 'make clean_all' to delete all files except for the Makefile so be careful when using. This will also remove twilio. 

(6) You will need python 3.6

(7) You will need to install pip3

(8) You will need to install twilio manually or invoke 'make twilio'. The program will run without twilio library installed, but you will not get the message so make sure to install.

(9) Please refer to https://www.youtube.com/watch?v=IoV57uTw7Es&feature=youtu.be to see the process on my phone as the API only works for verified phone numbers. That feature costs 20$. :(


*****************************************************************/
*****************************************************************/

<>> Procedure for python and pip. Skip if not needed <<>
$ sudo apt-get update
$ sudo apt-get upgrade
$ sudo apt-get install python3.6
$ sudo apt install python3-pip

<>> Procedure for program <<>
$ make twilio 
$ make 
$ ./autho 
$ make clean 

<>> In addition <<>
$ make clean_all 



