.name    "coeur-de-love"
.comment "memento mori"


        ld    %34341394, r16
        sti r1, %:live, %1
        ld    %1879311801, r3
        ld    %65940, r1
        ld    72, r4
        ld    71, r5
        ld    70, r6
        ld    69, r7
        ld    68, r8
        ld    67, r9
        ld    66, r10
        ld    65, r11
        ld    64, r12
        ld    63, r13
        ld    62, r14
        ld    %34341394, r15
loop:    add r1, r3, r3
val:    st r4, 465
        st r3, -4
        and    r3, %1248576, r2
        zjmp %:loop
live:    live %1
        ld    %1879311801, r3
        ld %0, r2
fork:    fork %430
        ld %62, r2
        sub r16, r2, r16
        st r16, -16
        sub r3, r2, r3
        st r3, -64
        st r3, -42
        ld %0, r2
zjmp %:loop
