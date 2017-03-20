#include "Main.h"

class ADCW_channel: public Histogrammer {
	public:
		void process_event(const vector<tophit> &hits);
};

void ADCW_channel::process_event(const vector<tophit> &hits) {
	if (nhist!=16 || ndim!=2) return;
	int nhits=hits.size();
	int evtno, slotno, channelno, adcwidth;
	TH3F *h;
	h=(TH3F*)hlist.At(0);
	for (int i=0;i<nhits;i++) {
		evtno = hits[i].evt_no;
		adcwidth = hits[i].PulseWidth;
		slotno = hits[i].slot_no -1;
		channelno = hits[i].channel_id -1;
		h->Fill(channelno,adcwidth,slotno);
	}
}

