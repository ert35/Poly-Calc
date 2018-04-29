//
//  polynomial.h
//  ERT35P2
//
//  Copyright © 2017 Elaina Teramoto. All rights reserved.
//

#ifndef polynomial_h
#define polynomial_h

using namespace std;
template <typename T>
class Polynomial;

template <typename T>
class Polynomial{
public:
    Polynomial();
    Polynomial( const Polynomial<T> &);
    ~Polynomial();
    void addToList(const T&, const T&);
    void display();
    void clear();
    int evaluate(const int);
    int powerEval(int , int );
    
    Polynomial<T> operator+ (const Polynomial<T>&);
    Polynomial<T> operator- (const Polynomial<T>&);
    const Polynomial<T>& operator= (const Polynomial<T>&);
    Polynomial<T> multiply(const Polynomial<T>&);
    Polynomial<T> exponentiation(const int exp);
    
    void merge(int **arr, int l, int m, int r);
    void mergeSort(int **arr, int l, int r);
    
    
private:
    
    Node<T> *frontPtr;
    Node <T> *backPtr;
    int terms;
    
};
///
template<typename T>
Polynomial<T>:: Polynomial()
{
    // initalizing
    frontPtr = 0;
    backPtr = 0;
    terms = 0;
}

template<typename T>
Polynomial<T>::Polynomial( const Polynomial<T> &poly1 )
{
    // copy constructor
    frontPtr = 0, backPtr = 0, terms = 0;
    Node<T> *oCurrent = poly1.frontPtr;
    while(oCurrent!=NULL)
    {
        this->addToList(oCurrent->coef, oCurrent->exponent);
        oCurrent = oCurrent->getNextPtr();
    }
}

///
template<typename T>
void Polynomial<T>:: addToList(const T& coef, const T& expon)
{
    //adds the object to the end of the linked list so it
    //stays in order from largest exponent to smallest
    Node<T> *tempBPtr = new Node<T>(coef, expon, NULL);
    if(frontPtr==NULL)
    {
        frontPtr = tempBPtr;
    }
    else
    {
        backPtr->nextPtr = tempBPtr;
        backPtr = tempBPtr;
    }
    backPtr = tempBPtr;
    terms++;
    
}
///
template<typename T>
void Polynomial<T>:: display()
{
    // print out the polynomial
    Node <T> * current = frontPtr;
    for (int i = 0; i <terms; i++)
    {
        if (!(current->coef == 0))
        {
            // if coefficient is zero then dont show exponent
            if (!(current->coef ==1))
            // if coefficient is one then don't display
            {
                cout << current->coef;
            }
            if (current->exponent ==1)
            {
            // dont show the '^'
                cout << "x";
            }
            else if (!(current->exponent == 0))
            {
            // as long as the exponent doesn't equal 0
                cout << "x^" << current->exponent;
            }
            if (!(i == (terms-1)))
            {
            // if it is not the last term then print +
                cout << " + ";
            }
        }
        //get it's next value
        current = current ->getNextPtr();
    }
    cout << endl;
}

///
template <typename T>
void Polynomial<T>::clear()
{
    // clearing the polynomial until it is equal to zero
    /*
     as long as the frontPtr does not equal 0, keep traversing 
     and deleting the objects until it does equal 0. 
     make a temporary pointer to front ptr's next object and delete frontPtr 
     and then make frontPtr equal to the temp ptr.
     */
    while (frontPtr != 0)
    {
        if(frontPtr->getNextPtr() == NULL ) //only one value on the list
        {
            delete frontPtr;
            frontPtr = NULL;
        }
        else
        {
            Node <T> *fptr = frontPtr->getNextPtr();
            delete frontPtr;
            frontPtr = fptr;
        }
    }
    backPtr = 0;
    terms = 0;
}
///
template<typename T>
Polynomial<T>::~Polynomial()
{
    // deconstructor
    this ->clear();
}
///
template <typename T>
const Polynomial<T>& Polynomial<T>::operator=(const Polynomial<T>& temp )
{
    //overloaded =
    // if the current polynomial does not equal the other polynomial (temp)
    // make the current polynomial equal to the temp polynomial.
    // to do this, first clear the contents of current and then traverse through
    // temp and add the objcts to current.
    if (this != &temp)
    {
        this->clear();
        Node<T> *current = temp.frontPtr;
        while(current!= NULL)
        {
            this->addToList(current->coef, current->exponent);
            current = current->getNextPtr();
        }
    }
    return *this;
}

