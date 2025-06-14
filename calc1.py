


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(348, 347)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.verticalLayout_6 = QtWidgets.QVBoxLayout(self.centralwidget)
        self.verticalLayout_6.setObjectName("verticalLayout_6")
        self.textEdit = QtWidgets.QTextEdit(self.centralwidget)
        self.textEdit.setObjectName("textEdit")
        self.verticalLayout_6.addWidget(self.textEdit)
        self.verticalLayout_5 = QtWidgets.QVBoxLayout()
        self.verticalLayout_5.setObjectName("verticalLayout_5")
        self.horizontalLayout = QtWidgets.QHBoxLayout()
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.verticalLayout_4 = QtWidgets.QVBoxLayout()
        self.verticalLayout_4.setObjectName("verticalLayout_4")
        self.pushButton_10 = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton_10.setObjectName("pushButton_10")
        self.verticalLayout_4.addWidget(self.pushButton_10)
        self.pushButton_11 = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton_11.setObjectName("pushButton_11")
        self.verticalLayout_4.addWidget(self.pushButton_11)
        self.pushButton_12 = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton_12.setObjectName("pushButton_12")
        self.verticalLayout_4.addWidget(self.pushButton_12)
        self.pushButton_16 = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton_16.setObjectName("pushButton_16")
        self.verticalLayout_4.addWidget(self.pushButton_16)
        self.pushButton_20 = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton_20.setObjectName("pushButton_20")
        self.verticalLayout_4.addWidget(self.pushButton_20)
        self.horizontalLayout.addLayout(self.verticalLayout_4)
        self.verticalLayout_2 = QtWidgets.QVBoxLayout()
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.pushButton_2 = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton_2.setObjectName("pushButton_2")
        self.verticalLayout_2.addWidget(self.pushButton_2)
        self.pushButton_4 = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton_4.setObjectName("pushButton_4")
        self.verticalLayout_2.addWidget(self.pushButton_4)
        self.pushButton_6 = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton_6.setObjectName("pushButton_6")
        self.verticalLayout_2.addWidget(self.pushButton_6)
        self.pushButton_14 = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton_14.setObjectName("pushButton_14")
        self.verticalLayout_2.addWidget(self.pushButton_14)
        self.pushButton_18 = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton_18.setObjectName("pushButton_18")
        self.verticalLayout_2.addWidget(self.pushButton_18)
        self.horizontalLayout.addLayout(self.verticalLayout_2)
        self.verticalLayout = QtWidgets.QVBoxLayout()
        self.verticalLayout.setObjectName("verticalLayout")
        self.pushButton_17 = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton_17.setObjectName("pushButton_17")
        self.verticalLayout.addWidget(self.pushButton_17)
        self.pushButton = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton.setObjectName("pushButton")
        self.verticalLayout.addWidget(self.pushButton)
        self.pushButton_13 = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton_13.setObjectName("pushButton_13")
        self.verticalLayout.addWidget(self.pushButton_13)
        self.pushButton_5 = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton_5.setObjectName("pushButton_5")
        self.verticalLayout.addWidget(self.pushButton_5)
        self.pushButton_3 = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton_3.setObjectName("pushButton_3")
        self.verticalLayout.addWidget(self.pushButton_3)
        self.horizontalLayout.addLayout(self.verticalLayout)
        self.verticalLayout_3 = QtWidgets.QVBoxLayout()
        self.verticalLayout_3.setObjectName("verticalLayout_3")
        self.pushButton_7 = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton_7.setObjectName("pushButton_7")
        self.verticalLayout_3.addWidget(self.pushButton_7)
        self.pushButton_8 = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton_8.setObjectName("pushButton_8")
        self.verticalLayout_3.addWidget(self.pushButton_8)
        self.pushButton_9 = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton_9.setObjectName("pushButton_9")
        self.verticalLayout_3.addWidget(self.pushButton_9)
        self.pushButton_15 = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton_15.setObjectName("pushButton_15")
        self.verticalLayout_3.addWidget(self.pushButton_15)
        self.pushButton_19 = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton_19.setObjectName("pushButton_19")
        self.verticalLayout_3.addWidget(self.pushButton_19)
        self.horizontalLayout.addLayout(self.verticalLayout_3)
        self.verticalLayout_5.addLayout(self.horizontalLayout)
        self.verticalLayout_6.addLayout(self.verticalLayout_5)
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 348, 21))
        self.menubar.setObjectName("menubar")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.pushButton_10.setText(_translate("MainWindow", "1"))
        self.pushButton_11.setText(_translate("MainWindow", "4"))
        self.pushButton_12.setText(_translate("MainWindow", "7"))
        self.pushButton_16.setText(_translate("MainWindow", "0"))
        self.pushButton_20.setText(_translate("MainWindow", "^"))
        self.pushButton_2.setText(_translate("MainWindow", "2"))
        self.pushButton_4.setText(_translate("MainWindow", "5"))
        self.pushButton_6.setText(_translate("MainWindow", "8"))
        self.pushButton_14.setText(_translate("MainWindow", "."))
        self.pushButton_18.setText(_translate("MainWindow", "√"))
        self.pushButton_17.setText(_translate("MainWindow", "3"))
        self.pushButton.setText(_translate("MainWindow", "6"))
        self.pushButton_13.setText(_translate("MainWindow", "9"))
        self.pushButton_5.setText(_translate("MainWindow", "="))
        self.pushButton_3.setText(_translate("MainWindow", "!"))
        self.pushButton_7.setText(_translate("MainWindow", "+"))
        self.pushButton_8.setText(_translate("MainWindow", "-"))
        self.pushButton_9.setText(_translate("MainWindow", "*"))
        self.pushButton_15.setText(_translate("MainWindow", "/"))
        self.pushButton_19.setText(_translate("MainWindow", "C"))


        
