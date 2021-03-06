#include "FlacDecoder.h"
#include <util/PluginHelper.h>

static const PluginInfo info = {
    "Yanhui Shen",
    "FLAC Decoder",
    "Decoder for FLAC audio.",
    1
};

MOUS_DEF_PLUGIN(PluginType::Decoder, &info, FlacDecoder);
