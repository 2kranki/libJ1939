# Generated file - Edits will be discarded by next generation!
# ( 3/16/2021 12:59:33.000)

.DEFAULT_GOAL := all
SHELL=/bin/sh

LIBNAM=libJ1939
SYS=macos64
TEMP=/tmp
BASE_OBJ = $(TEMP)/$(LIBNAM)
SRCDIR = ./src
TEST_SRC = ./tests
INSTALL_BASE = $(HOME)/Support/lib/$(SYS)
LIB_BASE = $(HOME)/Support/lib/$(SYS)

CFLAGS += -g -Werror -I$(SRCDIR)
ifdef  NDEBUG
CFLAGS += -DNDEBUG
else   #DEBUG
CFLAGS += -D_DEBUG
endif  #NDEBUG
CFLAGS += -D__MACOS64_ENV__
CFLAGS_LIBS = 
# libCmn
LIBCMN_BASE = $(LIB_BASE)/libCmn
CFLAGS += -I$(LIBCMN_BASE)/include
CFLAGS_LIBS += -lCmn -L$(LIBCMN_BASE)
CFLAGS_TEST = -I$(TEST_SRC) $(CFLAGS_LIBS) -lcurses -lsqlite3

INSTALL_DIR = $(INSTALL_BASE)/$(LIBNAM)
LIBOBJ = $(BASE_OBJ)/$(SYS)
ifdef  NDEBUG
LIB_FILENAME=$(LIBNAM)R.a
OBJDIR = $(LIBOBJ)/o/r
else   #DEBUG
LIB_FILENAME=$(LIBNAM)D.a
OBJDIR = $(LIBOBJ)/o/d
endif  #NDEBUG
TEST_OBJ = $(OBJDIR)/obj
TEST_BIN = $(OBJDIR)/bin
LIB_PATH = $(LIBOBJ)/$(LIB_FILENAME)

.SUFFIXES:
.SUFFIXES: .asm .c .cpp .o

OBJS =

TESTS =


OBJS += $(OBJDIR)/j1939bs.o

$(OBJDIR)/j1939bs.o: $(SRCDIR)/j1939bs.c $(SRCDIR)/j1939bs.h $(SRCDIR)/j1939bs_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/j1939bs_object.o

$(OBJDIR)/j1939bs_object.o: $(SRCDIR)/j1939bs_object.c $(SRCDIR)/j1939bs.h $(SRCDIR)/j1939bs_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/j1939ca.o

$(OBJDIR)/j1939ca.o: $(SRCDIR)/j1939ca.c $(SRCDIR)/j1939ca.h $(SRCDIR)/j1939ca_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/j1939ca_object.o

$(OBJDIR)/j1939ca_object.o: $(SRCDIR)/j1939ca_object.c $(SRCDIR)/j1939ca.h $(SRCDIR)/j1939ca_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/j1939cab.o

$(OBJDIR)/j1939cab.o: $(SRCDIR)/j1939cab.c $(SRCDIR)/j1939cab.h $(SRCDIR)/j1939cab_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/j1939cab_object.o

$(OBJDIR)/j1939cab_object.o: $(SRCDIR)/j1939cab_object.c $(SRCDIR)/j1939cab.h $(SRCDIR)/j1939cab_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/j1939cam.o

$(OBJDIR)/j1939cam.o: $(SRCDIR)/j1939cam.c $(SRCDIR)/j1939cam.h $(SRCDIR)/j1939cam_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/j1939cam_object.o

$(OBJDIR)/j1939cam_object.o: $(SRCDIR)/j1939cam_object.c $(SRCDIR)/j1939cam.h $(SRCDIR)/j1939cam_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/j1939can.o

$(OBJDIR)/j1939can.o: $(SRCDIR)/j1939can.c $(SRCDIR)/j1939can.h $(SRCDIR)/j1939can_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/j1939can_object.o

