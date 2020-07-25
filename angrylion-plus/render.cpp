auto RDP::render() -> void {
  auto& memory = !command.source ? rdram.ram : rsp.dmem;

  auto fetch = [&]() -> u64 {
    u64 op = memory.readDoubleUnaligned(command.current);
    command.current += 8;
    return op;
  };

  auto fetchEdge = [&](u64 op) {
    op = fetch();
    op = fetch();
    op = fetch();
  };

  auto fetchShade = [&](u64 op) {
    op = fetch();
    op = fetch();
    op = fetch();
    op = fetch();
    op = fetch();
    op = fetch();
    op = fetch();
    op = fetch();
  };

  auto fetchTexture = [&](u64 op) {
    op = fetch();
    op = fetch();
    op = fetch();
    op = fetch();
    op = fetch();
    op = fetch();
    op = fetch();
    op = fetch();
  };

  auto fetchZBuffer = [&](u64 op) {
    op = fetch();
    op = fetch();
  };

  auto fetchRectangle = [&](u64 op) {
    op = fetch();
  };

  while(command.current < command.end) {
    u64 op = fetch();

    switch(op >> 56 & 0x3f) {

    case 0x00: {
//      noOperation();
    } break;

    case 0x01:
    case 0x02:
    case 0x03:
    case 0x04:
    case 0x05:
    case 0x06:
    case 0x07: {
//      invalidOperation();
    } break;

    case 0x08: {
      fetchEdge(op);
//      unshadedTriangle();
    } break;

    case 0x09: {
      fetchEdge(op);
      fetchZBuffer(op);
//      unshadedZbufferTriangle();
    } break;

    case 0x0a: {
      fetchEdge(op);
      fetchTexture(op);
//      textureTriangle();
    } break;

    case 0x0b: {
      fetchEdge(op);
      fetchTexture(op);
      fetchZBuffer(op);
//      textureZbufferTriangle();
    } break;

    case 0x0c: {
      fetchEdge(op);
      fetchShade(op);
//      shadedTriangle();
    } break;

    case 0x0d: {
      fetchEdge(op);
      fetchShade(op);
      fetchZBuffer(op);
//      shadedZbufferTriangle();
    } break;

    case 0x0e: {
      fetchEdge(op);
      fetchShade(op);
      fetchTexture(op);
//      shadedTextureTriangle();
    } break;

    case 0x0f: {
      fetchEdge(op);
      fetchShade(op);
      fetchTexture(op);
      fetchZBuffer(op);
//      shadedTextureZbufferTriangle();
    } break;

    case 0x10:
    case 0x11:
    case 0x12:
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1a:
    case 0x1b:
    case 0x1c:
    case 0x1d:
    case 0x1e:
    case 0x1f:
    case 0x20:
    case 0x21:
    case 0x22:
    case 0x23: {
//      invalidOperation();
    } break;

    case 0x24: {
      fetchRectangle(op);
//      textureRectangle();
    } break;

    case 0x25: {
      fetchRectangle(op);
//      textureRectangleFlip();
    } break;

    case 0x26: {
//      syncLoad();
    } break;

    case 0x27: {
//      syncPipe();
    } break;

    case 0x28: {
//      syncTile();
    } break;

    case 0x29: {
      mi.raise(MI::IRQ::DP);
//      syncFull();
    } break;

    case 0x2a: {
//      setKeyGB();
    } break;

    case 0x2b: {
//      setKeyR();
    } break;

    case 0x2c: {
//      setConvert();
    } break;

    case 0x2d: {
//      setScissor();
    } break;

    case 0x2e: {
//      setPrimitiveDepth();
    } break;

    case 0x2f: {
//      setOtherModes();
    } break;

    case 0x30: {
//      loadTLUT();
    } break;

    case 0x31: {
//      invalidOperation();
    } break;

    case 0x32: {
//      setTileSize();
    } break;

    case 0x33: {
//      loadBlock();
    } break;

    case 0x34: {
//      loadTile();
    } break;

    case 0x35: {
//      setTile();
    } break;

    case 0x36: {
//      fillRectangle();
    } break;

    case 0x37: {
//      setFillColor();
    } break;

    case 0x38: {
//      setFogColor();
    } break;

    case 0x39: {
//      setBlendColor();
    } break;

    case 0x3a: {
//      setPrimitiveColor();
    } break;

    case 0x3b: {
//      setEnvironmentColor();
    } break;

    case 0x3c: {
//      setCombineMode();
    } break;

    case 0x3d: {
//      setTextureImage();
    } break;

    case 0x3e: {
//      setMaskImage();
    } break;

    case 0x3f: {
//      setColorImage();
    } break;

    }
  }
}
