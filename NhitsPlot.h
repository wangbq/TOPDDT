#include "Main.h"

class NhitsPlot: public Histogrammer {
	public:
		NhitsPlot() {};
		~NhitsPlot() {};
		void process_event(const TList &hits);
};

void NhitsPlot::process_event(const TList &hits) {
	if (nhist!=1 || ndim!=1) return;
	int nhits=hits.Capacity();
	if (nhits>0) hlist.At(0)->Fill(nhits);
}

