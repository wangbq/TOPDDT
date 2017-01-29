#include "Main.h"

class NhitsPerModulePlot: public Histogrammer {
	public:
		int sum[16], sumsq[16], nevents[16]; // ****************************************** ACR
	// nevents is non-empty events, each module
		double sd[16], mean[16], meansq[16]; // ****************************************** ACR
		void process_event(const vector<tophit> &hits, int &hID);
};

void NhitsPerModulePlot::process_event(const vector<tophit> &hits, int &hID) {
//******************************************************************** ACR
	int activeevent[16] = {0}; // //**************************************************** ACR
//	cout << "NhitsPerModulePlot: hID = " << hID << endl;
	if (nhist!=16 || ndim!=1) return;
	int nhits=hits.size();
	int slot_hits[16]={0};
	TH2F *h;
	h=(TH2F*)hlist.At(0);
	for (int i=0;i<nhits;i++) {
		slot_hits[hits[i].slot_no-1]++;
	}
	for (int i=0;i<16;i++) {
		if (slot_hits[i]>0) {
			h->Fill(slot_hits[i],i);
//	cout << "NhitsPerModulePlot: fill hist " << hID <<  endl;
			// ****************************************************** Begin ACR Code Block 
			if (activeevent[i] == 0) { // change active event to 1 and increment nevents
				activeevent[i] = 1;
				nevents[i]++ ;
				}
//	cout << "NhitsperModulePlot: nevents = "<< nevents[i] << endl;
			sum[i] += slot_hits[i];
			sumsq[i] += slot_hits[i] * slot_hits[i] ;
			if (nevents[i]!=0) {
				mean[i] = ((double) sum[i]) / nevents[i];
				meansq[i] = ((double) sumsq[i]) / nevents[i];
			} else {
				mean[i] = 0;
				meansq[i] = 0;
			}
			sd[i] = sqrt( meansq[i] - mean[i] * mean[i] );
			// ******************************************************** End ACR Code Block
		}
	}
//	cout << "NhitsperModulePlot: end event " << hits[0].evt_no <<  endl;
	hID++;
}

