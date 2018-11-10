
\ Port D is data
\ Port E + PC0-PC3 is address
\ PC4 is ~E, PC5 is ~G
\ conflicts: buttons on black board: PE3, PE4 (meh!)

: set-data-input 16 0 do imode-float 3 i io io-mode! loop ;
: set-data-output 16 0 do omode-pp 3 i io io-mode! loop ;
: set-address-low-output 16 0 do omode-pp 4 i io io-mode! 4 i io ioc! loop ;
: set-address-high-output 4 0 do omode-pp 2 i io io-mode! loop ;
: set-e-g-low omode-pp dup pc4 io! pc5 io! pc4 ios! pc5 ios! ;

: write-low-address ( address -- ) $FFFF and pe0 io-base GPIO.ODR + ! ;
: write-high-address ( address -- ) 16 rshift $000F and pc0 io-base GPIO.ODR + ! ;
: write-address dup write-low-address write-high-address ; 
: write-data ( data -- ) $FFFF and pd0 io-base GPIO.ODR + ! ;

\ for write mode and verify mode
: drop-e pc4 ioc! ; 
: raise-e pc4 ios! ; 
: pulse-e drop-e 50 us raise-e ; 
: drop-g pc5 ioc! ; 
: raise-g pc5 ios! ;

: compare? drop drop ; \ todo

: read ( address -- data ) write-address drop-e drop-g 1 us pd0 io-base GPIO.IDR + @ ;
: burn ( data address -- data ) 
	write-address
	dup \ extra copy of data
	set-data-output
	write-data
	pulse-e
;

: verify ( -- data ) 
	set-data-input
	drop-g
	read-data
	raise-g
;

: program ( data address -- data verified_data ) burn verify ;







