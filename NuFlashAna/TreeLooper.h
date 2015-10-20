/**
 * \file TreeLooper.h
 *
 * \ingroup NuFlashAna
 * 
 * \brief Class def header for a class TreeLooper
 *
 * @author kazuhiro
 */

/** \addtogroup NuFlashAna

    @{*/
#ifndef TREELOOPER_H
#define TREELOOPER_H

#include <iostream>
#include <TChain.h>
#include <TGraphErrors.h>
#include <vector>
#include <string>
#include <exception>
/**
   \class TreeLooper
   User defined class TreeLooper ... these comments are used to generate
   doxygen documentation!
 */
class TreeLooper{

public:

  /// Default constructor
  TreeLooper() : _ch(nullptr), _gDT(nullptr)
  {
    Reset("opflashfilter/opflash_opflash_tree");
  }

  /// Default destructor
  ~TreeLooper(){}

  void Reset(std::string treename)
  {
    if(_ch) delete _ch;
    _dt = _pe_total = -1;
    _event = _run = _subrun = 0;
    _ch = new TChain(treename.c_str(),"");
    _flash_count.clear();
    _min_dt = _max_dt = _bin_width = 0;
  }

  void SetBinning(double min, double max, size_t nbins)
  {
    if(max <= min || !nbins) throw std::exception();
    _flash_count.resize(nbins);
    _bin_width = (max - min) / (double(nbins));
  }

  void AddFile(std::string fname)
  {
    _ch->AddFile(fname.c_str());
  }

  void Analyze();
  
  TChain*       _ch;
  TGraphErrors* _gDT;
  double        _dt;
  double        _pe_total;
  unsigned int  _run, _subrun, _event;

  std::vector<double> _flash_count;
  double _min_dt;
  double _max_dt;
  double _bin_width;
  size_t _nbins;
  
};

#endif
/** @} */ // end of doxygen group 

