// ZmqSourcePlugin.cc
#include <JANA/JApplication.h>
#include <JANA/JEventSourceGeneratorT.h>

#include <edm4eic/EDM4eicVersion.h>
#include <TMath.h>
#include <edm4eic/unit_system.h>
#include <edm4hep/SimTrackerHit.h>
#include <Evaluator/DD4hepUnits.h>


#include "ZmqEventSource.h"

#include "extensions/jana/JOmniFactoryGeneratorT.h"
#include "factories/reco/LGADHitCalibration_factory.h"
#include "factories/tracking/LGADHitClustering_factory.h"


extern "C" {
void InitPlugin(JApplication* app) {
    InitJANAPlugin(app);

    using namespace eicrecon;

    app->Add(new JEventSourceGeneratorT<ZmqEventSource>());

    app->Add(new JOmniFactoryGeneratorT<LGADHitCalibration_factory>(
      "KumaTOFBarrelCalibratedHits", {"TOFBarrelADCTDC"},
      {"KumaTOFBarrelCalibratedHits"}, {}, app));
    app->Add(new JOmniFactoryGeneratorT<LGADHitClustering_factory>(
      "KumaTOFBarrelClusterHits", {"KumaTOFBarrelCalibratedHits"}, // Input data collection tags
      {"KumaTOFBarrelClusterHits"},                            // Output data tag
      {}, app));
    }
}