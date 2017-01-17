#include "TObject.h"
#include "TList.h"
#include "TH1.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TProfile.h"
#include "TCanvas.h"
#include <vector>
#include <iostream>

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
	int hitQFlag;
} tophit;


class Histogrammer: public TObject {
	public:
		Histogrammer() {};
		~Histogrammer() {};
		virtual void setup_type(int nhist, int ndim, int hit_type);
		virtual void setup_histo(TString name, TString title, int nbinsx, float xmin, float xmax);
		virtual void setup_histo(TString name, TString title, int nbinsx, float xmin, float xmax, int nbinsy, float ymin, float ymax);
		virtual void setup_histo(TString name, TString title, int nbinsx, float xmin, float xmax, int nbinsy, float ymin, float ymax, int nbinsz, float zmin, float zmax);
		virtual void initialize(int &hID);
		virtual void process_event(const vector<tophit> &hits, int &hID)=0;
		virtual void plot();
		virtual void getHitType(int &HTtype);
		virtual void finalize();
	protected:
		int nhist,ndim, hit_type;
		TString name, title;
		int nbinsx, xmin, xmax;
		int nbinsy, ymin, ymax;
		int nbinsz, zmin, zmax;
		TList hlist;
};

void Histogrammer::setup_type(int nhist, int ndim, int hit_type) {
	this->nhist=nhist;
	this->ndim=ndim;
	this->hit_type=hit_type;
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

void Histogrammer::setup_histo(TString name, TString title, int nbinsx, float xmin, float xmax, int nbinsy, float ymin, float ymax, int nbinsz, float zmin, float zmax) {
	this->name=name;
	this->title=title;
	this->nbinsx=nbinsx;
	this->xmin=xmin;
	this->xmax=xmax;
	this->nbinsy=nbinsy;
	this->ymin=ymin;
	this->ymax=ymax;
	this->nbinsz=nbinsz;
	this->zmin=zmin;
	this->zmax=zmax;
}

void Histogrammer::initialize(int &hID) {
// initialize histograms, 1-d and 2-d
	cout << nhist << " histograms initialized" << endl;
//	for (int i=0;i<nhist;i++) {
		TString t,v;
		t.Form("%d",hID);
//		v.Form("_%d",i);
		if (name == "hit_profile") {
//			cout << "histID = " << hID << " hit profile" << endl;
			TProfile *h0  = new TProfile(name+"_H"+t,title+"_H"+t,nbinsx,xmin,xmax, 0,300);
			hlist.Add(h0);
			int hNum= atol(h0->GetName());			
			cout << "hNum = " << hNum << endl;
		} else if (name=="ADC_channel") {
			TH3F *h3=new TH3F(name+"mean_H"+t,title+"mean_H"+t,nbinsx,xmin,xmax,nbinsy,ymin,ymax,nbinsz,zmin,zmax);
			cout << "2-d histID = " << hID << "nbinsZ "<< nbinsz << endl;
			hlist.Add(h3);			
		} else if (ndim*nhist==1) {
			TH1F *h1=new TH1F(name+"_H"+t,title+"_H"+t,nbinsx,xmin,xmax);
//			cout << "histID = " << hID << endl;
//			cout << "name = " << h1->GetName() << endl;
//			cout << "title = " << h1->GetTitle() << endl;
			hlist.Add(h1);
			int hNum= atol(h1->GetName());			
//			cout << "hNum = " << hNum << endl;
		} else if (ndim*nhist==16) {
			TH2F *h2=new TH2F(name+"_H"+t,title+"_H"+t,nbinsx,xmin,xmax,nbinsy,ymin,ymax);		
			hlist.Add(h2);
			cout << "initialized 1-d x 16, histID = " << hID << endl;
		} else if (ndim==2) {
			TH3F *h3=new TH3F(name+"_H"+t,title+"_H"+t,nbinsx,xmin,xmax,nbinsy,ymin,ymax,nbinsz,zmin,zmax);
			cout << "2-d histID = " << hID << "nbinsZ "<< nbinsz << endl;
			hlist.Add(h3);
		} else
			return;
		hID++;
//	}
}

void Histogrammer::plot() {
// set up canvas
//	TString prefix="c_";
	TObject *h;
	if(name == "hit_profile") {
		return;
	} else if (nhist*ndim==1) {
		TCanvas *c=new TCanvas(name, title, 800,600);
		h=(TH1*)hlist.At(0);
		h->Draw();
	} else if (nhist*ndim==16) {
		TCanvas *c=new TCanvas(name, title, 1200,1200);
		c->Divide(4,4);
		for (int i=0;i<16;i++) {
			c->cd(i+1);
			h=(TH2*)hlist.At(i);
			h->Draw();
		}
	} else return;
}

void Histogrammer::getHitType(int &HTtype) {
	HTtype = hit_type;
}

void Histogrammer::finalize() {
	cout << "Histogrammer: finalizing" << endl;
	TObject *h;
	if(name == "hit_profile") {
			h=(TProfile*)hlist.At(0);
		} else if (ndim*nhist==1) {
			h=(TH1F*)hlist.At(0);
		} else if (ndim*nhist==16) {
			h=(TH2F*)hlist.At(0);
		} else if (ndim==2) {
			h=(TH3F*)hlist.At(0);
		} else
			return;
	h->Write();
}
#endif
