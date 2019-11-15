#ifndef OVERDRIVEEFFECT_H
#define OVERDRIVEEFFECT_H

#include <QMap>

#include "effects/effect.h"
#include "effects/effectprocessor.h"
#include "engine/effects/engineeffect.h"
#include "engine/effects/engineeffectparameter.h"
#include "util/class.h"
#include "util/types.h"

struct OverdriveGroupState : public EffectState {
    // Default accumulator to 1 so we immediately pick an input value.
    OverdriveGroupState(const mixxx::EngineParameters& bufferParameters)
            : EffectState(bufferParameters) /*,
              hold_l(0),
              hold_r(0),
              accumulator(1)*/ {
    }
    //CSAMPLE hold_l, hold_r;
    // Accumulated fractions of a samplerate period.
    //CSAMPLE accumulator;
};

class OverdriveEffect : public EffectProcessorImpl<OverdriveGroupState> {
  public:
    OverdriveEffect(EngineEffect* pEffect);
    virtual ~OverdriveEffect();

    static QString getId();
    static EffectManifestPointer getManifest();

    // See effectprocessor.h
    void processChannel(const ChannelHandle& handle,
                        OverdriveGroupState* pState,
                        const CSAMPLE* pInput, CSAMPLE *pOutput,
                        const mixxx::EngineParameters& bufferParameters,
                        const EffectEnableState enableState,
                        const GroupFeatureState& groupFeatureState);

  private:
    QString debugString() const {
        return getId();
    }

    EngineEffectParameter* m_pGainParameter;

    DISALLOW_COPY_AND_ASSIGN(OverdriveEffect);
};

#endif /* OVERDRIVEEFFECT_H */
