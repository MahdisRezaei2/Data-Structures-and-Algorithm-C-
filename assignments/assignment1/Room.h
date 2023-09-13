#ifndef ROOM_H
#define ROOM_H
#include <iostream>
#include "math.h"
#include <stdexcept>
#include <string>
// creating a class of room
class Room
{
private:
// information that is connected or related to each room
    int totalNumberOf1Bedrooms;
    int totalNumberOf2Bedrooms;
    int totalNumberOf3Bedrooms;
    std::string customer_id;
    std::string check_in_date;
    std::string check_out_date;
    int number_of_beds;
    int number_of_rooms;

public:
    Room();// default construtor 
    Room(int number_of_beds, int number_of_rooms); // parameterized constructor 
    ~Room();


     // we have some getters here 
    int getTotalNumberOf1Bedrooms() const;
    int getTotalNumberOf2Bedrooms() const;
    int getTotalNumberOf3Bedrooms() const;
    std::string getCustomer_id() const;
    std::string getCheck_in_date() const;
    std::string getCheck_out_date() const;
    int getNumber_of_beds() const;
    int getNumber_of_rooms() const;
   
   // Setters
    void setCheck_in_date(const std::string &check_in_date);
    void setCheck_out_date(const std::string &check_out_date);
    void setCustomer_id(const std::string &customer_id);
    

    /*Here we have the functions thaht help us to mange the reservation of the rooms 
    /*these functions are called in different parts of the Testing.ccp file*/

    // for each number of beds of rooms we have a function to do the occupation of that room
    void room_with_one_bed_occupied_by( std::string &customer_id, std::string &check_in_date,  std::string &check_out_date);
    void room_with_two_beds_occupied_by( std::string &customer_id,  std::string &check_in_date,  std::string &check_out_date);
    void room_with_three_beds_occupied_by( std::string &customer_id,  std::string &check_in_date,  std::string &check_out_date);

    // this function checks that do we have any available rooms based on the number of beds and number of not occupied bedrooms
    bool is_room_available(int number_of_beds);

    /**
     * this function helps us to update our system, 
     *whever the checkin date is not samwe as the previous checkin date, we understand that day is chenged so we need to do some updates
     * this is the function which should dequeuing the rooms which their chech out date is close (tommorrow)
    */
    void update(std::string& checkInDay);
    
};


#endif