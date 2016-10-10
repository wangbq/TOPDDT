#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include "Array_updates.h" 
// quotientnonzero, AlexArrayU, AlexArrayU_2D, AlexArrayU_3D, AlexArrayD, AllexArrayD_2D, AlexArrayD_3D
//#include "files_new.h"
//#include "globalconstants_updates.h"

// ***************************************************************************************
//
// Begin Boqun Functions
//
// ***************************************************************************************

//Average of a vector.
float average( vector<float> inputVector ){
    
    if (inputVector.size() == 0) {
        return 0.;
    }
    
    float b_average = 0.;
    for (unsigned int i = 0; i<inputVector.size(); i++) {
        b_average += float(inputVector[i]);
    }
    b_average = b_average/(float(inputVector.size()));
    return b_average;
}

//Initialize a 2D vector with a specified size in X.
vector < vector <float> >  initializedXSize2D(int vectorSize){
    vector<float> dummy_vector;
    vector< vector < float > > returnVector;
    for (unsigned int i = 0; i<vectorSize; i++) {
        returnVector.push_back(dummy_vector);
    }
    return returnVector;
}

//Initialize a 2D vector with a specified size in X & Y.
vector < vector <float> >  intializedXYSize2D(unsigned int vectorSizeX,unsigned int vectorSizeY){
    vector<float> dummy_vector(vectorSizeY,0.);
    vector< vector < float > > returnVector;
    for (unsigned int i = 0; i<vectorSizeX; i++) {
        returnVector.push_back(dummy_vector);
    }
    return returnVector;
}

//Initialize a 3D vector with a specified size in X & Y.
vector < vector < vector <float> > > intializedXYSize3D(unsigned int vectorSizeX,unsigned int vectorSizeY){
    vector < vector < vector <float> > > returnVector;
    
    vector < vector <float> > dummy_vector_x;
    
    for (unsigned int i = 0; i<vectorSizeX; i++) {
        returnVector.push_back(dummy_vector_x);
    }
    
    vector <float> dummy_vector_y;
    
    for (unsigned int i = 0; i< returnVector.size(); i++ ){
        for (unsigned int j = 0; j<vectorSizeY; j++) {
            returnVector[i].push_back(dummy_vector_y);
        }
    }
    
    return returnVector;
}

//Mean of TH1F histogram.
float histogramMean(TH1F* histogram){
    
    if ( int(histogram->GetNbinsX()) == 0 ) return 0.;
    
    float b_sum = 0.;
    for (unsigned int i = 0; i<histogram->GetNbinsX(); i++) {
        b_sum += histogram->GetBinContent(i+1);
    }
    return b_sum/(float(histogram->GetNbinsX()));
    
}

//Stardard deviation of TH1F histogram.
float histogramSTD(TH1F* histogram){
    float dummy = 0.;
    float mean = histogramMean(histogram);
    for (unsigned int i = 0; i<histogram->GetNbinsX(); i++) {
        dummy += pow((histogram->GetBinContent(i+1) - mean),2);
    }
    
    return sqrt(dummy/(float(histogram->GetNbinsX())));
}

//Coversion function from PMT pixel number to PMT pixel row.
unsigned int pmtrow(unsigned int pmtChannel){
    unsigned int row = (pmtChannel -1)/64 +1;
    return row;
}

//Coversion function from PMT pixel number to PMT pixel column.
unsigned int pmtcolumn( unsigned int pmtChannel){
   	unsigned int column = (pmtChannel -1)%64 +1;
    return column;
}

//Creates a 1D vector<float> of the same size as input vector with elements 1, 2, 3, ...
vector<float> iterator_vector(vector<float> buffer){
    vector<float> return_vector;
    
    for (int i = 0; i<buffer.size(); i++) {
        return_vector.push_back(float(i+1));
    }
    
    return return_vector;
}


// ***************************************************************************************
//
// Begin Reineck functions
//
// ***************************************************************************************


