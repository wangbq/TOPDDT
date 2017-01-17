#include "Main.h"


// https://root.cern.ch/doc/master/classTProfile.html
class NhitsProfile: public Histogrammer {
	public:
		int sum[16], sumsq[16], nevents[16]; // ****************************************** ACR
	// nevents is non-empty events, each module
		double sd[16], mean[16], meansq[16]; // ****************************************** ACR
		void process_event(const vector<tophit> &hits, int &hID);
};

void NhitsProfile::process_event(const vector<tophit> &hits, int &hID) {
	if (nhist!=1 || ndim!=1) return;
	int nhits=hits.size();
//	cout << "NhitsPlot: nhits = " << nhits << endl;
//	cout << "NhitsPlot: hID = " << hID << endl;
	int slot_hits[16]={0};
	for (int i=0;i<nhits;i++) {
		slot_hits[hits[i].slot_no -1]++;
	}
	for (int i=0;i<16;i++) {
		if (slot_hits[i]>0) {
//			cout << "NhitsProfile: nhits = " << nhits << endl;
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
			nevents[i]++ ;
			if (nevents[i]==500) {
//				cout << "500 events, i="<<i<<",mean="<<mean[i]<< endl;
			}
		}
	}

	if (nhits>0) {
		TProfile *h=(TProfile*)hlist.At(0);
		for (int i=0;i<16;i++) {
			if (slot_hits[i]>0) {
				h->Fill(i+.01,slot_hits[i],1);
			}
		}
//		cout << "NhitsPlot: fill hist " << hID <<  endl;
	}
	hID++;
}

