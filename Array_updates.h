#include <iostream>
#include <vector>
#include <math.h>
#include "TOPglobalconstants.h"
using namespace std;

// ************************************ quotientnonzero **********************************

// does division, but accounts for the possibility that the denominator is zero
// if denominator == 0, outputs 0. otherwise, outputs    numerator / denominator  
// defined for multiple datatypes
double quotientnonzero( double loc_a, double loc_b ) //
{ // *
double loc_quotient;
if ( loc_b == 0 ) { loc_quotient = 0 ;}
else { loc_quotient = loc_a / loc_b ;}
return loc_quotient;
} // *

double quotientnonzero( unsigned int loc_a, unsigned int loc_b ) //
{ // * 
double loc_quotient;
if ( loc_b == 0 ) { loc_quotient = 0 ;}
else { loc_quotient = ((double) loc_a) / ((double) loc_b) ;}
return loc_quotient;
} // *

double quotientnonzero( int loc_a, int loc_b ) //
{ // *
double loc_quotient;
if ( loc_b == 0 ) { loc_quotient = 0 ;}
else { loc_quotient = ((double) loc_a) / ((double) loc_b) ;}
return loc_quotient;
} // *

double quotientnonzero( float loc_a, float loc_b ) //
{ // *
double loc_quotient;
if ( loc_b == 0 ) { loc_quotient = 0 ;}
else { loc_quotient = ((double) loc_a) / ((double) loc_b) ;}
return loc_quotient;
} // *

double quotientnonzero( unsigned int loc_a, double loc_b) //
{ // *
if (loc_b == 0) { return 0.0;}
// otherwise
return (  ((double) loc_a) / loc_b  );
} // *

double quotientnonzero( double loc_a, unsigned int loc_b ) //
{ // *
if ( loc_b == 0) { return 0 ;}
// otherwise
return ( loc_a / ((double) loc_b) );
} // *

// ***************************************************************************************
// ********************** AlexArrayU and functions thereof *******************************
// ***************************************************************************************

class AlexArrayU // an array of unsigned ints
{ //
unsigned int length; // number of terms in the array
unsigned int *array; // the array itself
bool sizeisset; // will be set to true when the size of the array has been set -- SizeIsSet
public:
void setsize( unsigned int);
void print( void ); // displays the array on the screen
void setvalue( unsigned int, unsigned int );  // sets a single value in the array
unsigned int size( void ); // outputs the size of the array
unsigned int getvalue( unsigned int ); // returns a single value of the array
void increment( unsigned int ); // increases a single value in the array by one
AlexArrayU( ); // creates an AllexArrayU of undefined length
AlexArrayU( unsigned int ); // creates an AlexArrayU of defined size
AlexArrayU( unsigned int, unsigned int); // creates an AlexArrayU of defined size, whose entries are all set to a certain value
bool sizeset( void ); // says whether or not the size of the array has been set
void setall(unsigned int); // sets all members of the array equal to the inputted value
vector<double> arraystats( void ); // calculates statistical values of all entries in array
vector<double> arraystats_nonzero( void ); // calculates statistical values of nonzero entries in array
bool nulltest( void ); // determines if the array is null -- returns true if the list is null
void onearray( void ); // turns the array into a onearray -- array[i] = i
void onearray( unsigned int ); // turns the array into a onearray -- array[i] = i + k
unsigned int sum( void ); // sums all terms in array
};


// *************************************** setsize ***************************************
void AlexArrayU::setsize( unsigned int newlength ) //
{ //
length = newlength;
array = new unsigned int [newlength];
} //

// *********************************** print *********************************************

void AlexArrayU::print( void )
{ 
cout << "{ ";
for (unsigned int it1 = 0; it1 < (length - 1); it1++)
	{ 
	cout << array[it1] << ", ";
	} 
cout << array[length - 1] << " }" << endl;
} 

// **************************************** setvalue *************************************

void AlexArrayU::setvalue( unsigned int location, unsigned int invalue ) //
{ // *
if ( location < length ) { array[location] = invalue; }
else { cout << "INVALID LOCATION -- INPUT LOCATION WAS " << location << ", BUT ARRAY ONLY HAS LENGTH " << length << endl; }
} // *

// ********************************** getvalue *******************************************

unsigned int AlexArrayU::getvalue( unsigned int location ) //
{ // *
if ( location < length ) { return array[location] ;}
else //
	{  //
	cout << "INVALID LOCATION -- INPUT LOCATION WAS " << location << ", BUT ARRAY ONLY HAS LENGTH " << length << endl; 
	return 0;
	} //
}  // *


// *********************************** size **********************************************

unsigned int AlexArrayU::size( void ) { return length ;}

// *********************************** increment *****************************************

void AlexArrayU::increment( unsigned int location1 ) //
{ // *
if (location1 < length) //
{ //
unsigned int blah = array[location1];
blah++ ;
array[location1] = blah;
} //
else { cout << "INVALID LOCATION -- INPUT LOCATION WAS " << location1 << ", BUT THE ARRAY ONLY HAS LENGTH " << length << endl; }
} // *

// ************************************* constructors ************************************

AlexArrayU::AlexArrayU( ) //
{ // *
sizeisset = false;
unsigned int length;
} // *


AlexArrayU::AlexArrayU( unsigned int length1 ) //
{ // *
length = length1;
array = new unsigned int [length1];
sizeisset = true;
} // *

AlexArrayU::AlexArrayU( unsigned int length1, unsigned int invalue ) //
{ // *
length = length1;
array = new unsigned int [length1];
for (unsigned int it1 = 0; it1 < length; it1++) { array[it1] = invalue ;}
sizeisset = true;
} // *

// *************************************** sizeset ***************************************
bool AlexArrayU::sizeset( void )
{
return sizeisset;
}

// ************************************ setall *******************************************

void AlexArrayU::setall( unsigned int local_invalue ) //
{ // *
for (unsigned int it1 = 0; it1 < length; it1++) // through all entries in array
	{ //
	array[it1] = local_invalue;
	} //
} // *

// ************************************* arraystats **************************************

vector<double> AlexArrayU::arraystats( void )
{
//
//
if ( length == 0 ) // do no calculations if the list is empty
	{
	cout << "THE ARRAY IS CURRENTLY EMPTY, AND THEREFORE HAS NO STATISTICAL VALUES; ALL ZEROS WILL BE RETURNED" << endl;
	vector<double> returnvector;
	for (unsigned int it1 = 0; it1 < 32; it1++) // will be longer than vectorstatslength
		{
		returnvector.push_back( 0.0 );
		}
	return returnvector;
	}
//
//
unsigned int sum = 0;
unsigned int sumsq = 0; // sum of squares 
unsigned int value;
double mean;
double meansq; // mean of squares
double sd; // standard deviation
unsigned int maxval = 0; // maximum value in the array
unsigned int minval = array[0]; // minimum value in the array
//
// find sum and sumsq
for (unsigned int it1 = 0; it1 < length; it1++)
	{
	value = array[it1];
	if (value != 0) // there's no point in taking the processing time to add zero to sum and sumsq
		{
		sum += value ;
		sumsq += value * value ;
		}
	if (maxval < value) {maxval = value ;}
	if (minval > value) {minval = value ;}
	}
//
//
// for mean, meansq, and sd
mean = (sum + 0.0) / (length);
meansq = (sumsq + 0.0) / (length);
sd = sqrt( meansq - mean * mean);
//
// prepare output vector
vector<double> outputarray;
outputarray.push_back( (double) sum );
outputarray.push_back( (double) sumsq );
outputarray.push_back( mean );
outputarray.push_back( meansq);
outputarray.push_back( sd );
outputarray.push_back( (double) minval );
outputarray.push_back( (double) maxval );
//
return outputarray;
}



// *************************************** arraystats_nonzero *****************************


vector<double> AlexArrayU::arraystats_nonzero( void )
{
//
//
if ( length == 0) // do no calculations if the list is empty
	{
	cout << "THE ARRAY IS CURRENTLY EMPTY, AND THEREFORE HAS NO STATISTICAL VALUES; ALL ZEROS WILL BE RETURNED" << endl;
	vector<double> returnvector;
	for (unsigned int it1 = 0; it1 < 32; it1++) // will be longer than arraystatslength_nonzero
		{
		returnvector.push_back( 0.0 );
		}
	return returnvector;
	}
//
//
unsigned int sum = 0;
unsigned int sumsq = 0; // sum of squares 
unsigned int value;
double mean;
double meansq; // mean of squares
double sd; // standard deviation
unsigned int maxval = 0; // maximum value in the array
unsigned int minval = array[0]; // minimum value in the array
unsigned int nonzeros = 0;
//
// find sum and sumsq
for (unsigned int it1 = 0; it1 < length; it1++)
	{
	value = array[it1];
	if (value != 0) 
		{
		sum += value ;
		sumsq += value * value ;
		if (maxval < value) {maxval = value ;}
		if (minval > value) {minval = value ;}
		nonzeros++ ;
		}
	}
//
//
// for mean, meansq, and sd
mean = quotientnonzero(sum, nonzeros);
meansq = quotientnonzero(sumsq, nonzeros);
sd = sqrt( meansq - mean * mean);
//
// prepare output vector
vector<double> outputarray;
outputarray.push_back( (double) sum );
outputarray.push_back( (double) sumsq );
outputarray.push_back( mean );
outputarray.push_back( meansq);
outputarray.push_back( sd );
outputarray.push_back( (double) minval );
outputarray.push_back( (double) maxval );
outputarray.push_back( (double) nonzeros );
//
return outputarray;
}

