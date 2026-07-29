# Source resolution for ara2-rt.
FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

# Resolve the archive location at parse time. Runs for every build that parses the
# layer, so it must never abort; falls back to an empty URI when no path/URL is set.
python () {
    url = d.getVar("ARA_RT_URL")
    if url:
        d.setVar("SRC_URI_ARCHIVE", url)
        return

    tar = d.getVar("ARA_RT_TAR_PATH")
    if tar:
        if os.path.isabs(tar):
            d.setVar("SRC_URI_ARCHIVE", "file://" + tar)
            return
        else:
            paths = (d.getVar("FILESEXTRAPATHS") or "").split(":")
            for path in paths:
                candidate = os.path.join(path, tar)
                if os.path.exists(candidate):
                    d.setVar("SRC_URI_ARCHIVE", "file://" + candidate)
                    return

    d.setVar("SRC_URI_ARCHIVE", "")
}