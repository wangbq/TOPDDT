#include "Main.h"

class HitQuality: public Histogrammer {
	public:
		void process_event(const vector<tophit> &hits, int &hID);
};

void HitQuality::process_event(const vector<tophit> &hits, int &hID) {
//******************************************************************** ACR
	int activeevent[16] = {0}; // //**************************************************** ACR
//	cout << "HitQuality: hID = " << hID << endl;
	if (nhist!=16 || ndim!=1) return;
	int nhits=hits.size();
	TH2F *h;
	h=(TH2F*)hlist.At(0);
	for (int i=0;i<nhits;i++) {
		h->Fill(hits[i].hitQFlag,hits[i].slot_no-1);
//	cout << "HitQuality: fill hist " << hID <<  endl;

		}
//	cout << "HitQuality: end event " << hits[0].evt_no <<  endl;
	hID++;
}

