LICENSE = "Kinara-Proprietary"
LIC_FILES_CHKSUM = "file://art/LICENSE.txt;md5=609f4b4e754be5a7000f9af9a2d0971e"
NO_GENERIC_LICENSE[Kinara-Proprietary] = "art/LICENSE.txt"

ARA_RT_TAR_PATH ??= ""
ARA_RT_URL ??= ""

require ara2-rt-src.inc

SRC_URI = " \
    ${SRC_URI_ARCHIVE} \
    file://0001-dvapi-add-system-library-path-fallback.patch \
    file://proxy_config.yaml \
    file://ara2.conf \
    file://ara2-hw-init \
    file://ara2-proxy-config-sync \
    file://ara2-uiodma-bind \
    file://ara2-uiodma-bind.service \
    file://ara2-hw-init.service \
    file://ara2-proxy.service \
    file://99-ara2.rules \
    file://nnapp_config.yaml \
"

# BitBake only auto-verifies SRC_URI checksums for remote fetches; a local
# ARA_RT_TAR_PATH (file://) is not checked, so validate it manually here.
python do_fetch:append() {
    if d.getVar('ARA_RT_URL'):
        return

    ara_rt_tar_path = d.getVar('ARA_RT_TAR_PATH')
    if not ara_rt_tar_path:
        return

    if not os.path.isabs(ara_rt_tar_path):
        paths = (d.getVar("FILESEXTRAPATHS") or "").split(":")
        for path in paths:
            candidate = os.path.join(path, ara_rt_tar_path)
            if os.path.exists(candidate):
                ara_rt_tar_path = candidate
                break

    sha256_expected = d.getVarFlag('SRC_URI', 'sha256sum')
    md5_expected = d.getVarFlag('SRC_URI', 'md5sum')

    sha256_actual = bb.utils.sha256_file(ara_rt_tar_path)
    md5_actual = bb.utils.md5_file(ara_rt_tar_path)

    if sha256_actual != sha256_expected:
        bb.fatal(f"SHA256 mismatch: expected {sha256_expected}, found {sha256_actual}")
    if md5_actual != md5_expected:
        bb.fatal(f"MD5 mismatch: expected {md5_expected}, found {md5_actual}")
}

COMPATIBLE_MACHINE = "s32n79rdb|s32n79sim"

inherit bin_package systemd python3-dir

SYSTEMD_PACKAGES = "${PN}"
SYSTEMD_SERVICE:${PN} = " \
    ara2-uiodma-bind.service \
    ara2-hw-init.service \
    ara2-proxy.service \
"
SYSTEMD_AUTO_ENABLE:${PN} = "enable"

# Machine-level tunables (override in machine conf or local.conf)
ARA2_BOARD     ?= "willow"
ARA2_DDR_PLL   ?= "3"
ARA2_DDR_CFG   ?= "ddr_cfg_35.bin"

# Hardware utility lists
# Core tools (required for boot-time init, shipped in ara2-rt)
ARA2_HW_UTILS_CORE ?= "chip_info_aarch64 active_enable_aarch64 ddr_unified_config_aarch64"
# Extra tools (provisioning/debug, shipped in ara2-rt-utils)
ARA2_HW_UTILS_EXTRA ?= "program_flash_aarch64 program_pll_aarch64 ddr_mem_united_config_aarch64"

ARA_LIBEXEC = "${libexecdir}/ara2"

