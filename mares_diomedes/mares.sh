./mangercentos &
sleep 3
kill -9 -$(ps x -o  "%r %c" | grep -m 1 "mangercentos" | awk '{print $1}')
