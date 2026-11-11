// Research Project: Hadronic Cosmic Ray Showers
// Principal Investigator: Ashmi A. Chamoli
// Date: May 3,2026
// Objective: Simulating 13 Tev Proton -Nitrogen imteractions to investigate muons in UHECR atmospheric showers.

#include "Pythia8/Pythia.h"
using namespace Pythia8;
int main() {
  // Generating values.
  Pythia pythia;
  pythia.readString("Beams:eCM = 13000.");
  pythia.readString("Beams:idA = 2212");
  pythia.readString("Beams:idB = 1000070140");
  pythia.readString("HeavyIon:mode = 1");
  pythia.readString("HadronLevel:Rescatter = on");
  // Initialise simulation.
  if (!pythia.init()) return 1;
  Hist mult("charged multiplicity", 100, -0.5, 799.5);
  // Begin event loop.
  for (int iEvent = 0; iEvent < 5000; ++iEvent) {
    if (!pythia.next()) continue;
    // Find number of all final charged particles and fill histogram.
    int nCharged = 0;
    for (int i = 0; i < pythia.event.size(); ++i)
      if (pythia.event[i].isFinal() && pythia.event[i].isCharged())
        ++nCharged;
    mult.fill( nCharged );
  // End of event loop.
  }
  pythia.stat();
  cout << mult;
  return 0;
}
