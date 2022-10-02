//
//  order_class.hpp
//  Assignment 11
//
//  Created by CarloDavid Soto on 4/20/22.
//

#ifndef order_class_hpp
#define order_class_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
class order_record
{
public:
    std::string cell_number;
    std::string item_number;
    double quantity;
    double price;
    int processing_plant;
    double tax_rate;
    double order_tax;
    double net_cost;
    double total_cost;
};

class order_class
{
public:
    order_class();  //default constructor
    order_class(const order_class &); //copy constructor
    ~order_class(); //de-allocates all memory allocate to INV by operator new.
    bool is_Empty(); //inline implementation
    bool is_full();//inline implementation
    int search(const std::string key);//returns location if item in INV; otherwise return -1
    void add( ); //adds a order record to INV
    order_class & operator-(const std::string key); //removes all items in INV with a cell number that matches key.
    void double_size();
    void process();
    friend std::ostream & operator<<(std::ostream & out, order_class & Org); //prints all the elements in INV to the screen
private:
    int count;
    int size;
    order_record *INV;
};
#endif /* order_class_hpp */