// ********************************** listsum ********************************************

unsigned int listsum( vector<unsigned int> in_vector ) // sums togeather all terms in the vector
{ // *
unsigned int sum = 0;
unsigned int length = in_vector.size();
for (unsigned int it1 = 0; it1 < length; it1++) { sum += in_vector[it1] ;}
return sum;
} // *

unsigned int listsum( unsigned int in_array[], unsigned int in_length ) // sums together all terms in the  array
// in_length = in_array.size()
{ // *
unsigned int sum = 0;
for (unsigned int it1 = 0; it1 < in_length; it1++) { sum += in_array[it1] ;}
return sum;
} // *

// ******************************* fill histogram per bar ********************************

void fillbarhistograms( unsigned int in_array[totalbars], TH1I* in_histlist[totalbars] ) // for each bar, fill the corresponding histogram
{ // *
for (unsigned int it_barnumber = 0; it_barnumber < totalbars; it_barnumber++) { in_histlist[it_barnumber]->Fill( (int) in_array[it_barnumber] ) ;}
} // *

void fillbarhistograms( double in_array[totalbars], TH1D* in_histlist[totalbars] ) // for each bar, fill the corresponding histogram
{ // *
for (unsigned int it_barnumber = 0; it_barnumber < totalbars; it_barnumber++) { in_histlist[it_barnumber]->Fill( in_array[it_barnumber] ) ;}
} // *

// ********************************** min ************************************************ 

unsigned int min(unsigned int in_a, unsigned int in_b) // returns the smallest of the two values
{ // *
if (in_a > in_b ) { return in_b ;}
// otherwise
return in_a ;
} // *

double min(double in_a, double in_b) // returns the smallest of the two values
{ // *
if (in_a > in_b ) { return in_b ;}
// otherwise
return in_a ;
} // *

//*****************************************************************************************
// ***************************** findpadrow and findpadcolumn ****************************
//*****************************************************************************************


unsigned int findpadrow( unsigned int padnumber)
{ //
unsigned int loc_padrow;
loc_padrow = padnumber / (plotrows);
return loc_padrow;
}


unsigned int findpadcolumn( unsigned int padnumber)
{ //
unsigned int loc_padcolumn;
loc_padcolumn = padnumber % (plotrows);
return loc_padcolumn;
}

// ****************************** plotperbar *********************************************
// initialises one plot for every bar in the form of an array

void initialise_plotperbar( TH1D *in_hist[totalbars], TString in_histname, double in_xmin, double in_xmax, unsigned int in_nbins ) //
{ // *
TString histtitle, histname;
for (unsigned int it_barnumber = 0; it_barnumber < totalbars; it_barnumber++) // through bars
	{ // 
	histname = Form("Slot %d",it_barnumber + 1);
	histtitle = in_histname + " " + histname;
	TH1D *histmodel = new TH1D(histname, histtitle, in_nbins, in_xmin, in_xmax );
	in_hist[it_barnumber] = histmodel;
	} //
} // *

// *************************** manyplotter ***********************************************

