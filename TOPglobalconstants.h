//Number of events to be processed. -- reading in events
const unsigned int totalbars = 16;
const unsigned int channels = 512; // channels per module
const unsigned int nrows = 8; // number of rows in a module
const unsigned int ncolumns = 64; //number of columns in a module

//Location of diagnostic variables ( l stands for location ). -- analysis
unsigned int l_ADC = 0;     //ADC
unsigned int l_PW = 1;      //PW
unsigned int l_TDC = 2;     //TDC
unsigned int l_BID = 3;     //Bar ID
unsigned int l_CID = 4;     //Channel ID
    
//TOP Geometry Constants.
unsigned int nTOPModules = 16;
unsigned int nPMTsPerModule = 512;
    
//Number of variables stored within each + within the input Root file. Currently
//ADC, Pulse Width, TDC, Bar ID, Channel ID.
unsigned int nVariables = 5;

const unsigned int MAXHITS = 32768; // maximum hits per event -- I just guessed 2^15



const unsigned int arraystatslength = 7; // length of the vector returned by arraystats
const unsigned int vectorstatslength = arraystatslength;
const unsigned int arraystatslength_nonzero = 8; // the length of the vector returned by arraystats_nonzero
const unsigned int vectorstatslength_nonzero = arraystatslength_nonzero + 1; // the length of the vector returned by vectorstats_nonzero
// the following are the locations of the measurements in the array ouput by arraystats and similar statistical functions
const unsigned int l_sum = 0;
const unsigned int l_sumsq = 1;
const unsigned int l_mean = 2;
const unsigned int l_meansq = 3;
const unsigned int l_sd = 4;
const unsigned int l_max = 6;
const unsigned int l_min = 5;
const unsigned int l_nonzeros = 7;

// these constants deal with the canvases which show multiple little graphs
const double barbottom = .94; // the bottom yvalue of the top, wide TPad
const unsigned int plotrows = 4;
const unsigned int plotcolumns = 4;
const unsigned int plotcells = plotrows * plotcolumns;

const unsigned int ncuts = 4;
double tdccutoffmin[ncuts];
tdccutoffmin[0] = -4000;
tdccutoffmin[1] = -280;
tdccutoffmin[2] = -260;
tdccutoffmin[3] = 0;

double tdccutoffmax[ncuts];
tdccutoffmax[0] = -280;
tdccutoffmax[1] = -260;
tdccutoffmax[2] = 0;
tdccutoffmax[3] = 4300;
