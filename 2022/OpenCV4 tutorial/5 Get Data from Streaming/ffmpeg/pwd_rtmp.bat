start rtsp-simple-server.exe
start ffmpeg -re -stream_loop -1  -i "Beautiful blue 3d ball abstract background.mp4" -c copy -f flv -s 850*480 -r 25 -y rtmp://admin:a12345678@192.168.3.4:1935/live/test