// this definition doesn't require in_nulldata, and assumes that NO DATASETS ARE NULL
void manyplotter( TCanvas *in_canvas, TH1D *in_array[totalbars], TString in_plotname, double in_namenumber)
{ 
in_canvas->cd();

double padxmin, padymin, padxmax, padymax; //these will control the location of each pad
unsigned int padrow, padcolumn;
TString canvasname = in_canvas->GetName();
TString padname;
double mean, lowererror, uppererror;

// loop through the graph vector; make a pad for each graph; draw the graph and the associated lines, and then draw corresponding pad.
for (unsigned int it1; it1 < totalbars; it1++)
	{ //
	// define pad
	padrow = findpadrow( it1 );
	padcolumn = findpadcolumn( it1 );
	padname = Form("N_%d__",it1) + canvasname; // it really doesn't matter what the pad name is, so long as it is unique
	padrow = findpadrow( it1 );
	padcolumn = findpadcolumn( it1 );
	padxmin = ((double)(padcolumn)) / plotrows;
	padxmax = ((double)(padcolumn + 1.0)) / plotcolumns;
	padymax = barbottom - ((barbottom * padrow) / plotrows);
	padymin = barbottom - (  ((barbottom ) * (padrow + 1.0)) / plotrows  );
	TPad *pad = new TPad(padname," ",padxmin,padymin,padxmax,padymax);
	pad->cd();
	//  draw graph
	in_array[it1]->Draw();
	// draw pad
	in_canvas->cd();
	pad->Draw();
	}
// define and draw the top pad -- the pad which will have the big title on it
TString toppadname;
toppadname = "toppad__" + canvasname;
TPad *toppad = new TPad(toppadname,toppadname,0,barbottom,1,1);
toppad->cd();
TLatex latex_plottitle;
latex_plottitle.SetTextSize(.667);
latex_plottitle.DrawLatex(in_namenumber, .3, in_plotname);
in_canvas->cd();
toppad->Draw();
in_canvas->Update();
}

// ***************************************************************************************
//
// Define graphing functions
//
// ***************************************************************************************

// *************************** define cutgraphs_update ***********************************

void cutgraphs_update( unsigned int in_channelhits_cuts[ncuts][channels] ) // draws the hits per channel graphs for each cut
{ // *** cutgraphs_update
//
//
//
// make onearray
double onearray_channels[channels];
for (unsigned int it_channelnumber = 0; it_channelnumber < channels; it_channelnumber++) { onearray_channels[it_channelnumber] = (double)( it_channelnumber + 1); }
// for each cut, create a canvas
double arraymodel[channels]; // since TGraph needs two double inputs, the entries of in_channelhits_cuts[ncuts][channels] will be fed into this array
TString title;
TString filename;
for (unsigned int it_cutnumber = 0; it_cutnumber < ncuts; it_cutnumber++) // through cuts
	{ //
	for (unsigned int it_channelnumber = 0; it_channelnumber < channels; it_channelnumber++) { arraymodel[it_channelnumber] = (double) in_channelhits_cuts[it_cutnumber][it_channelnumber]; }
	//  convert the array of unsigned ints into an array of doubles
	title = Form("Hits per Channel, Cut %d", it_cutnumber + 1);
	TCanvas *modelcanvas = new TCanvas(title,title,2200,1800);
	modelcanvas->cd();
	TGraph *tgraphmodel = new TGraph(channels, onearray_channels, arraymodel );
	tgraphmodel->SetTitle(title);
	tgraphmodel->GetXaxis()->SetTitle( "Channel Number" );
	tgraphmodel->GetYaxis()->SetTitle( "Hits" );
	tgraphmodel->GetXaxis()->SetRangeUser( .5, channels + .5);
	tgraphmodel->Draw("AB");
	filename = Form("channelhits_cut%d.ps", it_cutnumber + 1);
	modelcanvas->Update();
	modelcanvas->SaveAs( filename );
	} //
//
//
// create a graph for total hits per channel across all channels
//
// find total hits per channel
unsigned int sum = 0; // this will be used as a placeholder value
double channelhits[channels];
for (unsigned int it_channelnumber = 0; it_channelnumber < channels; it_channelnumber++ ) // through channels
	{ //
	sum = 0;
	for (unsigned int it_cutnumber = 0; it_cutnumber < ncuts; it_cutnumber++) // through cuts
		{ //
		sum += in_channelhits_cuts[it_cutnumber][it_channelnumber] ;
		} //
	channelhits[it_channelnumber] = (double) sum;
	} //
//
// plot the sum array
TCanvas *modelcanvas = new TCanvas("Hits per Channel","Hits Per Channel",2200,1800);
modelcanvas->cd();
TGraph *tgraphmodel = new TGraph(channels, onearray_channels, channelhits );
tgraphmodel->SetTitle("Hits per Channel");
tgraphmodel->GetXaxis()->SetTitle( "Channel Number" );
tgraphmodel->GetYaxis()->SetTitle( "Hits" );
tgraphmodel->GetXaxis()->SetRangeUser( .5, channels + .5);
tgraphmodel->Draw("AB");
modelcanvas->Update();
modelcanvas->SaveAs("channelhits.ps");
} // *** cutgraphs_update

