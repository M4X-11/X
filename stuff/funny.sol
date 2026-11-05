fun fact n {
    if (1==n){ret 1;}
    ret n*fact(n-1);
};

start:
write fact(5);
return 0;
