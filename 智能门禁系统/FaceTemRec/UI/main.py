import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QFileDialog,QVBoxLayout,QWidget

import sys
from PyQt5 import QtWidgets
from PyQt5.QtWidgets import QApplication, QMainWindow
from mainWindow import Ui_Form

if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    widget = QtWidgets.QWidget()
    new = Ui_Form()
    new.setupUi(widget)
    widget.show()
    sys.exit(app.exec())