///
template<typename T>
Polynomial<T> Polynomial<T>::operator+(const Polynomial<T>&secondPoly)
{
    /*
     add the secondPolynomial to the polynomial on the left (frontPtr is pointing 
     to it). as long as they both don't point to 0, check if their exponents are the same,
     then add the coefficents togeter and move both frontPtrs. if not add the object to the resulting
     polynomial and keep traversing through. The 2 while loops are for if one list has less polynomials than the other then it should still traverse through until they point to 0.
     */
    try
    {
        Polynomial<T> additionResult; //result polynomial
        Node<T> *firstP = frontPtr;
        Node<T> *secondP = secondPoly.frontPtr;
        while((firstP != 0 ) && (secondP != 0))
        {
            if (firstP->exponent  == secondP->exponent)
            {
                //if same exponent then add the coef together
                int resultcoef = firstP->coef + secondP->coef;
                if (!((secondP->coef) == resultcoef - (firstP->coef)))
                {
                    // overflow error
                    throw string("coefficient overflow: operator +");
                }
                additionResult.addToList(resultcoef, firstP->exponent);
                firstP= firstP->getNextPtr();
                secondP= secondP->getNextPtr();
            }
            else if(firstP->exponent > secondP->exponent)
            {
                //if the expon is bigger than the second expon
                additionResult.addToList(firstP->coef ,firstP->exponent);
                firstP= firstP->getNextPtr();
            }
            else if (firstP->exponent < secondP->exponent)
            {
                //add the expon if its not in the list
                additionResult.addToList(secondP->coef,secondP->exponent);
                secondP= secondP->getNextPtr();
            }
        }
        while (firstP !=0)
        {
            // if firstP still has objects
            additionResult.addToList(firstP->coef, firstP->exponent);
            firstP= firstP->getNextPtr();
        }
        while (secondP !=0)
        {
            //if secondP still has objects
            additionResult.addToList(secondP->coef, secondP->exponent);
            secondP= secondP->getNextPtr();
        }
        
        return additionResult;
    }
    catch (string s)
    {
        // catch the overflow error
        cout << s <<endl; // print it out
        //but keep going-> dont end the program
        Polynomial <int> catchingReturn;
        catchingReturn.addToList(~0,~0);
        return catchingReturn;
    }
}
///
template<typename T>
Polynomial<T> Polynomial<T>::operator-(const Polynomial<T>&secondPoly)
{
    //overloaded -
    /*
     subtracts the second polynomial from the first. If the exponents are the same then subtract the 
     coeffificent. if there is a term that the second has and the first doesnt then it should be equal to 0- second Polynomial coefficient. The 2 else if statements take care of that.
     */
    try
    {
        Polynomial<T> subtractionResult;
        Node<T> *firstP = frontPtr;
        Node<T> *secondP = secondPoly.frontPtr;
        while((firstP != 0 ) && (secondP != 0))
        {
            if (firstP->exponent  == secondP->exponent)
            {
                //if same exponent then subtract the coef together
                int resultcoef = firstP->coef - secondP->coef;
                if (!((firstP->coef) == resultcoef + (secondP->coef)))
                {
                    //if there is an overflow issue
                    throw string("coefficient overflow: operator -");
                }
                subtractionResult.addToList(resultcoef, firstP->exponent);
                firstP= firstP->getNextPtr();
                secondP= secondP->getNextPtr();
            }
            else if(firstP->exponent > secondP->exponent)
            {
                subtractionResult.addToList(firstP->coef ,firstP->exponent);
                firstP= firstP->getNextPtr();
            }
            else if (firstP->exponent < secondP->exponent)
            {
                int result = (secondP->coef * -1);
                subtractionResult.addToList(result,secondP->exponent);
                secondP= secondP->getNextPtr();
            }
        }
        while (firstP !=0)
        {
            //add the rest of the objects in firstP to resultP
            subtractionResult.addToList(firstP->coef, firstP->exponent);
            firstP= firstP->getNextPtr();
        }
        while (secondP !=0)
        {
            //add the rest of the secondPointer to resultP
            int result = (secondP->coef * -1);
            subtractionResult.addToList(result, secondP->exponent);
            secondP= secondP->getNextPtr();
        }
        return subtractionResult;
    }
    catch (string s)
    {
        //print out the overflow error but dont end the program
        cout << s << endl;
        Polynomial <int> catchingReturn;
        catchingReturn.addToList(~0,~0);
        return catchingReturn;
    }
}
///
template <typename T>
Polynomial<T> Polynomial<T>::multiply(const Polynomial<T> &secondPoly)
{
    try
    {
        Node<T> *firstP = frontPtr;
        Node<T> *secondP = secondPoly.frontPtr;
        
        int totalSize = terms * secondPoly.terms;
        int indexTerm = 0;
        int **terms1 = new int*[totalSize];
        /*
         It is faster and easier to run merge sort to sort the exponents from highest 
         to lowest on an array than doing it with pointers/ linked lists. Because of this
         I used up some time and space to fill the 2D array with the current objects that
         are in the linked list.
         */
        for (int i = 0; i < terms; i++)
        {
            //distrbute so have to reset everytime
            secondP = secondPoly.frontPtr;
            
            for (int j = 0; j < secondPoly.terms; j++)
            {
                terms1[indexTerm] = new int[2];
                terms1[indexTerm][0] = firstP->coef*secondP->coef;
                terms1[indexTerm][1] = firstP->exponent + secondP->exponent;
                if (terms1[indexTerm][0]/firstP->coef != secondP->coef ||
                    terms1[indexTerm][1] - firstP->exponent != secondP->exponent)
                {
                    //overflow is true
                    throw string("overflow: multiply");
                }
                indexTerm++;
                secondP = secondP->getNextPtr();
            }
            firstP = firstP->getNextPtr();
        }
        
        //sort from greatest to least exponents
        mergeSort(terms1, 0, indexTerm- 1);
        
        /*
         add the coefficients together if the exponents are the same. Continue traversing through, but 
         if you've already looked at that object because it shares the same exponent then, make sure the next object you look at is the object that is after the last object that had the same exponent.
         
         */
        Polynomial<T> result;
        int j = 1;
        int m =0;
        
        while (m< totalSize)
        {
            j = 1;
            if (m + j < totalSize)
            {
                if (terms1[m][1] == terms1[m + j][1])
                {
                    while (terms1[m][1] == terms1[m + j][1])
                    {
                        int oldTerm2 = terms1[m][0];
                        terms1[m][0] += terms1[m + j][0];
                        if (terms1[m][0] - oldTerm2 != terms1[m + j][0])
                        {
                            //overflow is true
                            cout <<("overflow: multiply") <<endl;
                        }
                        if (j+m >= totalSize)
                        {
                            m=totalSize; break;
                        }
                        else
                            j++;
                
                    }
                    result.addToList(terms1[m][0], terms1[m][1]);
                    m+= j;
                }
                else
                {
                    result.addToList(terms1[m][0],terms1[m][1]);
                    m++;
                }
            }
            else
            {
                result.addToList(terms1[m][0], terms1[m][1]);
                m++;
            }
        }
        for (int i = 0; i <totalSize ;i++)
        {
            delete[] terms1[i];
        }
        delete[] terms1;
        return result;
    }
    catch (string s)
    {
        // print out the s string
        cout << s <<endl;
        Polynomial <int> catchingReturn;
        catchingReturn.addToList(~0,~0);
        return catchingReturn;
    }
    
}

