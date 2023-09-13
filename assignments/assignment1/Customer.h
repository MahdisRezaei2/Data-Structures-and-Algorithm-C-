#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <iostream>
#include "math.h"
#include <stdexcept>
#include <string>

/**
 * customer ID
 * number of requested beds
 */

class Customer
{

private:
   // information we need about each customer
   std::string customer_id;
   int number_of_requested_bed;

public:
   Customer(); // default constructor

   Customer(std::string customer_id, int number_of_requested_bed); // parameterized constructor

   ~Customer(); // destructor

   Customer(Customer &myCustomer); // copy constructor

   // some getters
   int getNumber_Of_requested_bed() const;
   std::string getCustomer_id() const;

   // some setters
   void setCCheck_in_date(std::string sIn);
   void setCCheck_out_date(std::string sOut);
   void setCustomer_id(std::string sId);
};

#endif