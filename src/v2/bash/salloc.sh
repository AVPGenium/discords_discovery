#salloc -N 1 -p comm -C mic_online -t 20-0:00:00
salloc --partition=knl -C cache --time=360 --nodes=1