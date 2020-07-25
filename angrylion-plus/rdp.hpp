struct RDP : Thread, Memory::IO<RDP> {
  Node::Component node;

  //rdp.cpp
  auto load(Node::Object) -> void;
  auto unload() -> void;

  auto main() -> void;
  auto step(uint clocks) -> void;
  auto power() -> void;

  //render.cpp
  auto render() -> void;

  //io.cpp
  auto readWord(u32 address) -> u32;
  auto writeWord(u32 address, u32 data) -> void;

  //serialization.cpp
  auto serialize(serializer&) -> void {}

  struct Command {
    uint24 start = 0;
    uint24 end = 0;
    uint24 current = 0;
    uint24 clock = 0;
    uint24 bufferBusy = 0;
    uint24 pipeBusy = 0;
    uint24 tmemBusy = 0;
     uint1 source = 0;  //0 = RDRAM, 1 = DMEM
     uint1 freeze = 0;
     uint1 flush = 0;
     uint1 ready = 1;
  } command;

  uint32_t status = 0;

  struct IO : Memory::IO<IO> {
    RDP& self;
    IO(RDP& self) : self(self) {}

    //io.cpp
    auto readWord(u32 address) -> u32;
    auto writeWord(u32 address, u32 data) -> void;

    struct BIST {
      uint1 check = 0;
      uint1 go = 0;
      uint1 done = 0;
      uint8 fail = 0x00;
    } bist;
    struct Test {
       uint1 enable = 0;
       uint7 address = 0;
      uint32 data = 0;
    } test;
  } io{*this};
};

extern RDP rdp;
