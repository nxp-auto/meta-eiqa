SUMMARY = "Deploy eIQAuto prebuilt into Yocto build image"
DESCRIPTION = "This recipe will install prebuilt of EIQA_RUNTIME into the OE linux"

LICENSE = "LA_OPT_NXP_Software_License"
LIC_FILES_CHKSUM = "file://${EIQAUTO_LICENSE};md5=fbfd764b6215b180651ec625cbee62e5"

python do_display_banner() {
    bb.plain("**********************************");
    bb.plain("*  eiqa-runtime-prebuilt recipe  *");
    bb.plain("**********************************");
}

addtask display_banner before do_build

S = "${WORKDIR}"

EIQA_ROOT = "${prefix}/local/eiqa"
EIQA_SO = "${libdir_native}"
EIQA_AR = "${EIQA_ROOT}/lib"
EIQA_BIN = "${EIQA_ROOT}/bin"
EIQA_INCLUDE = "${EIQA_ROOT}/include"
EIQA_CMAKE = "${EIQA_ROOT}/cmake"

python do_fetch:append() {
    if d.getVar('EIQA_RUNTIME_PREBUILT_URL'):
        return

    eiqa_runtime_prebuilt_tar_path = d.getVar('EIQA_RUNTIME_PREBUILT_TAR_PATH')
    if not os.path.isabs(eiqa_runtime_prebuilt_tar_path):
        eiqa_runtime_prebuilt_tar_path = os.path.join(d.getVar('THISDIR'), 'files', eiqa_runtime_prebuilt_tar_path)

    sha256_expected = d.getVarFlag('SRC_URI', 'sha256sum')
    md5_expected = d.getVarFlag('SRC_URI', 'md5sum')

    sha256_actual = bb.utils.sha256_file(eiqa_runtime_prebuilt_tar_path)
    md5_actual = bb.utils.md5_file(eiqa_runtime_prebuilt_tar_path)

    if sha256_actual != sha256_expected:
        bb.fatal(f"SHA256 mismatch: expected {sha256_expected}, found {sha256_actual}")
    if md5_actual != md5_expected:
        bb.fatal(f"MD5 mismatch: expected {md5_expected}, found {md5_actual}")
}

do_install() {
    install -d ${D}/${nonarch_base_libdir}/firmware
    install -m 0755 ${S}/neutron/lib/s32n79_board_a78_linux/NeutronFirmware.elf ${D}/${nonarch_base_libdir}/firmware

    install -d ${D}${EIQA_SO}
    install -m 0755 ${S}/lib/cortex-a78/*.so* ${D}${EIQA_SO}

    install -d ${D}${EIQA_AR}
    install -m 0755 ${S}/neutron/lib/s32n79_board_a78_linux/*.a ${D}${EIQA_AR}
    install -m 0755 ${S}/eiqa_carv/lib/*.a ${D}${EIQA_AR}
    for f in ${S}/lib/cortex-a78/libeiqa*.a; do
        [ -f "$f" ] && install -m 0755 "$f" ${D}${EIQA_AR}
    done

    install -d ${D}${libdir_nativesdk}
    for f in ${S}/lib/cortex-a78/*.a; do
        basename=$(basename $f)
        case $basename in
            libeiqa*.a) ;;
            *) install -m 0755 "$f" ${D}${libdir_nativesdk} ;;
        esac
    done

    install -d ${D}${EIQA_BIN}
    cp -R ${S}/bin/a78/* ${D}${EIQA_BIN}
    for f in $(find ${S}/bin/a78 -type f); do
        case "$(file -b "$f")" in
            *ELF*executable*) [ -f "$f" ] && install -m 0755 "$f" ${D}${EIQA_BIN} ;;
        esac
    done

    install -d ${D}${EIQA_INCLUDE}
    cp -R ${S}/include/* ${D}${EIQA_INCLUDE}
    cp -R ${S}/neutron/include/* ${D}${EIQA_INCLUDE}
    cp -R ${S}/eiqa_carv/include/* ${D}${EIQA_INCLUDE}

    install -d ${D}${EIQA_CMAKE}
    cp -R ${S}/lib/cortex-a78/cmake/* ${D}${EIQA_CMAKE}
    cp -R ${S}/neutron/lib/s32n79_board_a78_linux/cmake/* ${D}${EIQA_CMAKE}
    cp -R ${S}/eiqa_carv/lib/cmake/* ${D}${EIQA_CMAKE}
}

PACKAGES += "${PN}-firmware"

FILES:${PN} += "${EIQA_SO} ${EIQA_BIN}"
FILES:${PN}-firmware = "${nonarch_base_libdir}/firmware/NeutronFirmware.elf"

FILES:${PN}-dev += "${EIQA_INCLUDE} ${EIQA_CMAKE}"
FILES:${PN}-staticdev += "${EIQA_AR}"

RDEPENDS:${PN} += "libstdc++"
RDEPENDS:${PN}-dev += "${PN}-staticdev"
BBCLASSEXTEND = "native nativesdk"

ALLOW_EMPTY:${PN} = "1"
ALLOW_EMPTY:${PN}-firmware = "1"

INHIBIT_PACKAGE_DEBUG_SPLIT = "1"
INHIBIT_PACKAGE_STRIP = "1"
INHIBIT_SYSROOT_STRIP = "1"

INSANE_SKIP:${PN} += "ldflags"
INSANE_SKIP:${PN} += "already-stripped"
INSANE_SKIP:${PN}-firmware += "arch"

FILES_SOLIBSDEV = ""
