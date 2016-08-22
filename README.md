# wificurrent

in this directory with the flasktest.py file enter:
	export FLASK_APP=flasktest.py
	flask run --host=0.0.0.0

to test the server:
	curl -v --data "pin1=323" 127.0.0.1:5000/data

to monitor the connection:
        tcpdump -i eth0 -A -n -tt -v tcp port 5000
