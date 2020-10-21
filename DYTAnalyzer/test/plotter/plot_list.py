# coding: utf-8
import sys
oldargv = sys.argv[:]
sys.argv = [ '-b-' ]
import ROOT
ROOT.gROOT.SetBatch(True)
sys.argv = oldargv

ROOT.gROOT.ProcessLine( "gErrorIgnoreLevel = 1001;")


def createRatio(h1, h2):
     h3 = h1.Clone("h3")
     h3.SetLineColor(ROOT.kBlack)
     h3.SetMarkerColor(1)
     h3.SetMarkerStyle(9)
     h3.SetMarkerSize(0.8)
     h3.SetTitle("")
     h3.SetMinimum(0.8)
     h3.SetMaximum(1.35)
     # Set up plot for markers and errors
     h3.Sumw2()
     h3.SetStats(0)
     h3.Divide(h2)
 
     # Adjust y-axis settings
     y = h3.GetYaxis()
     y.SetTitle("#frac{new DyT}{old DyT}")
     y.SetNdivisions(505)
     y.SetTitleSize(20)
     y.SetTitleFont(43)
     y.SetTitleOffset(1.55)
     y.SetLabelFont(43)
     y.SetLabelSize(15)
 
     # Adjust x-axis settings
     x = h3.GetXaxis()
     x.SetTitleSize(20)
     x.SetTitleFont(43)
     x.SetTitleOffset(4.0)
     x.SetLabelFont(43)
     x.SetLabelSize(15)
 
     return h3
 
 
def createCanvasPads():
    c = ROOT.TCanvas("c", "canvas", 800, 800)
    # Upper histogram plot is pad1
    pad1 = ROOT.TPad("pad1", "pad1", 0, 0.3, 1, 1.0)
    pad1.SetBottomMargin(0)  # joins upper and lower plot
    pad1.SetGridx()
    pad1.Draw()
    # Lower ratio plot is pad2
    c.cd()  # returns to main canvas before defining pad2
    pad2 = ROOT.TPad("pad2", "pad2", 0, 0.05, 1, 0.3)
    pad2.SetTopMargin(0)  # joins upper and lower plot
    pad2.SetBottomMargin(0.2)
    pad2.SetGridx()
    pad2.SetGridy()
    pad2.Draw()

    return c, pad1, pad2

 

old = ROOT.TFile('output_oldDyT.root')
new = ROOT.TFile('output_newDyT.root')
lisfOfFile = new.GetListOfKeys()
lisfOfFile
for item in lisfOfFile:
    print item
    
directory = new.GetDirectory('demo')
directory
print directory
listOfKeyInDir = directory.GetListOfKeys()
    
histosList = []
for item in listOfKeyInDir:
    #print item.GetClassName()
    #print item.GetName()
    histosList.append(item.GetName())
    
for num, histo in enumerate(histosList):
#    sys.stdout.write("Processing: %d / %d"%(num,len(histosList)) )
#    sys.stdout.flush()

    leg = ROOT.TLegend(0.,0.9,0.2,1.)
    new_h = new.Get('demo/'+histo)
    old_h = old.Get('demo/'+histo)
    if histo.find('_eta') > -1 or histo.find('_phi') > -1:
        new_h.Rebin(10)
        old_h.Rebin(10)
    if (histo.find('_pt') > -1 and histo.find('Pull') == -1) or (histo.find('_p') > -1 and histo.find('_phi') == -1 )or histo.find('ResInv') > -1 or histo.find('Chi2') > -1 or histo.find('_sp') > -1:
        new_h.Rebin(50)
        old_h.Rebin(50)
    if histo.find('Pull') > -1:
        new_h.Rebin(25)
        old_h.Rebin(25)
    ratio = createRatio(new_h, old_h)
    c1, pad1, pad2 = createCanvasPads()
    new_h.SetStats(0)
    new_h.SetLineColor(ROOT.kRed)
    new_h.SetLineWidth(2)
    old_h.SetLineColor(ROOT.kBlue)
    old_h.SetLineWidth(2)

    pad1.cd()
    new_h.Draw()
    old_h.Draw("Same")
    pad2.cd()
    ratio.Draw()
    c1.cd()
    leg.AddEntry(new_h, 'New DyT', 'l')
    leg.AddEntry(old_h, 'Old DyT', 'l')
    leg.Draw()
    if num == 0:
        c1.Print("DyT_comparison.pdf(" ,"Title:"+new_h.GetName())
    else:
        c1.Print("DyT_comparison.pdf" ,"Title:"+new_h.GetName())


c1.Print( "DyT_comparison.pdf)" ,"pdf")
