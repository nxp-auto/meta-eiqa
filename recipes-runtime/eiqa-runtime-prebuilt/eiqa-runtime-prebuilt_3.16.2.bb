EIQA_RUNTIME_PREBUILT_TAR_PATH ?= "eIQAuto_S32N7_PRM_3.16.2.tar.gz"
EIQA_RUNTIME_PREBUILT_URL ??= ""

require eiqa-runtime-prebuilt-src.inc

SRC_URI[md5sum] = "f5f3600b24586ffe036877fef9b93f23"
SRC_URI[sha256sum] = "5b1906f69f062d67b9e59e5436c0fa5c04f21f33b7da01562bef5768b9ae3bc3"

require eiqa-runtime-prebuilt.inc

# 3.16.2 reorganised the archive.
EIQA_SRC_LIBDIR      = "${S}/a78/lib"
EIQA_SRC_INCDIR      = "${S}/a78/include"
EIQA_SRC_CARV_LIBDIR = "${S}/carv/lib"
EIQA_SRC_CARV_INCDIR = "${S}/carv/include"
