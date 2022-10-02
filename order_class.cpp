//
//  order_class.cpp
//  Assignment 11
//
//  Created by CarloDavid Soto on 4/20/22.
//

#include "order_class.hpp"
#include <iostream>
#include <string>
#include <fstream>

//Name: default constructor
//Precondition: INV array has not been initialized, data from input file has not been opened, variables not initialized.
//Postcondition: INV array has been initialized, data file opened, variables have been initialized.
//Decription: Reads the data file of purchase order information (cell number, item, quantity, price, and processing plant) into the dynamic array of order records,
//INV. If the count become equal to the size the function double_size is called and the memory allocated to INV is doubled.
order_class::order_class()
{
    std::cout << "The default constructor has been called\n";
    count = 0;
    size = 1;
    INV = new order_record[size];
    std::ifstream in;
    in.open("purchase_data_Assignment11.txt");
    while (!in.eof())
        {
            if (is_full())
            {
                double_size();
                in >> INV[count].cell_number;
                in >> INV[count].item_number;
                in >> INV[count].quantity;
                in >> INV[count].price;
                in >> INV[count].processing_plant;
            }
            else {
                in >> INV[count].cell_number;
                in >> INV[count].item_number;
                in >> INV[count].quantity;
                in >> INV[count].price;
                in >> INV[count].processing_plant;
            }
            count++;
        }
    in.close();
}

//Name: copy constructor
//Precondition: Deep copy of dynamic array not made.
//Postcondition: Deep copy of dynamic array made.
//Decription: performs a deep copy.
order_class::order_class(const order_class & org)
{
    count = org.count;
    size = org.size;

    INV = new order_record[size]; // create an array of size

       // loop to deep copy each record's field from org to this object
    for(int i=0;i<count;i++)
    {
    INV[i].cell_number = org.INV[i].cell_number;
    INV[i].item_number = org.INV[i].item_number;
    INV[i].quantity = org.INV[i].quantity;
    INV[i].price = org.INV[i].price;
    INV[i].processing_plant = org.INV[i].processing_plant;
    }

    process();
}

//Name: is_Empty
//Precondition: Has not to checked if INV is empty.
//Postcondition: Has checked if INV is empty.
//Decription: returns true if INV is empty
bool order_class::is_Empty()
{
    return count == 0;
}

//Name: is_full
//Precondition: Array has not been checked to see if its full.
//Postcondition: Array has been checked to see if its full.
//Decription: returns true if INV is full
bool order_class::is_full()
{
    return count == size;
}

//Name: search
//Precondition: Array has not been searched.
//Postcondition: Array has been searched and if found, -1 is returned.
//Decription: locates key in INV if it is there; otherwise -1 is returned
int order_class::search(const std::string key)
{
    for (int i = 0; i < count; i++) {
           if (INV[i].cell_number == key) {
               return i;
           }
       }
    return -1;
}

//Name: add
//Precondition: Has not requested the user to fill in the data fields.
//Postcondition: Has requested the user to fill in the required data fields. If the array is full, then it calls the double_size to double the array size.
//Decription: adds a call_record to INV; if INV is full, double_size is called to increase the size of INV. The user
//            is prompted to enter the cell number, item, quantity, price, and processing plant.
void order_class::add( )
{
    if(is_full())
    {
        double_size();
        std::cout << "Enter customer cell number: ";
        std::cin >> INV[count].cell_number;
        std::cout << "Enter item number: ";
        std::cin >> INV[count].item_number;
        std::cout << "Enter quantity of item: ";
        std::cin >> INV[count].quantity;
        std::cout << "Enter price of the item: ";
        std::cin >> INV[count].price;
        std::cout << "Enter processing plant: ";
        std::cin >> INV[count].processing_plant;
        count++;
    }
    else
    {
        std::cout << "Enter customer cell number: ";
        std::cin >> INV[count].cell_number;
        std::cout << "Enter item number: ";
        std::cin >> INV[count].item_number;
        std::cout << "Enter quantity of item: ";
        std::cin >> INV[count].quantity;
        std::cout << "Enter price of the item: ";
        std::cin >> INV[count].price;
        std::cout << "Enter processing plant: ";
        std::cin >> INV[count].processing_plant;
        count++;
    }
    process();
}

