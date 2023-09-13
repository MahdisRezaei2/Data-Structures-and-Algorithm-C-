#ifndef LL_H
#define LL_H
#include <iostream>
#include "Room.h"
#include <iostream>
#include <string>

/**
 * we have this class to make linked lists od Room,  in other words, linked lists of objects
 */

class ListNode
{
public:
    Room room;
    ListNode *next;

    ListNode(Room room)
    {
        this->room = room;
        next = nullptr;
    }
};

class RoomList
{
private:
public:

    // need 3v heads because we are going to have three lists
    ListNode *head1;
    ListNode *head2;
    ListNode *head3;

    //default constructor 
    RoomList()
    {
        head1 = nullptr;
        head2 = nullptr;
        head3 = nullptr;
    }

    // this function is for when we want to add an occupied room to our lists based on the number of beds
    void addRoom(const Room &room)
    {
        int numberOfBeds = room.getNumber_of_beds();
        ListNode *newNode = new ListNode(room);
        if (numberOfBeds == 1)
        {
            newNode->next = head1;
            head1 = newNode;
        }
        else if (numberOfBeds == 2)
        {
            newNode->next = head2;
            head2 = newNode;
        }
        else if (numberOfBeds == 3)
        {
            newNode->next = head3;
            head3 = newNode;
        }
        else
        {
            std::cout << "invalid number of beds" << std::endl;
            delete newNode;
        }
    }

    // this function is to check if our lists are empty or not

    bool isEmpty() const
    {
        return head1 == nullptr && head2 == nullptr && head3 == nullptr;
    }
    
    // for the update function, we need to be able to get the check out date of first node (room) to compare it to the checkin date
    // this function helps us with that
    std::string getFirstRoomCheckoutDate() const
    {
        ListNode *current = head1;
        std::string earliestCheckoutDate;

        while (current != nullptr)
        {
            std::string checkoutDate = current->room.getCheck_out_date();
            if (earliestCheckoutDate.empty() || checkoutDate < earliestCheckoutDate)
            {
                earliestCheckoutDate = checkoutDate;
            }
            current = current->next;
        }

        return earliestCheckoutDate;
    }
   
   // when the check out date of a room is close, the room is going to be available soo, so we need to remove it from our occupied room lists
   // this function helps us with that
    Room removeFirstRoom()
    {
        if (head1 != nullptr)
        {
            ListNode *temp = head1;
            head1 = head1->next;
            delete temp;
        }
    }

    //this function helps us to get a room from our lists
    
    Room *RoomList::getRoom() const
    {
        if (head1 != nullptr)
        {
            return &(head1->room);
        }
        else if (head2 != nullptr)
        {
            return &(head2->room);
        }
        else if (head3 != nullptr)
        {
            return &(head3->room);
        }
        else
        {
            return nullptr;
        }
    }
};

#endif