// ******************************* define graph_update ************************************

void graph_update( TCanvas *in_canvas, TH1D *in_hist, TString in_filename ) // plots the histogram on the canvas and then saves it
{ // graph_update
in_canvas->cd();
in_hist->Draw();
in_canvas->Update();
in_canvas->SaveAs(in_filename);
} // graph_update


void graph_update( TCanvas *in_canvas, TH2D *in_hist, TString in_filename ) // plots the histogram on the canvas and then saves it
{ // graph_update
in_canvas->cd();
in_hist->Draw("colz");
in_canvas->Update();
in_canvas->SaveAs(in_filename);
} // graph_update

// ***************************************************************************************
//
// Define analyseeventvector
//
// ***************************************************************************************


void analyseeventvector( vector< vector < vector < float > > > eventvector, unsigned int totalevents ) //
{ // *** analyse

cout << "ANALYSING EVENTVECTOR" << endl;
cout << "eventvectorlength " << eventvector.size() << endl;
unsigned int guess_stepsize = 5000; // how often the graphs are updated

// ********************************* define histogram arrays *****************************

TString histname, histtitle, partialtitle;
TH1D *hist_tdc_bybar[totalbars];
double guess_maxtdc = 400;
double guess_mintdc = -400;
unsigned int guess_nbins = 100;
initialise_plotperbar( hist_tdc_bybar, "TDC Distribution, By Module ", guess_mintdc, guess_maxtdc, guess_nbins );

// ************************* define graphs and canvases ***********************************

unsigned int eventlength; // will be equal to eventvector[i].size() in a loop
unsigned int instancelength; // will be equal to eventvector[i][j].size() 
TCanvas *canv_hist_tdc_acrossbars = new TCanvas("TDC Distribution, Across All Bars","TDC Distribution, Across All Bars",2200,1800);
TCanvas *canv_hist_tdc_bybar = new TCanvas("TDC Distribution, By Bar","TDC Distribution, By Bar",2200,1800);
double guess_maxtdc = 400;
double guess_mintdc = -400;
double guess_tdccutoffmin = -285;
double guess_tdccutoff = -260;
unsigned int guess_nbins = 100;
TCanvas *canv_tdc_acrossbars_2D = new TCanvas("TDC versus Channel Number","TDC versus Channel Number",2200,1800);
TCanvas *canv_tdc_acrossbars_2D_cutoff = new TCanvas("TDC versus Channel Number (With Cutoff)","TDC versus Channel Number (With Cutoff)",2200,1800);
TH1D *hist_tdc_acrossbars = new TH1D("TDC Distribution, Across All Bars","TDC Distribution, Across All Bars",guess_nbins,guess_mintdc,guess_maxtdc);
TH2D *hist_tdc_acrossbars_2D = new TH2D("TDC versus Channel Number","TDC versus Channel Number",channels,1,channels,guess_nbins, guess_mintdc,guess_maxtdc);
TH2D *hist_tdc_acrossbars_2D_cutoff = new TH2D("TDC versus Channel Number (With Cutoff)","TDC versus Channel Number (With Cutoff)",channels,1,channels,guess_nbins, guess_tdccutoffmin,guess_tdccutoff);
hist_tdc_acrossbars_2D->SetStats(kFALSE);
hist_tdc_acrossbars_2D_cutoff->SetStats(kFALSE);

double guess_minadc = 90;
double guess_maxadc = 1200;
double guess_minpulsewidth = 2.5;
double guess_maxpulsewidth = 11;
TCanvas *canv_hist_pulsewidth_acrossbars = new TCanvas("Pulsewidth Distribution, Across Modules","Pulsewidth Distribution, Across Modules",2200,1800);
TCanvas *canv_hist_adc_acrossbars = new TCanvas("ADC Distribution, Across Modules","ADC Distribution, Across Modules",2200,1800);
TH1D *hist_pulsewidth_acrossbars = new TH1D("Pulsewidth Distribution, Across Modules","Pulsewidth Distribution, Across Modules",guess_nbins,guess_minpulsewidth,guess_maxpulsewidth);
TH1D *hist_adc_acrossbars = new TH1D("ADC Distribution, Across Modules","ADC Distribution, Across Modules",guess_nbins,guess_minadc,guess_maxadc);

// ******************************* define arrays *****************************************

unsigned int channelhits_cuts[ncuts][channels] = {0};

// ************************** loop through eventvector ***********************************
cout << "LOOPING THROUGH EVENTVECTOR" << endl;

unsigned int barnumber, channelnumber;
double tdc, adc, pulsewidth; // these will be used as placeholder values

for (unsigned int it_eventnumber = 0; it_eventnumber < totalevents; it_eventnumber++) // through events
{ // 
// define loop variables
unsigned int barhitsevent = 0; // will be the number of times a bar was hit during an event
eventlength = eventvector[it_eventnumber].size();
//
//
// loop through instances
for (unsigned int it_instancenumber = 0; it_instancenumber < eventlength; it_instancenumber++) // through instances 
{ // 
barnumber = eventvector[it_eventnumber][it_instancenumber][l_BID] - 1;
barhitsevent[barnumber] ++;
tdc = (double) eventvector[it_eventnumber][it_instancenumber][l_TDC];
pulsewidth = (double) eventvector[it_eventnumber][it_instancenumber][l_PW];
adc = (double) eventvector[it_eventnumber][it_instancenumber][l_ADC];
channelnumber = eventvector[it_eventnumber][it_instancenumber][l_CID] - 1;
hist_tdc_acrossbars->Fill( tdc );
hist_tdc_bybar[barnumber]->Fill( tdc );
hist_tdc_acrossbars_2D->Fill( channelnumber + 1, tdc );
hist_tdc_acrossbars_2D_cutoff->Fill( channelnumber + 1, tdc );
hist_pulsewidth_acrossbars->Fill( pulsewidth );
hist_adc_acrossbars->Fill( adc );
// increment hits per channel
// for each cut number, increment the his per channel if the tdc falls within the cut range
for (unsigned int it_cutnumber = 0; it_cutnumber < ncuts; it_cutnumber++) // through cuts
	{ // 
	if ( (tdccutoffmin[it_cutnumber] < tdc ) && (tdccutoffmax[it_cutnumber] > tdc) ) 
		{ //
		channelhits_cuts[it_cutnumber][channelnumber]++ ;
		} //	
	} // 
} // 
if ( (it_eventnumber % guess_stepsize == 0) && (it_eventnumber != 0) )
	{ // 
	cout << it_eventnumber << " events have been looped through." << endl;
	graph_update( canv_hist_tdc_acrossbars, hist_tdc_acrossbars, "TDCVersusChannel_AcrossBars.ps");
//	manyplotter( canv_hist_tdc_bybar, hist_tdc_bybar, "TDC Distribution, By Module", .4 ); 
//	graph_update( canv_tdc_acrossbars_2D, hist_tdc_acrossbars_2D, "TDCVersusChannel_AcrossBars_2D.ps");
//	graph_update( canv_tdc_acrossbars_2D_cutoff, hist_tdc_acrossbars_2D_cutoff, "TDCVersusChannel_AcrossBars_2D_Cutoff.ps" );
//	graph_update( canv_hist_pulsewidth_acrossbars, hist_pulsewidth_acrossbars, "PulsewidthDistribution_AcrossBars.ps");
//	graph_update( canv_hist_adc_acrossbars, hist_adc_acrossbars, "ADCDistribution_AcrossBars.ps");
//	cutgraphs_update( channelhits_cuts );
	} // 
} // 
graph_update( canv_hist_tdc_acrossbars, hist_tdc_acrossbars, "TDCVersusChannel_AcrossBars.ps");
/*
manyplotter( canv_hist_tdc_bybar, hist_tdc_bybar, "TDC Distribution, By Module", .4 ); 
graph_update( canv_tdc_acrossbars_2D, hist_tdc_acrossbars_2D, "TDCVersusChannel_AcrossBars_2D.ps");
graph_update( canv_tdc_acrossbars_2D_cutoff, hist_tdc_acrossbars_2D_cutoff, "TDCVersusChannel_AcrossBars_2D_Cutoff.ps" );
graph_update( canv_hist_pulsewidth_acrossbars, hist_pulsewidth_acrossbars, "PulsewidthDistribution_AcrossBars.ps");
graph_update( canv_hist_adc_acrossbars, hist_adc_acrossbars, "ADCDistribution_AcrossBars.ps");
cutgraphs_update( channelhits_cuts );
*/
} // *** analyse