$(OBJDIR)/j1939can_object.o: $(SRCDIR)/j1939can_object.c $(SRCDIR)/j1939can.h $(SRCDIR)/j1939can_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/j1939cc.o

$(OBJDIR)/j1939cc.o: $(SRCDIR)/j1939cc.c $(SRCDIR)/j1939cc.h $(SRCDIR)/j1939cc_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/j1939cc_object.o

$(OBJDIR)/j1939cc_object.o: $(SRCDIR)/j1939cc_object.c $(SRCDIR)/j1939cc.h $(SRCDIR)/j1939cc_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/j1939ccu.o

$(OBJDIR)/j1939ccu.o: $(SRCDIR)/j1939ccu.c $(SRCDIR)/j1939ccu.h $(SRCDIR)/j1939ccu_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/j1939ccu_object.o

$(OBJDIR)/j1939ccu_object.o: $(SRCDIR)/j1939ccu_object.c $(SRCDIR)/j1939ccu.h $(SRCDIR)/j1939ccu_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/j1939cu.o

$(OBJDIR)/j1939cu.o: $(SRCDIR)/j1939cu.c $(SRCDIR)/j1939cu.h $(SRCDIR)/j1939cu_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/j1939cu_object.o

$(OBJDIR)/j1939cu_object.o: $(SRCDIR)/j1939cu_object.c $(SRCDIR)/j1939cu.h $(SRCDIR)/j1939cu_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/j1939data.o

$(OBJDIR)/j1939data.o: $(SRCDIR)/j1939data.c $(SRCDIR)/j1939data.h $(SRCDIR)/j1939data_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/j1939data_object.o

$(OBJDIR)/j1939data_object.o: $(SRCDIR)/j1939data_object.c $(SRCDIR)/j1939data.h $(SRCDIR)/j1939data_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/j1939dg.o

$(OBJDIR)/j1939dg.o: $(SRCDIR)/j1939dg.c $(SRCDIR)/j1939dg.h $(SRCDIR)/j1939dg_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/j1939dg_object.o

$(OBJDIR)/j1939dg_object.o: $(SRCDIR)/j1939dg_object.c $(SRCDIR)/j1939dg.h $(SRCDIR)/j1939dg_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/j1939ecu.o

$(OBJDIR)/j1939ecu.o: $(SRCDIR)/j1939ecu.c $(SRCDIR)/j1939ecu.h $(SRCDIR)/j1939ecu_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/j1939ecu_object.o

$(OBJDIR)/j1939ecu_object.o: $(SRCDIR)/j1939ecu_object.c $(SRCDIR)/j1939ecu.h $(SRCDIR)/j1939ecu_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/j1939en.o

$(OBJDIR)/j1939en.o: $(SRCDIR)/j1939en.c $(SRCDIR)/j1939en.h $(SRCDIR)/j1939en_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/j1939en_object.o

$(OBJDIR)/j1939en_object.o: $(SRCDIR)/j1939en_object.c $(SRCDIR)/j1939en.h $(SRCDIR)/j1939en_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/j1939er.o

$(OBJDIR)/j1939er.o: $(SRCDIR)/j1939er.c $(SRCDIR)/j1939er.h $(SRCDIR)/j1939er_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/j1939er_object.o

$(OBJDIR)/j1939er_object.o: $(SRCDIR)/j1939er_object.c $(SRCDIR)/j1939er.h $(SRCDIR)/j1939er_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/j1939misc.o

$(OBJDIR)/j1939misc.o: $(SRCDIR)/j1939misc.c $(SRCDIR)/j1939misc.h $(SRCDIR)/j1939misc_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/j1939misc_object.o

$(OBJDIR)/j1939misc_object.o: $(SRCDIR)/j1939misc_object.c $(SRCDIR)/j1939misc.h $(SRCDIR)/j1939misc_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/j1939msg.o

$(OBJDIR)/j1939msg.o: $(SRCDIR)/j1939msg.c $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/j1939ss.o

