from flask import Flask
from flask import request
import time

app = Flask(__name__)


@app.route('/')
def hello_world():
    return 'Hello, World!\r\n'
# create file (csv+ datestamp. )


@app.route('/data', methods=['POST'])
def current():
	current = request.form['pin1'].strip()
	name = request.form['name'].strip()

	fp = open("somefile", "a")
	fp.write(str(time.time()) + "," + name + "," + current + "\r\n")
	fp.close()
	print current
	return "done"

if __name__ == '__main__':
    # Bind to PORT if defined, otherwise default to 5000.
    port = int(os.environ.get('PORT', 5000))
    app.run(host='0.0.0.0', port=port)