///
template<typename T>
int Polynomial<T>::evaluate(const int base)
{
    /*
     evalute the polynomial with the value that is given. multiply the coef from
     the result of the powerEval function. That way we don't have to do x*x*x.. etc. Throw a string if 
     there is overflow and add a temporary value to make the function still run.
     */
    try
    {
        Node<T> *tempPoly = frontPtr;
        int result = 0;
        int tempResult = 0;
        while (tempPoly !=0)
        {
            tempResult = result;
            result += tempPoly->coef * powerEval(base,tempPoly->exponent );
            if (tempResult != result - tempPoly->coef * powerEval(base,tempPoly->exponent ))
            {
                //checks for overflow
                throw string("overflow: evaluate");
            }
            tempPoly = tempPoly->getNextPtr();
        }
        return result;
    }
    catch (string s)
    {
        cout << s  <<endl;
        Polynomial <int> catchingReturn;
        catchingReturn.addToList(~0,~0);
        return 1;
    }
    
}
///
template <typename T>
int Polynomial<T>::powerEval(int base, int exponent)
{
    /*
     if the exponent is 1 then return the base. anything to the power of 1 is itself. 
     while the exponent is bigger than 0, multiply itself. print out an overflow statement if it occurs
     */
    try {
        if (exponent == 1)
            return base;
        int current = 1;
        
        while (exponent > 0)
        {
            int old = current;
            int oBase = base;
            if (exponent &1)
            {
                current = current*base;
                if (old != current/base)
                {
                    //check for overflow
                    throw string("overflow: power evaluation: result");
                }
            }
            base = base * base;
            exponent >>= 1;
            if (oBase != base / oBase)
            {
                throw string("overflow: power evaluation: base");
                //check for base overflow
            }
        }
        return current;
    }
    catch (string s)
    {
        cout << s << endl;
        Polynomial <int> catchingReturn;
        catchingReturn.addToList(~0,~0);
        return 1;
    }
    
}
///
template <typename T>
Polynomial<T> Polynomial<T>::exponentiation(const int exponent)
{
    // check if negative 
    if (exponent < 0 )
    {
        //returns itself
        cout << "the exponent is negative "<<endl;
        return *this;
    }
    
    Polynomial<T> exponReturn;
    if (exponent == 0)
    {
        exponReturn.addToList(1, 1);
        return exponReturn;
        // something to the 0 is 1
    }
    exponReturn = *this;
    if (exponent == 1)
    {
        return exponReturn;
    }
    Polynomial <T> originial = exponReturn;
    exponReturn = exponReturn.multiply(*this);
    Polynomial <T> exponReturnSquared= exponReturn;
    if (exponent % 2 == 0)//even exponent
    {
        for (int i = 1; i < exponent/2; i++)
        {
            exponReturn = exponReturn.multiply(exponReturnSquared);
        }
    }
    else //odd exponent
    {
        for (int i = 1; i < (exponent - 1) / 2; i++)
        {
            exponReturn = exponReturn.multiply(exponReturnSquared);
        }
        exponReturn = exponReturn.multiply(originial);
    }
    return exponReturn;
}

