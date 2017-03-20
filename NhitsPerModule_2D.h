#include "Main.h"

class NhitsPerModule_2D: public Histogrammer {
	public:
		void process_event(const vector<tophit> &hits);
};

void NhitsPerModule_2D::process_event(const vector<tophit> &hits) {
	if (nhist!=16 || ndim!=2) return;
	int nhits=hits.size();
	int evtno, slotno, xbin, ybin;
	TH3F *h;
	h=(TH3F*)hlist.At(0);
	for (int i=0;i<nhits;i++) {
		evtno = hits[i].evt_no;
		slotno = hits[i].slot_no-1;
		xbin = (hits[i].channel_id -1)%64;
		ybin = (hits[i].channel_id -1)/64;
		h->Fill(xbin,ybin,slotno-.01);
	}
}

