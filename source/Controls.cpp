#include "Controls.h"
#include <functional>

using namespace SimpleRack;
using namespace daisy;

////////////// SIMPLE X DAISY PINOUT CHEATSHEET ///////////////

// 3v3           29  |       |   20    AGND
// D15 / A0      30  |       |   19    OUT 01
// D16 / A1      31  |       |   18    OUT 00
// D17 / A2      32  |       |   17    IN 01
// D18 / A3      33  |       |   16    IN 00
// D19 / A4      34  |       |   15    D14
// D20 / A5      35  |       |   14    D13
// D21 / A6      36  |       |   13    D12
// D22 / A7 DAC1 37  |       |   12    D11
// D23 / A8 DAC2 38  |       |   11    D10
// D24 / A9      39  |       |   10    D9
// D25 / A10     40  |       |   09    D8
// D26           41  |       |   08    D7
// D27           42  |       |   07    D6
// D28 / A11     43  |       |   06    D5
// D29           44  |       |   05    D4
// D30           45  |       |   04    D3
// 3v3 Digital   46  |       |   03    D2
// VIN           47  |       |   02    D1
// DGND          48  |       |   01    D0

// TODO: Add footprint numbers to these

static constexpr daisy::Pin kOutputVolumeAdcPin = daisy::seed::A0;  // 30
static constexpr daisy::Pin kOutputVolumeCvPin = daisy::seed::A1;   // 31

void Controls::Init(DaisySeed& hw, Engine& engine) {
  params_.Init(hw.AudioSampleRate() / hw.AudioBlockSize());
  // CVRegistry doesn't need Init() - it works at audio rate without smoothing
  // del_sw_.Init(static_cast<Pin>(kDelaySwitchPin), 1000.0f,
  // Switch::TYPE_TOGGLE,
  //              Switch::POLARITY_INVERTED, GPIO::Pull::PULLUP);
  initADCs(hw);
  registerParams(engine);
}

void Controls::UpdateParameter(DaisySeed& hw) {
  params_.UpdateNormalized(Parameter::OutputVolume, hw.adc.GetFloat(0));
}

void Controls::initADCs(DaisySeed& hw) {
  AdcChannelConfig config[kNumAdcChannels];
  config[0].InitSingle(kOutputVolumeAdcPin);

  hw.adc.Init(config, kNumAdcChannels);
  hw.adc.Start();
}

void Controls::registerParams(Engine& engine) {
  using namespace std::placeholders;

  params_.Register(Parameter::OutputVolume, 0.5f, 0.0f, 1.0f,
                   std::bind(&Engine::SetOutputLevel, &engine, _1),
                   0.0f,  // smoothing
                   daisysp::Mapping::EXP);
}