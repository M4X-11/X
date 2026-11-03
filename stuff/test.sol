
/fun yo(n){ret 4*n};

fun foo arg1 arg2 ret 4;


/{
/ret 5*arg1+arg2;
/}



/asm rax	

/write("%d",4);

start:
/write <yo:4>;
write 120*2;
write 1;

write 1+foo(); 

return 0;


