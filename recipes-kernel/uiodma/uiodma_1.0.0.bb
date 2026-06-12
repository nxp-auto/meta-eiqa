SUMMARY = "Linux kernel driver providing userspace I/O (UIO) access to DMA-capable memory regions."
DESCRIPTION = "Builds the uiodma kernel module for the ARA SDK against the custom Linux kernel"
LICENSE = "GPL-2.0-only"
LIC_FILES_CHKSUM = "file://../LICENSE.txt;md5=d760609e3a6f440f8b6f5f689a1c5f0b"

SRC_URI = "${UIODMA_SRC};branch=${SRCBRANCH}"
UIODMA_SRC ?= "git://github.com/nxp-imx-support/uiodma-driver.git;protocol=https"
SRCBRANCH = "lf-6.18.20_2.0.0"

SRCREV = "ba17c6a82dd98d74abc434291059c5d27a96ea96"

S = "${WORKDIR}/git/uiodma_cache_management"

inherit module

EXTRA_OEMAKE += "KERNEL_SRC=${STAGING_KERNEL_DIR}"

do_install:append() {
    # Install to standard kernel module location
    install -d ${D}${nonarch_base_libdir}/modules/${KERNEL_VERSION}/extra
    install -m 0644 ${B}/uiodma.ko ${D}${nonarch_base_libdir}/modules/${KERNEL_VERSION}/extra/
}