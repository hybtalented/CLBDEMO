IP_ADDRESS=192.168.1.21
USER_NAME=ubuntu
rsync -avz --rsync-path="sudo rsync" --delete bin/ ${USER_NAME}@$IP_ADDRESS:/home/${USER_NAME}/CLBDEMO