$(OBJDIR)/j1939ss.o: $(SRCDIR)/j1939ss.c $(SRCDIR)/j1939ss.h $(SRCDIR)/j1939ss_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/j1939ss_object.o

$(OBJDIR)/j1939ss_object.o: $(SRCDIR)/j1939ss_object.c $(SRCDIR)/j1939ss.h $(SRCDIR)/j1939ss_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/j1939sys.o

$(OBJDIR)/j1939sys.o: $(SRCDIR)/j1939sys.c $(SRCDIR)/j1939sys.h $(SRCDIR)/j1939sys_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/j1939sys_object.o

$(OBJDIR)/j1939sys_object.o: $(SRCDIR)/j1939sys_object.c $(SRCDIR)/j1939sys.h $(SRCDIR)/j1939sys_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/j1939tc.o

$(OBJDIR)/j1939tc.o: $(SRCDIR)/j1939tc.c $(SRCDIR)/j1939tc.h $(SRCDIR)/j1939tc_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/j1939tc_object.o

$(OBJDIR)/j1939tc_object.o: $(SRCDIR)/j1939tc_object.c $(SRCDIR)/j1939tc.h $(SRCDIR)/j1939tc_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/j1939tcu.o

$(OBJDIR)/j1939tcu.o: $(SRCDIR)/j1939tcu.c $(SRCDIR)/j1939tcu.h $(SRCDIR)/j1939tcu_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/j1939tcu_object.o

$(OBJDIR)/j1939tcu_object.o: $(SRCDIR)/j1939tcu_object.c $(SRCDIR)/j1939tcu.h $(SRCDIR)/j1939tcu_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/j1939tp.o

$(OBJDIR)/j1939tp.o: $(SRCDIR)/j1939tp.c $(SRCDIR)/j1939tp.h $(SRCDIR)/j1939tp_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/j1939tp_object.o

$(OBJDIR)/j1939tp_object.o: $(SRCDIR)/j1939tp_object.c $(SRCDIR)/j1939tp.h $(SRCDIR)/j1939tp_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/truck.o

$(OBJDIR)/truck.o: $(SRCDIR)/truck.c $(SRCDIR)/truck.h $(SRCDIR)/truck_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/truck_object.o

$(OBJDIR)/truck_object.o: $(SRCDIR)/truck_object.c $(SRCDIR)/truck.h $(SRCDIR)/truck_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

TESTS += j1939bs_test

j1939bs_test: $(TEST_SRC)/j1939bs_test.c $(SRCDIR)/j1939bs.h $(SRCDIR)/j1939bs_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $(TEST_SRC)/common.c $(TEST_SRC)/common2.c $(TEST_SRC)/common3.c $(TEST_SRC)/common4.c $<
	$(TEST_BIN)/$(@F)

TESTS += j1939ca_test

j1939ca_test: $(TEST_SRC)/j1939ca_test.c $(SRCDIR)/j1939ca.h $(SRCDIR)/j1939ca_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $(TEST_SRC)/common.c $(TEST_SRC)/common2.c $(TEST_SRC)/common3.c $(TEST_SRC)/common4.c $<
	$(TEST_BIN)/$(@F)

TESTS += j1939cab_test

j1939cab_test: $(TEST_SRC)/j1939cab_test.c $(SRCDIR)/j1939cab.h $(SRCDIR)/j1939cab_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $(TEST_SRC)/common.c $(TEST_SRC)/common2.c $(TEST_SRC)/common3.c $(TEST_SRC)/common4.c $<
	$(TEST_BIN)/$(@F)

TESTS += j1939cam_test

j1939cam_test: $(TEST_SRC)/j1939cam_test.c $(SRCDIR)/j1939cam.h $(SRCDIR)/j1939cam_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $(TEST_SRC)/common.c $(TEST_SRC)/common2.c $(TEST_SRC)/common3.c $(TEST_SRC)/common4.c $<
	$(TEST_BIN)/$(@F)