// ************************************ nulltest *****************************************

bool AlexArrayU::nulltest( void ) //
{ // *
if ( length == 0 ) //
	{ //
	cout << "THE LIST HAS LENGTH 0; OF COURSE IT'S NULL!" << endl;
	return true;
	} //
//
//
// loop through the array and see if the value are all zero
for (unsigned int it1 = 0; it1 < length; it1++) // through all entries of array
	{ //
	if ( array[it1] != 0) { return false; }
	} //
return true;
} // *

// ******************************** onearray *********************************************

void AlexArrayU::onearray( void ) //
{ // *
for (unsigned int it1 = 0; it1 < length; it1++) { array[it1] = it1 ;}
} // *

void AlexArrayU::onearray( unsigned int entry0 ) //
{ // *
for (unsigned int it1 = 0; it1 < length; it1++) { array[it1] = it1 + entry0 ;}
} // *

// ********************************** sum ***********************************************

unsigned int AlexArrayU::sum( void ) //
{ // *
unsigned int local_sum = 0;
// loop through array and sum together all entries therein
for (unsigned int it1 = 0; it1 < length; it1++) { local_sum += array[it1] ;}
return local_sum;
} // *

//****************************************************************************************
// ********************************* AlexArrayU_2D and functions thereof *****************
//****************************************************************************************

class AlexArrayU_2D // a 2D array of unsigned ints
{ //
unsigned int length1; // the array will have the dimensions [length1][length2]
unsigned int length2; 
bool sizeisset; // will be set to true when the size of the array has been set
AlexArrayU *array2D; // the 2D array itself
public:
void setsize( unsigned int, unsigned int ); // sets the size of array2D to [length1][length2]
void print( void ); // outputs to screen all of the values in array2D
unsigned int getvalue( unsigned int, unsigned int ); // returns a single value in array2D
void setvalue(unsigned int, unsigned int, unsigned int); // sets a single value of array2D
unsigned int size( void ); // returns the length1
vector<unsigned int> dimensions( void ); // returns a vector where the entries are <length1, length2>
vector<double> arraystats_nonzero( void ); // calculates statistical values of all entries in array2D
vector<double> arraystats_nonzero( unsigned int); // calculates statistical values of all nonzero entries within a single array in array2D
void increment( unsigned int, unsigned int); // increases a single value of array2D by 1
AlexArrayU_2D ();
AlexArrayU_2D ( unsigned int, unsigned int);
AlexArrayU_2D( unsigned int, unsigned int, unsigned int );
bool sizeset( void ); // returns sizeisset -- says whether or not the dimensions of the AlexArrayU_2D have been set
void setall( unsigned int); // sets all values in array2D to the inputted value
vector<double> arraystats( void ); // calculates statistical values of all entries in array2D
vector<double> arraystats( unsigned int ); // calculates statistical values of all entries within a single chosen array in array2D
AlexArrayU getarray( unsigned int); // returns a specific 1D array within array2D
bool nulltest( void ); // tests to see if the entire array2D is a null array; returns true if it's null
bool nulltest( unsigned int); // tests to see if array2D[i] is a null list; returns true if it is
unsigned int sum( void ); // sums together all entries in array2D
unsigned int sum( unsigned int); // sums together all entries in a specified 1D array
};

// ************************************* setsize ******************************************

void AlexArrayU_2D::setsize( unsigned int newlength1, unsigned int newlength2 ) // effectively creates unsigned int array2D[length1][length2]
{ 
sizeisset = true;
length1 = newlength1;
length2 = newlength2;
array2D = new AlexArrayU[newlength1];
for (unsigned int it1 = 0; it1 < length1; it1++)
	{
	array2D[it1].setsize( length2 );
	}
}

// ************************************* print *******************************************

void AlexArrayU_2D::print( void )
{
unsigned int loc_returnvalue;
cout << "{";
for (unsigned int it1 = 0; it1 < (length1 - 1); it1++)
	{
	cout << "{";
	for (unsigned int it2 = 0; it2 < (length2 - 1); it2++)
		{
		loc_returnvalue = array2D[it1].getvalue( it2 );
		cout << loc_returnvalue << ", ";
		}
	loc_returnvalue = array2D[it1].getvalue( length2 - 1);
	cout << loc_returnvalue << "}, "; 
	}
	cout << "{";
for (unsigned int it2 = 0; it2 < (length2 - 1); it2++)
	{
	loc_returnvalue = array2D[length1 - 1].getvalue( it2 );
	cout << loc_returnvalue << ", ";
	}
loc_returnvalue = array2D[length1 - 1].getvalue( length2 - 1);
cout << loc_returnvalue << "}, " << endl; 
}

unsigned int AlexArrayU_2D::getvalue( unsigned int location1, unsigned int location2 )
{
return array2D[location1].getvalue( location2 );
}

void AlexArrayU_2D::setvalue( unsigned int location1, unsigned int location2, unsigned int invalue )
{
if ( (location1 < length1)&&(location2 < length2) ) { array2D[location1].setvalue( location2, invalue ); }
else { cout << "INVALID LOCATION" << endl; }
}

// ******************************************* size **************************************

unsigned int AlexArrayU_2D::size( void )
{
return length1;
}

// ************************************** dimensions *************************************

vector<unsigned int> AlexArrayU_2D::dimensions( void )
{
vector<unsigned int> loc_outputvector;
loc_outputvector.push_back( length1 );
loc_outputvector.push_back( length2 );
return loc_outputvector;
}

// ************************************* arraystats_nonzero ******************************

vector<double> AlexArrayU_2D::arraystats_nonzero( void )
{
if ( (length1 == 0) || (length2 == 0) ) // do no calculations if the list is empty
	{
	cout << "THE ARRAY IS CURRENTLY EMPTY, AND THEREFORE HAS NO STATISTICAL VALUES; ALL ZEROS WILL BE RETURNED" << endl;
	vector<double> returnvector;
	for (unsigned int it1 = 0; it1 < 32; it1++) // will be longer than arraystatslength_nonzero
		{
		returnvector.push_back( 0.0 );
		}
	return returnvector;
	}
//	
//	
unsigned int sum = 0;
unsigned int sumsq = 0; // sum of squares 
unsigned int value;
double mean;
double meansq; // mean of squares
double sd; // standard deviation
unsigned int nonzeros = 0; // the number of nonzero entries in list1
unsigned int maxval = array2D[0].getvalue(0); // the maximum value in list1
unsigned int minval = 1073741824; // the minimum nonzero value in list1
//
// sum together all terms in the array
for (unsigned int it1 = 0; it1 < length1; it1++)
	{
	for (unsigned int it2 = 0; it2 < length2; it2++)
		{
		value = array2D[it1].getvalue(it2);
		if (value != 0)
			{
			sum += value;
			sumsq += value * value;
			nonzeros ++;
			if (maxval < value) {maxval = value ;}
			if (minval > value) {minval = value ;}
			}
		}
	}
//
//
mean = quotientnonzero(sum, nonzeros);
meansq = quotientnonzero(sumsq, nonzeros);
sd = sqrt( meansq - (mean * mean) );
//
//
vector<double> returnvector;
returnvector.push_back( (double) sum );
returnvector.push_back( (double) sumsq );
returnvector.push_back( mean );
returnvector.push_back( meansq );
returnvector.push_back( sd );
returnvector.push_back( (double) minval );
returnvector.push_back( (double) maxval );
returnvector.push_back( (double) nonzeros );
return returnvector;
}


vector<double> AlexArrayU_2D::arraystats_nonzero( unsigned int location1 ) { return array2D[location1].arraystats_nonzero() ;}

// ******************************************* increment *********************************

void AlexArrayU_2D::increment( unsigned int location1, unsigned int location2 )
{
unsigned int loc_invalue = array2D[location1].getvalue(location2);
array2D[location1].setvalue( location2, loc_invalue + 1);
}

// ************************************** sizeset ****************************************

bool AlexArrayU_2D::sizeset( void ) { return sizeisset ;}

// ********************************** constructors ***************************************

AlexArrayU_2D::AlexArrayU_2D() { sizeisset = false ;}


