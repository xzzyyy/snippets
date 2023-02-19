import os
import PyQt6.QtWidgets


class MyWindow(PyQt6.QtWidgets.QMainWindow):
    def __init__(self):
        super().__init__()

        cw = PyQt6.QtWidgets.QWidget(self)
        self.setCentralWidget(cw)
        layout = PyQt6.QtWidgets.QHBoxLayout(cw)

        self.lbl = PyQt6.QtWidgets.QLabel(self)
        layout.addWidget(self.lbl)
        self.btn = PyQt6.QtWidgets.QPushButton("choose files...", self)
        self.btn.clicked.connect(self.clicked)
        layout.addWidget(self.btn)

    def clicked(self):
        res = PyQt6.QtWidgets.QFileDialog.getOpenFileNames(self, "choose several `.md` files...",
                                                           "c:/users/veryp/desktop/run/interviews_server",
                                                           "markdown files (*.md)")
        print(res)

        fns = [os.path.basename(full_fn) for full_fn in res[0]]
        self.lbl.setText(", ".join(fns))


app = PyQt6.QtWidgets.QApplication([])
wind = MyWindow()
wind.show()
app.exec()