TESTS += j1939can_test

j1939can_test: $(TEST_SRC)/j1939can_test.c $(SRCDIR)/j1939can.h $(SRCDIR)/j1939can_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $(TEST_SRC)/common.c $(TEST_SRC)/common2.c $(TEST_SRC)/common3.c $(TEST_SRC)/common4.c $<
	$(TEST_BIN)/$(@F)

TESTS += j1939cc_test

j1939cc_test: $(TEST_SRC)/j1939cc_test.c $(SRCDIR)/j1939cc.h $(SRCDIR)/j1939cc_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $(TEST_SRC)/common.c $(TEST_SRC)/common2.c $(TEST_SRC)/common3.c $(TEST_SRC)/common4.c $<
	$(TEST_BIN)/$(@F)

TESTS += j1939ccu_test

j1939ccu_test: $(TEST_SRC)/j1939ccu_test.c $(SRCDIR)/j1939ccu.h $(SRCDIR)/j1939ccu_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $(TEST_SRC)/common.c $(TEST_SRC)/common2.c $(TEST_SRC)/common3.c $(TEST_SRC)/common4.c $<
	$(TEST_BIN)/$(@F)

TESTS += j1939cu_test

j1939cu_test: $(TEST_SRC)/j1939cu_test.c $(SRCDIR)/j1939cu.h $(SRCDIR)/j1939cu_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $(TEST_SRC)/common.c $(TEST_SRC)/common2.c $(TEST_SRC)/common3.c $(TEST_SRC)/common4.c $<
	$(TEST_BIN)/$(@F)

TESTS += j1939data_test

j1939data_test: $(TEST_SRC)/j1939data_test.c $(SRCDIR)/j1939data.h $(SRCDIR)/j1939data_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $(TEST_SRC)/common.c $(TEST_SRC)/common2.c $(TEST_SRC)/common3.c $(TEST_SRC)/common4.c $<
	$(TEST_BIN)/$(@F)

TESTS += j1939dg_test

j1939dg_test: $(TEST_SRC)/j1939dg_test.c $(SRCDIR)/j1939dg.h $(SRCDIR)/j1939dg_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $(TEST_SRC)/common.c $(TEST_SRC)/common2.c $(TEST_SRC)/common3.c $(TEST_SRC)/common4.c $<
	$(TEST_BIN)/$(@F)

TESTS += j1939ecu_test

j1939ecu_test: $(TEST_SRC)/j1939ecu_test.c $(SRCDIR)/j1939ecu.h $(SRCDIR)/j1939ecu_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $(TEST_SRC)/common.c $(TEST_SRC)/common2.c $(TEST_SRC)/common3.c $(TEST_SRC)/common4.c $<
	$(TEST_BIN)/$(@F)

TESTS += j1939en_test

j1939en_test: $(TEST_SRC)/j1939en_test.c $(SRCDIR)/j1939en.h $(SRCDIR)/j1939en_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $(TEST_SRC)/common.c $(TEST_SRC)/common2.c $(TEST_SRC)/common3.c $(TEST_SRC)/common4.c $<
	$(TEST_BIN)/$(@F)

TESTS += j1939er_test

j1939er_test: $(TEST_SRC)/j1939er_test.c $(SRCDIR)/j1939er.h $(SRCDIR)/j1939er_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $(TEST_SRC)/common.c $(TEST_SRC)/common2.c $(TEST_SRC)/common3.c $(TEST_SRC)/common4.c $<
	$(TEST_BIN)/$(@F)

TESTS += j1939misc_test

j1939misc_test: $(TEST_SRC)/j1939misc_test.c $(SRCDIR)/j1939misc.h $(SRCDIR)/j1939misc_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $(TEST_SRC)/common.c $(TEST_SRC)/common2.c $(TEST_SRC)/common3.c $(TEST_SRC)/common4.c $<
	$(TEST_BIN)/$(@F)

