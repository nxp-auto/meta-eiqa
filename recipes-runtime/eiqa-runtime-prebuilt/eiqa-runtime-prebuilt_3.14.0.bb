EIQA_RUNTIME_PREBUILT_TAR_PATH ?= "eIQAuto_S32N7_PRM_3.14.0_CD4_EngBuild0.tar.gz"
EIQA_RUNTIME_PREBUILT_URL ??= ""

FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

python () {
    url = d.getVar("EIQA_RUNTIME_PREBUILT_URL")
    if url:
        d.setVar("SRC_URI", url)
        return

    tar = d.getVar("EIQA_RUNTIME_PREBUILT_TAR_PATH")
    if os.path.isabs(tar):
        d.setVar("SRC_URI", "file://" + tar)
        return
    else:
        paths = (d.getVar("FILESEXTRAPATHS") or "").split(":")
        for path in paths:
            candidate = os.path.join(path, tar)
            if os.path.exists(candidate):
                d.setVar("SRC_URI", "file://" + candidate)
                return

    d.setVar("SRC_URI", "")
}

SRC_URI[md5sum] = "36d9e9b5a631ed8816b84d37bdfefc71"
SRC_URI[sha256sum] = "f1360ddf1f29fff9c644ec29ee1638221b9b8fb675339fa746ec694d75e3fd02"

require eiqa-runtime-prebuilt.inc
