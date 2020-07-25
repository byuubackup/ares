#include <n64/n64.hpp>

#include "common.h"
#include "msg.h"
#include "gl_core_3_3.h"
#include "n64video.h"
#include "parallel.h"
#include "screen.h"
#include "vdac.h"

#include "msg.c"
#include "gl_core_3_3.c"
#include "n64video.c"
#include "parallel.cpp"
#include "vdac.c"
#include "gl.cpp"

namespace ares::Nintendo64 {

RDP rdp;
#include "render.cpp"
#include "io.cpp"

auto RDP::load(Node::Object parent) -> void {
  node = parent->append<Node::Component>("RDP");

  n64video_config config;
  n64video_config_init(&config);
  config.gfx.rdram = rdram.ram.data;
  config.gfx.rdram_size = rdram.ram.size;
  config.gfx.dmem = rsp.dmem.data;
  config.gfx.vi_reg = nullptr;  //todo
  config.gfx.dp_reg = nullptr;  //todo
  config.gfx.mi_intr_reg = nullptr;  //todo
  config.gfx.mi_intr_cb = nullptr;  //todo
  config.vi.widescreen = false;
  config.vi.hide_overscan = false;
  config.vi.vsync = false;
  config.vi.exclusive = false;
  config.parallel = false;
  config.num_workers = 1;
  n64video_init(&config);
}

auto RDP::unload() -> void {
  node = {};
}

auto RDP::main() -> void {
  step(93'750'000);
}

auto RDP::step(uint clocks) -> void {
  clock += clocks;
}

auto RDP::power() -> void {
  Thread::reset();
  command = {};
  io.bist = {};
  io.test = {};
}

}
