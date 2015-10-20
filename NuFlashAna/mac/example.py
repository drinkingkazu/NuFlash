import sys
from ROOT import gSystem
gSystem.Load("libNuFlash_NuFlashAna")
from ROOT import sample

try:

    print "PyROOT recognized your class %s" % str(sample)

except NameError:

    print "Failed importing NuFlashAna..."

sys.exit(0)

