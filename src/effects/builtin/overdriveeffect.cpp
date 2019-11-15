#include "effects/builtin/overdriveeffect.h"

#include "util/sample.h"

// static
QString OverdriveEffect::getId() {
    return "org.mixxx.effects.overdrive";
}

// static
EffectManifestPointer OverdriveEffect::getManifest() {
    EffectManifestPointer pManifest(new EffectManifest());
    pManifest->setId(getId());
    pManifest->setName(QObject::tr("Overdrive"));
    pManifest->setShortName(QObject::tr("Overdrive"));
    pManifest->setAuthor("The Mixxx Team");
    pManifest->setVersion("1.0");
    pManifest->setDescription(QObject::tr(
        "Adds overdrive distortion by limiting the output value using tanh"));
    pManifest->setEffectRampsFromDry(true);
    pManifest->setMetaknobDefault(0.0);

    EffectManifestParameterPointer depth = pManifest->addParameter();
    depth->setId("gain");
    depth->setName(QObject::tr("Tanh pregain"));
    depth->setShortName(QObject::tr("Tanh pregain"));
    depth->setDescription(QObject::tr(
        "The gain with which the input signal is multiplied"));
    depth->setControlHint(EffectManifestParameter::ControlHint::KNOB_LOGARITHMIC);
    depth->setSemanticHint(EffectManifestParameter::SemanticHint::UNKNOWN);
    depth->setUnitsHint(EffectManifestParameter::UnitsHint::UNKNOWN);
    depth->setDefaultLinkType(EffectManifestParameter::LinkType::LINKED);
    depth->setDefaultLinkInversion(EffectManifestParameter::LinkInversion::INVERTED);
    depth->setNeutralPointOnScale(1.0);
    depth->setDefault(1.0);
    // we do not allow a 0 gain in case we need to /gain
    depth->setMinimum(0.1);
    depth->setMaximum(16);

    return pManifest;
}

OverdriveEffect::OverdriveEffect(EngineEffect* pEffect)
        : m_pGainParameter(pEffect->getParameterById("gain")) {
}

OverdriveEffect::~OverdriveEffect() {
    //qDebug() << debugString() << "destroyed";
}

void OverdriveEffect::processChannel(const ChannelHandle& handle,
                                      OverdriveGroupState* pState,
                                      const CSAMPLE* pInput, CSAMPLE* pOutput,
                                      const mixxx::EngineParameters& bufferParameters,
                                      const EffectEnableState enableState,
                                      const GroupFeatureState& groupFeatures) {
    Q_UNUSED(handle);
    Q_UNUSED(groupFeatures);
    Q_UNUSED(enableState); // no need to ramp, it's simple limiter

    const CSAMPLE gain = m_pGainParameter ?
            m_pGainParameter->value() : 1.0;

    for (unsigned int i = 0;
            i < bufferParameters.samplesPerBuffer();
            i += 1) {
	    // tanh already clamps, but we are probably going to add postgain
        pOutput[i] = SampleUtil::clampSample(tanh(pInput[i]*gain))
    }
}
