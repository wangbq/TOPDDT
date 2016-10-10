#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
const int NFILES = 1; // number of files to be read

/*
void arraylister( TString in_array[], unsigned int in_nterms ) //
{ //
for (unsigned int it1 = 0; it1 < in_nterms; it1++) { cout << in_array[in_nterms] << endl ;}
} //
*/

/*
TString filenames[1]; // this is the list of the names of the files from which we want to take the data
filenames[0] = "TOPDDT_gun_converted.root";


unsigned int totaleventlistgun[0]; // this is the number of events which we want to process from each file
const unsigned int alleventlength = 300;
totaleventlistgun[0] = alleventlength;
*/


TString filenames[NFILES]; // this is the list of the names of the files from which we want to take the data
filenames[0] = "TOPDDT_gun_converted.root";


unsigned int totaleventlist[NFILES]; // this is the number of events which we want to process from each file
const unsigned int alleventlength = 300;
totaleventlist[0] = alleventlength;

void makegraphs_any( TString in_filenames[], unsigned int in_totaleventlist[], const int in_nfiles ){
     makegraphs_monte( filenames, totaleventlist, NFILES );
//	makegraphs( filenames, totaleventlist, NFILES );
}