#include "regs.hpp"
#include "../../../cpu/interpreter/registers/cpu.hpp"
#include <iomanip>

wxBEGIN_EVENT_TABLE(Regview, wxListView)
wxEND_EVENT_TABLE()

Regview::Regview(wxFrame *f) : wxListView(f) {
    AppendColumn("Register");
    AppendColumn("Hex", wxLIST_FORMAT_LEFT, 110);
    AppendColumn("Value (unsigned int)", wxLIST_FORMAT_LEFT, 130);
    
    // Insert names for all registers in the MIPS ISA:
    InsertItem(0, "zero (r0)");
    InsertItem(1, "at (r1)");
    InsertItem(2, "v0 (r2)");
    InsertItem(3, "v1 (r3)");
    InsertItem(4, "a0 (r4)");
    InsertItem(5, "a1 (r5)");
    InsertItem(6, "a2 (r6)");
    InsertItem(7, "a3 (r7)");
    InsertItem(8, "t0 (r8)");
    InsertItem(9, "t1 (r9)");
    InsertItem(10, "t2 (r10)");
    InsertItem(11, "t3 (r11)");
    InsertItem(12, "t4 (r12)");
    InsertItem(13, "t5 (r13)");
    InsertItem(14, "t6 (r14)");
    InsertItem(15, "t7 (r15)");
    InsertItem(16, "s0 (r16)");
    InsertItem(17, "s1 (r17)");
    InsertItem(18, "s2 (r18)");
    InsertItem(19, "s3 (r19)");
    InsertItem(20, "s4 (r20)");
    InsertItem(21, "s5 (r21)");
    InsertItem(22, "s6 (r22)");
    InsertItem(23, "s7 (r23)");
    InsertItem(24, "t8 (r24)");
    InsertItem(25, "t9 (r25)");
    InsertItem(26, "k0 (r26)");
    InsertItem(27, "k1 (r27)");
    InsertItem(28, "gp (r28)");
    InsertItem(29, "sp (r29)");
    InsertItem(30, "s8/fp (r30)");
    InsertItem(31, "ra (r31)");
    InsertItem(32, "pc");

    // Set string to output hexadecimals.
    ss << std::hex << std::setw(16);

    // Set zero register to 0.
    set(0, 0);
    set(0, 0);
    // Update registers.
    update();
}

// Set register i with value val in the view.
void Regview::set(const uint i, const s64 val) {
    ss.str("");
    ss << val;
    SetItem(i, 1, ss.str().c_str());
}

// Update the register view with the current value of the CPU registers.
void Regview::update() {
    for (auto i = 1; i < 32; i++)
        set(i, Cpu::regs[i]);
    set(32, Cpu::pc);
}
