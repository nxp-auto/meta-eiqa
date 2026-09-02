SUMMARY = "Connector - OpenAI compatible server for AI Agentic Framework."
DESCRIPTION = "REST-based server for inference on LLMs running on NXP devices with Kinara NPU"
LICENSE = "Proprietary"
LIC_FILES_CHKSUM = "file://LICENSE;md5=d8ff2d641cc45adce1b1882be29d1e35"

SRC_URI = " \
    ${EIQ_AAF_CONNECTOR_SRC};branch=${SRCBRANCH} \
    file://0001-AIMLPRD-495-Support-for-Auto-BSP.patch \
"

EIQ_AAF_CONNECTOR_SRC ?= "git://github.com/nxp-imx-support/eiq-aaf-connector.git;protocol=https"
SRCBRANCH = "lf-6.18.37_2.1.0"
SRCREV = "53122a29f5d3628c3b18f7c87712141bd9758b94"

S = "${WORKDIR}/git"

inherit python_setuptools_build_meta

do_install() {

    install -d ${D}${bindir}
    install -m 0755 ${S}/aaf-connector ${D}${bindir}

    install -d ${D}${datadir}/python-wheels
    install -m 0644 ${PEP517_WHEEL_PATH}/*.whl ${D}${datadir}/python-wheels

    install -d ${D}${datadir}/eiq/aaf-connector
    install -m 0755 ${S}/install.sh ${D}${datadir}/eiq/aaf-connector/install.sh
    install -m 0644 ${S}/config/server_config.json ${D}${datadir}/eiq/aaf-connector
}

FILES:${PN} += " \
    ${datadir}/python-wheels \
    ${datadir}/eiq/aaf-connector \
"

RDEPENDS:${PN} += " \
    optimum-ara \
    python3-modules \
    python3-misc \
    python3-pip \
    python3-venv \
    curl \
    bash \
    coreutils \
"
