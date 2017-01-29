#include "Main.h"

class ADCW_channel: public Histogrammer {
	public:
		void process_event(const vector<tophit> &hits, int &hID);
};

void ADCW_channel::process_event(const vector<tophit> &hits, int &hID) {
	if (nhist!=16 || ndim!=2) return;
	int nhits=hits.size();
	int evtno, slotno, channelno, adcwidth;
//	cout << "ADCW_channel: nhits = " << nhits << endl;
	TH3F *h;
	h=(TH3F*)hlist.At(0);
	for (int i=0;i<nhits;i++) {
		evtno = hits[i].evt_no;
		adcwidth = hits[i].PulseWidth;
		slotno = hits[i].slot_no -1;
		channelno = hits[i].channel_id -1;
//		xbin = (hits[i].channel_id -1)%64;
//		ybin = (hits[i].channel_id -1)/64;
//		cout << "ADCW_channel: event = " << evtno << " hit no = " << i << endl;
//		cout << "ADCW_channel: slot/ch/adcW = " << slotno << ", " << channelno << ", "  << adcwidth << endl;
		h->Fill(channelno,adcwidth,slotno);
	}
}

