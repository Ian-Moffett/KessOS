bits 32
global _kentry
extern main

_kentry:
    call main

post_exec:
    hlt
    jmp post_exec
