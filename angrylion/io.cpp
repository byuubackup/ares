#define DP_XBUS_DMEM_DMA          0x00000001
#define DP_FREEZE                 0x00000002
#define DP_FLUSH                  0x00000004

#define DP_CLEAR_XBUS_DMEM_DMA    0x00000001
#define DP_SET_XBUS_DMEM_DMA      0x00000002
#define DP_CLEAR_FREEZE           0x00000004
#define DP_SET_FREEZE             0x00000008
#define DP_CLEAR_FLUSH            0x00000010
#define DP_SET_FLUSH              0x00000020

static const vector<string> registerNamesSCC = {
  "DPC_START",
  "DPC_END",
  "DPC_CURRENT",
  "DPC_STATUS",
  "DPC_CLOCK",
  "DPC_BUSY",
  "DPC_PIPE_BUSY",
  "DPC_TMEM_BUSY",
};

auto RDP::readWord(u32 address) -> u32 {
  address = (address & 0xfffff) >> 2;
  uint32 data;

  if(address == 0) {
    //DPC_START
    data.bit(0,23) = command.start;
  }

  if(address == 1) {
    //DPC_END
    data.bit(0,23) = command.end;
  }

  if(address == 2) {
    //DPC_CURRENT
    data.bit(0,23) = command.current;
  }

  if(address == 3) {
    //DPC_STATUS
    data = status;
  }

  if(address == 4) {
    //DPC_CLOCK
    data.bit(0,23) = command.clock;
  }

  if(address == 5) {
    //DPC_BUSY
    data.bit(0,23) = command.bufferBusy;
  }

  if(address == 6) {
    //DPC_PIPE_BUSY
    data.bit(0,23) = command.pipeBusy;
  }

  if(data == 7) {
    //DPC_TMEM_BUSY
    data.bit(0,23) = command.tmemBusy;
  }

//print("* ", registerNamesSCC(address, "DPC_UNKNOWN"), " => ", hex(data, 8L), "\n");
  return data;
}

auto RDP::writeWord(u32 address, u32 data_) -> void {
  address = (address & 0xfffff) >> 2;
  uint32 data = data_;

  if(address == 0) {
    //DPC_START
    command.start = data.bit(0,23) & ~7;
    command.current = command.start;
  }

  if(address == 1) {
    //DPC_END
    command.end = data.bit(0,23) & ~7;
    rdp_process_list();
  }

  if(address == 2) {
    //DPC_CURRENT (read-only)
  }

  if(address == 3) {
    //DPC_STATUS
      if (data & DP_CLEAR_XBUS_DMEM_DMA)
        status &= ~DP_XBUS_DMEM_DMA;
      else if (data & DP_SET_XBUS_DMEM_DMA)
        status |= DP_XBUS_DMEM_DMA;

      if (data & DP_CLEAR_FREEZE)
        status &= ~DP_FREEZE;
//      else if (data & DP_SET_FREEZE)
//        status |= DP_FREEZE;

      if (data & DP_CLEAR_FLUSH)
        status &= ~DP_FLUSH;
      else if (data & DP_SET_FLUSH)
        status |= DP_FLUSH;
  }

  if(address == 4) {
    //DPC_CLOCK (read-only)
  }

  if(address == 5) {
    //DPC_BUSY (read-only)
  }

  if(address == 6) {
    //DPC_PIPE_BUSY (read-only)
  }

  if(address == 7) {
    //DPC_TMEM_BUSY (read-only)
  }

//print("* ", registerNamesSCC(address, "DPC_UNKNOWN"), " <= ", hex(data, 8L), "\n");
}

static const vector<string> registerNames = {
  "DPS_TBIST",
  "DPS_TEST_MODE",
  "DPS_BUFTEST_ADDR",
  "DPS_BUFTEST_DATA",
};

auto RDP::IO::readWord(u32 address) -> u32 {
  address = (address & 0xfffff) >> 2;
  uint32 data;

  if(address == 0) {
    //DPS_TBIST
    data.bit(0)    = bist.check;
    data.bit(1)    = bist.go;
    data.bit(2)    = bist.done;
    data.bit(3,10) = bist.fail;
  }

  if(address == 1) {
    //DPS_TEST_MODE
    data.bit(0) = test.enable;
  }

  if(address == 2) {
    //DPS_BUFTEST_ADDR
    data.bit(0,6) = test.address;
  }

  if(address == 3) {
    //DPS_BUFTEST_DATA
    data.bit(0,31) = test.data;
  }

//print("* ", registerNames(address, "DPS_UNKNOWN"), " => ", hex(data, 8L), "\n");
  return data;
}

auto RDP::IO::writeWord(u32 address, u32 data_) -> void {
  address = (address & 0xfffff) >> 2;
  uint32 data = data_;

  if(address == 0) {
    //DPS_TBIST
    bist.check = data.bit(0);
    bist.go    = data.bit(1);
    if(data.bit(2)) bist.done = 0;
  }

  if(address == 1) {
    //DPS_TEST_MODE
    test.enable = data.bit(0);
  }

  if(address == 2) {
    //DPS_BUFTEST_ADDR
    test.address = data.bit(0,6);
  }

  if(address == 3) {
    //DPS_BUFTEST_DATA
    test.data = data.bit(0,31);
  }

//print("* ", registerNames(address, "DPS_UNKNOWN"), " <= ", hex(data, 8L), "\n");
}
