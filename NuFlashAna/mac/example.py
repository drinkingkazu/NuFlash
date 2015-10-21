import sys
import ROOT
from ROOT import gSystem,gStyle,TCanvas,TFile
gSystem.Load("libNuFlash_NuFlashAna")
from ROOT import TreeLooper

f=TFile.Open("out.root","RECREATE")
c=TCanvas("c","c",600,500)

t=TreeLooper()
t.SetBinning(0,20.8,26)
#for i in xrange(len(sys.argv)-1):
#    t.AddFile(sys.argv[i+1])
files = [x for x in open('files.txt','r').read().split() if x.endswith('.root')]
for r in files:
    t.AddFile(r)
t.SetRunRange(0,3458,0,1350)
t.Analyze()
c.cd()
t._gDT.SetMarkerStyle(20)
t._gDT.SetMarkerSize(1)
t._gDT.SetMarkerColor(ROOT.kBlue)
t._gDT.SetLineColor(ROOT.kBlue)
t._gDT.SetLineWidth(2)
t._gDT.Draw("AP")
c.Update()
sys.stdin.readline()

f.cd()
t._gDT.Write()
t._tree.Write()
f.Close()
