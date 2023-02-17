> TODO

- test cases for `int.luxoft_WorldQuant.cpp`
- TODO why no flush function in output trace (`binary_search.cpp`)?
    
    
> commands

- query function names after instrument_functions run  
  `app=shared_ptr; while read INDENT ADDR; do echo "$INDENT" " " $(addr2line -f -C -e $app.exe $ADDR | head -1); done 
  < $app.log 2> /dev/null`