#include "Main.h"
#include "TCanvas.h"

class NhitHistogrammer: public Histogrammer {
	public:
		NhitHistogrammer();
		~NhitHistogrammer() {};
		void process_event(const vector<tophit> &hits);
		void finalize();
		void plot();
	private:
		TH1F *h_num_hits;
		vector<TH1F*> h_hits;
};

NhitHistogrammer::NhitHistogrammer() {
	h_num_hits=new TH1F("h_num_hits","h_num_hits",100,0,100);
	for (int i=0;i<16;i++) {
		TH1F *h=new TH1F(Form("h_%d", i+1), Form("nhits for slot %d", i+1),100,0,100);
		h_hits.push_back(h);
	}
}

void NhitHistogrammer::process_event(const vector<tophit> &hits) {
	int nhits=hits.size();
	if (nhits>0) h_num_hits->Fill(nhits);
	int slot_hits[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	for (int i=0;i<nhits;i++) {
		slot_hits[hits[i].slot_no-1]++;
	}
	for (int i=0;i<16;i++) {
		if (slot_hits[i]>0) h_hits[i]->Fill(slot_hits[i]);
	}
}

void NhitHistogrammer::finalize() {
	h_num_hits->Write();
	for (int i=0;i<16;i++) {
		h_hits[i]->Write();
	}
}

void NhitHistogrammer::plot() {
	TCanvas *c1=new TCanvas("C1_NhitHistogrammer","number of hits per event",800,600);
	h_num_hits->Draw();
	TCanvas *c2=new TCanvas("C2_NhitHistogrammer","number of hits per event for each module",800,600);
	c2->Divide(4,4);
	for (int i=1;i<=16;i++) {
		c2->cd(i);
		h_hits[i-1]->Draw();
	}
}

