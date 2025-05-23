target sim
load

# this breakpoint will trap call to uart_putchar and 
# re-route to output char in gdb
b uart_putchar
comm
silent
printf "%c", $r0
return
cont
end
