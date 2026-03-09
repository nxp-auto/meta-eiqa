SUMMARY = "The firmware and library for Neutron NPU"
DESCRIPTION = "The firmware and library for Neutron NPU"

LICENSE = "LA_OPT_NXP_Software_License"
LIC_FILES_CHKSUM = "file://${EIQAUTO_LICENSE};md5=8b13b71da2ba9684156478a0800d536a"

python do_display_banner() {
    bb.plain("************************");
    bb.plain("*  neutron-sdk recipe  *");
    bb.plain("************************");
}

addtask display_banner before do_build

NEUTRON_TARGET = ""
NEUTRON_TARGET:s32n79sim = "s32n79"
NEUTRON_TARGET:s32n79rdb = "s32n79"

NEUTRON_CORE = ""
NEUTRON_CORE:s32n79sim = "ca78"
NEUTRON_CORE:s32n79rdb = "ca78"

DEPENDS:append = "${@' eiqa-runtime-prebuilt' if d.getVar('EIQA_PROVIDER') == '1' else ''}"

do_fetch[depends] += "unzip-native:do_populate_sysroot"

python do_fetch:append() {
    if d.getVar('NEUTRON_SDK_URL') or d.getVar('EIQA_PROVIDER') == '1':
        return

    neutron_sdk_archive_path = d.getVar('NEUTRON_SDK_ARCHIVE_PATH')
    if not os.path.isabs(neutron_sdk_archive_path):
        paths = (d.getVar("FILESEXTRAPATHS") or "").split(":")
        for path in paths:
            candidate = os.path.join(path, neutron_sdk_archive_path)
            if os.path.exists(candidate):
                neutron_sdk_archive_path = candidate
                break

    sha256_expected = d.getVarFlag('SRC_URI', 'sha256sum')
    md5_expected = d.getVarFlag('SRC_URI', 'md5sum')

    sha256_actual = bb.utils.sha256_file(neutron_sdk_archive_path)
    md5_actual = bb.utils.md5_file(neutron_sdk_archive_path)

    if sha256_actual != sha256_expected:
        bb.fatal(f"SHA256 mismatch: expected {sha256_expected}, found {sha256_actual}")
    if md5_actual != md5_expected:
        bb.fatal(f"MD5 mismatch: expected {md5_expected}, found {md5_actual}")
}

do_install () {
    # Install firmware
    install -d ${D}${nonarch_base_libdir}/firmware
    install -m 0644 ${NEUTRON_SRC}/target/${NEUTRON_TARGET}/${NEUTRON_TARGET}/NeutronFirmware.elf ${D}${nonarch_base_libdir}/firmware/

    # Install header files
    install -d ${D}${includedir}/neutron
    cp ${NEUTRON_SRC}/target/${NEUTRON_TARGET}/common/include/* ${D}${includedir}/neutron
    cp ${NEUTRON_SRC}/target/${NEUTRON_TARGET}/driver/include/* ${D}${includedir}/neutron

    # Install .so libraries
    install -d ${D}${libdir}
    install -m 0755 ${NEUTRON_SRC}/target/${NEUTRON_TARGET}/${NEUTRON_TARGET}/${NEUTRON_CORE}/*.so* ${D}${libdir} 2>/dev/null || true

    # Install .a libraries
    install -d ${D}${libdir}
    install -m 0755 ${NEUTRON_SRC}/target/${NEUTRON_TARGET}/${NEUTRON_TARGET}/${NEUTRON_CORE}/*.a* ${D}${libdir} 2>/dev/null || true
}

PACKAGES =+ "${PN}-firmware"

FILES:${PN}-firmware = "${nonarch_base_libdir}/firmware/NeutronFirmware.elf"

RDEPENDS:${PN} += "${PN}-firmware"

# The packaged binaries have been stripped of debug info, so disable operations accordingly.
INHIBIT_PACKAGE_DEBUG_SPLIT = "1"
INHIBIT_PACKAGE_STRIP = "1"
INHIBIT_SYSROOT_STRIP = "1"

# Library file is unversioned
SOLIBS = ".so"
FILES_SOLIBSDEV = ""

INSANE_SKIP:${PN}-firmware += "arch"

COMPATIBLE_MACHINE = "(s32n79sim|s32n79rdb)"
