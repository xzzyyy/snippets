import os
import flask
import werkzeug.utils

app = flask.Flask(__name__)
app.config["UPLOAD_FOLDER"] = "C:\\Users\\veryp\\Desktop\\run\\memorizing_app"


@app.route("/", methods=["POST"])
def upload_response():
    if flask.request.method == "POST":

        file = flask.request.files["file"]
        if file.filename == "":
            return flask.redirect(flask.request.url)

        if file.filename.endswith(".md"):
            filename = werkzeug.utils.secure_filename(file.filename)
            file.save(os.path.join(app.config["UPLOAD_FOLDER"], filename))
            return flask.redirect(flask.request.url)

    return flask.redirect(flask.request.url)


@app.route("/", methods=["GET"])
def upload_form():
    return """
        <!DOCTYPE html>
        <title>Upload new File</title>
        <h1>Upload new File</h1>
        <form method=post enctype=multipart/form-data>
            <input type=file name=file>
            <input type=submit value=Upload>
        </form>
    """
