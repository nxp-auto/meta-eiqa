EIQA_RUNTIME_PREBUILT_TAR_PATH ?= "eIQAuto_S32N7_PRM_3.17.1.tar.gz"
EIQA_RUNTIME_PREBUILT_URL ??= ""

require eiqa-runtime-prebuilt-src.inc

SRC_URI[md5sum] = "ec0faa86d480cf3d7ae007e833923519"
SRC_URI[sha256sum] = "6164613542de7f2a628a27ddad07a23594f1cb04963149a47e9b684aebc8b771"

require eiqa-runtime-prebuilt.inc
