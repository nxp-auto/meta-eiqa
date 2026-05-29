SUMMARY = "llama.cpp"
DESCRIPTION = "LLM inference in C/C++"

# Commit from 17 June 2026
SRCREV = "8086439a4cea94c71a5dfb8fe4ad1546aebd640f"

S = "${WORKDIR}/git"

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${S}/LICENSE;md5=223b26b3c1143120c87e2b13111d3e99"

SRC_URI = "\
    git://github.com/ggml-org/llama.cpp.git;protocol=https;branch=master \
"

DEPENDS = " openssl"

CPU_ARM_ARCH = ""
CPU_ARM_ARCH:s32n79sim = "armv8.2-a+dotprod+fp16"
CPU_ARM_ARCH:s32n79rdb = "armv8.2-a+dotprod+fp16"
CPU_ARM_ARCH:append = "${@bb.utils.contains('TUNE_FEATURES', 'crypto', '+crypto', '', d)}"

inherit cmake

EXTRA_OECMAKE = "\
    -DCMAKE_BUILD_TYPE=Release \
    -DFETCHCONTENT_FULLY_DISCONNECTED=OFF \
    -DGGML_CPU_KLEIDIAI=ON \
    -DGGML_CPU_ARM_ARCH=${CPU_ARM_ARCH} \
"

FILES:${PN} += "\
    ${bindir}/* \
    ${libdir}/*.so \
"

FILES:${PN}-dev += "\
    ${includedir}/* \
"

# Prevent -dev from claiming bare .so files.
FILES_SOLIBSDEV = ""
INSANE_SKIP:${PN} += "buildpaths dev-so"

INHIBIT_PACKAGE_DEBUG_SPLIT = "1"
