from flask import Flask
from flask import render_template


app=Flask(__name__)

@app.route('/')
def home():
    return render_template('index.html')

@app.route("/recommend")
def recomend_function():
    return render_template('recommend.html')


@app.route("/analyze")
def analyze_function():
    return render_template('analyze.html')


if __name__=='__main__':
    app.run(debug=True)