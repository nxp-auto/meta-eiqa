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