AlexArrayU_2D::AlexArrayU_2D( unsigned int newlength1, unsigned int newlength2 ) //
{ // *
sizeisset = true;
length1 = newlength1;
length2 = newlength2;
array2D = new AlexArrayU[length1];
for (unsigned int it1 = 0; it1 < length1; it1++) //
	{ //
	array2D[it1].setsize( length2 );
	} //
} // *

AlexArrayU_2D::AlexArrayU_2D( unsigned int newlength1, unsigned int newlength2, unsigned int invalue ) //
{ // *
length1 = newlength1;
length2 = newlength2;
array2D = new AlexArrayU[length1];
sizeisset = true;
for (unsigned int it1 = 0; it1 < length1; it1++) //
	{ // 
	array2D[it1].setsize( newlength2 );
	array2D[it1].setall( invalue );
	} //
} // *

// ************************************** setall *****************************************

void AlexArrayU_2D::setall( unsigned int local_invalue ) //
{ // *
for (unsigned int it1 = 0; it1 < length1; it1++) //
	{ //
	array2D[it1].setall( local_invalue );
	} //
} // *

// ************************************ arraystats ***************************************

vector<double> AlexArrayU_2D::arraystats( void )
{
//
//
if ( (length1 == 0) || (length2 == 0) ) // do no calculations if the list is empty
	{
	cout << "THE ARRAY IS CURRENTLY EMPTY, AND THEREFORE HAS NO STATISTICAL VALUES; ALL ZEROS WILL BE RETURNED" << endl;
	vector<double> returnvector;
	for (unsigned int it1 = 0; it1 < 32; it1++) 
		{
		returnvector.push_back( 0.0 );
		}
	return returnvector;
	}
//
//
unsigned int sum = 0;
unsigned int sumsq = 0; // sum of squares 
unsigned int value;
double mean;
double meansq; // mean of squares
double sd; // standard deviation
unsigned int maxval = 0; // maximum value in the array
unsigned int minval = array2D[0].getvalue(0); // minimum value in the array
//
// find sum and sumsq
for (unsigned int it1 = 0; it1 < length1; it1++)
	{
	for (unsigned int it2 = 0; it2 < length2; it2++)
		{
		value = array2D[it1].getvalue(it2);
		if (value != 0) // there's no point in taking the processing time to add zero to sum and sumsq
			{
			sum += value ;
			sumsq += value * value ;
			}
		if (maxval < value) {maxval = value ;}
		if (minval > value) {minval = value ;}
		}
	}
//
//
// for mean, meansq, and sd
mean = (sum + 0.0) / (length1 * length2);
meansq = (sumsq + 0.0) / (length1 * length2);
sd = sqrt( meansq - mean * mean);
//
// prepare output vector
vector<double> outputarray;
outputarray.push_back( (double) sum );
outputarray.push_back( (double) sumsq );
outputarray.push_back( mean );
outputarray.push_back( meansq);
outputarray.push_back( sd );
outputarray.push_back( (double) minval );
outputarray.push_back( (double) maxval );
//
return outputarray;
}

// *************************************** getarray **************************************

AlexArrayU AlexArrayU_2D::getarray( unsigned int location)
{
if (location < length1) { return array2D[ location ] ;}
//
//
else {
	cout << "INVALID LOCATION -- THE LOCATION " << location << " WAS ENTERED, BUT THE ARRAY ONLY HAS LENGTH " << length1 << endl;
	AlexArrayU nullarray(1);
	nullarray.setall(0);
	return nullarray;
	}
} 	



vector<double> AlexArrayU_2D::arraystats( unsigned int location1 ) { return array2D[location1].arraystats() ;}

// *********************************** nulltest ******************************************

bool AlexArrayU_2D::nulltest( void )
{ //
if ( (length1 == 0) || (length2 == 0) )
	{ //
	cout << "THE ARRAY HAS NO ENTRIES; OF COURSE IT'S A NULL ARRAY!" << endl;
	return true;
	}
//
//
// loop through array2D to see if all values are 0
for (unsigned int it1 = 0; it1 < length1; it1++)
	{ //
	for (unsigned int it2 = 0; it2 < length2; it2++)
		{ //
		if ( array2D[it1].getvalue( it2 ) != 0 ) { return false; }
		}
	}
return true;
}

bool AlexArrayU_2D::nulltest( unsigned int location1) { return array2D[location1].nulltest() ; }

// ************************************* sum *********************************************

unsigned int AlexArrayU_2D::sum(void) //
{ // *
double local_sum = 0;
// loop through array2D and sum the sums of the 1D arrays therein
for (unsigned int it1 = 0; it1 < length1; it1++) { local_sum += array2D[it1].sum(); }
return local_sum;
} // *

unsigned int AlexArrayU_2D::sum(unsigned int location1) { return array2D[location1].sum() ;}
			

// ***************************************************************************************
// *********************************** AlexArrayU_3D *************************************
// ***************************************************************************************

class AlexArrayU_3D // a 3D array of unsigned ints
{ //
unsigned int length1; // the array will have the dimensions [length1][length2][length3]
unsigned int length2;
unsigned int length3;
bool sizeisset; // will be set to true when the size of the array is set
AlexArrayU_2D *array3D; // the 3D array itself -- technically an array of 2D AlexArrayUs
public:
void setsize( unsigned int, unsigned int, unsigned int ); // sets the size of the AlexArrayU_3D
void print( void ); // outputs the array to the screen
unsigned int getvalue( unsigned int, unsigned int, unsigned int ); // returns a single value within the array
void setvalue( unsigned int, unsigned int, unsigned int, unsigned int ); // sets a single value within the array
unsigned int size( void ); // returns length1
vector<unsigned int> dimensions( void ); // returns a vector of form {length1, lengtht2, length3}
vector<double> arraystats_nonzero( void ); // calculates statistical value of nonzero the entries in the array
vector<double> arraystats_nonzero( unsigned int, unsigned int); // calculates statistical value of nonzero the entries within a 1D array in array3D
vector<double> arraystats_nonzero( unsigned int ); // calculates statistical value of nonzero the entries within a 2D array in array3D
void increment( unsigned int, unsigned int, unsigned int); // increases a certain value within the array by one
AlexArrayU_3D(); // creates an array whose size remains undefined
AlexArrayU_3D( unsigned int, unsigned int, unsigned int ); // creates an array of defines size
AlexArrayU_3D( unsigned int, unsigned int, unsigned int, unsigned int); // creates an array of defined size, whose entries are all set to a certain value ********************
bool sizeset( void ); // outputs sizeisset -- says whether or not the size of the array is set
void setall( unsigned int ); // sets all values within the array to a certain value
vector< double > arraystats( void ); // calculates statistical value of all the entries in the array
vector<double> arraystats( unsigned int, unsigned int); // calculates statistical value of the entries within a 1D array in array3D
vector<double> arraystats( unsigned int ); // calculates statistical value of the entries within a 2D array in array3D
AlexArrayU_2D getarray( unsigned int ); // returns a certain 2D array
AlexArrayU getarray( unsigned int, unsigned int); // returns a certain 1D array
bool nulltest( void ); // test to see if all entries in array3D are null; returns true if it's null
bool nulltest( unsigned int ); // test to see if array3D[i] is a null array; returns true if it's null
bool nulltest( unsigned int, unsigned int ); // test to see if array3D[i][j] is a null array; returns true if it is
unsigned int sum( void ); // sums all terms in array3D
unsigned int sum( unsigned int ); // sums together all terms in a specific 2D array within array3D
unsigned int sum( unsigned int, unsigned int); // sums togeather all entries in a 1D array within array3D
};


// *************************** AlexArrayU_3D constructors *********************************

AlexArrayU_3D::AlexArrayU_3D()
{ //
sizeisset = false; 
}


AlexArrayU_3D::AlexArrayU_3D( unsigned int newlength1, unsigned int newlength2, unsigned int newlength3 )
{ //
length1 = newlength1;
length2 = newlength2;
length3 = newlength3;
array3D = new AlexArrayU_2D[length1];
// set the size of every 2D array within array3D
for (unsigned int it1 = 0; it1 < length1; it1++) { array3D[it1].setsize( length2, length3 ); }
sizeisset = true;
}

AlexArrayU_3D::AlexArrayU_3D( unsigned int newlength1, unsigned int newlength2, unsigned int newlength3, unsigned int invalue )
{ //
length1 = newlength1;
length2 = newlength2;
length3 = newlength3;
array3D = new AlexArrayU_2D[length1];
// set the size of every 2D array within array3D
for (unsigned int it1 = 0; it1 < length1; it1++) 
	{ // 
	array3D[it1].setsize( length2, length3 ); 
	array3D[it1].setall( invalue );
	}
sizeisset = true;
}


// *********************************** setsize *******************************************

