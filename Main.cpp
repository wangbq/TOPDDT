#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include "TH1F.h"
#include "TChain.h"
#include "TFile.h"
#include "TString.h"
#include "Main.h"
#include "NhitHistogrammer.h"

Experiment::Experiment(string input, string treename, string output, int type) {
	t_input=input;
	t_output=output;
	t_treename=treename;
	t_type=type;
	hts=new TList();
}

void Experiment::event_loop() {
	TChain *eventNtuple = new TChain(t_treename.c_str());
	eventNtuple->Add(t_input.c_str());

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

	int n_eventProcessed=eventNtuple->GetEntries();
	cout<<"total events: "<<n_eventProcessed<<endl;
	for (int i = 0; i< n_eventProcessed; i++) { 
		if (i%1000==0) { std::cout << i << endl; }
		eventNtuple->GetEntry(i);
		vector<tophit> b_eventVector;     
		for (int j = 0; j<nhits; j++) { 
			// cuts for topcaf hit
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
		TIter next(hts);
		Histogrammer *ht;
		while ((ht = (Histogrammer *) next())) {
			ht->process_event(b_eventVector);
		}
	}
}

void Experiment::plot() {
	TIter next(hts);
	Histogrammer *ht;
	while ((ht=(Histogrammer*)next())) {
		ht->plot();
	}
}

void Experiment::finalize() {
	TFile outfile(t_output.c_str(),"recreate");
	TIter next(hts);
	Histogrammer *ht;
	while ((ht=(Histogrammer*)next())) {
		ht->finalize();
	}
	outfile.Close();
}

void Main() {
	Experiment e("run003423_slot03_laserWithB_cpr3003_converted.root","topddt","outfile.root",0);
	NhitHistogrammer *nh=new NhitHistogrammer();
	e.add_histogrammer(nh);
	e.event_loop();
	//e.plot();
	e.finalize();
}

int main() {
	Main();
}