do_install() {
    # Proxy daemon
    install -d ${D}${ARA_LIBEXEC}/proxy/mcp0
    install -m 0755 ${S}/art/linux/aarch64/proxy/proxy_aarch64 \
                     ${D}${ARA_LIBEXEC}/proxy/proxy_aarch64
    install -m 0644 ${S}/art/linux/aarch64/proxy/mcp0/vpu0.hex \
                     ${D}${ARA_LIBEXEC}/proxy/mcp0/vpu0.hex

    # Client library
    install -d ${D}${libdir}
    install -m 0755 ${S}/art/linux/aarch64/lib/libaraclient_aarch64.so \
                     ${D}${libdir}/libaraclient_aarch64.so

    # Headers (for -dev package)
    install -d ${D}${includedir}/ara2
    install -m 0644 ${S}/art/linux/aarch64/include/dvapi.h \
                     ${D}${includedir}/ara2/dvapi.h
    install -m 0644 ${S}/art/linux/aarch64/include/dv_status_codes.h \
                     ${D}${includedir}/ara2/dv_status_codes.h

    # Static library (for -dev package)
    install -m 0644 ${S}/art/linux/aarch64/lib/libaraclient_aarch64.a \
                     ${D}${libdir}/libaraclient_aarch64.a

    # Hardware utilities (core — required for boot)
    install -d ${D}${ARA_LIBEXEC}/hw_utils
    for bin in ${ARA2_HW_UTILS_CORE}; do
        install -m 0755 ${S}/art/linux/aarch64/hw_utils/bins/${bin} \
                         ${D}${ARA_LIBEXEC}/hw_utils/${bin}
    done

    # DDR configuration binaries
    install -d ${D}${datadir}/ara2/ddr_config
    if [ -d ${S}/art/linux/aarch64/hw_utils/ddr_config ]; then
        for cfg in ${S}/art/linux/aarch64/hw_utils/ddr_config/*; do
            [ -f "${cfg}" ] || continue
            install -m 0644 "${cfg}" ${D}${datadir}/ara2/ddr_config/
        done
    fi

    # Proxy configuration
    install -d ${D}${sysconfdir}/ara2
    install -m 0644 ${WORKDIR}/proxy_config.yaml ${D}${sysconfdir}/ara2/proxy_config.yaml

    # Patch proxy_config.yaml with machine-level tunables
    sed -i \
        -e 's|boardname:.*|boardname: "${ARA2_BOARD}"|' \
        -e 's|cfg_bin:.*|cfg_bin: ${datadir}/ara2/ddr_config/${ARA2_DDR_CFG}|' \
        ${D}${sysconfdir}/ara2/proxy_config.yaml

    # Default environment file
    install -d ${D}${sysconfdir}/default
    install -m 0644 ${WORKDIR}/ara2.conf ${D}${sysconfdir}/default/ara2

    # Patch env file with machine tunables
    sed -i \
        -e 's|^ARA2_BOARD=.*|ARA2_BOARD=${ARA2_BOARD}|' \
        -e 's|^ARA2_DDR_PLL=.*|ARA2_DDR_PLL=${ARA2_DDR_PLL}|' \
        -e 's|^ARA2_DDR_CFG=.*|ARA2_DDR_CFG=${datadir}/ara2/ddr_config/${ARA2_DDR_CFG}|' \
        ${D}${sysconfdir}/default/ara2

    # Integration scripts
    install -d ${D}${bindir}
    install -m 0755 ${WORKDIR}/ara2-hw-init           ${D}${bindir}/ara2-hw-init
    install -m 0755 ${WORKDIR}/ara2-proxy-config-sync ${D}${bindir}/ara2-proxy-config-sync
    install -m 0755 ${WORKDIR}/ara2-uiodma-bind       ${D}${bindir}/ara2-uiodma-bind

    # systemd units
    install -d ${D}${systemd_system_unitdir}
    install -m 0644 ${WORKDIR}/ara2-uiodma-bind.service ${D}${systemd_system_unitdir}/
    install -m 0644 ${WORKDIR}/ara2-hw-init.service     ${D}${systemd_system_unitdir}/
    install -m 0644 ${WORKDIR}/ara2-proxy.service       ${D}${systemd_system_unitdir}/

    # udev rule
    install -d ${D}${sysconfdir}/udev/rules.d
    install -m 0644 ${WORKDIR}/99-ara2.rules ${D}${sysconfdir}/udev/rules.d/

    # Utilities subpackage (provisioning/debug tools)
    install -d ${D}${ARA_LIBEXEC}/hw_utils/boot_img
    for bin in ${ARA2_HW_UTILS_EXTRA}; do
        if [ -f ${S}/art/linux/aarch64/hw_utils/bins/${bin} ]; then
            install -m 0755 ${S}/art/linux/aarch64/hw_utils/bins/${bin} \
                             ${D}${ARA_LIBEXEC}/hw_utils/${bin}
        fi
    done
    if [ -d ${S}/art/linux/aarch64/hw_utils/boot_img ]; then
        cp -R ${S}/art/linux/aarch64/hw_utils/boot_img/* ${D}${ARA_LIBEXEC}/hw_utils/boot_img/
    fi

    # nnapp subpackage
    if [ -f ${S}/art/linux/aarch64/nnapp/nnapp_aarch64 ]; then
        install -d ${D}${bindir}
        install -m 0755 ${S}/art/linux/aarch64/nnapp/nnapp_aarch64 \
                         ${D}${bindir}/nnapp
    fi
    install -d ${D}${sysconfdir}/ara2
    install -m 0644 ${WORKDIR}/nnapp_config.yaml ${D}${sysconfdir}/ara2/nnapp_config.yaml

    # Python binding (for -python subpackage)
    if [ -f ${S}/art/linux/aarch64/include/dvapi.py ]; then
        install -d ${D}${PYTHON_SITEPACKAGES_DIR}
        install -m 0644 ${S}/art/linux/aarch64/include/dvapi.py \
                         ${D}${PYTHON_SITEPACKAGES_DIR}/dvapi.py
    fi
}

# Package split.
PACKAGES =+ " \
    ${PN}-utils \
    ${PN}-nnapp \
    ${PN}-python \
"

FILES:${PN} = " \
    ${ARA_LIBEXEC}/proxy \
    ${libdir}/libaraclient_aarch64.so \
    ${ARA_LIBEXEC}/hw_utils/chip_info_aarch64 \
    ${ARA_LIBEXEC}/hw_utils/active_enable_aarch64 \
    ${ARA_LIBEXEC}/hw_utils/ddr_unified_config_aarch64 \
    ${datadir}/ara2/ddr_config \
    ${sysconfdir}/ara2 \
    ${sysconfdir}/default/ara2 \
    ${sysconfdir}/udev/rules.d/99-ara2.rules \
    ${bindir}/ara2-hw-init \
    ${bindir}/ara2-proxy-config-sync \
    ${bindir}/ara2-uiodma-bind \
    ${systemd_system_unitdir}/ara2-uiodma-bind.service \
    ${systemd_system_unitdir}/ara2-hw-init.service \
    ${systemd_system_unitdir}/ara2-proxy.service \
"

FILES:${PN}-dev = " \
    ${includedir}/ara2 \
    ${libdir}/libaraclient_aarch64.a \
"

FILES:${PN}-utils = " \
    ${ARA_LIBEXEC}/hw_utils/program_flash_aarch64 \
    ${ARA_LIBEXEC}/hw_utils/program_pll_aarch64 \
    ${ARA_LIBEXEC}/hw_utils/ddr_mem_united_config_aarch64 \
    ${ARA_LIBEXEC}/hw_utils/boot_img \
"

FILES:${PN}-nnapp = " \
    ${bindir}/nnapp \
    ${sysconfdir}/ara2/nnapp_config.yaml \
"

FILES:${PN}-python = " \
    ${PYTHON_SITEPACKAGES_DIR}/dvapi.py \
"

# Configuration files can be edited by users.
CONFFILES:${PN} = " \
    ${sysconfdir}/ara2/proxy_config.yaml \
    ${sysconfdir}/default/ara2 \
"

CONFFILES:${PN}-nnapp = " \
    ${sysconfdir}/ara2/nnapp_config.yaml \
"

# Runtime dependencies.
RDEPENDS:${PN} += " \
    uiodma \
    libusb1 \
    dbus-lib \
    libstdc++ \
"

RDEPENDS:${PN}-python = " \
    ${PN} \
    python3-ctypes \
"

RDEPENDS:${PN}-nnapp = " \
    ${PN} \
"

RDEPENDS:${PN}-utils = " \
    libusb1 \
    libstdc++ \
"

#  QA overrides for vendor prebuilt binaries
INSANE_SKIP:${PN}       += "already-stripped ldflags"
INSANE_SKIP:${PN}-utils += "already-stripped ldflags"
INSANE_SKIP:${PN}-nnapp += "already-stripped ldflags"
