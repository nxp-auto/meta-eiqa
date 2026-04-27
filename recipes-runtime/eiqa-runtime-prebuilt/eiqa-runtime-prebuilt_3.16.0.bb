EIQA_RUNTIME_PREBUILT_TAR_PATH ?= "eIQAuto_S32N7_PRM_3.16.0.tar.gz"
EIQA_RUNTIME_PREBUILT_URL ??= ""

require eiqa-runtime-prebuilt-src.inc

SRC_URI[md5sum] = "1e5a16c388011e9d8914f8c18008975e"
SRC_URI[sha256sum] = "ca68187c9c2797cf5ee123a18850d332848664ea75351b1ba9c5d0db6e119091"

require eiqa-runtime-prebuilt.inc
