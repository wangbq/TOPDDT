#include "Main.h"

class ADC_channel: public Histogrammer {
	public:
		void process_event(const vector<tophit> &hits, int &hID);
};

void ADC_channel::process_event(const vector<tophit> &hits, int &hID) {
	if (nhist!=16 || ndim!=2) return;
	int nhits=hits.size();
	int evtno, slotno, channelno, adcvalue;
//	cout << "ADC_channel: nhits = " << nhits << endl;
	TH3F *h;
	h=(TH3F*)hlist.At(0);
	for (int i=0;i<nhits;i++) {
		evtno = hits[i].evt_no;
		adcvalue = hits[i].ADC;
		slotno = hits[i].slot_no -1;
		channelno = hits[i].channel_id -1;
//		xbin = (hits[i].channel_id -1)%64;
//		ybin = (hits[i].channel_id -1)/64;
//		cout << "ADC_channel: event = " << evtno << " hit no = " << i << endl;
//		cout << "ADC_channel: slot/ch/adc = " << slotno << ", " << channelno << ", "  << adcvalue << endl;
		h->Fill(channelno,adcvalue,slotno);
	}
}

