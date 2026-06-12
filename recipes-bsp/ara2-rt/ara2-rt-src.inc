# Source resolution for ara2-rt.
FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

python () {
    url = d.getVar("ARA_RT_URL")
    if url:
        d.setVar("SRC_URI_ARCHIVE", url)
        return

    tar = d.getVar("ARA_RT_TAR_PATH")
    if not tar:
        bb.fatal("ara-rt: set ARA_RT_TAR_PATH or ARA_RT_URL to the Ara-2 runtime archive")

    import os
    if os.path.isabs(tar):
        d.setVar("SRC_URI_ARCHIVE", "file://" + tar)
        return

    paths = (d.getVar("FILESEXTRAPATHS") or "").split(":")
    for path in paths:
        candidate = os.path.join(path, tar)
        if os.path.exists(candidate):
            d.setVar("SRC_URI_ARCHIVE", "file://" + candidate)
            return

    bb.fatal("ara-rt: could not locate archive '%s' in FILESEXTRAPATHS" % tar)
}
