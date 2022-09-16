/*****************************************************************
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
//  FILE:        record.h
//
//  DESCRIPTION:
//   This file is a header file with a struct. A struct is our
//   custom datatype. It is used to store the account number,
//   name, mailing/housing address, and the address of the next
//   record. This is mostly used in the backend of our banking
//   application. But in order to save the hassle of declaring
//   the same variables in multiple files, we use a header file
//   instead.
//
****************************************************************/

struct record
{
    int accountno;
    char name[25];
    char address[50];
    struct record* next;
};
