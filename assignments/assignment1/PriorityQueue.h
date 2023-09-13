#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
#include"Room.h"
#include"ll.h"


class PriorityQueue{
       
       private:
       // creating the 3 lists of occupied rooms in the priority queue
         RoomList list1;
         RoomList list2;
         RoomList list3;

        public:
        PriorityQueue(){}; // default constructor
        ~PriorityQueue(){}; // destructor 
        // this function does enqueing 
        void enqueue(const Room& room, int priority) {
        int numberOfBeds = room.getNumber_of_beds();
        
        // Add the room to the list in the priority queue
        if (numberOfBeds == 1) {
            list1.addRoom(room);
        } else if (numberOfBeds == 2) {
            list2.addRoom(room);
        } else if (numberOfBeds == 3) {
            list3.addRoom(room);
        } else {
            std::cout << "Invalid number of beds" << std::endl;
        }
    }
   // dequeue a room if the chechout dare is close (next day)
    Room dequeue() {
        Room room;
        int priority =  std::numeric_limits<int>::max();
        if(!list1.isEmpty()&& std::stoi(list1.getFirstRoomCheckoutDate())< priority){
            room = list1.removeFirstRoom();
            priority= std::stoi(room.getCheck_out_date());
        }
         if(!list2.isEmpty()&& std::stoi(list2.getFirstRoomCheckoutDate())< priority){
            room = list2.removeFirstRoom();
            priority= std::stoi(room.getCheck_out_date());
        }
         if(!list3.isEmpty()&& std::stoi(list3.getFirstRoomCheckoutDate())< priority){
            room = list3.removeFirstRoom();
           
        }
        return room;
    }

    bool isEmpty() const {
        // Check if all RoomLists are empty
        return list1.isEmpty() && list2.isEmpty() && list3.isEmpty();
    }
            
};

#endif
