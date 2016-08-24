# wificurrent
![picture of the hardware][hardware]

in this directory with the flasktest.py file enter:

	export FLASK_APP=flasktest.py
	flask run --host=0.0.0.0

to test the server:

	curl -v --data "pin1=323" 127.0.0.1:5000/data

to monitor the connection: (replace eth0 with your interface, perhaps wlan1)

        tcpdump -i eth0 -s 512 -A -n -tt -v tcp port 5000

[hardware]: ./hardware.jpg
