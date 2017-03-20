#include "Main.h"

class NhitsPerChannel: public Histogrammer {
	public:
		void process_event(const vector<tophit> &hits);
};

void NhitsPerChannel::process_event(const vector<tophit> &hits) {
	if (nhist!=16 || ndim!=1) return;
	int nhits=hits.size();
	int evtno, slotno, channelno;
	TH2F *h;
	h=(TH2F*)hlist.At(0);
	for (int i=0;i<nhits;i++) {
		evtno = hits[i].evt_no;
		slotno = hits[i].slot_no-1;
		channelno = hits[i].channel_id -1;
		h->Fill(channelno,slotno);
	}
}