void AlexArrayU_3D::setsize( unsigned int newlength1, unsigned int newlength2, unsigned int newlength3 )
{ //
length1 = newlength1;
length2 = newlength2;
length3 = newlength3;
array3D = new AlexArrayU_2D[length1];
// set the size of every 2D array within array3D
for (unsigned int it1 = 0; it1 < length1; it1++) { array3D[it1].setsize( length2, length3 ); }
sizeisset = true;
}


// ******************************* increment *********************************************

void AlexArrayU_3D::increment( unsigned int location1, unsigned int location2, unsigned int location3 )
{ //
unsigned int local_value = array3D[location1].getvalue(location2,location3);
local_value++ ;
array3D[location1].setvalue(location2,location3,local_value);
}





// *********************************** getvalue *******************************************

unsigned int AlexArrayU_3D::getvalue( unsigned int location1, unsigned int location2, unsigned int location3 )
{ //
return array3D[location1].getvalue( location2, location3 );
}


// *********************************** setvalue *******************************************

void AlexArrayU_3D::setvalue( unsigned int location1, unsigned int location2, unsigned int location3, unsigned int invalue )
{ //
array3D[location1].setvalue( location2, location3, invalue );
}

// ************************************** size *******************************************

unsigned int AlexArrayU_3D::size( void )
{ //
return length1;
}


// *********************************** dimensions ****************************************

vector< unsigned int> AlexArrayU_3D::dimensions( void )
{ // 
vector<unsigned int> dimensionsvector;
dimensionsvector.push_back( length1 );
dimensionsvector.push_back( length2 );
dimensionsvector.push_back( length3 );
return dimensionsvector;
} 

// ************************************** sizeset ****************************************

bool AlexArrayU_3D::sizeset( void ) { return sizeisset; }

// *************************************** setall ****************************************

void AlexArrayU_3D::setall( unsigned int invalue )
{ //
for (unsigned int it1 = 0; it1 < length1; it1++) { array3D[it1].setall( invalue ) ;}
}

// ************************************* getarray ****************************************

AlexArrayU_2D AlexArrayU_3D::getarray( unsigned int location1 )
{ //
if (location1 < length1) { return array3D[length1] ;}

else { //
	cout << "INVALID LOCATION -- THE ARRAY ONLY HAS LENGTH " << length1 << ", BUT A LOCATION OF " << location1 << "WAS ENTERED; A ZERO ARRAY WILL BE RETURNED." << endl;
	AlexArrayU_2D zeroarray( 1,1,0);
	return zeroarray;
	}
}
	

AlexArrayU AlexArrayU_3D::getarray( unsigned int location1, unsigned int location2 )
{ //
if ( length1 > location1 )
	{ //
	AlexArrayU returnarray;
	returnarray = array3D[location1].getarray( location2 );
	return returnarray;
	}
else { //
	cout << "INVALID LOCATION -- THE ARRAY ONLY HAS LENGTH " << length1 << ", BUT A LOCATION OF " << location1 << "WAS ENTERED; A ZERO ARRAY WILL BE RETURNED." << endl;
	AlexArrayU zeroarray( 1,0 );
	return zeroarray;
	}
}


// ******************************** arraystats_nonzero ***********************************

vector<double> AlexArrayU_3D::arraystats_nonzero( void )
{ //
if ( (length1 == 0) || (length2 == 0) || (length3 == 0) ) // do no calculations if the list is empty
	{ //
	cout << "THE ARRAY IS CURRENTLY EMPTY, AND THEREFORE HAS NO STATISTICAL VALUES; ALL ZEROS WILL BE RETURNED" << endl;
	vector<double> returnvector;
	for (unsigned int it1 = 0; it1 < 32; it1++) // will be longer than arraystatslength_nonzero
		{
		returnvector.push_back( 0.0 );
		}
	return returnvector;
	}
//	
//	
unsigned int sum = 0;
unsigned int sumsq = 0; // sum of squares 
unsigned int value;
double mean;
double meansq; // mean of squares
double sd; // standard deviation
unsigned int nonzeros = 0; // the number of nonzero entries in list1
unsigned int maxval = array3D[0].getvalue(0,0); // the maximum value in list1
unsigned int minval = 1073741824; // the minimum nonzero value in list1
//
// sum together all terms in the array. also find minimum and maximum value
for (unsigned int it1 = 0; it1 < length1; it1++)
	{ //
	for (unsigned int it2 = 0; it2 < length2; it2++)
		{ //
		for (unsigned int it3 = 0; it3 < length3; it3++)
			{ //
			value = array3D[it1].getvalue(it2,it3);
			if (value != 0 ) // do no calculations if the value is equal to zero
				{ //
				sum += value;
				sumsq += value * value;
				nonzeros++ ;
				if (maxval < value) { maxval = value ;}
				if (minval > value) { minval = value ;}
				}
			}
		}
	}
//
//
mean = quotientnonzero( sum, nonzeros );
meansq = quotientnonzero( (double) sumsq,(double) nonzeros );
sd = sqrt( meansq - ( mean * mean ) );
//
// prepare output vector
vector<double> outputarray;
outputarray.push_back( (double) sum );
outputarray.push_back( (double) sumsq );
outputarray.push_back( mean );
outputarray.push_back( meansq);
outputarray.push_back( sd );
outputarray.push_back( (double) minval );
outputarray.push_back( (double) maxval );
outputarray.push_back( (double) nonzeros );
//
return outputarray;
}


vector<double> AlexArrayU_3D::arraystats_nonzero( unsigned int location1, unsigned int location2) { return array3D[location1].arraystats_nonzero(location2); }


vector<double> AlexArrayU_3D::arraystats_nonzero( unsigned int location1 ) { return array3D[location1].arraystats_nonzero() ;}

// ********************************** arraystats *****************************************

vector<double> AlexArrayU_3D::arraystats( void )
{ //
if ( (length1 == 0) || (length2 == 0) || (length3 == 0) ) // do no calculations if the list is empty
	{ //
	cout << "THE ARRAY IS CURRENTLY EMPTY, AND THEREFORE HAS NO STATISTICAL VALUES; ALL ZEROS WILL BE RETURNED" << endl;
	vector<double> returnvector;
	for (unsigned int it1 = 0; it1 < 32; it1++) // will be longer than arraystatslength_nonzero
		{
		returnvector.push_back( 0.0 );
		}
	return returnvector;
	}
//	
//	
unsigned int sum = 0;
unsigned int sumsq = 0; // sum of squares 
unsigned int value;
double mean;
double meansq; // mean of squares
double sd; // standard deviation
unsigned int nonzeros = 0; // the number of nonzero entries in list1
unsigned int maxval = array3D[0].getvalue(0,0); // the maximum value in list1
unsigned int minval = 1073741824; // the minimum nonzero value in list1
unsigned int arrayentries = length1 * length2 * length3;
//
//
// sum together entries in list. also find minimum and maximum value
for (unsigned int it1 = 0; it1 < length1; it1++)
	{ //
	for (unsigned int it2 = 0; it2 < length2; it2++)
		{ //
		for (unsigned int it3 = 0; it3 < length3; it3++)
			{ //
			value = array3D[it1].getvalue( it2, it3 );
			if (value < minval) { minval = value ;}
			if (value != 0) // there's no point in doing the following calculations for a null entry
				{ //
				sum += value;
				sumsq += value * value;
				if ( value > maxval ) { maxval = value ;}
				}
			}
		}
	}
//
//
mean = quotientnonzero( sum, arrayentries );
meansq = quotientnonzero( sumsq, arrayentries );
sd = sqrt( meansq - ( mean * mean ));
//
//
// prepare outputarray
vector<double> outputarray;
outputarray.push_back( (double) sum );
outputarray.push_back( (double) sumsq );
outputarray.push_back( mean );
outputarray.push_back( meansq);
outputarray.push_back( sd );
outputarray.push_back( (double) minval );
outputarray.push_back( (double) maxval );
//
return outputarray;
}

vector<double> AlexArrayU_3D::arraystats( unsigned int location1, unsigned int location2 ) { return array3D[location1].arraystats( location2 ); }

vector<double> AlexArrayU_3D::arraystats( unsigned int location1 ) { return array3D[location1].arraystats( ); }

// ********************************** print **********************************************

void AlexArrayU_3D::print( void )
{ //
if ( (length1 == 0) || (length2 == 0) || (length3 == 0) )
	{ //
	cout << "THIS ARRAY HAS NO ENTRIES; IT IS A NULL LIST" << endl;
	}
//
//
//
//
else { //
	cout << "{";
	for (unsigned int it1 = 0; it1 < length1; it1++)
		{ //
		cout << "{";
		for (unsigned int it2 = 0; it2 < length2; it2++)
			{ //
			cout << "{";
			for (unsigned int it3 = 0; it3 < length3; it3++)
				{ //
				cout << array3D[it1].getvalue( it2, it3 );
				if (it3 == length3 - 1) { cout << "}" ;}
				else {cout << ", " ;}
				}
			if (it2 == length2 - 1) { cout << "}" ;}
			else {cout << ", " ;}
			}
		if (it1 == length1 - 1) { cout << "}" << endl; }
		else { cout << ", " ;}
		}
	}
}
	
	
// ********************************** nulltest *******************************************

