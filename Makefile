# This file is intended for Project 1 Summer 2019
# CSCE4550 
# Tuyet Pham

CC=g++ -std=c++11
TARGET=autho
OBJS=main.o sms.o
OBJ_DIR=obj
IN_DIR=/inc
SRC_DIR=src

CXXFLAG=-I$(IN_DIR)


autho: $(OBJS)
	$(CC) $(OBJ_DIR)/main.o $(OBJ_DIR)/sms.o -o autho -lpython2.7
	@echo Build complete. Have fun!

main.o:	$(SRC_DIR)/main.cpp inc/resources.h 
	$(CC) -c $(SRC_DIR)/main.cpp $(CXXFLAG)/resources.h $(CXXFLAG)/twilioresources.h -o $(OBJ_DIR)/$@ 

sms.o:	$(SRC_DIR)/sms.cpp inc/sms.h
	$(CC) -c -I$(IN_DIR)/sms.h $(SRC_DIR)/sms.cpp -o $(OBJ_DIR)/$@ -lpython2.7

twilio:	
	pip3 install twilio
	pip3 install twilio --upgrade

clean:
	rm -f -r obj/*.o autho

clean_all:
	@echo *******!!DELETING EVERYTHING!!!*********
	rm -r etc inc obj src README.md autho
	pip3  uninstall twilio
