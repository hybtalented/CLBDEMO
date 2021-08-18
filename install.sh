IP_ADDRESS=192.168.0.105
rsync -avz --rsync-path="sudo rsync" --delete bin/ pi@$IP_ADDRESS:/home/pi/CLBDEMO