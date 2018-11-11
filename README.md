Flash black board, with base.fs in ROM

Basically working, in that can read/write/verify EPROMS
Not optimized, may only work when run from RAM
esp timing with pulse-e is sketchy -- suboptimal programming + workaround
rest is probably OK

program works until it can verify -- this will endless loop when a chip is pre-programmed or otherwise fails to write.  should probably have an attempt count and exit gracefully.

need to tie in hook to programming over serial
could do: send word + "program" and wait for ok 
would be slow.  maybe I don't care.