bool AlexArrayU_3D::nulltest( void )
{ //
if ( ( length1 == 0 ) || (length2 == 0) || (length3 == 0) )
	{ //
	cout << "THIS ARRAY HAS NO ENTRIES; OF COURSE IT'S NULL!" << endl;
	return true;
	}
//
//
// loop through array3D to see if all values are 0
for (unsigned int it1 = 0; it1 < length1; it1++)
	{ //
	for (unsigned int it2 = 0; it2 < length2; it2++)
		{ //
		for (unsigned int it3 = 0; it3 < length3; it3++)
			{ //
			if ( array3D[it1].getvalue( it2, it3 ) != 0) { return false; }
			}
		}
	}
// if no nonzero entries have been found, return true, because the list must then be null
return true;
}


bool AlexArrayU_3D::nulltest( unsigned int location1 ) { return array3D[location1].nulltest() ; }


bool AlexArrayU_3D::nulltest( unsigned int location1, unsigned int location2 ) { return array3D[location1].nulltest( location2 ) ; }

// ******************************** sum **************************************************

unsigned int AlexArrayU_3D::sum( void ) //
{ // *
unsigned int local_sum = 0;
// loop through array3D and sum the sums of the 2D arrays therein
for (unsigned int it1 = 0; it1 < length1; it1++) { local_sum += array3D[it1].sum() ;}
return local_sum;
} // *

unsigned int AlexArrayU_3D::sum( unsigned int location1 ) { return array3D[location1].sum(); }

unsigned int AlexArrayU_3D::sum( unsigned int location1, unsigned int location2 ) { return array3D[location1].sum(location2) ;}


// ***************************************************************************************
// ********************** AlexArrayD and functions thereof ******************************
// ***************************************************************************************


class AlexArrayD // an array of doubles
{ //
unsigned int length; // number of terms in the array
double *array; // the array itself
bool sizeisset; // will be set to true when the size of the array has been set -- SizeIsSet
public:
void setsize( unsigned int);
void print( void ); // displays the array on the screen
void setvalue( unsigned int, double );  // sets a single value in the array
unsigned int size( void ); // outputs the size of the array
double getvalue( unsigned int ); // returns a single value of the array
void increment( unsigned int ); // increases a single value in the array by one
void increment( unsigned int, double ); // increases a single value in the array by the inputted amount
AlexArrayD( ); // creates an AllexArrayD of undefined length
AlexArrayD( unsigned int ); // creates an AlexArrayD of defined size
AlexArrayD( unsigned int, double); // creates an AlexArrayD of defined size, whose entries are all a certain value
bool sizeset( void ); // says whether or not the size of the array has been set
void setall(double); // sets all members of the array equal to the inputted value
vector<double> arraystats( void ); // calculates statistical values of all entries in array
vector<double> arraystats_nonzero( void ); // calculates statistical values of nonzero entries in array
bool nulltest( void ); // returns True if all member in the array are 0
void onearray( void ); // makes the array a onearray -- array[i] = i
void onearray( double ); // makes the array a onearray -- array[i] = i + k
void onearray(unsigned int ); // makes the array a onearray -- array[i] = i + k
double sum( void ); // sums together all terms in array
};

// *********************************** setsize *******************************************

void AlexArrayD::setsize( unsigned int newlength )
{ 
length = newlength;
array = new double[newlength];
} 

// ************************************* print *******************************************

void AlexArrayD::print( void )
{ 
cout << "{ ";
for (unsigned int it1 = 0; it1 < (length - 1); it1++)
	{ 
	cout << array[it1] << ", ";
	} 
cout << array[length - 1] << " }" << endl;
} 

// ***************************************** setvalue ************************************

void AlexArrayD::setvalue( unsigned int location, double invalue )
{ 
if ( location < length ) { array[location] = invalue; }
else { cout << "INVALID LOCATION -- INPUT LOCATION WAS " << location << ", BUT ARRAY ONLY HAS LENGTH " << length << endl; }
} 

// ************************************** getvalue ***************************************

double AlexArrayD::getvalue( unsigned int location )
{ 
if ( location < length ) { return array[location] ;}
else 
	{ 
	cout << "INVALID LOCATION -- INPUT LOCATION WAS " << location << ", BUT ARRAY ONLY HAS LENGTH " << length << endl; 
	return 0;
	} 
} 

// ****************************************** size ***************************************

unsigned int AlexArrayD::size( void )
{ 
return length;
} 

// ************************************ increment ****************************************

void AlexArrayD::increment( unsigned int location1 )
{
if (location1 < length) {array[location1]++ ;}
else { cout << "INVALID LOCATION -- INPUT LOCATION WAS " << location1 << ", BUT THE ARRAY ONLY HAS LENGTH " << length << endl; }
} 

void AlexArrayD::increment( unsigned int location1, double invalue ) { array[location1] += invalue ;}

// ******************************************* constructors ******************************

AlexArrayD::AlexArrayD( ) { sizeisset = false ;}


AlexArrayD::AlexArrayD( unsigned int length1 ) //
{ // *
length = length1;
array = new double[length1];
sizeisset = true;
} // *

bool AlexArrayD::sizeset( void )
{
return sizeisset;
}

AlexArrayD::AlexArrayD( unsigned int length1, double invalue ) //
{ // *
length = length1;
array = new double[length1];
sizeisset = true;
for (unsigned int it1 = 0; it1 < length1; it1++) { array[it1] = invalue ;}
} // *

// ********************************* setall **********************************************

void AlexArrayD::setall( double local_invalue )
{
for (unsigned int it1 = 0; it1 < length; it1++)
	{
	array[it1] = local_invalue;
	}
}

// ******************************************** arraystats *******************************

vector<double> AlexArrayD::arraystats( void )
{
//
//
if ( length == 0 ) // do no calculations if the list is empty
	{
	cout << "THE ARRAY IS CURRENTLY EMPTY, AND THEREFORE HAS NO STATISTICAL VALUES; ALL ZEROS WILL BE RETURNED" << endl;
	vector<double> returnvector;
	for (unsigned int it1 = 0; it1 < 32; it1++) // will be longer than arraystatslength_nonzero
		{
		returnvector.push_back( 0.0 );
		}
	return returnvector;
	}
//
//
double sum = 0;
double sumsq = 0; // sum of squares 
double value;
double mean;
double meansq; // mean of squares
double sd; // standard deviation
double maxval = 0; // maximum value in the array
double minval = array[0]; // minimum value in the array
//
// find sum and sumsq
for (unsigned int it1 = 0; it1 < length; it1++)
	{
	value = array[it1];
	if (value != 0) // there's no point in taking the processing time to add zero to sum and sumsq
		{
		sum += value ;
		sumsq += value * value ;
		}
	if (maxval < value) {maxval = value ;}
	if (minval > value) {minval = value ;}
	}
//
//
// for mean, meansq, and sd
mean = (sum + 0.0) / (length);
meansq = (sumsq + 0.0) / (length);
sd = sqrt( meansq - mean * mean);
//
// prepare output vector
vector<double> outputarray;
outputarray.push_back( sum );
outputarray.push_back( sumsq );
outputarray.push_back( mean );
outputarray.push_back( meansq );
outputarray.push_back( sd );
outputarray.push_back( minval );
outputarray.push_back( maxval );
//
return outputarray;
}

// ********************************* arraystats_nonzero **********************************

vector<double> AlexArrayD::arraystats_nonzero( void )
{
//
//
if ( length == 0) // do no calculations if the list is empty
	{
	cout << "THE ARRAY IS CURRENTLY EMPTY, AND THEREFORE HAS NO STATISTICAL VALUES; ALL ZEROS WILL BE RETURNED" << endl;
	vector<double> returnvector;
	for (unsigned int it1 = 0; it1 < 32; it1++) // will be longer than arraystatslength_nonzero
		{
		returnvector.push_back( 0.0 );
		}
	return returnvector;
	}
//
//
double sum = 0;
double sumsq = 0; // sum of squares 
double value;
double mean;
double meansq; // mean of squares
double sd; // standard deviation
double maxval = 0; // maximum value in the array
double minval = array[0]; // minimum value in the array
unsigned int nonzeros = 0;
//
// find sum and sumsq
for (unsigned int it1 = 0; it1 < length; it1++)
	{
	value = array[it1];
	if (value != 0) 
		{
		sum += value ;
		sumsq += value * value ;
		if (maxval < value) {maxval = value ;}
		if (minval > value) {minval = value ;}
		nonzeros++ ;
		}
	}
//
//
// for mean, meansq, and sd
mean = quotientnonzero(sum, (double)nonzeros);
meansq = quotientnonzero(sumsq, (double)nonzeros);
sd = sqrt( meansq - mean * mean);
//
// prepare output vector
vector<double> outputarray;
outputarray.push_back( sum );
outputarray.push_back( sumsq );
outputarray.push_back( mean );
outputarray.push_back( meansq);
outputarray.push_back( sd );
outputarray.push_back( minval );
outputarray.push_back( maxval );
outputarray.push_back( (double) nonzeros );
//
return outputarray;
}

