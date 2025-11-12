EIQA_RUNTIME_PREBUILT_TAR_PATH ?= "eIQAuto_S32N7_PRM_3.14.0_CD4_EngBuild1.tar.gz"
EIQA_RUNTIME_PREBUILT_URL ??= ""

require eiqa-runtime-prebuilt-src.inc

SRC_URI[md5sum] = "68133f3c2f2fe8e3f2cff71b29b99e67"
SRC_URI[sha256sum] = "28fc688f3fa1322f5a8c0d00931c9aa62166f1407fab62af80c32518696b7e5e"

require eiqa-runtime-prebuilt.inc
