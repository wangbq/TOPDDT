#include <vector>
#include <string>

#ifndef MAIN_H
#define MAIN_H

#define MAXHITS 32000

using namespace std;

typedef struct {
	int evt_no;
	int slot_no;
	int channel_id;
	int flag;
	float ADC;
	float TDC;
	float PulseWidth;
	float CorrTime;
} tophit; 


class Histogrammer {
	public:
		Histogrammer() {};
		~Histogrammer() {};
		void process_event(const vector<tophit> &hits) {};
		void finalize() {};
		void plot() {};
};

class Experiment {
	public:
		Experiment(string input, string treename, string output, int type);
		~Experiment() {};
		void add_histogrammer(Histogrammer *ht) { hts.append(ht); };
		void event_loop();
		void finalize();
		void plot();
	private:
		vector<Histogrammer*> hts;
		string t_input;
		string t_treename;
		string t_output;
		int t_type;
};

#endif