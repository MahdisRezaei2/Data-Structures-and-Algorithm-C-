#include "Room.h"
#include "ll.h"
#include <iostream>
#include "math.h"
#include <stdexcept>
#include <string>
/**
 * this file is to do the implementaiotn of the functions we defined in the Room.h
*/

// default constructor
Room::Room()
{
    totalNumberOf1Bedrooms = 100;
    totalNumberOf2Bedrooms = 50;
    totalNumberOf3Bedrooms = 30;
    number_of_beds = 0;
    number_of_rooms = 0;
}

// parametarized constructor 
Room::Room(int number_of_beds, int number_of_rooms)
{
    totalNumberOf1Bedrooms = 100;
    totalNumberOf2Bedrooms = 50;
    totalNumberOf3Bedrooms = 30;
    number_of_beds = number_of_beds;
    number_of_rooms = number_of_rooms;
}
Room room1;

Room::~Room()
{
    // Destructor
}

// implementaion of some getter
int Room::getTotalNumberOf1Bedrooms() const
{
    return totalNumberOf1Bedrooms;
}

int Room::getTotalNumberOf2Bedrooms() const
{
    return totalNumberOf2Bedrooms;
}

int Room::getTotalNumberOf3Bedrooms() const
{
    return totalNumberOf3Bedrooms;
}

std::string Room::getCustomer_id() const
{
    return customer_id;
}

std::string Room::getCheck_in_date() const
{
    return check_in_date;
}

std::string Room::getCheck_out_date() const
{
    return check_out_date;
}

int Room::getNumber_of_beds() const
{
    return number_of_beds;
}

int Room::getNumber_of_rooms() const
{
    return number_of_rooms;
}

// implementaition of some setters

void Room::setCheck_in_date(const std::string &check_in_date)
{
    this->check_in_date = check_in_date;
}

void Room::setCheck_out_date(const std::string &check_out_date)
{
    this->check_out_date = check_out_date;
}

void Room::setCustomer_id(const std::string &customer_id)
{
    this->customer_id = customer_id;
}

// the next 3 functions, do the occupation for each room for each customer based on number of beds
void Room::room_with_one_bed_occupied_by(std::string &customer_id, std::string &check_in_date, std::string &check_out_date)
{

    customer_id = customer_id;
    check_in_date = check_in_date;
    check_out_date = check_out_date;
    totalNumberOf1Bedrooms--;
    RoomList roomList1;
    Room room_1_beds(1, 1);
    roomList1.addRoom(room_1_beds);
}
void Room::room_with_two_beds_occupied_by(std::string &customer_id, std::string &check_in_date, std::string &check_out_date)
{

    customer_id = customer_id;
    check_in_date = check_in_date;
    check_out_date = check_out_date;
    totalNumberOf2Bedrooms--;
    RoomList roomList2;
    Room room_2_beds(2, 1);
    roomList2.addRoom(room_2_beds);
}
void Room::room_with_three_beds_occupied_by(std::string &customer_id, std::string &check_in_date, std::string &check_out_date)
{

    customer_id = customer_id;
    check_in_date = check_in_date;
    check_out_date = check_out_date;
    totalNumberOf3Bedrooms--;
    RoomList roomList3;
    Room room_3_beds(3, 1);
    roomList3.addRoom(room_3_beds);
}

// this function checkes the availability, based on the requested number of beds and not occupied rooms we have
bool Room::is_room_available(int number_of_beds)
{
    if (number_of_beds <= 3 && (totalNumberOf1Bedrooms >= number_of_beds || totalNumberOf2Bedrooms >= number_of_beds || totalNumberOf3Bedrooms >= number_of_beds))
    {
        return true;
    }
    else if (number_of_beds > 3)
    {
        int remainingBeds = number_of_beds;
        if (totalNumberOf3Bedrooms > 0)
        {
            remainingBeds -= 3;
        }
        if (remainingBeds > 0 && totalNumberOf2Bedrooms > 0)
        {
            remainingBeds -= 2;
        }
        if (remainingBeds <= 0)
        {
            return true;
        }
        else if (remainingBeds <= totalNumberOf1Bedrooms)
        {
            return true;
        }
    }
    return false;
}

// this function updates the system based on the explanation mentioned in header and testing file
void Room::update(std::string &checkInDay)
{
    RoomList roomList1;
    RoomList roomList2;
    RoomList roomList3;
    // Room *room1 = roomList1.getRoom();
    //  Room *room2 = roomList2.getRoom();
    //   Room *room3 = roomList3.getRoom();
    ListNode *previousNode = nullptr;
    ListNode *currentRoom1 = roomList1.head1;
    ListNode *currentRoom2 = roomList2.head1;
    ListNode *currentRoom3 = roomList3.head1;
    while (currentRoom1 != nullptr && currentRoom2 != nullptr && currentRoom3 != nullptr)
    {

        if (checkInDay == currentRoom1->room.getCheck_out_date())
        {
            previousNode->next = currentRoom1->next;
            totalNumberOf1Bedrooms++;
        }
        else if (checkInDay == currentRoom2->room.getCheck_out_date())
        {
            previousNode->next = currentRoom2->next;
            totalNumberOf2Bedrooms++;
        }
        else if (checkInDay == currentRoom3->room.getCheck_out_date())
        {
            previousNode->next = currentRoom3->next;
            totalNumberOf3Bedrooms++;
        }
        else
        {
            roomList1.head1 = currentRoom1->next;
            roomList2.head2 = currentRoom2->next;
            roomList3.head3 = currentRoom3->next;
        }
        break;
    }
    previousNode = currentRoom1;
    currentRoom1 = currentRoom1->next;
}
