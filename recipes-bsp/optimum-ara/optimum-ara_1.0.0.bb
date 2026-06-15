SUMMARY = "Optimum integration for Kinara Ara-2"
DESCRIPTION = "Hugging Face Optimum extension for running supported models on the Kinara Ara-2 NPU runtime."
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${WORKDIR}/optimum-license/LICENSE.txt;md5=175792518e4ac015ab6696d16c4f607e"

WHEEL = "optimum_ara-${PV}-py3-none-any.whl"

OPTIMUM_ARA_SRC ?= "https://eiq.nxp.com/repository/optimum-ara"
SRC_URI = "${OPTIMUM_ARA_SRC}/${WHEEL};name=wheel;unpack=0"
SRC_URI[wheel.sha256sum] = "5dbf2b27041edbb3be2062b96b2dbef536e094d4970efc3cf0b8ee3701aecbae"

S = "${WORKDIR}"

# extract just the license so LIC_FILES_CHKSUM can verify it.
do_unpack[depends] += "unzip-native:do_populate_sysroot"
do_unpack:append() {
    import subprocess
    whl = d.expand("${WORKDIR}/${WHEEL}")
    dest = d.expand("${WORKDIR}/optimum-license")
    member = d.expand("optimum_ara-${PV}.dist-info/licenses/LICENSE.txt")
    bb.utils.mkdirhier(dest)
    subprocess.check_call(["unzip", "-j", "-o", whl, member, "-d", dest])
}

do_install() {
    install -d ${D}${datadir}/python-wheels
    install -m 0644 ${WORKDIR}/${WHEEL} ${D}${datadir}/python-wheels/
}

RDEPENDS:${PN} += " \
    ara2-rt \
    ara2-rt-python \
    python3-ctypes \
    python3-json \
    python3-logging \
    python3-pip \
    python3-venv \
"

FILES:${PN} = "${datadir}/python-wheels/*.whl"
