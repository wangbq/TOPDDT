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
#include "NhitsPerModulePlot.h"

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
	while((index=TString(s(start,end)).Index(','))!=-1) {
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
	Experiment e("run003424*converted.root","topddt","outfile.root",0);
	ifstream f("input.csv");
	string line;
	while (getline(f,line)) {
		if (line[0]=='#') continue;
		TList *l=parse_csv(TString(line.c_str()));
		TString nhist,ndim,class_name,name,title,nbinsx,xmin,xmax,nbinsy,ymin,ymax;
		nhist=trim(((TObjString*)l->At(0))->GetString());
		ndim=trim(((TObjString*)l->At(1))->GetString());
		class_name=trim(((TObjString*)l->At(2))->GetString());
		name=trim(((TObjString*)l->At(3))->GetString());
		title=trim(((TObjString*)l->At(4))->GetString());
		nbinsx=trim(((TObjString*)l->At(5))->GetString());
		xmin=trim(((TObjString*)l->At(6))->GetString());
		xmax=trim(((TObjString*)l->At(7))->GetString());
		if (ndim.Atoi()==2) {
			nbinsy=trim(((TObjString*)l->At(8))->GetString());
			ymin=trim(((TObjString*)l->At(9))->GetString());
			ymax=trim(((TObjString*)l->At(10))->GetString());
		}

		Histogrammer *nh;
		if (class_name=="NhitsPlot") {
			nh=new NhitsPlot();
		} else if (class_name=="NhitsPerModulePlot") {
			nh=new NhitsPerModulePlot();
		}

		nh->setup_type(nhist.Atoi(),ndim.Atoi());
		if (ndim.Atoi()==1)
			nh->setup_histo(name,title,nbinsx.Atoi(),xmin.Atof(),xmax.Atof());
		else if (ndim.Atoi()==2)
			nh->setup_histo(name,title,nbinsx.Atoi(),xmin.Atof(),xmax.Atof(),nbinsy.Atoi(),ymin.Atof(),ymax.Atof());
		nh->initialize();
		e.add_histogrammer(nh);
	}
	e.event_loop();
	e.plot();
	e.finalize();
}

int main() {
	Main();
}

