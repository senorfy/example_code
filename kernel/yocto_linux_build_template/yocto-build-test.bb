DESCRIPTION = "author:chendening"
LICENSE = "CLOSED"

inherit module
DEPENDS = "virtual/kernel"
FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRC_URI += "file://*"

SRCREV = "${AUTOREV}"

S = "${WORKDIR}"

do_install() {
    cp ${S}/*.ko ${THISDIR}/files/ -rf
}


# 把编译文件都放到files文件夹下
# 生成的ko也在files文件夹下
