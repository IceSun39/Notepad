#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::on_actionSave_triggered);
    connect(ui->actionSaveAs, &QAction::triggered, this, &MainWindow::on_actionSaveAs_triggered);
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::on_actionOpen_triggered);
    connect(ui->actionWhite_view, &QAction::triggered, this, &MainWindow::on_actionWhite_view_triggered);
    connect(ui->actionDark_view, &QAction::triggered, this, &MainWindow::on_actionDark_view_triggered);
    connect(ui->textEdit, &QTextEdit::textChanged, this, [=]() {
        isModified = true;
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered(){
    newFile();
}

void MainWindow::on_actionSave_triggered(){
    save();
}

void MainWindow::on_actionSaveAs_triggered(){
    saveAs();
}

void MainWindow::on_actionOpen_triggered(){
    openFile();
}


void MainWindow::on_actionWhite_view_triggered(){
    setLightTheme();
}

void MainWindow::on_actionDark_view_triggered(){
    setDarkTheme();
}

void MainWindow::save() {
    if (currentFilePath.isEmpty()) {
        saveAs(); // якщо файл ще не зберігався
    } else {
        QFile file(currentFilePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << ui->textEdit->toPlainText();
            file.close();
            isModified = false;
        } else {
            QMessageBox::warning(this, "Помилка", "Не вдалося зберегти файл.");
        }
    }
}

// Слот для "Зберегти як..."
void MainWindow::saveAs() {
    QString fileName = QFileDialog::getSaveFileName(this, "Зберегти файл як", "", "Текстові файли (*.txt);;Усі файли (*)");
    if (!fileName.isEmpty()) {
        currentFilePath = fileName; // зберігаємо шлях
        save(); // знову викликаємо save(), але вже буде шлях
    }
}

bool MainWindow::maybeSave() {
    if (!isModified)
        return true; // нічого зберігати

    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Зберегти зміни?",
        "Файл було змінено. Бажаєте зберегти зміни?",
        QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel
        );

    if (reply == QMessageBox::Yes) {
        save();
        return true;
    } else if (reply == QMessageBox::No) {
        return true;
    } else {
        return false; // Cancel — перериваємо дію
    }
}


void MainWindow::newFile() {
    if (!maybeSave())
        return; // користувач відмінив

    ui->textEdit->clear();
    currentFilePath.clear();
    isModified = false;
}

void MainWindow::openFile(){
    if (!maybeSave()) return;

    QString fileName = QFileDialog::getOpenFileName(
        this,
        "Відкрити файл",
        "",
        "Текстові файли (*.txt);;Усі файли (*)"
        );

    if (!fileName.isEmpty()) {
        loadFile(fileName);
    }

}

void MainWindow::loadFile(const QString &fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Помилка", "Не вдалося відкрити файл.");
        return;
    }

    QTextStream in(&file);
    QString text = in.readAll();
    file.close();

    ui->textEdit->setPlainText(text);
    currentFilePath = fileName;
    isModified = false;

    setWindowTitle(QFileInfo(currentFilePath).fileName() + " - Блокнот");
}


void MainWindow::setDarkTheme()
{
    qApp->setStyleSheet("");  // скидає всі стилі
}

void MainWindow::setLightTheme()
{
    qApp->setStyleSheet(R"(
    QWidget {
        background-color: #ffffff;
        color: #000000;
    }

    QTextEdit {
        background-color: #ffffff;
        color: #000000;
        border: 1px solid #ccc;
    }

    QPushButton {
        background-color: #f0f0f0;
        color: #000000;
        border: 1px solid #cccccc;
        border-radius: 6px;
    }

    QPushButton:hover {
        background-color: #e0e0e0;
        border-color: #888888;
        border-radius: 6px;
    }

    QPushButton:pressed {
        background-color: #d0d0d0;
    }

    QMenuBar {
        background-color: #f8f8f8;
        color: #000000;
    }

    QMenuBar::item:selected {
        background-color: #e0e0e0;
    }

    QMenu {
        background-color: #ffffff;
        color: #000000;
        border: 1px solid #ccc;
        border-radius: 6px;
    }

    QMenu::item:selected {
        background-color: #e0e0e0;
    }
    )");
}







