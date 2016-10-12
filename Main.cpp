#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include "TH1F.h"
#include "TChain.h"
#include "TFile.h"
//#include "TOPDDTmain.h"

using namespace std;

#define MAXHITS 65536

typedef struct {
	int evt_no;
	int slot_no;
	int channel_id;
	int flag;
	float ADC;
	float TDC;
	float PulseWidth;
	float CorrTime;
} tophit; 

TH1F *h_num_hits;
TH1F *h_adc;
TH1F *h_tdc;

void initialize() {
	//example histos, range and bins should be determined later
	h_num_hits=new TH1F("h_num_hits","h_num_hits",100,0,100);
	h_adc=new TH1F("h_adc","h_adc",100,0,100);
	h_tdc=new TH1F("h_tdc","h_tdc",100,0,100);
}

void finalize() {
	//save histos to pdf files
	TFile outfile("outfile.root","recreate");
	h_num_hits->Write();
	h_adc->Write();
	h_tdc->Write();
	outfile.Close();
}

void plot_histos(const vector<tophit> &hits) {
	int nhits=hits.size();
	h_num_hits->Fill(nhits);
	for (int i=0;i<nhits;i++) {
		h_adc->Fill(hits[i].ADC);
		h_tdc->Fill(hits[i].TDC);
	}
}

void Main(){
	initialize(); // initialize histograms
	string filename="run003330_slot01_laser_cpr3001_converted.root";
	TChain *eventNtuple = new TChain("topddt");
	eventNtuple->Add(filename.c_str());

	float t_ADC[MAXHITS], t_PulseWidth[MAXHITS], t_TDC[MAXHITS], t_BarID[MAXHITS], t_ChannelID[MAXHITS],t_CorrTime[MAXHITS];
	int t_Flag[MAXHITS];
	int evt, nhits;

	eventNtuple->SetBranchAddress("ADC",t_ADC);
	eventNtuple->SetBranchAddress("PulseWidth",t_PulseWidth);
	eventNtuple->SetBranchAddress("TDC",t_TDC);
	eventNtuple->SetBranchAddress("BarID",t_BarID);
	eventNtuple->SetBranchAddress("ChannelID",t_ChannelID);
	eventNtuple->SetBranchAddress("evt",&evt);
	eventNtuple->SetBranchAddress("nhits",&nhits);
	eventNtuple->SetBranchAddress("Flag",t_Flag);
	eventNtuple->SetBranchAddress("CorrTime",t_CorrTime);

	//event loop
	int n_eventProcessed=eventNtuple->GetEntries();
	for (int i = 0; i< n_eventProcessed; i++) { 
		if (i%1000==0) { std::cout << i << endl; }
		eventNtuple->GetEntry(i);
		vector<tophit> b_eventVector;     
		for (int j = 0; j<nhits; j++) { 
			if (t_ADC[j]<100 || t_ADC[j]>2048) continue;
			if (t_PulseWidth[j]<3 || t_PulseWidth[j]>10) continue;
			if (t_Flag[j]<=0) continue;
			if (t_CorrTime[j]==0) continue;
			tophit hit;
			hit.evt_no=evt;
			hit.slot_no=(int)t_BarID[j];
			hit.channel_id=(int)t_ChannelID[j];
			hit.flag=(int)t_Flag[j];
			hit.ADC=t_ADC[j];
			hit.TDC=t_TDC[j];
			hit.PulseWidth=t_PulseWidth[j];
			hit.CorrTime=t_CorrTime[j];
			b_eventVector.push_back(hit);
		}
		plot_histos(b_eventVector);
	}
	finalize(); // finalize works
}
