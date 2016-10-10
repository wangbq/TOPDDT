#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
const int NFILES = 16; // number of files to be read

void arraylister( TString in_array[], unsigned int in_nterms ) //
{ //
for (unsigned int it1 = 0; it1 < in_nterms; it1++) { cout << in_array[in_nterms] << endl ;}
} //

TString filenames[NFILES]; // this is the list of the names of the files from which we want to take the data
filenames[0] = "run003258_slot01_laser_cpr3001_converted.root";
filenames[1] = "run003258_slot02_laser_cpr3002_converted.root";
filenames[2] = "run003258_slot03_laser_cpr3003_converted.root";
filenames[3] = "run003258_slot04_laser_cpr3004_converted.root";
filenames[4] = "run003258_slot05_laser_cpr3005_converted.root";
filenames[5] = "run003258_slot06_laser_cpr3006_converted.root";
filenames[6] = "run003258_slot07_laser_cpr3007_converted.root";
filenames[7] = "run003258_slot08_laser_cpr3008_converted.root";
filenames[8] = "run003220_slot09_laser_cpr3009_converted.root";
filenames[9] = "run003220_slot10_laser_cpr3010_converted.root";
filenames[10] = "run003220_slot11_laser_cpr3011_converted.root";
filenames[11] = "run003220_slot12_laser_cpr3012_converted.root";
filenames[12] = "run003220_slot13_laser_cpr3013_converted.root";
filenames[13] = "run003220_slot14_laser_cpr3014_converted.root";
filenames[14] = "run003220_slot15_laser_cpr3015_converted.root";
filenames[15] = "run003220_slot16_laser_cpr3016_converted.root";


unsigned int totaleventlist[NFILES]; // this is the number of events which we want to process from each file
const unsigned int alleventlength = 300;
totaleventlist[0] = alleventlength;
totaleventlist[1] = alleventlength;
totaleventlist[2] = alleventlength;
totaleventlist[3] = alleventlength;
totaleventlist[4] = alleventlength;
totaleventlist[5] = alleventlength;
totaleventlist[6] = alleventlength;
totaleventlist[7] = alleventlength;
totaleventlist[8] = alleventlength;
totaleventlist[9] = alleventlength;
totaleventlist[10] = alleventlength;
totaleventlist[11] = alleventlength;
totaleventlist[12] = alleventlength;
totaleventlist[13] = alleventlength;
totaleventlist[14] = alleventlength;
totaleventlist[15] = alleventlength;

void makegraphs_any( TString in_filenames[], unsigned int in_totaleventlist[], const int in_nfiles ){
//     makegraphs_monte( filenames, totaleventlist, NFILES );
	makegraphs( filenames, totaleventlist, NFILES );
}
