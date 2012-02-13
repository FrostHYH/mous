#include "AacDecoder.h"
#include <mous/PluginHelper.h>

static const PluginInfo info = {
    "Yanhui Shen",
    "FAAD Decoder",
    "Decoder for mp4 audio.",
    1
};

MOUS_DEF_PLUGIN(MousDecoder, &info, IDecoder, AacDecoder);
