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
#include "NhitsPerModulePlot.h"
#include "NhitsPerChannel.h"
#include "ADC_channel.h"
#include "ADCW_channel.h"
#include "TDC_channel.h"
#include "HitQuality.h"


class Experiment {
	public:
		Experiment(TString input, TString treename, TString output, int type);
		~Experiment() {};
		void add_histogrammer(Histogrammer *ht) { hts->Add(ht); }
		void event_loop(string dattyp);
		void good_hitB(const float adc, const float tdc, const float pulsewidth, const float flag, const float corrtime, int &htFLAG, string dattyp);
		void finalize();
		void plot();
	private:
		TList *hts;
		TString input;
		TString treename;
		TString output;
		int type;
		int histID;
};

Experiment::Experiment(TString input, TString treename, TString output, int type) {
	this->input=input;
	this->output=output;
	this->treename=treename;
	this->type=type;
	hts=new TList();
}

void Experiment::event_loop(string dattyp) {
	TChain *eventNtuple = new TChain(treename);
	eventNtuple->Add(input);

	float t_ADC[MAXHITS], t_PulseWidth[MAXHITS], t_TDC[MAXHITS], t_BarID[MAXHITS], t_ChannelID[MAXHITS],t_CorrTime[MAXHITS];
	int t_Flag[MAXHITS];
	int evt, nhits, hitflag, badhitscalefactor ;

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
	int badhitcount = 0;
	badhitscalefactor = 1;
	for (int i = 0; i< n_eventProcessed; i++) { 
//		cout << "Event_loop: begin event " << i <<  endl;
		if (i%1000==0) { std::cout << i << endl; }
		eventNtuple->GetEntry(i);
		vector<tophit> b_eventVector;     
		vector<tophit> b_eventVector_cosmic;     
		vector<tophit> b_eventVector_laser;     
		vector<tophit> b_eventVector_calpulse;     
		vector<tophit> b_badhitsVector;     
		for (int j = 0; j<nhits; j++) { 
			// cuts for topcaf hit
			good_hitB(t_ADC[j], t_TDC[j], t_PulseWidth[j], t_Flag[j], t_CorrTime[j], hitflag, dattyp) ;
// scale bad hits as necessary
			if(hitflag != 0) {
				badhitcount++;
				if(badhitcount==badhitscalefactor){
					badhitcount = 0;
				}
				else {
					continue;
				}
//				cout << badhitcount << endl;
			}
			tophit hit;
			hit.evt_no=evt;
			hit.slot_no=(int)t_BarID[j];
			hit.channel_id=(int)t_ChannelID[j];
			hit.flag=(int)t_Flag[j];
			hit.ADC=t_ADC[j];
			hit.TDC=t_TDC[j];
			hit.PulseWidth=t_PulseWidth[j];
			hit.CorrTime=t_CorrTime[j];
			hit.hitQFlag = hitflag;
			if(hitflag == 0) {
				b_eventVector.push_back(hit);
			}
			else {
				b_badhitsVector.push_back(hit);
			}
		}
		TIter next(hts);
		Histogrammer *ht;
		int histID = 0;
		int HTtype = -1;
		while ((ht = (Histogrammer *) next())) {
			ht-> getHitType(HTtype);
			if(HTtype==0){
					ht->process_event(b_eventVector);
				} else {
					ht->process_event(b_badhitsVector);
					}
		}
//	cout << "Event_loop: end event " << i << " " << b_eventVector[0].evt_no <<  endl;
	}
}


