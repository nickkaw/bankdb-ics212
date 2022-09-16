/*****************************************************************
//
//  NAME:        Nicholas Kaw
//
//  HOMEWORK:    Project 2
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        November 27, 2021
//
//  FILE:        llist.cpp
//
//  DESCRIPTION:
//   We replicate the same program as in Project 1, but now in C++.
//   This file is the backend of our interpretation of a banking
//   application. This is where records of customer's bank
//   information is stored, modified, or printed. As of right now
//   it does not work, but this file is necessary to connect to
//   the user interface file.
//
****************************************************************/

#include <iostream>
#include <fstream>
#include <cstring>
#include "llist.h"

/*****************************************************************
//
//  Function name: llist
//
//  DESCRIPTION:   This function is a constructor, which initializes
//                 all the variables and functions of the llist
//                 class. In this constructor we let the program 
//                 decide the name of the save file.
//
//  Parameters:    No Parameters
//
//  Return values:  Nothing is returned.
//
****************************************************************/

llist::llist()
{
#ifdef DEBUGMODE
    std::cout << "\n---------- DEBUG MODE ----------" << std::endl;
    std::cout << "Function name: llist\nParameter(s):" << std::endl;
    std::cout << "No Parameters" << std::endl;
    std::cout << "--------------------------------\n" << std::endl;
#endif

    start = NULL;
    std::strcpy(filename, "savefile.txt");
    readfile();
}

/*****************************************************************
//
//  Function name: llist
//
//  DESCRIPTION:   This function is an overloaded constructor,
//                 which initializes all the variables and 
//                 functions of the llist class. However as an
//                 overloaded constructor, it takes in a variable
//                 that would decide the name of the save file.
//
//  Parameters:    fileinput (char[]) : The name of a specified
//                 file dedicated to write & read in the data.
//
//  Return values:  Nothing is returned.
//
****************************************************************/

llist::llist(char fileinput[])
{
#ifdef DEBUGMODE
    std::cout << "---------- DEBUG MODE ----------" << std::endl;
    std::cout << "Function name: llist\nParameter(s):" << std::endl;
    std::cout << "char filename[]: " << filename << std::endl;
    std::cout << "--------------------------------" << std::endl;
#endif

    start = NULL;
    std::strcpy(filename, fileinput);
    readfile();
}

/*****************************************************************
//
//  Function name: ~llist
//
//  DESCRIPTION:   This function is a destructor, which deletes
//                 or deallocate memory for all the variables and
//                 functions of the llist class.
//
//  Parameters:    No Parameters
//
//  Return values:  Nothing is returned.
//
****************************************************************/

llist::~llist()
{
#ifdef DEBUGMODE
    std::cout << "\n---------- DEBUG MODE ----------" << std::endl;
    std::cout << "Function name: ~llist\nParameter(s):" << std::endl;
    std::cout << "No Parameters" << std::endl;
    std::cout << "--------------------------------\n" << std::endl;
#endif

    writefile();
    cleanup();
}

/*****************************************************************
//
//  Function name: addRecord
//
//  DESCRIPTION:   This addRecord function adds the user's
//                 "bank information".
//
//  Parameters:    uiaccnum (int) : The account number the user
//                 inputted.
//                 uiname (char[]) : The name the user inputted.
//                 uiaddress (char[]) : The "mailing address" the
//                 user inputted.
//
//  Return values:  0 : success
//                  -1 : fail
//
****************************************************************/

int llist::addRecord(int uiaccnum, char uiname[], char uiaddress[])
{
#ifdef DEBUGMODE
    std::cout << "\n---------- DEBUG MODE ----------" << std::endl;
    std::cout << "Function name: addRecord\nParameter(s):" << std::endl;
    std::cout << "int uiaccnum: " << uiaccnum << std::endl;
    std::cout << "char uiname[]: " << uiname << std::endl;
    std::cout << "char uiaddress[]: " << uiaddress;
    std::cout << "--------------------------------\n" << std::endl;
#endif

    int returnval = 1;
    int getaccnum;
    struct record *insertptr;
    struct record *temp;
    struct record *nexttemp;
    struct record *prevtemp = NULL;

    if(this->start == NULL)
    {
        insertptr = new record;
        insertptr->accountno = uiaccnum;
        strcpy(insertptr->name, uiname);
        strcpy(insertptr->address, uiaddress);
        insertptr->next = NULL;
        this->start = insertptr;
        returnval = 0;
    }
    else
    {
        temp = this->start;
        nexttemp = temp->next;
        prevtemp = NULL;
        getaccnum = temp->accountno;
    }
    while (returnval > 0)
    {
        if(uiaccnum == getaccnum)
        {
            returnval = -1;
        }
        else if(uiaccnum < getaccnum)
        {
            if(nexttemp == NULL)
            {
                insertptr = new record;
                insertptr->accountno = uiaccnum;
                strcpy(insertptr->name, uiname);
                strcpy(insertptr->address, uiaddress);
                insertptr->next = NULL;
                temp->next = insertptr;
                returnval = 0;
            }
            else
            {
                prevtemp = temp;
                temp = nexttemp;
                nexttemp = temp->next;
                getaccnum = temp->accountno;
            }
        }
        else if(uiaccnum > getaccnum)
        {
            insertptr = new record;
            insertptr->accountno = uiaccnum;
            strcpy(insertptr->name, uiname);
            strcpy(insertptr->address, uiaddress);
            insertptr->next = temp;

            if(prevtemp == NULL)
            {
                this->start = insertptr;
            }
            else
            {
                prevtemp->next = insertptr;
            }
            returnval = 0;
        }
    }
    return returnval;
}