///
template <typename T>
void Polynomial<T>::merge(int **unorderarr, int left, int middle, int right)
{
    /*
    merge
     */
    int bsize = right - middle;
    int tsize = middle - left + 1;
    int a = 0, b = 0, c = left;
    int** bottom = new int*[bsize];
    int** top = new int*[tsize];
    
    //copy data into temporary arrays
    for (int i = 0; i < bsize; i++)
    {
        bottom[i] = unorderarr[middle + 1+ i];
    }
    for (int j = 0; j < tsize; j++)
        top[j] = unorderarr[left + j];
    
    //merge the temporary arrays back in the original array
    while (a < bsize && b < tsize)
    {
        if (top[b][1] <=bottom[a][1])
        {
            unorderarr[c] = bottom[a];
            a++;
        }
        else
        {
            unorderarr[c] = top[b];
            b++;
        }
        c++;
    }
    
    while (a < bsize)
    {
        unorderarr[c] = bottom[a];
        a++;
        c++;
    }
    while (b < tsize)
    {
        unorderarr[c] = top[b];
        b++;
        c++;
    }
}
///
template <typename T>
void Polynomial<T>::mergeSort(int **unorderarr, int left, int right)
{
    //returns the arrray from highest exponent to lowest exponent
    //instead of the originial lowest exponent to highest
    //subarray
    if (left < right)
    {
        int middle = left+(right-left)/2;
        //sort first and second half
        mergeSort(unorderarr, left, middle);
        mergeSort(unorderarr, middle+1, right);
        merge(unorderarr, left, middle, right);
    }
}

#endif /* polynomial_h */
