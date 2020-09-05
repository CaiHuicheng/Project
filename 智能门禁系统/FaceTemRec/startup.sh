#£¡/bin/bash
sleep 20
ps -ef | grep thermometry.py | grep -v grep | awk '{print $2}' | xargs kill -9
cd /home/pi/FaceTemRec/
python3 main.py >> /home/pi/FaceTemRec/log.txt