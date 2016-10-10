#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include "TOPDDTmain.h"
//#include "files_laser.h"
#include "files_gun.h"
//#include "Array_updates.h"
// quotientnonzero, AlexArrayU, AlexArrayU_2D, AlexArrayU_3D, AlexArrayD, AllexArrayD_2D, AlexArrayD_3D
//#include "files_new.h"
//#include "globalconstants_updates.h"

using namespace std;
//-------------------------------------------
//                                          -
//                Analysis                  -
//                                          -
//-------------------------------------------


void Main(){
     makegraphs_monte( filenames, totaleventlist, NFILES );
//	makegraphs( filenames, totaleventlist, NFILES );
}