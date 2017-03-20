#include "Main.h"

class ADC_channel: public Histogrammer {
	public:
		void process_event(const vector<tophit> &hits);
};

void ADC_channel::process_event(const vector<tophit> &hits) {
	if (nhist!=16 || ndim!=2) return;
	int nhits=hits.size();
	int evtno, slotno, channelno, adcvalue;
	TH3F *h;
	h=(TH3F*)hlist.At(0);
	for (int i=0;i<nhits;i++) {
		evtno = hits[i].evt_no;
		adcvalue = hits[i].ADC;
		slotno = hits[i].slot_no -1;
		channelno = hits[i].channel_id -1;
		h->Fill(channelno,adcvalue,slotno);
	}
}

