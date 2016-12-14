#include "TObject.h"
#include "TList.h"
#include "TH1.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TCanvas.h"
#include <vector>

#ifndef MAIN_H
#define MAIN_H

#define MAXHITS 32000

using namespace std;

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


class Histogrammer: public TObject {
	public:
		Histogrammer() {};
		~Histogrammer() {};
		virtual void setup_type(int nhist, int ndim);
		virtual void setup_histo(TString name, TString title, int nbinsx, float xmin, float xmax);
		virtual void setup_histo(TString name, TString title, int nbinsx, float xmin, float xmax, int nbinsy, float ymin, float ymax);
		virtual void initialize();
		virtual void process_event(const vector<tophit> &hits)=0;
		virtual void plot();
		virtual void finalize();
	protected:
		int nhist,ndim;
		TString name, title;
		int nbinsx, xmin, xmax;
		int nbinsy, ymin, ymax;
		TList hlist;
};

void Histogrammer::setup_type(int nhist, int ndim) {
	this->nhist=nhist;
	this->ndim=ndim;
}

void Histogrammer::setup_histo(TString name, TString title, int nbinsx, float xmin, float xmax) {
	this->name=name;
	this->title=title;
	this->nbinsx=nbinsx;
	this->xmin=xmin;
	this->xmax=xmax;
}

void Histogrammer::setup_histo(TString name, TString title, int nbinsx, float xmin, float xmax, int nbinsy, float ymin, float ymax) {
	this->name=name;
	this->title=title;
	this->nbinsx=nbinsx;
	this->xmin=xmin;
	this->xmax=xmax;
	this->nbinsy=nbinsy;
	this->ymin=ymin;
	this->ymax=ymax;
}

void Histogrammer::initialize() {
	for (int i=0;i<nhist;i++) {
		TString t;
		t.Form("_%d",i);
		if (ndim==1) {
			TH1F *h1=new TH1F(name+t,title,nbinsx,xmin,xmax);
			hlist.Add(h1);
		} else if (ndim==2) {
			TH2F *h2=new TH2F(name+t,title,nbinsx,xmin,xmax,nbinsy,ymin,ymax);
			hlist.Add(h2);
		} else
			return;
	}
}

void Histogrammer::plot() {
	TString prefix="c_";
	TH1 *h;
	if (nhist==1) {
		TCanvas *c=new TCanvas(name, title, 800,600);
		h=(TH1*)hlist.At(0);
		h->Draw();
	} else if (nhist==16) {
		TCanvas *c=new TCanvas(name, title, 1200,1200);
		c->Divide(4,4);
		for (int i=0;i<16;i++) {
			c->cd(i+1);
			h=(TH1*)hlist.At(i);
			h->Draw();
		}
	} else return;
}

void Histogrammer::finalize() {
	TIter next(&hlist);
	TH1 *h;
	while ((h = (TH1 *) next())) {
		h->Write();
	}
}

#endif
