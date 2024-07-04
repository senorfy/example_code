DESCRIPTION = "author:chendening"
LICENSE = "CLOSED"

inherit module
DEPENDS = "virtual/kernel"
FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRC_URI += "file://*"

SRCREV = "${AUTOREV}"

S = "${WORKDIR}"

RPROVIDES_${PN} += "debugfs-test"

do_install() {
    echo "install"
}