// ******************************* nulltest **********************************************

bool AlexArrayD::nulltest( void )
{ //
if (length == 0) // don't run through any calculations if there aren't any members in the list
	{ //
	cout << "ALEXARRAYD::NULLTEST" << endl;
	cout << "THE LENGTH OF THE ARRAY IS ZERO; OF COURSE IT'S NULL!!!" << endl;
	return true;
	}
//
//
for (unsigned int it1 = 0; it1 < length; it1++) // loop through array to see if all entries are zero
	{ //
	if ( array[it1] != 0 ) { return false ;}
	}
// if no nonzero values were found, the array must be null
return true;
}

// ********************************* onearray ********************************************

void AlexArrayD::onearray( void ) //
{ // *
for (unsigned int it1 = 0; it1 < length; it1++) { array[it1] = (double) it1 ;}
} // *

void AlexArrayD::onearray( unsigned int entry0 ) //
{ // *
for (unsigned int it1 = 0; it1 < length; it1++) { array[it1] = (double)(it1 + entry0) ;}
} // *

void AlexArrayD::onearray( double entry0 ) //
{ // *
for (unsigned int it1 = 0; it1 < length; it1++) { array[it1] = ((double) it1) + entry0 ;}
} // *

// ******************************* sum ***************************************************

double AlexArrayD::sum( void ) //
{ // *
double local_sum = 0;
// loop through array and sum together all entries therein
for (unsigned int it1 = 0; it1 < length; it1++) { local_sum += array[it1] ;}
return local_sum;
} // * 

// ***************************************************************************************
// ********************************* AlexArrayD_2D and functions thereof *****************
// ***************************************************************************************

class AlexArrayD_2D // a 2D array of doubles
{ //
unsigned int length1; // the array will have the dimensions [length1][length2]
unsigned int length2; 
bool sizeisset; // will be set to true when the size of the array has been set
AlexArrayD *array2D; // the 2D array itself
public:
void setsize( unsigned int, unsigned int ); // sets the size of array2D to [length1][length2]
void print( void ); // outputs to screen all of the values in array2D
double getvalue( unsigned int, unsigned int ); // returns a single value in array2D
void setvalue(unsigned int, unsigned int, double); // sets a single value of array2D
unsigned int size( void ); // returns the length1
vector<unsigned int> dimensions( void ); // returns a vector where the entries are <length1, length2>
vector<double> arraystats_nonzero( void ); // calculates statistical values of all entries in array2D
void increment( unsigned int, unsigned int); // increases a single value of array2D by 1
AlexArrayD_2D (); // creates an AlexArrayD_2D of undefined size
AlexArrayD_2D ( unsigned int, unsigned int); // creates an AlexArrayD_2D of defined size
AlexArrayD_2D ( unsigned int, unsigned int, double ); // creates an AlexArrayD_2D of defined size, whose entries are all a certain number
bool sizeset( void ); // returns sizeisset -- says whether or not the dimensions of the AlexArrayU_2D have been set
void setall( double ); // sets all values in array2D to the inputted value
vector<double> arraystats( void ); // calculates statistical values of all entries in array2D
AlexArrayD getarray( unsigned int); // returns a specific AlexArrayD within Array2D
bool nulltest( void ); // returns true if all entries are zero
bool nulltest( unsigned int); // returns true if all entries within a certain 1D array are zero
};

// ***************************************** setsize *************************************

void AlexArrayD_2D::setsize( unsigned int newlength1, unsigned int newlength2 ) // effectively creates unsigned int array2D[length1][length2]
{ // *
sizeisset = true;
length1 = newlength1;
length2 = newlength2;
array2D = new AlexArrayD[newlength1];
for (unsigned int it1 = 0; it1 < length1; it1++) //
	{ //
	AlexArrayD AlexArrayModel (length2);
	array2D[it1] = AlexArrayModel;
	} //
} // *

// ****************************** print **************************************************

void AlexArrayD_2D::print( void )
{
double loc_returnvalue;
cout << "{";
for (unsigned int it1 = 0; it1 < (length1 - 1); it1++)
	{
	cout << "{";
	for (unsigned int it2 = 0; it2 < (length2 - 1); it2++)
		{
		loc_returnvalue = array2D[it1].getvalue( it2 );
		cout << loc_returnvalue << ", ";
		}
	loc_returnvalue = array2D[it1].getvalue( length2 - 1);
	cout << loc_returnvalue << "}, "; 
	}
	cout << "{";
for (unsigned int it2 = 0; it2 < (length2 - 1); it2++)
	{
	loc_returnvalue = array2D[length1 - 1].getvalue( it2 );
	cout << loc_returnvalue << ", ";
	}
loc_returnvalue = array2D[length1 - 1].getvalue( length2 - 1);
cout << loc_returnvalue << "}, " << endl; 
}

// *********************************** getvalue ******************************************

double AlexArrayD_2D::getvalue( unsigned int location1, unsigned int location2 ) //
{ // *
return array2D[location1].getvalue( location2 );
} // *

// ********************************** setvalue *******************************************

void AlexArrayD_2D::setvalue( unsigned int location1, unsigned int location2, double invalue ) //
{ // *
if ( (location1 < length1)&&(location2 < length2) ) { array2D[location1].setvalue( location2, invalue ); }
else { cout << "INVALID LOCATION" << endl; }
} // *

// ******************************** size *************************************************

unsigned int AlexArrayD_2D::size( void )
{
return length1;
}

// ****************************************** dimensions *********************************

vector<unsigned int> AlexArrayD_2D::dimensions( void )
{
vector<unsigned int> loc_outputvector;
loc_outputvector.push_back( length1 );
loc_outputvector.push_back( length2 );
return loc_outputvector;
}

// ***************************** arraystats_nonzero **************************************

vector<double> AlexArrayD_2D::arraystats_nonzero( void )
{
if ( (length1 == 0) || (length2 == 0) ) // do no calculations if the list is empty
	{
	cout << "THE ARRAY IS CURRENTLY EMPTY, AND THEREFORE HAS NO STATISTICAL VALUES; ALL ZEROS WILL BE RETURNED" << endl;
	vector<double> returnvector;
	for (unsigned int it1 = 0; it1 < 32; it1++) // will be longer than arraystatslength_nonzero
		{
		returnvector.push_back( 0.0 );
		}
	return returnvector;
	}
	
	
double sum = 0;
double sumsq = 0; // sum of squares 
double value;
double mean;
double meansq; // mean of squares
double sd; // standard deviation
unsigned int nonzeros = 0; // the number of nonzero entries in list1
double maxval = array2D[0].getvalue(0); // the maximum value in list1
double minval = 1073741824; // the minimum nonzero value in list1
//
// sum together all terms in the array
for (unsigned int it1 = 0; it1 < length1; it1++)
	{
	for (unsigned int it2 = 0; it2 < length2; it2++)
		{
		value = array2D[it1].getvalue(it2);
		if (value != 0)
			{
			sum += value;
			sumsq += value * value;
			nonzeros ++;
			if (maxval < value) {maxval = value ;}
			if (minval > value) {minval = value ;}
			}
		}
	}
//
//
mean = quotientnonzero(sum, (double)nonzeros);
meansq = quotientnonzero(sumsq, (double)nonzeros);
sd = sqrt( meansq - (mean * mean) );
//
//
vector<double> returnvector;
returnvector.push_back( (double) sum );
returnvector.push_back( (double) sumsq );
returnvector.push_back( mean );
returnvector.push_back( meansq );
returnvector.push_back( sd );
returnvector.push_back( (double) minval );
returnvector.push_back( (double) maxval );
returnvector.push_back( (double) nonzeros );
return returnvector;
}

// *********************************** increment *****************************************

void AlexArrayD_2D::increment( unsigned int location1, unsigned int location2 ) //
{ // *
double loc_invalue = array2D[location1].getvalue(location2);
array2D[location1].setvalue( location2, loc_invalue + 1);
} // *

// ******************************** sizeisset ********************************************

bool AlexArrayD_2D::sizeset( void ) { return sizeisset ;}

// ************************************* constructors ************************************

AlexArrayD_2D::AlexArrayD_2D()  {sizeisset = false ;}

AlexArrayD_2D::AlexArrayD_2D( unsigned int newlength1, unsigned int newlength2 ) //
{ // *
sizeisset = true;
length1 = newlength1;
length2 = newlength2;
array2D = new AlexArrayD[length1];
for (unsigned int it1 = 0; it1 < length1; it1++) //
	{ //
	array2D[it1].setsize( length2 );
	} //
} // *

