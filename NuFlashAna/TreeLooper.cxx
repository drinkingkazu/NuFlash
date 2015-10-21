#ifndef TREELOOPER_CXX
#define TREELOOPER_CXX

#include "TreeLooper.h"
#include <cmath>
void TreeLooper::Analyze()
{
  long long nevents = _ch->GetEntries();

  std::cout<< "Looping over " << nevents << " events..."<<std::endl;
  if(nevents<=0) return;

  _ch->SetBranchAddress("dt",&_dt);
  _ch->SetBranchAddress("pe_total",&_pe_total);
  _ch->SetBranchAddress("run",&_run);
  _ch->SetBranchAddress("subrun",&_subrun);
  _ch->SetBranchAddress("event",&_event);

  _tree->Branch("run",&_run,"run/i");
  _tree->Branch("subrun",&_subrun,"subrun/i");
  _tree->Branch("event",&_event,"event/i");
  _tree->Branch("dt",&_dt,"dt/D");
  _tree->Branch("pe_total",&_pe_total,"pe_total/D");

  std::cout<<_min_dt<<" => "<<_max_dt<<" ... width "<<_bin_width<<std::endl;
  for(size_t i=0; i<nevents; ++i) {

    _ch->GetEntry(i);

    if(_run < _min_run || _max_run < _run) continue;

    if(_run == _min_run && _subrun < _min_subrun) continue;
    if(_run == _max_run && _max_subrun < _subrun) continue;

    if(_dt < _min_dt || _max_dt < _dt) continue;

    if(_pe_total < 50) continue;

    int bin_index = int((_dt - _min_dt)/_bin_width);

    _flash_count[bin_index] += 1;

    _tree->Fill();
  }

  std::vector<double> x_v, xerr_v, yerr_v;

  xerr_v.resize(_flash_count.size(),0);
  x_v.reserve(_flash_count.size());
  yerr_v.reserve(_flash_count.size());

  for(size_t i=0; i<_flash_count.size(); ++i) {

    x_v.push_back(_min_dt + i * _bin_width + _bin_width*0.5);
    yerr_v.push_back(sqrt(_flash_count[i]));

  }
  
  _gDT = new TGraphErrors(_flash_count.size(),&x_v[0],&_flash_count[0],&xerr_v[0],&yerr_v[0]);
  _gDT->SetName("gDT");

}

#endif