void makegraphs( TString in_filenames[], unsigned int in_totaleventlist[], const int in_nfiles )
// in_nfiles = in_filesnames.size() = in_totaleventlist.size()
// in_nfiles is the number of files which we want the program to take data from
{ // *** main

// ***************************************************************************************
//
// Define Loading Functions
//
// ***************************************************************************************

vector<vector<vector <float > > > loaddatafile( TString filename, unsigned int nevents, vector<vector<vector <float > > > invector )
{
cout << "loading " << filename << endl;
TFile *file = new TFile( filename);
//
    //Number of events to be processed.
    unsigned int n_eventProcessed = nevents;
    
    std::cout << "Proccessing: " << n_eventProcessed << " Events" << endl;
    
	float t_ADC[MAXHITS], t_PulseWidth[MAXHITS], t_TDC[MAXHITS], t_BarID[MAXHITS], t_ChannelID[MAXHITS],t_CorrTime[MAXHITS];
	int t_Flag[MAXHITS];
	int evt, nhits;
	TTree *eventNtuple = (TTree*) file->Get("topddt");
	
	eventNtuple->SetBranchAddress("ADC",t_ADC);
	eventNtuple->SetBranchAddress("PulseWidth",t_PulseWidth);
	eventNtuple->SetBranchAddress("TDC",t_TDC);
	eventNtuple->SetBranchAddress("BarID",t_BarID);
	eventNtuple->SetBranchAddress("ChannelID",t_ChannelID);
	eventNtuple->SetBranchAddress("evt",&evt);
	eventNtuple->SetBranchAddress("nhits",&nhits);
	eventNtuple->SetBranchAddress("Flag",t_Flag);
	eventNtuple->SetBranchAddress("CorrTime",t_CorrTime);

//Reading in events from input file. Will be stored in eventVector.
cout << n_eventProcessed << endl;
for (int i = 0; i< n_eventProcessed; i++) { // *
if (i%1000==0) { std::cout << i << endl; }
eventNtuple->GetEntry(i);
//Number of hits within this event.
int hitsPerEvent = nhits;      
//Buffer vector to temporarily store hits for a single event. Will be
//permanently stored in eventVector.
//vector< vector< float > > b_eventVector = initializedXSize2D(hitsPerEvent);
vector< vector< float > > b_eventVector;     
//Filling buffer vector.
for (int j = 0; j<hitsPerEvent; j++) { // **
if (t_ADC[j]<100 || t_ADC[j]>2048) continue;
if (t_PulseWidth[j]<3 || t_PulseWidth[j]>10) continue;
if (t_Flag[j]<=0) continue;
if (t_CorrTime[j]==0) continue;
vector<float> hitVector;
hitVector.push_back(t_ADC[j]);
hitVector.push_back(t_PulseWidth[j]);
hitVector.push_back(t_TDC[j]);
hitVector.push_back(t_BarID[j]);
hitVector.push_back(t_ChannelID[j]);
b_eventVector.push_back(hitVector);
} // **
//Storing the hits for the event.
invector.push_back(b_eventVector);
} // *
return invector;
}


// ***************************************************************************************
//
// Load files into eventvector
//
// ***************************************************************************************


// find the number of files which the program will analyse
const unsigned int global_eventsum = listsum( totaleventlist, in_nfiles );

// load files into eventvector
vector<vector<vector<float> > > global_eventvector;
for (unsigned int it1 = 0; it1 < in_nfiles; it1++) // through the files in the array
	{ // *
	global_eventvector = loaddatafile( filenames[it1], totaleventlist[it1], global_eventvector ) ;
	} // *

const unsigned int global_events = global_eventvector.size();
//
//
// events may not be loaded if their data isn't good
const unsigned int global_totalevents = min( global_eventsum,  global_events  ); 

// ***************************************************************************************
//
// analyse eventvector
//
// ***************************************************************************************


analyseeventvector( global_eventvector, global_totalevents );


} // *** main