//Name: double_size
//Precondition: Size of dynamic array unchanged.
//Postcondition: Size of dynamic array changed by a 2x.
//Decription: doubles the size (capacity) of INV
void order_class::double_size( )
{
    size *=2;
    order_record *temp = new order_record[size];
    for(int i=0; i<count; i++)
    {
        temp[i] = INV[i];
    }
    delete [ ] INV;
    INV = temp;
}

//Name: process
//Precondition: Variable values have not been calculated.
//Postcondition: Variable values have been calculated and initialized.
//Decription: calculate the tax rate, order tax, net cost, total order cost for every call record in INV.
void order_class::process()
{
    for(int i = 0; i < count; i++){
        if(INV[i].processing_plant >= 0 && INV[i].processing_plant <= 50){
            INV[i].tax_rate = 6;
        }
        else if(INV[i].processing_plant >= 51 && INV[i].processing_plant <= 110){
            INV[i].tax_rate = 7;
        }
        else if(INV[i].processing_plant >= 111 && INV[i].processing_plant <= 200){
            INV[i].tax_rate = 8;
        }
        else if(INV[i].processing_plant >= 201 && INV[i].processing_plant <= 500){
            INV[i].tax_rate = 9;
        }
        else if(INV[i].processing_plant > 500){
            INV[i].tax_rate = 11;
        }
    
        INV[i].order_tax = INV[i].quantity * INV[i].price * (INV[i].tax_rate/100);
        INV[i].net_cost = INV[i].quantity * INV[i].price;
        INV[i].total_cost = INV[i].net_cost + INV[i].order_tax;
    }
}

//Name: destructor
//Precondition: Memory has not been de-allocated.
//Postcondition: Memory has been de-allocated.
//Decription: de-allocates all memory allocated to INV.  This will be the last function to be called (automatically by the compiler)
//before the program is exited.
order_class::~order_class()
{
    std::cout << "The destructor has been called\n";
    delete [] INV;
    count = 0;
    size = 0;
}

//Name: operator-
//Precondition: Order recrods INV remains unchanged.
//Postcondition: Fields that matched key removed.
//Decription: removes all order records in INV with a cell number field that matches key, if it is there. Chain was
//            implemented.
order_class & order_class::operator-(const std::string key) //removes an item from the list
{
    if(search(key) != -1){
        int loc = search(key);
        for(;loc < count -1; loc++){
            INV[loc] = INV[loc +1];
        }
        count--;
    }
    return *this;
}

//Name: operator<<
//Precondition: All fields not printed to the screen.
//Postcondition: Every field of INV is printed to the screen.
//Decription: prints every field of every call_record in INV formatted to the screen.

std::ostream & operator<<(std::ostream & out, order_class & Org) //prints all the elements in INV to the screen
{
    for(int i=0; i< Org.count; i++)
    {
        out.setf(std::ios::fixed);
        out.setf(std::ios::showpoint);
        out.precision(2);
        out << Org.INV[i].cell_number << std::setw(10) << std::left;
        out << Org.INV[i].item_number << std::setw(10) << std::left;
        out << int(Org.INV[i].quantity) << std::setw(10) << std::left;
        out << Org.INV[i].price << std::setw(10) << std::left;
        out << Org.INV[i].processing_plant << std::setw(10) << std::left;
        out << int(Org.INV[i].tax_rate) << std::setw(10) << std::left;
        out << Org.INV[i].order_tax << std::setw(10) << std::left;
        out << Org.INV[i].net_cost << std::setw(10) << std::left;
        out << Org.INV[i].total_cost << std::endl;
    }
    return out;
}
