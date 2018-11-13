\ Port D is data
\ Port E + PC0-PC3 is address
\ PC4 is ~E, PC5 is ~G
\ conflicts: buttons on black board: PE3, PE4 (meh!)

: set-data-input 16 0 do imode-float 3 i io io-mode! loop ; ( D = 3)
: set-data-output 16 0 do omode-pp 3 i io io-mode! loop ;
: set-address-low-output 16 0 do omode-pp 4 i io io-mode! 4 i io ioc! loop ; ( E = 4 )
: set-address-high-output 4 0 do omode-pp 2 i io io-mode! loop ; ( C = 2 )
: set-e-g-output omode-pp dup pc4 io-mode! pc5 io-mode! pc4 ios! pc5 ios! ;
: eprom-init set-data-input set-address-low-output set-address-high-output set-e-g-output ; 

pc0 io-base GPIO.ODR + constant portC-output
: write-low-address ( address -- ) $FFFF and pe0 io-base GPIO.ODR + ! ;
: write-high-address ( address -- ) 16 rshift $000F and $FFF0 portc-output @ and or portc-output ! ;
: write-address dup write-low-address write-high-address ; 
: write-data ( data -- ) $FFFF and pd0 io-base GPIO.ODR + ! ;
: read-data ( -- data )  pd0 io-base GPIO.IDR + @ ;

\ for write mode and verify mode
: drop-e pc4 ioc! ; 
: raise-e pc4 ios! ; 
: pulse-e drop-e 29 us raise-e ; ( overhead? )
: drop-g pc5 ioc! ; 
: raise-g pc5 ios! ;

: read ( address -- data ) write-address drop-e drop-g 1 us read-data raise-e raise-g ;

: burn ( data address -- ) 
	raise-e
	raise-g
	write-address
	set-data-output
	write-data
	pulse-e
;

: verify ( -- data ) 
	set-data-input
	drop-g
	1 us
	read-data
	raise-g
;

: program ( data address --  ) begin 2dup burn verify 2 pick = until 2drop ;

: ?carriage-return dup 7 and 0= if cr then 1-foldable ;
: 4. 0 <# # # # # #> type ;

: dump ( start #words -- bytestream ) 0 hex ?do ?carriage-return dup read 4. bl emit 1+ loop decimal cr ; 

: dump-all 0 1 20 lshift dump ;

\ debugging helpers
: bits-cleared?  bit 0 do i read $ffff <> if cr ." unmatch: " i hex. ." " i read hex. then loop cr ;
: all-cleared? 20 bits-cleared? ; \ takes ~ 60 sec

: bits-zero?  bit 0 do i read 0 <> if cr ." unmatch: " i hex. ." " i read hex. then loop cr ;
: all-zero? 20 bits-zero? ; \ takes ~ 60 sec

: all pd0 io. pe0 io. pc0 io. ;

: printstack ( -- ) depth dup if   begin  dup pick .  1- dup 0= until  then drop ;
: .s 	( -- ) [char] [ emit space printstack [char] ] emit ;
: tab 9 emit ;
: prompt-stack ( -- ) begin query interpret tab .s space ." ok." cr again ;
: print.stack ['] prompt-stack hook-quit !  quit ; 

eprom-init

\ vim: set ft=forth:
