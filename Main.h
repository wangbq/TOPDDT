#include "TObject.h"
#include "TList.h"

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
		virtual void initiaize();
		virtual void process_event(const TList &hits)=0;
		virtual void plot();
		virtual void finalize();
	private:
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

virtual void Histogrammer::initiaize() {
	for (int i=0;i<nhist;i++) {
		TString t;
		t.Form("_%d",i)
		if (ndim==1) 
			TH1F *h=new TH1F(name+t,title,nbinsx,xmin,xmax);
		else if (ndim==2)
			TH2F *h=new TH2F(name+t,title,nbinsx,xmin,xmax,nbinsy,ymin,ymax);
		else
			return;
		hlist.Add(h);
	}
}

virtual void Histogrammer::plot() {
	TIter next(hlist);
	while ((TH1 *h = (TH1 *) next())) {
		h->Draw();
	}
}

virtual void Histogrammer::finalize() {
	TIter next(hlist);
	while ((TH1 *h = (TH1 *) next())) {
		h->Write();
	}
}

#endif
