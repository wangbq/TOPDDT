#include "Main.h"

class HitQuality: public Histogrammer {
	public:
		void process_event(const vector<tophit> &hits);
};

void HitQuality::process_event(const vector<tophit> &hits) {
	//******************************************************************** ACR
	int activeevent[16] = {0}; // //**************************************************** ACR
	if (nhist!=16 || ndim!=1) return;
	int nhits=hits.size();
	TH2F *h;
	h=(TH2F*)hlist.At(0);
	for (int i=0;i<nhits;i++) {
		h->Fill(hits[i].hitQFlag,hits[i].slot_no-1);
	}
}

