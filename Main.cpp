#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include "TH1F.h"
#include "TChain.h"
#include "TFile.h"
#include "TString.h"
#include "Main.h"

void Experiment::Experiment(string input, string treename, string output, int type) {
	t_input=input;
	t_output=output;
	t_treename=treename;
	t_type=type;
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

	//event loop
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
		//plot_histos(b_eventVector);
		for (j=0;j<hts.size();j++) {
			hts[j]->process_event(b_eventVector);
		}
	}
}

void Experiment::plot() {
	for (int i=0;i<hts.size();i++) {
		hts[i]->plot();
	}
}

void Experiment::finalize() {
	TFile outfile(t_output.c_str(),"recreate");
	for (int i=0;i<hts.size();i++) {
		hts[i]->finalize();
	}
	outfile.Close();
}

void Main() {
	Experiment e("run003423_slot03_laserWithB_cpr3003_converted.root","topddt","outfile.root",0);
	//e.add_histogrammer();
	e.event_loop();
	e.plot();
	e.finalize();
}