/*****************************************************************
//
//  Function name: printAllRecords
//
//  DESCRIPTION:   This printAllRecords function prints all of the
//                 records that are stored in the bank's database.
//
//  Parameters:    No Parameters
//
//  Return values:  Nothing is returned.
//
****************************************************************/

void llist::printAllRecords()
{
#ifdef DEBUGMODE
    std::cout << "\n---------- DEBUG MODE ----------" << std::endl;
    std::cout << "Function name: printAllRecords\nParameter(s):" << std::endl;
    std::cout << "No Parameters" << std::endl;
    std::cout << "--------------------------------\n" << std::endl;
#endif 

    int count = 1;
    struct record *temp;
    struct record *nexttemp;

    if(this->start == NULL)
    {
        std::cout << "No Records in the Database." << std::endl;
    }
    else
    {
        temp = this->start;
        nexttemp = temp->next;
        while(temp != NULL)
        {
            nexttemp = temp->next;
            std::cout << "Record #" << count << std::endl;
            std::cout << "Account Number: " << temp->accountno << std::endl;
            std::cout << "Name: " << temp->name << std::endl;
            std::cout << "Address: " << temp->address << std::endl;
            temp = nexttemp;
            count++;
        }
    }

}

/*****************************************************************
//
//  Function name: findRecord
//
//  DESCRIPTION:   This findRecord function finds the record of
//                 a specific account number in the database. The
//                 account number is given from the user.
//
//  Parameters:    accountno (int) : The account number the user
//                 inputted.
//
//  Return values:  0 : success
//                  -1 : fail
//
****************************************************************/

int llist::findRecord(int uiaccnum)
{
#ifdef DEBUGMODE
    std::cout << "\n---------- DEBUG MODE ----------" << std::endl;
    std::cout << "Function name: findRecord\nParameter(s):" << std::endl;
    std::cout << "int uiaccnum: " << uiaccnum << std::endl;
    std::cout << "--------------------------------\n" << std::endl;
#endif

    int returnval = 1;
    int getaccnum;
    struct record *temp;
    struct record *nexttemp;

    if(this->start == NULL)
    {
        std::cout << "There are no records in the database." << std::endl;
        returnval = -1;
    }
    else
    {
        temp = this->start;
        nexttemp = temp->next;
        getaccnum = temp->accountno;
        while (returnval > 0)
        {
            if(uiaccnum == getaccnum)
            {
                std::cout << "Record Found..." << std::endl;
                std::cout << "Account Number: " << temp->accountno << std::endl;
                std::cout << "Name: " << temp->name << std::endl;
                std::cout << "Address: " << temp->address << std::endl;
                returnval = 0;
            }
            else if(uiaccnum != getaccnum)
            {
                if(nexttemp == NULL)
                {
                    returnval = -1;
                }
                else
                {
                    temp = nexttemp;
                    nexttemp = temp->next;
                    getaccnum = temp->accountno;
                }
            }
        }
    }
    return returnval;
}

/*****************************************************************
//
//  Function name: deleteRecord
//
//  DESCRIPTION:   This deleteRecord function deletes a record of
//                 a specific account number from the database.
//                 The account number is given from the user.
//
//  Parameters:    uiaccountno (int) : The account number the user
//                 inputted.
//
//  Return values:  0 : success
//                  -1 : fail
//
****************************************************************/

int llist::deleteRecord(int uiaccnum)
{
#ifdef DEBUGMODE
    std::cout << "\n---------- DEBUG MODE ----------" << std::endl;
    std::cout << "Function name: deleteRecord\nParameter(s):" << std::endl;
    std::cout << "int uiaccnum: " << uiaccnum << std::endl;
    std::cout << "--------------------------------\n" << std::endl;
#endif

    int returnval = 1;
    int getaccnum;
    struct record *getnext;
    struct record *temp;
    struct record *nexttemp;
    struct record *prevtemp = NULL;

    if(this->start == NULL)
    {
        returnval = -1;
    }
    else
    {
        temp = this->start;
        nexttemp = temp->next;
        getaccnum = temp->accountno;
    }
    while(returnval > 0)
    {
        if(uiaccnum == getaccnum)
        {
            if(prevtemp == NULL)
            {
                getnext = temp->next;
                delete temp;
                this->start = getnext;
            }
            else if(nexttemp == NULL)
            {
                getnext = NULL;
                delete temp;
                prevtemp->next = getnext;
            }
            else if(prevtemp != NULL && nexttemp != NULL)
            {
                getnext = temp->next;
                delete temp;
                prevtemp->next = getnext;
            }
            returnval = 0;
        }
        else if(uiaccnum != getaccnum)
        {
            if(nexttemp == NULL)
            {
                returnval = -1;
            }
            else
            {
                prevtemp = temp;
                temp = nexttemp;
		nexttemp = temp->next;
                getaccnum = temp->accountno;
            }
        }
    }

    return returnval;
}