// cuts for topcaf hit
void Experiment::good_hitB(const float adc, const float tdc, const float pulsewidth, const float flag, const float corrtime, int &htFLAG, string dattyp) {
	htFLAG = 0;
	if (adc<100 || adc>2048) htFLAG=htFLAG+1 ;
	if (pulsewidth<3 || pulsewidth>10)  htFLAG=htFLAG+2;
	if (flag<=0)  htFLAG=htFLAG+4;
	if(dattyp=="cosmic") {
//		cout << dattyp << endl;
		if(tdc>-200) htFLAG=htFLAG+8;
		}
	else if(dattyp=="cal"){
//		cout << dattyp << endl;
		if(abs(tdc)>50)  htFLAG=htFLAG+8;
	}
	else if(dattyp=="laser"){
//		cout << dattyp << endl;
		if(tdc<-200 || abs(tdc)<50)  htFLAG=htFLAG+8;
	}
	else if(dattyp=="all"){
	}
//	if (corrtime==0)  htFLAG=htFLAG+8;
//	if(htFLAG != 0) cout << " " << htFLAG << endl;
	return;
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
	int histID = 0;
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

// Main - open data file(s), histogram steering file, initialize histograms
void Main() {
	string dattyp;
//	string datafiles = "run003424"; dattyp="all";
//	string datafiles = "run003830_laser"; dattyp="laser";
	string datafiles = "run003524_new"; dattyp="laser";
//	string datafiles = "run003524_cosmic"; dattyp="cosmic";
	Experiment e("./"+datafiles+"/*.root","topddt",datafiles+"_out.root",0);
	ifstream f("input.csv");
	string line;
	int histID = 0;
	while (getline(f,line)) {
		if (line[0]=='#') continue;
		TList *l=parse_csv(TString(line.c_str()));
		TString nhist,ndim,class_name,hit_type,name,title,nbinsx,xmin,xmax,nbinsy,ymin,ymax;
		nhist=trim(((TObjString*)l->At(0))->GetString());
		ndim=trim(((TObjString*)l->At(1))->GetString());
		class_name=trim(((TObjString*)l->At(2))->GetString());
		hit_type=trim(((TObjString*)l->At(3))->GetString());
		name=trim(((TObjString*)l->At(4))->GetString());
		title=trim(((TObjString*)l->At(5))->GetString());
		nbinsx=trim(((TObjString*)l->At(6))->GetString());
		xmin=trim(((TObjString*)l->At(7))->GetString());
		xmax=trim(((TObjString*)l->At(8))->GetString());
		if (ndim.Atoi()==2) {
			nbinsy=trim(((TObjString*)l->At(9))->GetString());
			ymin=trim(((TObjString*)l->At(10))->GetString());
			ymax=trim(((TObjString*)l->At(11))->GetString());
		}

		Histogrammer *nh;
		if (class_name=="NhitsPerModulePlot") {
			nh=new NhitsPerModulePlot();
		} else if (class_name=="HitQuality") {
			nh=new HitQuality();
		} else if (class_name=="NhitsPerChannel") {
			nh=new NhitsPerChannel();
		} else if (class_name=="ADC_channel") {
			nh=new ADC_channel();
		} else if (class_name=="ADCW_channel") {
			nh=new ADCW_channel();
		} else if (class_name=="TDC_channel") {
			nh=new TDC_channel();
		}

		cout << "Main: setup " <<  endl;
		nh->setup_type(nhist.Atoi(),ndim.Atoi(),hit_type.Atoi());
		if (ndim.Atoi()*nhist.Atoi()==1)
			nh->setup_histo(name,title,nbinsx.Atoi(),xmin.Atof(),xmax.Atof());
		else if (ndim.Atoi()*nhist.Atoi()==16)
				nh->setup_histo(name,title,nbinsx.Atoi(),xmin.Atof(),xmax.Atof(),16,0.,16.);
		else if (ndim.Atoi()==2)
nh->setup_histo(name,title,nbinsx.Atoi(),xmin.Atof(),xmax.Atof(),nbinsy.Atoi(),ymin.Atof(),ymax.Atof(),16,0.,16.);
		nh->initialize(histID);
		e.add_histogrammer(nh);
//		cout << "histID added " << histID << endl;
	}
//	cout << "Main: entering event loop " <<  endl;
	e.event_loop(dattyp);
//	e.plot();
	e.finalize();
}

int main() {
	Main();
}