void makegraphs_monte( TString in_filenames[], unsigned int in_totaleventlist[], const int in_nfiles  )
// in_nfiles = in_filesnames.size() = in_totaleventlist.size()
// in_nfiles is the number of files which we want the program to take data from
{ // *** main

// ***************************************************************************************
//
// Define Loading Functions
//
// ***************************************************************************************

vector< vector < vector < float > > > loaddatafile_monte( TString filename, unsigned int nevents, vector<vector<vector <float > > > invector )
{
cout << "loading " << filename << endl;
//
int evt, nhits, hitsperevent;
float t_ADC[MAXHITS], t_PulseWidth[MAXHITS], t_TDC[MAXHITS], t_BarID[MAXHITS], t_ChannelID[MAXHITS];
//
TFile *file = new TFile( filename);
TTree *eventntuple = (TTree*) file->Get("topddt");
//
eventntuple->SetBranchAddress("ADC",t_ADC);
eventntuple->SetBranchAddress("PulseWidth",t_PulseWidth);
eventntuple->SetBranchAddress("TDC",t_TDC);
eventntuple->SetBranchAddress("BarID",t_BarID);
eventntuple->SetBranchAddress("ChannelID",t_ChannelID);
eventntuple->SetBranchAddress("evt",&evt);
eventntuple->SetBranchAddress("nhits",&nhits);
//
for ( unsigned int it1 = 0; it1 < nevents; it1++)
	{
	eventntuple->GetEntry( it1 );
	hitsperevent = nhits;
	vector< vector< float > > tempvector = initializedXSize2D(hitsperevent);
//	
	for (int j = 0; j < hitsperevent; j++)
		{
        tempvector[j].push_back(t_ADC[j]);
        tempvector[j].push_back(t_PulseWidth[j]);
        tempvector[j].push_back(t_TDC[j]);
        tempvector[j].push_back(t_BarID[j]);
        tempvector[j].push_back(t_ChannelID[j]);
		}
	invector.push_back( tempvector );
	}
//	
//
return invector;
}

// ***************************************************************************************
//
// Load files into eventvector
//
// ***************************************************************************************


// load files into eventvector
vector<vector<vector<float> > > global_eventvector;
global_eventvector = loaddatafile_monte( filenames[0], 1000, global_eventvector ) ;
const unsigned int global_events = global_eventvector.size();
//
//
// events may not be loaded if their data isn't good
const unsigned int global_totalevents = 1000;

// ***************************************************************************************
//
// analyse eventvector
//
// ***************************************************************************************


analyseeventvector( global_eventvector, global_totalevents );


} // *** main

