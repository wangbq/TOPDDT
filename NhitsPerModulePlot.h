#include "Main.h"

class NhitsPerModulePlot: public Histogrammer {
	public:
		void process_event(const vector<tophit> &hits);
};

void NhitsPerModulePlot::process_event(const vector<tophit> &hits) {
	if (nhist!=16 || ndim!=1) return;
	int nhits=hits.size();
	int slot_hits[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	for (int i=0;i<nhits;i++) {
		slot_hits[hits[i].slot_no-1]++;
	}
	TH1F *h;
	for (int i=0;i<16;i++) {
		h=(TH1F*)hlist.At(i);
		if (slot_hits[i]>0) h->Fill(slot_hits[i]);
	}
}

