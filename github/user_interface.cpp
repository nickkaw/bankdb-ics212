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
//  FILE:        user_interface.cpp
//
//  DESCRIPTION:
//   We replicate the same program as in Project 1, but now in C++.
//   This is the user interface of our interpretation of a bank
//   application. Here the user interacts with the application.
//   The application gives information and instructions for the
//   user to follow. Lots of different datatypes are also stored
//   from the user. If the user does not follow the instructions
//   the application gives an error and tries again until a valid
//   input is entered. 
//
****************************************************************/

#include <iostream>
#include <iomanip>
#include <cstring>
#include "llist.h"

/*****************************************************************
//
//  Function name: main
//
//  DESCRIPTION:   This main function is the main bulk of our
//                 user interface. This how the user interacts
//                 with our program, which includes selecting
//                 menu options, adding/storing integers/strings.
//
//  Parameters:    argc (int) : The number of elements in argv
//                 argv (char*[]) : An array of arguments passed
//                                  to the program.
//
//  Return values:  0 : success
//
****************************************************************/

int main(int argc, char *argv[])
{
    int runapp;
    char menuinput[20];
    int an_input;
    char name_input[25];
    char address_input[50];

    llist mylist;

    runapp = 1;
    while(runapp > 0)
    {
        std::cout << "\n========== Main Menu ==========" << std::endl;
        std::cout << "To select a main menu option, please type the option name out. Then hit ENTER to proceed." << std::endl;
        std::cout << "add: Creates a new bank record in the database. User chooses an account number, name, and mail address." << std::endl;
        std::cout << "printall: Prints out a list of all the records in the database." << std::endl;
        std::cout << "find: Finds the record of a specific account number." << std::endl;
        std::cout << "delete: Deletes a record of a specific account number." << std::endl;
        std::cout << "quit: Exits the application." << std::endl;

        std::cin.getline(menuinput, sizeof(menuinput));

        if(std::strncmp(menuinput, "quit", std::strlen(menuinput)) == 0)
        {
            std::cout << "Quit option selected..." << std::endl;
            std::cout << std::endl;
            runapp = runapp - 2;
        }

        else if(std::strncmp(menuinput, "delete", std::strlen(menuinput)) == 0)
        {
            std::cout << "Delete option selected..." << std::endl;
            std::cout << std::endl;

            std::cout << "Enter an account number to delete:" << std::endl;
            std::cin >> an_input;

            while(!(an_input > 0))
            {
                if(std::cin.fail())
                {
                    std::cout << "Invalid Input." << std::endl;
                    std::cout << "Please enter a positive integer :" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(100, '\n');
                }
                else if(an_input <= 0)
                {
                    std::cout << "Invalid Input. Numbers cannot be 0 or below." << std::endl;
                    std::cout << "Please enter a positive integer :" << std::endl;
                }
                std::cin >> an_input;
            }
            std::cout << an_input << std::endl;
            std::cin.ignore(100, '\n');
            
            int success = mylist.deleteRecord(an_input);
            if(success == 0)
            {
                std::cout << "Successfully deleted a Record." << std::endl;
            }
            else if(success == -1)
            {
                std::cout << "Error, failed to delete a Record." << std::endl;
            }

            std::cout << "Returning to Main Menu." << std::endl;
        }

        else if(std::strncmp(menuinput, "find", std::strlen(menuinput)) == 0)
        {
            std::cout << "Find option selected..." << std::endl;
            std::cout << std::endl;

            std::cout << "Enter an account number to find:" << std::endl;
            std::cin >> an_input;

            while(!(an_input > 0))
            {
                if(std::cin.fail())
                {
                    std::cout << "Invalid Input." << std::endl;
                    std::cout << "Please enter a positive integer :" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(100, '\n');
                }
                else if(an_input <= 0)
                {
                    std::cout << "Invalid Input. Numbers cannot be 0 or below." << std::endl;
                    std::cout << "Please enter a positive integer :" << std::endl;
                }
                std::cin >> an_input;
            }
            std::cout << an_input << std::endl;
            std::cin.ignore(100, '\n');
            
            int success = mylist.findRecord(an_input);
            if(success == 0)
            {
                std::cout << "Successfully found a Record." << std::endl;
            }
            else if(success == -1)
            {
                std::cout << "Error, failed to find a Record." << std::endl;
            }

            std::cout << "Returning to Main Menu." << std::endl;
        }

        else if(std::strncmp(menuinput, "printall", std::strlen(menuinput)) == 0)
        {
            std::cout << "PrintAll option selected..." << std::endl;
            std::cout << std::endl;
            mylist.printAllRecords();

            std::cout << "Returning to Main Menu." << std::endl;
        }

        else if(std::strncmp(menuinput, "add", std::strlen(menuinput)) == 0)
        {
            std::cout << "Add option selected..." << std::endl;
            std::cout << std::endl;

            std::cout << "Enter an account number to add:" << std::endl;
            std::cin >> an_input;

            while(!(an_input > 0))
            {
                if(std::cin.fail())
                {
                    std::cout << "Invalid Input." << std::endl;
                    std::cout << "Please enter a positive integer :" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(100, '\n');
                }
                else if(an_input <= 0)
                {
                    std::cout << "Invalid Input. Numbers cannot be 0 or below." << std::endl;
                    std::cout << "Please enter a positive integer :" << std::endl;
                }
                std::cin >> an_input;
            }
            std::cout << an_input << std::endl;
            std::cin.ignore(100, '\n');

            std::cout << "Enter a name for the account :" << std::endl;
            std::cin.getline(name_input, sizeof(name_input));
            std::cout << "Name :" << name_input << std::endl;

            int getaddress = 1;
            char lineinput[50];
            std::cout << "Enter an address for the account :" << std::endl;
            std::cout << "Enter an EMPTY LINE when you are finished." << std::endl;
            while(getaddress > 0)
            {
                std::cin.getline(lineinput, sizeof(lineinput));
                if(std::strlen(lineinput) == 0)
                {
                    std::strncpy(address_input, address_input, sizeof(address_input));
                    getaddress = -1;
                }
                else
                {
                    std::strcat(address_input, lineinput);
                    std::strcat(address_input, "\n");
                }
            }
            std::cout << "Address :" << address_input << std::endl;

            int success = mylist.addRecord(an_input, name_input, address_input);
            if(success == 0)
            {
                std::cout << "Successfully added a Record." << std::endl;
            }
            else if(success == -1)
            {
                std::cout << "Error, failed to add a Record." << std::endl;
            }
            std::strcpy(name_input, "");
            std::strcpy(address_input, "");

            std::cout << "Returning to Main Menu." << std::endl;
        }
        else
        {
            std::cout << "Sorry, the option seleted does not exist. Please try again." << std::endl;
            std::cout << std::endl;
        }
    }
    return 0;
}
