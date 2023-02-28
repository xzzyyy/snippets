import os
import PyQt6.QtCore
import PyQt6.QtGui
import PyQt6.QtWidgets
import PyQt6.QtWebEngineWidgets


class MyWindow(PyQt6.QtWidgets.QMainWindow):

    class MyWebEngineView(PyQt6.QtWebEngineWidgets.QWebEngineView):

        def __init__(self, window):
            super().__init__()
            self.window = window
            self.menu = None

        def contextMenuEvent(self, evt):
            act_save_this = PyQt6.QtGui.QAction("Save this", self)
            act_save_this.triggered.connect(self.window.save_this)

            act_save_all = PyQt6.QtGui.QAction("Save all", self)
            act_save_all.triggered.connect(self.window.save_all)

            self.menu = self.createStandardContextMenu()
            self.menu.clear()
            self.menu.addAction(act_save_this)
            self.menu.addAction(act_save_all)

            self.menu.popup(evt.globalPos())

    def __init__(self):
        super().__init__()

        cw = PyQt6.QtWidgets.QWidget(self)
        self.setCentralWidget(cw)
        v_lay = PyQt6.QtWidgets.QVBoxLayout(cw)

        self.browser = MyWindow.MyWebEngineView(self)
        v_lay.addWidget(self.browser)
        h_lay = PyQt6.QtWidgets.QHBoxLayout()
        v_lay.addLayout(h_lay)

        self.lbl = PyQt6.QtWidgets.QLabel(self)
        h_lay.addWidget(self.lbl)
        self.btn = PyQt6.QtWidgets.QPushButton("choose files...", self)
        self.btn.clicked.connect(self.clicked)
        h_lay.addWidget(self.btn)

        self.browser.setUrl(PyQt6.QtCore.QUrl("https://en.wikipedia.org"))

    def clicked(self):
        res = PyQt6.QtWidgets.QFileDialog.getOpenFileNames(self, "choose several `.md` files...",
                                                           "c:/users/veryp/desktop/run/interviews_server",
                                                           "markdown files (*.md)")
        print(res)

        fns = [os.path.basename(full_fn) for full_fn in res[0]]
        self.lbl.setText(", ".join(fns))

    def save_this(self):
        self.lbl.setText("Save this chosen")

    def save_all(self):
        self.lbl.setText("Save all chosen")


app = PyQt6.QtWidgets.QApplication([])
wind = MyWindow()
wind.show()
app.exec()
