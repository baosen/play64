#pragma once
#define RD(name) u32 r_##name()
#define WR(name) void w_##name(const u32 val)
#define WRANY(name) void w_##name()
