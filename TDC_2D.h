#include "Main.h"

class TDC_2D: public Histogrammer {
	public:
		void process_event(const vector<tophit> &hits);
};

void TDC_2D::process_event(const vector<tophit> &hits) {
	if (nhist!=16 || ndim!=2) return;
	int nhits=hits.size();
	int evtno, slotno, xbin, ybin, tdcvalue;
	TH3F *h;
	h=(TH3F*)hlist.At(0);
	for (int i=0;i<nhits;i++) {
		evtno = hits[i].evt_no;
		tdcvalue = hits[i].TDC;
		slotno = hits[i].slot_no-1;
		xbin = (hits[i].channel_id -1)%64;
		ybin = (hits[i].channel_id -1)/64;
		if (evtno%500==0) {
		}
		h->Fill(xbin,ybin,slotno-.01,tdcvalue);
	}
}

