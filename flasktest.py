from flask import Flask
from flask import request
app = Flask(__name__)

@app.route('/')
def hello_world():
    return 'Hello, World!\r\n'

@app.route('/data', methods=['POST'])
def current():
	current = request.form['pin1']
	# assert request.method == 'POST'
	# assert request.path == '/data'
	print current
	return "done"
	
if __name__ == '__main__':
    # Bind to PORT if defined, otherwise default to 5000.
    port = int(os.environ.get('PORT', 5000))
    app.run(host='0.0.0.0', port=port)
