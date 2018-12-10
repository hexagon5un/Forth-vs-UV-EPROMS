## Here Be Nothing But Dragons

Hi.  This is some throwaway / quick-hack code to one-off burn an old synthesizer OS into a 27C160 UV EPROM.  I wrote about my experiences with these ancient beasties here: .  

If you've gotten here through some other path, you're probably lost.  Not that there's anything wrong with that.  Just don't expect there to be quality code or documentation here.  :)

## Set up Hackaday Forth on the black STM32F407 boards

Flash black board, with base.fs in ROM

## Progress / Notes to Self

Basically working, in that can read/write/verify EPROMS
Not optimized, may only work when run from RAM
esp timing with pulse-e is sketchy -- suboptimal programming + workaround
rest is probably OK

program works until it can verify -- this will endless loop when a chip is pre-programmed or otherwise fails to write.  should probably have an attempt count and exit gracefully.

need to tie in hook to programming over serial
could do: send word + "program" and wait for ok 
would be slow.  maybe I don't care.


## Dump ROMS

call up folie
include h if you need to 
call up folie with the -c parameter to dump output to a file
"folie -p /dev/ttyUSB0 -c dump_`now`.txt"
head -n -1 dump_2018-12-02-233500.txt | tail -n +2 > foo

dump-all
(wait 15 min)
then edit the file to keep just the hex dump
then use xxd to convert to bits if needed.

