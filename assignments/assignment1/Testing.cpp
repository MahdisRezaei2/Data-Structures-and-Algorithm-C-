/*
this file reads the txt file, calls functions from other header files such as Room.h and customer.h
*/

#include "Room.h"
#include "Customer.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <chrono>
#include <iomanip>
// we need to check if the year is leap, because this need to be considered when we want to calculate the check out date based on the duration
bool isLeapYear(int year)
{
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// this function calculates the check out date based on the checkin date and duration
std::string findCheckOutDate(std::string &checkInDate, int duration)
{
        std::tm checkInTime = {};
        std::istringstream checkInStream(checkInDate);
        checkInStream >> std::get_time(&checkInTime, "%d/%m/%Y");
     
        std::chrono::system_clock::time_point checkInDateTime = std::chrono::system_clock::from_time_t(std::mktime(&checkInTime));
        std::chrono::system_clock::time_point checkOutDateTime = checkInDateTime + std::chrono::hours(duration * 24);

        
        std::time_t checkOutTime = std::chrono::system_clock::to_time_t(checkOutDateTime);
        std::tm *checkOutTimeTM = std::gmtime(&checkOutTime);

    
        int checkOutDay = checkOutTimeTM->tm_mday;
        int checkOutMonth = checkOutTimeTM->tm_mon + 1;    
        int checkOutYear = checkOutTimeTM->tm_year + 1900; 

        
        while (checkOutDay > 28)
        {
                if (checkOutDay > 30 || (checkOutDay == 31 && !(checkOutMonth == 1 || checkOutMonth == 3 || checkOutMonth == 5 || checkOutMonth == 7 || checkOutMonth == 8 || checkOutMonth == 10 || checkOutMonth == 12)))
                {
                       
                        ++checkOutMonth;
                        if (checkOutMonth > 12)
                        {
                                checkOutMonth = 1;
                                ++checkOutYear;
                        }

                    
                        checkOutDay = 1;
                }
                else if (checkOutMonth == 2 && checkOutDay == 29 && !isLeapYear(checkOutYear))
                {
                       
                        ++checkOutMonth;
                        checkOutDay = 1;
                }
                else
                {

                     
                        break;
                }
        }

   
        std::stringstream checkOutDateString;
        checkOutDateString << std::setfill('0') << std::setw(2) << checkOutDay << "/" << std::setw(2) << checkOutMonth << "/" << checkOutYear;
        std::string checkOutDate = checkOutDateString.str();
        return checkOutDate;
}

int main()
{      
       //Asking for the name of the file
        std::string checkInDate;
        std::cout << "Enter file name :   " << std::endl;
        std::string file_name;
        std::cin >> file_name;
         //Reading the file
        std::ifstream file(file_name);
        if (!file.is_open())
        {
                std::cout << "File not found, failed to open" << std::endl;
                return 1;
        }

        std::string lineInfo;
        bool isFirstLine = true;
        std::string prevCheckInDate;
        while (std::getline(file, lineInfo))
        {
                if (isFirstLine)
                {
                        isFirstLine = false;
                        continue;
                }
                std::vector<std::string> fields;
                std::stringstream ss(lineInfo);
                std::string field;

                while (std::getline(ss, field, ','))
                {
                        fields.push_back(field);
                }
                checkInDate = fields[0];
                std::string custumerID = fields[1];
                int numberOfBeds = std::stoi(fields[2]);
                int duration = std::stoi(fields[3]);
                std::string checkOutDate = findCheckOutDate(checkInDate, duration);
                Room room1(numberOfBeds, 1);
                bool is_available = room1.is_room_available(numberOfBeds);
                if (prevCheckInDate.empty())
                {
                        prevCheckInDate = checkInDate;
                }
                else
                {
                        if (prevCheckInDate == checkInDate)
                        {
                                std::cout << "same day" << std::endl;
                                // we can check the availibility
                                if (is_available)
                                {
                                        if (numberOfBeds == 1)
                                                room1.room_with_one_bed_occupied_by(custumerID, checkInDate, checkOutDate);
                                        else if (numberOfBeds == 2)
                                                room1.room_with_two_beds_occupied_by(custumerID, checkInDate, checkOutDate);
                                        else if (numberOfBeds == 3)
                                                room1.room_with_three_beds_occupied_by(custumerID, checkInDate, checkOutDate);
                                }
                                else
                                        std::cout << "Sorry, we don't have enough available rooms" << std::endl;
                                // book room for customer
                        }
                        else
                        {
                                std::cout << "date has changed, we need to update" << std::endl;
                                // we need to update our data
                                room1.update(checkInDate);
                        }
                        prevCheckInDate = checkInDate;
                }

                std::cout << "Check-in Date : " << checkInDate << std::endl;
                std::cout << "Duration : " << duration << std::endl;
                std::cout << "Check-out Date : " << checkOutDate << std::endl;
                std::cout << "Customer ID : " << custumerID << std::endl;
                std::cout << "numberOfBeds : " << numberOfBeds << std::endl;
                std::cout << std::endl;
        }
        file.close();

        return 0;
}