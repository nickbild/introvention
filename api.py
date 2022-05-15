########
# Nick Bild
# nick.bild@gmail.com
#
# Starting the server:
# python3 api.py
#
# Accessing an endpoint:
# curl http://[SERVER_IP]:5000/[ENDPOINT_NAME]
########

from flask import Flask, request
from datetime import datetime
from contextlib import closing
import sqlite3


app = Flask(__name__)


@app.route("/anomaly")
def record_open():
    count = request.args.get('count')
    now = str(datetime.now())
    
    with closing(sqlite3.connect("introvention.db")) as connection:
        with closing(connection.cursor()) as cursor:
            cursor.execute("INSERT INTO events (patient_id, date, count) VALUES (1, '{0}', '{1}')".format(now, count))
            connection.commit()

    return "OK"


if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0')
