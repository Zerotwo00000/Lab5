#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_action_About_triggered();

    void on_action_Find_triggered();

    void on_action_Replace_triggered();

    void on_action_New_triggered();

    void on_action_Open_triggered();

    void on_action_Save_triggered();

    void on_action_SaveAs_triggered();

    void on_TextEdit_textChanged();

    void on_action_Undo_triggered();

    void on_action_Redo_triggered();

    void on_action_Cut_triggered();

    void on_action_Copy_triggered();

    void on_action_Paste_triggered();

    void on_TextEdit_copyAvailable(bool b);

    void on_TextEdit_redoAvailable(bool b);

    void on_TextEdit_undoAvailable(bool b);

    void on_action_SelectAll_triggered();

    void on_action_FontColor_triggered();

    void on_action_FontBackgroundColor_triggered();

    void on_action_AutoWrap_triggered();

    void on_action_Font_triggered();

    void on_action_EditorBackgroundColor_triggered();

    void on_action_ToolBar_triggered();

    void on_action_StatusBar_triggered();

    void on_action_Exit_triggered();

    void on_TextEdit_cursorPositionChanged();

    void on_action_ShowLineNo_triggered();

    void on_action_AutoSave_triggered();

private:
    Ui::MainWindow *ui;

    QLabel statusCursorLabel;
    QLabel statusLabel;

    QString filePath;
    bool textChanged;

    bool userEditConfirmed();

    QTimer *autoSaveTimer;
};
#endif // MAINWINDOW_H
