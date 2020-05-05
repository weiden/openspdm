## @file
#  SPDM library.
#
#  Copyright (c) 2020, Intel Corporation. All rights reserved.<BR>
#
#  SPDX-License-Identifier: BSD-2-Clause-Patent
#
##

#
# Platform Macro Definition
#

include $(WORKSPACE)/GNUmakefile.Flags

#
# Build Directory Macro Definition
#
BUILD_DIR = $(WORKSPACE)/Build
BIN_DIR = $(BUILD_DIR)/$(TARGET)_$(TOOLCHAIN)/$(ARCH)

#
# Default target, which will build dependent libraries in addition to source files
#

all:
	@"$(MAKE)" $(MAKE_FLAGS) -f $(WORKSPACE)/Library/SpdmLib/SpdmCommonLib/$(MAKEFILE) ARCH=$(ARCH) TARGET=$(TARGET)
	@"$(MAKE)" $(MAKE_FLAGS) -f $(WORKSPACE)/Library/SpdmLib/SpdmRequesterLib/$(MAKEFILE) ARCH=$(ARCH) TARGET=$(TARGET)
	@"$(MAKE)" $(MAKE_FLAGS) -f $(WORKSPACE)/Library/SpdmLib/SpdmResponderLib/$(MAKEFILE) ARCH=$(ARCH) TARGET=$(TARGET)
	@"$(MAKE)" $(MAKE_FLAGS) -f $(WORKSPACE)/OsStub/BaseMemoryLib/$(MAKEFILE) ARCH=$(ARCH) TARGET=$(TARGET)
	@"$(MAKE)" $(MAKE_FLAGS) -f $(WORKSPACE)/OsStub/DebugLib/$(MAKEFILE) ARCH=$(ARCH) TARGET=$(TARGET)
	@"$(MAKE)" $(MAKE_FLAGS) -f $(WORKSPACE)/OsStub/BaseCryptLib/$(MAKEFILE) ARCH=$(ARCH) TARGET=$(TARGET)
	@"$(MAKE)" $(MAKE_FLAGS) -f $(WORKSPACE)/OsStub/OpensslLib/$(MAKEFILE) ARCH=$(ARCH) TARGET=$(TARGET)
	@"$(MAKE)" $(MAKE_FLAGS) -f $(WORKSPACE)/OsStub/MemoryAllocationLib/$(MAKEFILE) ARCH=$(ARCH) TARGET=$(TARGET)
	@"$(MAKE)" $(MAKE_FLAGS) -f $(WORKSPACE)/OsTest/SpdmRequesterTest/$(MAKEFILE) ARCH=$(ARCH) TARGET=$(TARGET)
	@"$(MAKE)" $(MAKE_FLAGS) -f $(WORKSPACE)/OsTest/SpdmResponderTest/$(MAKEFILE) ARCH=$(ARCH) TARGET=$(TARGET)
	@$(CP) $(WORKSPACE)/OsTest/TestKey/* $(BIN_DIR)

#
# clean all generated files
#
clean:
	$(RD) $(BIN_DIR)