AlexArrayD_2D::AlexArrayD_2D( unsigned int newlength1, unsigned int newlength2, double invalue )
{ // *
sizeisset = true;
length1 = newlength1;
length2 = newlength2;
array2D = new AlexArrayD[length1];
for (unsigned int it1 = 0; it1 < length1; it1++) //
	{ //
	array2D[it1].setsize( length2 );
	array2D[it1].setall( invalue );
	} //
} // *

// ********************************** setall *********************************************


void AlexArrayD_2D::setall( double local_invalue )
{
for (unsigned int it1 = 0; it1 < length1; it1++)
	{
	array2D[it1].setall( local_invalue );
	}
}

// ***************************************** arraystats **********************************

vector<double> AlexArrayD_2D::arraystats( void )
{
//
//
if ( (length1 == 0) || (length2 == 0) ) // do no calculations if the list is empty
	{
	cout << "THE ARRAY IS CURRENTLY EMPTY, AND THEREFORE HAS NO STATISTICAL VALUES; ALL ZEROS WILL BE RETURNED" << endl;
	vector<double> returnvector;
	for (unsigned int it1 = 0; it1 < 32; it1++) // will be longer than arraystatslength_nonzero
		{
		returnvector.push_back( 0.0 );
		}
	return returnvector;
	}
//
//
double sum = 0;
double sumsq = 0; // sum of squares 
double value;
double mean;
double meansq; // mean of squares
double sd; // standard deviation
double maxval = 0; // maximum value in the array
double minval = array2D[0].getvalue(0); // minimum value in the array
//
// find sum and sumsq
for (unsigned int it1 = 0; it1 < length1; it1++)
	{
	for (unsigned int it2 = 0; it2 < length2; it2++)
		{
		value = array2D[it1].getvalue(it2);
		if (value != 0) // there's no point in taking the processing time to add zero to sum and sumsq
			{
			sum += value ;
			sumsq += (value * value) ;
			}
		if (maxval < value) {maxval = value ;}
		if (minval > value) {minval = value ;}
		}
	}
//
//
// for mean, meansq, and sd
mean = (sum + 0.0) / (length1 * length2);
meansq = (sumsq + 0.0) / (length1 * length2);
sd = sqrt( meansq - mean * mean);
//
// prepare output vector
vector<double> outputarray;
outputarray.push_back( sum );
outputarray.push_back( sumsq );
outputarray.push_back( mean );
outputarray.push_back( meansq);
outputarray.push_back( sd );
outputarray.push_back( minval );
outputarray.push_back( maxval );
//
return outputarray;
}

AlexArrayD AlexArrayD_2D::getarray( unsigned int location)
{
if (location < length1) { return array2D[ location ] ;}
//
//
else {
	cout << "INVALID LOCATION -- THE LOCATION " << location << " WAS ENTERED, BUT THE ARRAY ONLY HAS LENGTH " << length1 << endl;
	AlexArrayD nullarray(1);
	nullarray.setall(0);
	return nullarray;
	}
}

// ********************************** nulltest *******************************************

bool AlexArrayD_2D::nulltest(void)
{ // 
if ( (length1 == 0) || (length2 == 0) ) // do no calculations if there are no entries
	{ //
	cout << "ALEXARRAYD_2D::NULLTEST" << endl;
	cout << "THERE ARE NO ENTRIES IN THE LIST; OF COURSE ITS NULL!!!" << endl;
	return true;
	}
//
// loop through the list to see if there are any nonzero values
for (unsigned int it1 = 0; it1 < length1; it1++)
	{ //
	if ( ~( array2D[it1].nulltest() ) ) { return false; }
	}
// if no nonzero entries are found in the loop, the list must be null
return true;
}

bool AlexArrayD_2D::nulltest( unsigned int location1) { return array2D[location1].nulltest() ;}

// ***************************************************************************************
// *********************************** AlexArrayD_3D *************************************
// ***************************************************************************************

class AlexArrayD_3D // a 3D array of doubles
{ //
unsigned int length1; // the array will have the dimensions [length1][length2][length3]
unsigned int length2;
unsigned int length3;
bool sizeisset; // will be set to true when the size of the array is set
AlexArrayU_2D *array3D; // the 3D array itself -- technically an array of 2D AlexArrayUs
public:
void setsize( unsigned int, unsigned int, unsigned int ); // sets the size of the AlexArrayU_3D
void print( void ); // outputs the array to the screen
double getvalue( unsigned int, unsigned int, unsigned int ); // returns a single value within the array
void setvalue( unsigned int, unsigned int, unsigned int, double ); // sets a single value within the array
unsigned int size( void ); // returns length1
vector<unsigned int> dimensions( void ); // returns a vector of form {length1, lengtht2, length3}
vector<double> arraystats_nonzero( void ); // calculates statistical value of nonzero the entries in the array
vector<double> arraystats_nonzero( unsigned int, unsigned int); // calculates statistical value of nonzero the entries within a 1D array in array3D
vector<double> arraystats_nonzero( unsigned int ); // calculates statistical value of nonzero the entries within a 2D array in array3D
void increment( unsigned int, unsigned int, unsigned int); // increases a certain value within the array by one
AlexArrayU_3D(); // creates an array whose size remains undefined
AlexArrayU_3D( unsigned int, unsigned int, unsigned int ); // creates an array of defines size
AlexArrayU_3D( unsigned int, unsigned int, unsigned int, double); // creates an array of defined size, whose entries are all set to a certain value ********************
bool sizeset( void ); // outputs sizeisset -- says whether or not the size of the array is set
void setall( double ); // sets all values within the array to a certain value
vector< double > arraystats( void ); // calculates statistical value of all the entries in the array
vector<double> arraystats( unsigned int, unsigned int); // calculates statistical value of the entries within a 1D array in array3D
vector<double> arraystats( unsigned int ); // calculates statistical value of the entries within a 2D array in array3D
AlexArrayD_2D getarray( unsigned int ); // returns a certain 2D array
AlexArrayD getarray( unsigned int, unsigned int); // returns a certain 1D array
bool nulltest( void ); // test to see if all entries in array3D are null; returns true if it's null
bool nulltest( unsigned int ); // test to see if array3D[i] is a null array; returns true if it's null
bool nulltest( unsigned int, unsigned int ); // test to see if array3D[i][j] is a null array; returns true if it is
};


// *************************** AlexArrayU_3D constructors *********************************

AlexArrayD_3D::AlexArrayD_3D()
{ //
sizeisset = false; 
AlexArrayD_2D *array3D;
}


AlexArrayD_3D::AlexArrayD_3D( unsigned int newlength1, unsigned int newlength2, unsigned int newlength3 )
{ //
length1 = newlength1;
length2 = newlength2;
length3 = newlength3;
array3D = new AlexArrayD_2D[length1];
// set the size of every 2D array within array3D
for (unsigned int it1 = 0; it1 < length1; it1++) { array3D[it1].setsize( length2, length3 ); }
sizeisset = true;
}

AlexArrayU_3D::AlexArrayD_3D( unsigned int newlength1, unsigned int newlength2, unsigned int newlength3, unsigned int invalue )
{ //
length1 = newlength1;
length2 = newlength2;
length3 = newlength3;
array3D = new AlexArrayD_2D[length1];
// set the size of every 2D array within array3D
for (unsigned int it1 = 0; it1 < length1; it1++) 
	{ // 
	array3D[it1].setsize( length2, length3 ); 
	array3D[it1].setall( invalue );
	}
sizeisset = true;
}


// *********************************** setsize *******************************************

void AlexArrayD_3D::setsize( unsigned int newlength1, unsigned int newlength2, unsigned int newlength3 )
{ //
length1 = newlength1;
length2 = newlength2;
length3 = newlength3;
array3D = new AlexArrayD_2D[length1];
// set the size of every 2D array within array3D
for (unsigned int it1 = 0; it1 < length1; it1++) { array3D[it1].setsize( length2, length3 ); }
sizeisset = true;
}


// ******************************* increment *********************************************

void AlexArrayD_3D::increment( unsigned int location1, unsigned int location2, unsigned int location3 )
{ //
double local_value = array3D[location1].getvalue(location2,location3);
local_value++ ;
array3D[location1].setvalue(location2,location3,local_value);
}





// *********************************** getvalue *******************************************

unsigned int AlexArrayD_3D::getvalue( unsigned int location1, unsigned int location2, unsigned int location3 )
{ //
return array3D[location1].getvalue( location2, location3 );
}


// *********************************** setvalue *******************************************

void AlexArrayD_3D::setvalue( unsigned int location1, unsigned int location2, unsigned int location3, double invalue )
{ //
array3D[location1].setvalue( location2, location3, invalue );
}

// ************************************** size *******************************************