TESTS += j1939ss_test

j1939ss_test: $(TEST_SRC)/j1939ss_test.c $(SRCDIR)/j1939ss.h $(SRCDIR)/j1939ss_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $(TEST_SRC)/common.c $(TEST_SRC)/common2.c $(TEST_SRC)/common3.c $(TEST_SRC)/common4.c $<
	$(TEST_BIN)/$(@F)

TESTS += j1939sys_test

j1939sys_test: $(TEST_SRC)/j1939sys_test.c $(SRCDIR)/j1939sys.h $(SRCDIR)/j1939sys_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $(TEST_SRC)/common.c $(TEST_SRC)/common2.c $(TEST_SRC)/common3.c $(TEST_SRC)/common4.c $<
	$(TEST_BIN)/$(@F)

TESTS += j1939tc_test

j1939tc_test: $(TEST_SRC)/j1939tc_test.c $(SRCDIR)/j1939tc.h $(SRCDIR)/j1939tc_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $(TEST_SRC)/common.c $(TEST_SRC)/common2.c $(TEST_SRC)/common3.c $(TEST_SRC)/common4.c $<
	$(TEST_BIN)/$(@F)

TESTS += j1939tcu_test

j1939tcu_test: $(TEST_SRC)/j1939tcu_test.c $(SRCDIR)/j1939tcu.h $(SRCDIR)/j1939tcu_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $(TEST_SRC)/common.c $(TEST_SRC)/common2.c $(TEST_SRC)/common3.c $(TEST_SRC)/common4.c $<
	$(TEST_BIN)/$(@F)

TESTS += j1939tp_test

j1939tp_test: $(TEST_SRC)/j1939tp_test.c $(SRCDIR)/j1939tp.h $(SRCDIR)/j1939tp_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $(TEST_SRC)/common.c $(TEST_SRC)/common2.c $(TEST_SRC)/common3.c $(TEST_SRC)/common4.c $<
	$(TEST_BIN)/$(@F)

TESTS += truck_test

truck_test: $(TEST_SRC)/truck_test.c $(SRCDIR)/truck.h $(SRCDIR)/truck_internal.h $(SRCDIR)/j1939_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $(TEST_SRC)/common.c $(TEST_SRC)/common2.c $(TEST_SRC)/common3.c $(TEST_SRC)/common4.c $<
	$(TEST_BIN)/$(@F)



$(LIB_PATH):  $(OBJS)
	-cd $(LIBOBJ) ; [ -d $(LIB_FILENAME) ] && rm $(LIB_FILENAME)
	ar rc $(LIB_PATH) $(OBJS)


.PHONY: all
all:  clean create_dirs $(LIB_PATH)


.PHONY: build
build:  create_dirs $(LIB_PATH)


.PHONY: check
check: $(TESTS)


.PHONY: clean
clean:
	-cd $(TEMP) ; [ -d $(LIBNAM) ] && rm -fr $(LIBNAM)


.PHONY: create_dirs
create_dirs:
	[ ! -d $(TEST_OBJ) ] && mkdir -p $(TEST_OBJ)
	[ ! -d $(TEST_BIN) ] && mkdir -p $(TEST_BIN)


.PHONY: install
install:
	-cd $(INSTALL_BASE) ; [ -d $(LIBNAM) ] && rm -fr $(LIBNAM)
	-cd $(INSTALL_BASE) ; [ ! -d $(LIBNAM)/include ] && mkdir -p $(LIBNAM)/include/$(SYS)
	cp $(LIB_PATH) $(INSTALL_DIR)/$(LIBNAM).a
	cp src/*.h $(INSTALL_DIR)/include/
	if [ -d src/$(SYS) ]; then \
		cp src/$(SYS)/*.h $(INSTALL_DIR)/include/$(SYS)/; \
	fi


.PHONY: test
test: $(TESTS)


