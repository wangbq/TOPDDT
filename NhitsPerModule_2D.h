#include "Main.h"

class NhitsPerModule_2D: public Histogrammer {
	public:
		void process_event(const vector<tophit> &hits, int &hID);
};

void NhitsPerModule_2D::process_event(const vector<tophit> &hits, int &hID) {
	if (nhist!=16 || ndim!=2) return;
	int nhits=hits.size();
	int evtno, slotno, xbin, ybin;
//	cout << "NhitsPerModule_2D: nhits = " << nhits << endl;
	TH3F *h;
	h=(TH3F*)hlist.At(0);
	for (int i=0;i<nhits;i++) {
		evtno = hits[i].evt_no;
		slotno = hits[i].slot_no-1;
		xbin = (hits[i].channel_id -1)%64;
		ybin = (hits[i].channel_id -1)/64;
//		cout << "NhitsPerModule_2D: event = " << evtno << " hit no = " << i << endl;
//		cout << "NhitsPerModule_2D: slot/x/y = " << slotno << ", " << xbin << ", " << ybin << endl;
		h->Fill(xbin,ybin,slotno-.01);
	}
//	for (int i=0;i<16;i++) {
//		h=(TH2F*)hlist.At(hID);
//	cout << "NhitsPerModule_2D: hID = " << hID << endl;
//	hID++;
//	}
//	cout << "NhitsPerModule_2D: filled"  << endl;
}

