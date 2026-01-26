EIQA_RUNTIME_PREBUILT_TAR_PATH ?= "eIQAuto_S32N7_PRM_3.15.0.tar.gz"
EIQA_RUNTIME_PREBUILT_URL ??= ""

require eiqa-runtime-prebuilt-src.inc

SRC_URI[md5sum] = "ea330edfe7ac2c9f57777620930f49d5"
SRC_URI[sha256sum] = "47a338cff4745c04f5dc955f33f568243ac46ad4ac5251c84ecb14d9665bccf7"

require eiqa-runtime-prebuilt.inc
