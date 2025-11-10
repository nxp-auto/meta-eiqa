EIQA_RUNTIME_PREBUILT_TAR_PATH ?= "eIQAuto_S32N7_PRM_3.14.0_CD4_EngBuild0.tar.gz"
EIQA_RUNTIME_PREBUILT_URL ??= ""

require eiqa-runtime-prebuilt-src.inc

SRC_URI[md5sum] = "36d9e9b5a631ed8816b84d37bdfefc71"
SRC_URI[sha256sum] = "f1360ddf1f29fff9c644ec29ee1638221b9b8fb675339fa746ec694d75e3fd02"

require eiqa-runtime-prebuilt.inc
