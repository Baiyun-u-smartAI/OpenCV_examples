ffmpeg -re -stream_loop -1 -i "Beautiful blue 3d ball abstract background.mp4" -v 0 -vcodec libx264 -f h264 -s 850*480 -b 600k -r 25 udp://192.168.3.4:34869