/*****************************************************************
//
//  Function name: readfile
//
//  DESCRIPTION:   This readfile function will read a textfile
//                 from the same directory and create database
//                 records using information in the textfile.
//
//  Parameters:    No Parameters
//
//  Return values:  0 : success
//                  -1 : fail
//
****************************************************************/

int llist::readfile()
{
#ifdef DEBUGMODE
    std::cout << "\n---------- DEBUG MODE ----------" << std::endl;
    std::cout << "Function name: readfile\nParameter(s):" << std::endl;
    std::cout << "No Parameters" << std::endl;
    std::cout << "--------------------------------\n" << std::endl;
#endif

    int returnval;
    int an_finput;
    char name_finput[25];
    char address_finput[50];

    std::ifstream infile;
    infile.open(this->filename);
    if(infile.is_open())
    {
        char linein[50];
        int getaddress = 1;
        int getoutofwhile = 1;
        while(!infile.eof() && getoutofwhile == 1)
        {
            infile >> an_finput;
            if(an_finput == 0)
            {
                getaddress = 0;
                getoutofwhile = 0;
            }
            infile.ignore(100, '\n');
            infile.getline(name_finput, 100);
            while(getaddress > 0)
            {
                infile.getline(linein, 100);
                if(std::strlen(linein) == 0)
                {
                    getaddress = 0;
                    addRecord(an_finput, name_finput, address_finput);
                }
                else
                {
                    std::strcat(address_finput, linein);
                    std::strcat(address_finput, "\n");
                }
            }
            an_finput = 0;
            std::strcpy(name_finput, "");
            std::strcpy(address_finput, "");
            getaddress = 1;
        }
        returnval = 0;
    }
    else
    {
        std::fstream newfile;
        newfile.open(this->filename);
        newfile.close();
        returnval = -1;
    }
    infile.close();
    return returnval;
}

/*****************************************************************
//
//  Function name: writefile
//
//  DESCRIPTION:   This writefile function will take all of the
//                 records in the database and store their account
//                 number, name, and address in a textfile located
//                 in the same directory.
//
//  Parameters:    No Parameters
//
//  Return values:  0 : success
//                  -1 : fail
//
****************************************************************/

int llist::writefile()
{
#ifdef DEBUGMODE
    std::cout << "\n---------- DEBUG MODE ----------" << std::endl;
    std::cout << "Function name: writefile\nParameter(s):" << std::endl;
    std::cout << "No Parameters" << std::endl;
    std::cout << "--------------------------------\n" << std::endl;
#endif

    int returnval;
    struct record *temp;
    struct record *nexttemp;
    
    std::ofstream outfile;
    outfile.open(this->filename, std::ofstream::trunc);
    if(!(outfile.is_open()) || this->start == NULL)
    {
        returnval = -1;
    }
    else
    {
        temp = this->start;
        while(temp != NULL)
        {
            nexttemp = temp->next;
            outfile << temp->accountno << std::endl;
            outfile << temp->name << std::endl;
            outfile << temp->address << std::endl;
            temp = nexttemp;
        }
        returnval = 0;
    }
    outfile.close();

    return returnval;
}

/*****************************************************************
//
//  Function name: cleanup
//
//  DESCRIPTION:   This cleanup function will deallocate all of
//                 the memory that was allocated to the heap.
//                 This will help to ensure that there are no
//                 memory leaks before ending the program.
//
//  Parameters:    No Parameters
//
//  Return values: Nothing is returned.
//
****************************************************************/

void llist::cleanup()
{
#ifdef DEBUGMODE
    std::cout << "\n---------- DEBUG MODE ----------" << std::endl;
    std::cout << "Function name: cleanup\nParameter(s):" << std::endl;
    std::cout << "No Parameters" << std::endl;
    std::cout << "--------------------------------\n" << std::endl;
#endif

    struct record *temp = NULL;
    struct record *nexttemp;

    if (this->start != NULL)
    {
        temp = this->start;
        nexttemp = temp->next;
    }
    while(temp != NULL)
    {
        nexttemp = temp->next;
        delete temp;
        temp = nexttemp;
    }
    this->start = NULL;
}
