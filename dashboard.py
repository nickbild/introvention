import dash
import dash_bootstrap_components as dbc
from dash.dependencies import Input, Output
from dash import dcc
from dash import html
import flask
import time
import os
import sqlite3


external_stylesheets = [dbc.themes.MORPH]
connection = sqlite3.connect("introvention.db")
server = flask.Flask('app')
app = dash.Dash('app', server=server, external_stylesheets=external_stylesheets)
app.scripts.config.serve_locally = False
dcc._js_dist[0]['external_url'] = 'https://cdn.plot.ly/plotly-basic-latest.min.js'


# Retrieve and process data from SQLite3 DB.
cursor = connection.cursor()
dates = cursor.execute("SELECT date FROM events").fetchall()
counts = cursor.execute("SELECT count FROM events").fetchall()

x = []
for date in dates:
    x.append(date[0])

y = []
for count in counts:
    y.append(count[0])


# Display graph.
app.layout = html.Div([
    html.H1('Introvention Early Diagnosis - Jane Doe, 58 F'),
    dcc.Graph(
        id='my-graph',
        figure = {
            'data': [{
                'x': x,
                'y': y,
                'line': {
                    'width': 3,
                    'shape': 'spline'
                }
            }],
            'layout': {
                'margin': {
                    'l': 30,
                    'r': 20,
                    'b': 30,
                    't': 20
                }
            }
        }
    )
], className="container")


if __name__ == '__main__':
    app.run_server()
