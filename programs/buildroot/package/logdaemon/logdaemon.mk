#############################################################
#
# logdaemon
#
#############################################################
LOGDAEMON_VERSION:=0.1
LOGDAEMON_SOURCE:=logdaemon-$(LOGDAEMON_VERSION).tar.gz
LOGDAEMON_SITE:=
LOGDAEMON_INSTALL_STAGING=NO

define LOGDAEMON_BUILD_CMDS
	$(MAKE) CC=$(TARGET_CC) LD=$(TARGET_LD) -C $(@D) all
endef

define LOGDAEMON_INSTALL_TARGET_CMDS
	cp -dpf $(@D)/target/logdaemon $(TARGET_DIR)/usr/bin
	cp -dpf $(@D)/target/S99logdaemon $(TARGET_DIR)/etc/init.d
endef

$(eval $(call GENTARGETS,package,logdaemon))