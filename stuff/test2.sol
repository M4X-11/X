
fun uwu n{
    if ( 10 > n ) {ret 9;};
    write 2*4+2;
    write 5;
    ret 0;
}
fun yo {write 1; write 2; ret 3; write 6};

fun fact n {
    if ( 1==n ){ret 1;}
    ret 3*fact(1);
}

start:
/write uwu(3);
write fact(5);
/write yo();
return 0;
















/fun yay ret write 4+1;
/fun no ret 3;
/fun lol ret 2*no();

/fun test ret write 3 write 6;


/fun uwu n: ret if n=0 then 123 else n;

/fun bleh n {write 3; write 6; ret 9;};

/fun uh {write 8};
   
//}


/start:

/let x= 3;
/write x;
/uh();
/write 0;
/write "Hello World!";
/write bleh();
/write lol();
/return 0;


/fun yay ret 4;

/start:
/write 1+yay();
/return 0;
