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
#include "NhitsPlot.h"

class Experiment {
	public:
		Experiment(TString input, TString treename, TString output, int type);
		~Experiment() {};
		void add_histogrammer(Histogrammer *ht) { hts->Add(ht); }
		void event_loop();
		void finalize();
		void plot();
	private:
		TList *hts;
		TString input;
		TString treename;
		TString output;
		int type;
};

Experiment::Experiment(TString input, TString treename, TString output, int type) {
	this->input=input;
	this->output=output;
	this->treename=treename;
	this->type=type;
	hts=new TList();
}

void Experiment::event_loop() {
	TChain *eventNtuple = new TChain(treename);
	eventNtuple->Add(input);

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
		if (i>100) break;
		if (i%1000==0) { std::cout << i << endl; }
		eventNtuple->GetEntry(i);
		TList b_eventVector;     
		for (int j = 0; j<nhits; j++) { 
			// cuts for topcaf hit
			if (t_ADC[j]<100 || t_ADC[j]>2048) continue;
			if (t_PulseWidth[j]<3 || t_PulseWidth[j]>10) continue;
			if (t_Flag[j]<=0) continue;
			if (t_CorrTime[j]==0) continue;
			TopHit *hit=new TopHit();
			hit->evt_no=evt;
			hit->slot_no=(int)t_BarID[j];
			hit->channel_id=(int)t_ChannelID[j];
			hit->flag=(int)t_Flag[j];
			hit->ADC=t_ADC[j];
			hit->TDC=t_TDC[j];
			hit->PulseWidth=t_PulseWidth[j];
			hit->CorrTime=t_CorrTime[j];
			b_eventVector.Add(hit);
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
	TFile outfile(output,"recreate");
	TIter next(hts);
	Histogrammer *ht;
	while ((ht=(Histogrammer*)next())) {
		ht->finalize();
	}
	outfile.Close();
}

TList* parse_csv(const TString &s) {
	TList *l=new TList();
	int start=0,end=s.Length();
	int index=0;
	cout<<s<<endl;
	while((index=TString(s(start,end)).Index(','))!=-1) {
		cout<<start<<" "<<index<<endl;
		l->Add(new TObjString(TString(s(start,index))));
		start+=index+1;
	}
	l->Add(new TObjString(TString(s(start,end))));
	return l;
}

TString trim(const TString &s) {
	TString ss=s.Strip(TString::kLeading, ' ');
	TString sss=ss.Strip();
	return sss;
}

void Main() {
	ifstream f("input.csv");
	string line;
	while (getline(f,line)) {
		TList *l=parse_csv(TString(line.c_str()));
		TIter next(l);
		TObjString *ss;
		while((ss=(TObjString*)next())) {
			cout<<trim(ss->GetString())<<endl;
		}
	}
	Experiment e("run003424*converted.root","topddt","outfile.root",0);
	NhitsPlot *nh=new NhitsPlot();
	nh->setup_type(1,1);
	nh->setup_histo("nhits","nhits",100,0,100);
	nh->initialize();
	e.add_histogrammer(nh);
	e.event_loop();
	e.plot();
	e.finalize();
}

int main() {
	Main();
}

