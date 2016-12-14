#include "Main.h"

class NhitsPlot: public Histogrammer {
	public:
		void process_event(const vector<tophit> &hits);
};

void NhitsPlot::process_event(const vector<tophit> &hits) {
	if (nhist!=1 || ndim!=1) return;
	int nhits=hits.size();
	if (nhits>0) {
		TH1F *h=(TH1F*)hlist.At(0);
		h->Fill(nhits);
	}
}

