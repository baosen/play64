#define CMD(name)        void name(wxCommandEvent& e)
#define DCMDU(cls, name) void cls::name(wxCommandEvent& WXUNUSED(e))
#define CTX(name)        void name(wxContextMenuEvent& e)
#define DCTXU(cls, name) void Disassembler::name(wxContextMenuEvent& WXUNUSED(e))