unsigned int AlexArrayD_3D::size( void )
{ //
return length1;
}


// *********************************** dimensions ****************************************

vector< unsigned int> AlexArrayD_3D::dimensions( void )
{ // 
vector<unsigned int> dimensionsvector;
dimensionsvector.push_back( length1 );
dimensionsvector.push_back( length2 );
dimensionsvector.push_back( length3 );
return dimensionsvector;
} 

// ************************************** sizeset ****************************************

bool AlexArrayD_3D::sizeset( void ) { return sizeisset; }

// *************************************** setall ****************************************

void AlexArrayD_3D::setall( double invalue )
{ //
for (unsigned int it1 = 0; it1 < length1; it1++) { array3D[it1].setall( invalue ) ;}
}

// ************************************* getarray ****************************************

AlexArrayD_2D AlexArrayD_3D::getarray( unsigned int location1 )
{ //
if (location1 < length1) { return array3D[length1] ;}

else { //
	cout << "INVALID LOCATION -- THE ARRAY ONLY HAS LENGTH " << length1 << ", BUT A LOCATION OF " << location1 << "WAS ENTERED; A ZERO ARRAY WILL BE RETURNED." << endl;
	AlexArrayD_2D zeroarray( 1,1,0);
	return zeroarray;
	}
}
	

AlexArrayD AlexArrayD_3D::getarray( unsigned int location1, unsigned int location2 )
{ //
if ( length1 > location1 )
	{ //
	AlexArrayD returnarray;
	returnarray = array3D[location1].getarray( location2 );
	return returnarray;
	}
else { //
	cout << "INVALID LOCATION -- THE ARRAY ONLY HAS LENGTH " << length1 << ", BUT A LOCATION OF " << location1 << "WAS ENTERED; A ZERO ARRAY WILL BE RETURNED." << endl;
	AlexArrayU zeroarray( 1,0 );
	return zeroarray;
	}
}


// ******************************** arraystats_nonzero ***********************************

vector<double> AlexArrayD_3D::arraystats_nonzero( void )
{ //
if ( (length1 == 0) || (length2 == 0) || (length3 == 0) ) // do no calculations if the list is empty
	{ //
	cout << "THE ARRAY IS CURRENTLY EMPTY, AND THEREFORE HAS NO STATISTICAL VALUES; ALL ZEROS WILL BE RETURNED" << endl;
	vector<double> returnvector;
	for (unsigned int it1 = 0; it1 < 32; it1++) // will be longer than arraystatslength_nonzero
		{
		returnvector.push_back( 0.0 );
		}
	return returnvector;
	}
//	
//	
double sum = 0;
double sumsq = 0; // sum of squares 
double value;
double mean;
double meansq; // mean of squares
double sd; // standard deviation
unsigned int nonzeros = 0; // the number of nonzero entries in list1
double maxval = array3D[0].getvalue(0,0); // the maximum value in list1
double minval = 1073741824; // the minimum nonzero value in list1
//
// sum together all terms in the array. also find minimum and maximum value
for (unsigned int it1 = 0; it1 < length1; it1++)
	{ //
	for (unsigned int it2 = 0; it2 < length2; it2++)
		{ //
		for (unsigned int it3 = 0; it3 < length3; it3++)
			{ //
			value = array3D[it1].getvalue(it2,it3);
			if (value != 0 ) // do no calculations if the value is equal to zero
				{ //
				sum += value;
				sumsq += value * value;
				nonzeros++ ;
				if (maxval < value) { maxval = value ;}
				if (minval > value) { minval = value ;}
				}
			}
		}
	}
//
//
mean = quotientnonzero( sum, (double) nonzeros );
meansq = quotientnonzero( sumsq,(double) nonzeros );
sd = sqrt( meansq - ( mean * mean ) );
//
// prepare output vector
vector<double> outputarray;
outputarray.push_back( sum );
outputarray.push_back( sumsq );
outputarray.push_back( mean );
outputarray.push_back( meansq);
outputarray.push_back( sd );
outputarray.push_back( minval );
outputarray.push_back( maxval );
outputarray.push_back( (double) nonzeros );
//
return outputarray;
}


vector<double> AlexArrayU_3D::arraystats_nonzero( unsigned int location1, unsigned int location2) { return array3D[location1].arraystats_nonzero(location2); }


vector<double> AlexArrayU_3D::arraystats_nonzero( unsigned int location1 ) { return array3D[location1].arraystats_nonzero() ;}

// ********************************** arraystats *****************************************

vector<double> AlexArrayU_3D::arraystats( void )
{ //
if ( (length1 == 0) || (length2 == 0) || (length3 == 0) ) // do no calculations if the list is empty
	{ //
	cout << "THE ARRAY IS CURRENTLY EMPTY, AND THEREFORE HAS NO STATISTICAL VALUES; ALL ZEROS WILL BE RETURNED" << endl;
	vector<double> returnvector;
	for (unsigned int it1 = 0; it1 < 32; it1++) // will be longer than arraystatslength_nonzero
		{
		returnvector.push_back( 0.0 );
		}
	return returnvector;
	}
//	
//	
double sum = 0;
double sumsq = 0; // sum of squares 
double value;
double mean;
double meansq; // mean of squares
double sd; // standard deviation
unsigned int nonzeros = 0; // the number of nonzero entries in list1
double maxval = array3D[0].getvalue(0,0); // the maximum value in list1
double minval = 1073741824; // the minimum nonzero value in list1
unsigned int arrayentries = length1 * length2 * length3;
//
//
// sum together entries in list. also find minimum and maximum value
for (unsigned int it1 = 0; it1 < length1; it1++)
	{ //
	for (unsigned int it2 = 0; it2 < length2; it2++)
		{ //
		for (unsigned int it3 = 0; it3 < length3; it3++)
			{ //
			value = array3D[it1].getvalue( it2, it3 );
			if (value < minval) { minval = value ;}
			if (value != 0) // there's no point in doing the following calculations for a null entry
				{ //
				sum += value;
				sumsq += value * value;
				if ( value > maxval ) { maxval = value ;}
				}
			}
		}
	}
//
//
mean = quotientnonzero( sum, (double) arrayentries );
meansq = quotientnonzero( sumsq, (double) arrayentries );
sd = sqrt( meansq - ( mean * mean ));
//
//
// prepare outputarray
vector<double> outputarray;
outputarray.push_back( sum );
outputarray.push_back( sumsq );
outputarray.push_back( mean );
outputarray.push_back( meansq);
outputarray.push_back( sd );
outputarray.push_back( minval );
outputarray.push_back( maxval );
//
return outputarray;
}

vector<double> AlexArrayU_3D::arraystats( unsigned int location1, unsigned int location2 ) { return array3D[location1].arraystats( location2 ); }

vector<double> AlexArrayU_3D::arraystats( unsigned int location1 ) { return array3D[location1].arraystats( ); }

// ********************************** print **********************************************

void AlexArrayU_3D::print( void )
{ //
if ( (length1 == 0) || (length2 == 0) || (length3 == 0) )
	{ //
	cout << "THIS ARRAY HAS NO ENTRIES; IT IS A NULL LIST" << endl;
	}
//
//
//
//
else { //
	cout << "{";
	for (unsigned int it1 = 0; it1 < length1; it1++)
		{ //
		cout << "{";
		for (unsigned int it2 = 0; it2 < length2; it2++)
			{ //
			cout << "{";
			for (unsigned int it3 = 0; it3 < length3; it3++)
				{ //
				cout << array3D[it1].getvalue( it2, it3 );
				if (it3 == length3 - 1) { cout << "}" ;}
				else {cout << ", " ;}
				}
			if (it2 == length2 - 1) { cout << "}" ;}
			else {cout << ", " ;}
			}
		if (it1 == length1 - 1) { cout << "}" << endl; }
		else { cout << ", " ;}
		}
	}
}
	
	
// ********************************** nulltest *******************************************

bool AlexArrayU_3D::nulltest( void )
{ //
if ( ( length1 == 0 ) || (length2 == 0) || (length3 == 0) )
	{ //
	cout << "THIS ARRAY HAS NO ENTRIES; OF COURSE IT'S NULL!" << endl;
	return true;
	}
//
//
// loop through array3D to see if all values are 0
for (unsigned int it1 = 0; it1 < length1; it1++)
	{ //
	for (unsigned int it2 = 0; it2 < length2; it2++)
		{ //
		for (unsigned int it3 = 0; it3 < length3; it3++)
			{ //
			if ( array3D[it1].getvalue( it2, it3 ) != 0) { return false; }
			}
		}
	}
// if no nonzero entries have been found, return true, because the list must then be null
return true;
}


bool AlexArrayU_3D::nulltest( unsigned int location1 ) { return array3D[location1].nulltest() ; }


bool AlexArrayU_3D::nulltest( unsigned int location1, unsigned int location2 ) { return array3D[location1].nulltest( location2 ) ; }