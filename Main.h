#include "TObject.h"
#include "TList.h"
#include "TH1.h"

#ifndef MAIN_H
#define MAIN_H

#define MAXHITS 32000

using namespace std;

class TopHit: public TObject {
	public:
		int evt_no;
		int slot_no;
		int channel_id;
		int flag;
		float ADC;
		float TDC;
		float PulseWidth;
		float CorrTime;
};


class Histogrammer: public TObject {
	public:
		Histogrammer() {};
		~Histogrammer() {};
		virtual void setup_type(int nhist, int ndim);
		virtual void setup_histo(TString name, TString title, int nbinsx, float xmin, float xmax);
		virtual void setup_histo(TString name, TString title, int nbinsx, float xmin, float xmax, int nbinsy, float ymin, float ymax);
		virtual void initialize();
		virtual void process_event(const TList &hits)=0;
		virtual void plot();
		virtual void finalize();
	protected:
		int nhist,ndim;
		TString name, title;
		int nbinsx, xmin, xmax;
		int nbinsy, ymin, ymax;
		TList hlist;
};

virtual void Histogrammer::setup_type(int nhist, int ndim) {
	this->nhist=nhist;
	this->ndim=ndim;
}

virtual void Histogrammer::setup_histo(TString name, TString title, int nbinsx, float xmin, float xmax) {
	this->name=name;
	this->title=title;
	this->nbinsx=nbinsx;
	this->xmin=xmin;
	this->xmax=xmax;
}

virtual void Histogrammer::setup_histo(TString name, TString title, int nbinsx, float xmin, float xmax, int nbinsy, float ymin, float ymax) {
	this->name=name;
	this->title=title;
	this->nbinsx=nbinsx;
	this->xmin=xmin;
	this->xmax=xmax;
	this->nbinsy=nbinsy;
	this->ymin=ymin;
	this->ymax=ymax;
}

virtual void Histogrammer::initialize() {
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

virtual void Histogrammer::plot() {
	TIter next(&hlist);
	TH1 *h;
	while ((h = (TH1 *) next())) {
		h->Draw();
	}
}

virtual void Histogrammer::finalize() {
	TIter next(&hlist);
	TH1 *h;
	while ((h = (TH1 *) next())) {
		h->Write();
	}
}

#endif
