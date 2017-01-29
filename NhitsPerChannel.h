#include "Main.h"

class NhitsPerChannel: public Histogrammer {
	public:
		void process_event(const vector<tophit> &hits, int &hID);
};

void NhitsPerChannel::process_event(const vector<tophit> &hits, int &hID) {
	if (nhist!=16 || ndim!=1) return;
	int nhits=hits.size();
	int evtno, slotno, channelno;
//	cout << "NhitsPerChannel: nhits = " << nhits << endl;
	TH2F *h;
	h=(TH2F*)hlist.At(0);
	for (int i=0;i<nhits;i++) {
		evtno = hits[i].evt_no;
		slotno = hits[i].slot_no-1;
		channelno = hits[i].channel_id -1;
//		xbin = (hits[i].channel_id -1)%64;
//		ybin = (hits[i].channel_id -1)/64;
//		cout << "NhitsPerChannel: event = " << evtno << " hit no = " << i << endl;
//		cout << "NhitsPerChannel: slot/channel = " << slotno << ", " << channelno << endl;
		h->Fill(channelno,slotno);
	}
//	for (int i=0;i<16;i++) {
//		h=(TH2F*)hlist.At(hID);
//	cout << "NhitsPerChannel: hID = " << hID << endl;
//	hID++;
//	}
//	cout << "NhitsPerChannel: filled"  << endl;
}

