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
//  FILE:        llist.h
//
//  DESCRIPTION:
//   This is a header file that has a class, called "llist". In
//   this class we store some variables & functions as private,
//   and some functions as public. This file saves us the hassle
//   of making variable & function declarations in multiple files.
//
****************************************************************/

#include "record.h"

class llist
{
private:
    struct record* start;
    char filename[16];
    int readfile();
    int writefile();
    void cleanup();

public:
    llist();
    llist(char[]);
    ~llist();
    int addRecord(int accnum, char name[], char address[]);
    int findRecord(int accnum);
    void printAllRecords();
    int deleteRecord(int accnum);
};
