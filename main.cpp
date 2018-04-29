//
//  main.cpp
//  ERT35P2
//
//  Copyright © 2017 Elaina Teramoto. All rights reserved.
//


// the overloading error is equal to -999999 (sentiel value)
// try catch statements so the program can still go along without
// ending it if there is an overflow problem


#include "main.h"

using namespace std;

int main(int argc, const char * argv[]) {
    
    Polynomial<int> polynomial1;
    Polynomial<int> polynomial2;
    Polynomial<int> polynomial3;
    //fstream inFile(file);
    ifstream inFile(argv[1]);
    if (!(inFile.is_open()))
    {
        cout << "file does not open";
        return 0;
    }
    else
    {
        string poly1, poly2;
        int value, value2;
        getline(inFile, poly1);
        istringstream in(poly1);
        while (in >> value >> value2)
        {
            polynomial1.addToList(value, value2);
        }
        cout << "This is poly1 " <<endl;
        polynomial1.display();
        cout << "This is the evaluation for poly1 x = 10: " << polynomial1.evaluate(10) <<endl;
        getline(inFile, poly2);
        istringstream iss(poly2);
        while (iss >> value >> value2)
        {
            polynomial2.addToList(value, value2);
                
        }
        cout << "This is poly2" <<endl;
        polynomial2.display();
        cout << "This is the evaluation for poly2 x = 10: " << polynomial2.evaluate(10) <<endl;
            
        cout <<"This is the addition of poly 1 and poly2" <<endl;
        Polynomial< int> polynomial3 = polynomial1 + polynomial2;
        polynomial3.display();
        cout << "This is the evaluation for poly3 x = 10: " << polynomial3.evaluate(10) <<endl;
            
        cout <<endl << "This is multiplication of poly1 and poly2" <<endl;
        Polynomial< int> polynomial5 =polynomial1.multiply(polynomial2);
        polynomial5.display();
        cout << "This is the evaluation for poly3 x = 2: " << polynomial5.evaluate(2) <<endl;
            
        cout <<endl << "This is exponentiation of poly1 to the 3" <<endl;
        Polynomial<int> polynomial6 =polynomial1.exponentiation(3);
        polynomial6.display();
        
        cout <<endl<< "This is exponentiation of poly1 to the poly2 = 5:" <<endl;
        Polynomial<int> polynomial7 =polynomial1.exponentiation(polynomial2.evaluate(5));
        polynomial7.display();
            
      
    }
    
    return 0;
}
